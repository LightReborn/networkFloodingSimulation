#include <string>
#include <iostream>
#include "Packet.h"
#include "Router.h"

int main() {
	Router router1, router2, router3, router4, router5, router6, router7, router8;
	int * table;
	int toSendInt = 314159;
	Packet<int> toSend;
	toSend.setPayload(toSendInt);
	Settings config;
	extern int numberOfSends;

	table = new int[3];
	table[0] = 0;
	table[1] = 1;
	table[2] = 2;
	router1 = *new Router("192.168.0.1", 3, table);

	table = new int[1]{ 1 };
	router2 = *new Router("192.168.10.1", 2, table);
	
	table = new int[1]{ 1 };
	router3 = *new Router("192.168.20.1", 2, table);
	
	table = new int[2]{ 1, 3 };
	router4 = *new Router("192.168.30.1", 4, table);
	
	table = new int[1]{ 0 };
	router5 = *new Router("192.168.40.1", 1, table);
	
	table = new int[1]{ 0 };
	router6 = *new Router("192.168.50.1", 2, table);
	
	table = new int[1]{ 0 };
	router7 = *new Router("192.168.60.1", 2, table);
	
	table = new int[1]{ 0 };
	router8 = *new Router("192.168.70.1", 2, table);

	//creating the connections.
	router1.makeNewConnection(router2);
	router1.makeNewConnection(router3);
	router1.makeNewConnection(router4);

	router2.makeNewConnection(router7);

	router3.makeNewConnection(router6);

	router4.makeNewConnection(router5);
	router4.makeNewConnection(router6);
	router4.makeNewConnection(router8);

	router7.makeNewConnection(router8);


	//Declare routing mode
	if (config._routingMode == 0) std::cout << "Flood all mode engaged...\n\n";
	if (config._routingMode == 1) std::cout << "Flood all but source mode engaged...\n\n";
	if (config._routingMode == 2) std::cout << "Selectively flood mode engaged...\n\n";

	//time to start sending packets.
	router1.recieve(toSend);

	std::cout << "\nNumer of packets sent: \n" << numberOfSends << " \n\n\nPress [ENTER] to continue...";
	std::cin.sync();
	std::cin.ignore();

	return 1;
}
