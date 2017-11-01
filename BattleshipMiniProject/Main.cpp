#include<iostream>
#include<WS2tcpip.h>
#include<Winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace std;

//For testing SFML
void drawWindow() {
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	int Size = 10;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		
		sf::CircleShape shape(Size);
		shape.setFillColor(sf::Color(100, 250, 50));
		shape.setPosition(123,100);
		sf::Event event;
		
		if (Size < 400)
		Size++;
		
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// clear the window with black color
		window.clear(sf::Color::Black);

		window.draw(shape);
		// end the current frame
		window.display();
	}

}
void main()
{
	//SLET DRAWWINDOW() FOR AT KORE RESTEN AF PROGRAMMET 
	drawWindow();
	
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
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	//htons = host to network short. here we try to bind port 54000 to any address
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//tell winsock the socket is for listening
	listen(listening, SOMAXCONN); //SOMAXCONN limits the amount of outstanding connections 
	//in the sockets listen queue


	//wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Cannot connect to socket , quitting" << endl;
		return;
	}
	
	char host[NI_MAXHOST];		//client's remote name, if not available IP will be used
	char service[NI_MAXSERV];	//Service (i.e port) the client is connected on

	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		//If we can't get the client info, we display the port number it connected on.
		cout << host << "Connected on port" << service << endl; 
	}
	else
	{

		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port" <<
			ntohs(client.sin_port) << endl;
	}

	//close listening socket
	closesocket(listening);
	//while loop: accept echo message back to client
	char buf[4096];

	while (true)
	{
		memset(buf, 0, 4096);

		//wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). quitting" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected" << endl;
			break;
		}
		//Echo message back to client

		send(clientSocket, buf, bytesReceived + 1, 0);

	}
	//close socket
	closesocket(clientSocket);

	//clean up winsock
	WSACleanup();
}