// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Networking/TCPSocket.h"

#include <sys/socket.h>

TCPSocket::TCPSocket(string ipaddress, int port) : AbstractSocket(ipaddress, port, SOCK_STREAM, 6) {} //IPv4, stream (sequenced, two way, reliable datastream), and 6 is the protocol in /etc/protocols for TCP
