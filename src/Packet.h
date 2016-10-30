#pragma once

#include "string"
#include "Settings.h"

template <class T> 
class Packet{
public:
	Packet(void);
	Packet(T& payloadSrc);
	~Packet(void);

	Packet& operator=(Packet& src);

	void incHops();
	void decHops();
	void setPayload(T& src);
	void setHops(int newHops);
	void setOrigin(std::string src);

	int getHops();
	T getPayload();
	std::string getOrigin();
private:
	int hops;
	T payload;
	std::string origin;
	Settings settings;
};

template <class T>
Packet<T>::Packet(void) {
	//empty constructor
	this->hops = settings._defaultHopCount;
};

template <class T>
Packet<T>::Packet(T& payloadSrc) {
	//constructor
	this->hops = settings._defaultHopCount;
	this->payload = payloadSrc;
};

template <class T>
Packet<T>::~Packet(void) {
	//deconstructor
}//end deconstructor

template <class T>
Packet<T>& Packet<T>::operator=(Packet& src) {
	//assignment operator
	this->hops = src.hops;
	this->payload = src.payload;
	return *this;
}//end operator=

template <class T>
void Packet<T>::incHops() {
	this->hops++;
}

template <class T>
void Packet<T>::decHops() {
	this->hops--;
}

template <class T>
void Packet<T>::setOrigin(std::string src) {
	//change the origin of the packet. Can spoof or retransmit a packet.
	this->origin = src;
}//end changeOrigin

template <class T>
void Packet<T>::setPayload(T& src) {
	this->payload = src;
}//end setPayLoad

template <class T>
void Packet<T>::setHops(int newHops) {
	this->hops = newHops;
}//end setHops

template <class T>
int Packet<T>::getHops() {
	//get how many more hop this packet has left to live.
	return (this->hops);
}//end getHops

template <class T>
T Packet<T>::getPayload() {
	return (this->payload);
}//end getPaylod

template <class T>
std::string Packet<T>::getOrigin() {
	return (this->origin);
}//end getOrigin
