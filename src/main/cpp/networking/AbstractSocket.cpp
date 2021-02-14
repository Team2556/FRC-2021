// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Networking/AbstractSocket.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <Networking/SocketException.h>

#define BUFFER_SIZE 512

using std::string;

AbstractSocket::AbstractSocket(string ipaddress, int port, int socketType, int protocol) {
    fileDescriptor = socket(AF_INET, socketType, protocol);

    if (fileDescriptor < 0) {
        throw SocketException("could not create socket.");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(struct sockaddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ipaddress.c_str());

    int err = connect(fileDescriptor, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (err == -1) {
        throw SocketException("connect() failed. Is that port/address in use?");
    }
}

void AbstractSocket::writeString(string message) {
    write(fileDescriptor, message.c_str(), sizeof(message));
}

string AbstractSocket::readString() {
    char buffer[BUFFER_SIZE];
    ssize_t readLen = read(fileDescriptor, buffer, BUFFER_SIZE);
    if (readLen == -1) {
        return nullptr;
    }
    return string(buffer);
}

AbstractSocket::~AbstractSocket() {
    close(fileDescriptor);
}


