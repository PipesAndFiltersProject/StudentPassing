//
//  Networker.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "Networker.h"

namespace ohar_pipes {
	
	
	/**
	 Constructor for a networking object.
	 @param hostName The host address, either the local address used for receiving
	 data or the address of the next ProcessorNode where data is sent to. Address
	 is a numerical IP address, containing the port number. For example:
	 <ul>
	 <li>Local address for receiving data: 127.0.0.1:1234</li>
	 <li>Remote address to send data to: 130.231.99.123:3344</li>
	 </ul>
	 */
	Networker::Networker(const std::string & hostName)
	: running(false)
	{
		setHost(hostName);
	}
	
	
	/**
	 Constructor for a networking object.
	 @param hostName The host address, either the local address used for receiving
	 data or the address of the next ProcessorNode where data is sent to. Address
	 is a numerical IP address. For example:
	 <ul>
	 <li>Local address for receiving data: 127.0.0.1</li>
	 <li>Remote address to send data to: 130.231.99.123</li>
	 </ul>
	 @param portNumber The port number to listen to (when receiving) or send to (when sending).
	 */
	Networker::Networker(const std::string & hostName, int portNumber)
	: host(hostName), port(portNumber), running(false)
	{
	}
	
	Networker::~Networker() {
	}
	
	
	/**
	 Is the networker running or not (has it been start()'ed or not).
	 @return true, if the networker is running (reading or ready to send).
	 */
	bool Networker::isRunning() {
		return running;
	}
	
	/**
	 Sets the host IP address of the networking object.
	 @param hostName The address of the host (IPv4 number format, e.g. 130.231.98.123).
	 */
	void Networker::setHost(const std::string & hostName) {
		std::vector<std::string> strs;
		boost::split(strs, hostName, boost::is_any_of(":"));
		if (strs.size() > 0) {
			host = strs.at(0);
			if (strs.size() > 1) {
				port = boost::lexical_cast<int>(strs.at(1));
			}
		}
	}
	
	/**
	 Sets the port number of either the listening port or the port of the remote host
	 to send data to.
	 @param p Port number.
	 */
	void Networker::setPort(int p) {
		port = p;
	}
	
	/**
	 Gets the IP address of the host.
	 @return The IP address.
	 */
	const std::string Networker::getHost() const {
		return host;
	}
	
	/**
	 Gets the port number of the host.
	 @return The port number.
	 */
	int Networker::getPort() const {
		return port;
	}
	
	
} //namespace