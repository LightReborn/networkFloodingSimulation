#pragma once

//singleton that manages the settings of the router, and other part of the program.

class Settings {
public:
	static const int _routingMode = 2;
	/*
	*	0 : Flood every port
	*	1 : Flood everything but the source port
	*	2 : Flood on only pre-determined ports
	*/
	static const int _defaultHopCount = 6;
	static const int _defaultPortCount = 8;
};
