#pragma once

#include "string"
#include "Packet.h"
#include "Settings.h"
#include <array>

int numberOfSends = 0;

class Router {
public:
	Router(void);
	Router(std::string address);
	Router(std::string address, int numOfPorts);
	Router(std::string address, int numOfPorts, int * preferredPorts);
	//requires: numOfPorts > 0
	~Router(void);

	Router& operator = (Router& src);

	void makeNewConnection(Router &destination);
	void addConnection(Router& src);
	void recieve(Packet<int> message);
	void send(int port, Packet<int> message);
	std::string getIP();
	int * getRoutingTable();
private:
	int numberOfPorts = 0;
	int currentOpenPort = 0;
	std::string ipAddress;
	Router * connections; //array of connections meant to simulater ethernet/wireless ports
	static Settings settings;
	int * routingTable; //array meant to guide packets when being selective in transmission. Not a real routing table, just couldn't think of a better name.
};

Router::Router(void) {
} // end default constructor.

Router::Router(std::string address) {
	//default constructor
	this->ipAddress = address;
	this->numberOfPorts = settings._defaultPortCount;
	this->connections = new Router[settings._defaultPortCount];
}//end constr

Router::Router(std::string address, int numOfPorts) {
	//constructor that creates a provided number of ports.
	this->numberOfPorts = numOfPorts;
	this->ipAddress = address;
	this->connections = new Router[numOfPorts];
	this->routingTable = new int[numOfPorts];
}//end constr

Router::Router(std::string address, int numOfPorts, int * preferredPorts) {
	this->numberOfPorts = numOfPorts;
	this->ipAddress = address;
	this->connections = new Router[numOfPorts];
	this->routingTable = preferredPorts;
}

Router::~Router(void) {
	//deconstructor
}//end deconstructor

Router& Router::operator=(Router& src) {
	//assignment operator
	this->numberOfPorts = src.numberOfPorts;
	this->ipAddress = src.ipAddress;
	this->currentOpenPort = src.currentOpenPort;
	this->connections = src.connections;
	this->routingTable = src.routingTable;
	return *this;
}//end operator=

void Router::makeNewConnection(Router &destination) {
	//adds the destination to the array, then calls the destinations addConnection.
	this->connections[this->currentOpenPort] = destination;
	this->currentOpenPort++;

	//now to let the other router establish the connection.
	destination.addConnection(*this);
}//end makeNewConnection

void Router::addConnection(Router& src) {
	//Adds src to the connection array
	this->connections[this->currentOpenPort] = src;
	this->currentOpenPort++;
}//end addConnection

void Router::recieve(Packet<int> message) {
	//Is called by a different router through the Port object.

	std::cout << this->ipAddress << " recieved packet from " << message.getOrigin() << " with message\"" << message.getPayload() << "\"\n";

	//We recieved a package. What do we do with it?
	if (settings._routingMode == 0) {//flood EVERYTHING mode.
		for (int i = 0; i < numberOfPorts; i++) {
			if (connections[i].numberOfPorts != 0 && message.getHops() > 0) { //if it has no ports it can't be connected and therefore isn't instantiated.
				this->send(i, message);
			}
		}
	}
	else if (settings._routingMode == 1) {//Flood EVERYTHING (except for the sender) mode
		for (int i = 0; i < numberOfPorts; i++) {
			if ((connections[i].numberOfPorts != 0 && message.getHops() > 0) && connections[i].getIP().compare(message.getOrigin())) { //if it has no ports it can't be connected and therefore isn't instantiated.
				this->send(i, message);
			}
		}
	}
	else {//just send it to the statically chosen routes.
		for (int i = 0; i < numberOfPorts; i++) {
			for (int j = 0; j < sizeof(routingTable); j++) {
				if (i == routingTable[j] && connections[i].numberOfPorts != 0 && message.getHops() > 0) {
					this->send(i, message);
				}
			}
		}
	}
};

void Router::send(int port, Packet<int> message) {
	//This sends a message to another router by calling its recieve method through the connections array.
	//Port is the ethernet port it will be sendingthe packet along.
	numberOfSends++;
	message.setOrigin(this->ipAddress);//change the IP for retransmission. This way it can avoid having the packet flooded back to itself.
	message.decHops(); //decrements the hopcount
	connections[port].recieve(message);
}//end send

std::string Router::getIP() {
	return this->ipAddress;
}//end getIP

int * Router::getRoutingTable() {
	return this->routingTable;
}
