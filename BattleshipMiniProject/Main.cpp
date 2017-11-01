#include<iostream>
#include<WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <SFML/Window.hpp>

using namespace std;

void main()
{
	//initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2); //request version 2,2

	int wsOK = WSAStartup(ver, &wsData);

	if (wsOK = !0)
	{
		cerr << "Cannot initialize winsock, quitting" << endl;
		return;
	}


	//create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Cannot create a socket, quitting" << endl;
		return;
	}
	//bind the ip address and port to a socket

	//tell winsock the socket is for listening

	//wait for connection

	//close listening socket

	//while loop: accept echo message back to client

	//close socket

	//shutdoen winsock

}