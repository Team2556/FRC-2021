// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "AbstractServer.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <ServerException.h>

#define BUFFER_SIZE 512

using std::string;
using std::exception;

AbstractServer::AbstractServer(string ipaddress, int port, int socketType, int protocol) {
    fileDescriptor = socket(AF_INET, socketType, protocol);

    if (fileDescriptor < 0) {
        throw ServerException("could not create socket.");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(struct sockaddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ipaddress.c_str());

    int err = bind(fileDescriptor, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (err == -1) {
        throw ServerException("bind() failed. Is that port/address already in use?");
    }

    err = listen(fileDescriptor, 20);
    if (err != 0) {
        throw ServerException("listen() failed.");
    }
}

void AbstractServer::acceptWaiting() {
    int tempFd = accept(fileDescriptor, NULL, NULL);
    if (tempFd >= 0) {
        if (clientFileDescriptor != -1) { //We only need one at a time, and if there are two it's probably just been restarted improperly, so close and reopen.
            close(clientFileDescriptor);
        }
        clientFileDescriptor = tempFd;
    }
}

void AbstractServer::writeString(string message) {
    write(clientFileDescriptor, message.c_str(), sizeof(message));
}

string AbstractServer::readString() {
    char buffer[BUFFER_SIZE];
    ssize_t readLen = read(clientFileDescriptor, buffer, BUFFER_SIZE);
    if (readLen == -1) {
        return nullptr;
    }
    return string(buffer);
}

AbstractServer::~AbstractServer() {
    close(clientFileDescriptor);
}
