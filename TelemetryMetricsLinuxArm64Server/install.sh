#!/bin/bash

# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

set -eo pipefail

AMP_REMOTE_WRITE_ENDPOINT_VAR="https://aps-workspaces.ap-northeast-2.amazonaws.com/workspaces/ws-7bea2d7e-0640-45f7-8553-f1f3f33b1c80/api/v1/remote_write"
REGION_VAR="ap-northeast-2"

# If we're not root then sudo up.
if [[ "$UID" != "0" ]]; then
    sudo $0 $@
    exit $?
fi

echo "Updating dependencies..."

yum update -y

# Ensure jq is installed for JSON parsing
if ! command -v jq &> /dev/null; then
    echo "jq not found, installing..."
    yum install -y jq
fi

echo "Installing OTEL collector..."

cp /local/game/gl-otel-collector.rpm /tmp/gl-otel-collector.rpm

# Install GameLift OTEL collector.
rpm -Uvh /tmp/gl-otel-collector.rpm

echo "Configuring OTEL collector..."

# Install GameLift OTEL collector config files.
ln -s /local/game/gamelift-base.yaml /opt/aws/gl-otel-collector/etc/gamelift-base.yaml
ln -s /local/game/gamelift-ec2.yaml /opt/aws/gl-otel-collector/etc/gamelift-ec2.yaml

systemctl daemon-reload

# Parse fleetId and ComputeType from gamelift-metadata.json
# Default compute type to EC" if it wasn't found in the metadata.
FLEET_ID=$(jq -r '.fleetId' /local/gamemetadata/gamelift-metadata.json)
COMPUTE_TYPE=$(jq -r '.ComputeType // empty' /local/gamemetadata/gamelift-metadata.json)
if [ -z "$COMPUTE_TYPE" ]; then
    COMPUTE_TYPE="EC2"
fi

# Set environment variables for AWS OTel collector.
echo "AWS_PROFILE=FleetRoleCredentials" | tee -a /opt/aws/gl-otel-collector/etc/.env
echo "AWS_SHARED_CREDENTIALS_FILE=/local/credentials/credentials" | tee -a /opt/aws/gl-otel-collector/etc/.env
echo "AMP_REMOTE_WRITE_ENDPOINT=$AMP_REMOTE_WRITE_ENDPOINT_VAR" | tee -a /opt/aws/gl-otel-collector/etc/.env
echo "REGION=$REGION" | tee -a /opt/aws/gl-otel-collector/etc/.env
echo "GAMELIFT_FLEET_ID=$FLEET_ID" | tee -a /opt/aws/gl-otel-collector/etc/.env
echo "GAMELIFT_COMPUTE_TYPE=$COMPUTE_TYPE" | tee -a /opt/aws/gl-otel-collector/etc/.env

echo "Enabling OTEL collector service..."

# Enable the GameLift OTEL Collector.
systemctl enable gl-otel-collector.service

# enable bbr
modprobe tcp_bbr
sysctl -w net.core.default_qdisc=fq
sysctl -w net.ipv4.tcp_congestion_control=bbr