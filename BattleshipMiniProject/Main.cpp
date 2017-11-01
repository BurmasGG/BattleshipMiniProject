#include<iostream>
#include<WS2tcpip.h>
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

	//tell winsock the socket is for listening

	//wait for connection

	//close listening socket

	//while loop: accept echo message back to client

	//close socket

	//shutdoen winsock

}