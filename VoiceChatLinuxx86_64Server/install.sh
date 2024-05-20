#!/bin/bash
sudo yum -y install openssl11

sudo mv ./EmbeddedVoiceChatServer.service /etc/systemd/system/EmbeddedVoiceChatServer.service
sudo chmod u+x ./EmbeddedVoiceChatServer
sudo systemctl enable EmbeddedVoiceChatServer.service

