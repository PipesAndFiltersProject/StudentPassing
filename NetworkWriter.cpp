//
//  NetworkWriter.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "NetworkWriter.h"
#include "Log.h"

namespace OHARBase {
	
	/**
	 Constructor to create the writer with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName the host to send data to, including port number.
	 @param obs The observer who gets the notifications about data arrived.
	 */
	NetworkWriter::NetworkWriter(const std::string & hostName)
	: Networker(hostName), TAG("NetworkWriter")
	{
	}
	
	/**
	 Constructor to create the writer with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName The host to send data to.
	 @param portNumber The port to send data to.
	 @param obs The observer who gets the notifications about data arrived.
	 */
	NetworkWriter::NetworkWriter(const std::string & hostName, int portNumber)
	: Networker(hostName, portNumber), TAG("NetworkWriter")
	{
	}
	
	NetworkWriter::~NetworkWriter()
	{
	}
	
	
	
	/** Thread function which does all the relevant work of sending data packages.
	 First, the function sets up the networking things, and then runs in a loop, waiting
	 for data packages to arrive. When one arrives, it is notified of it, and then goes
	 through a round of a loop. There, the package is taken from the queue, packaged
	 in a data string and then sent over the network. Locks and synchronization are used
	 to make sure the queueu is handled by one thread at a time only. Function quits the loop
	 and returns when the stop() is called and the running flag is set to false.
	 @todo Reimplement using std lib socket implementation.
	 */
	void NetworkWriter::threadFunc() {
		if (host.length() > 0 && port > 0) {
			// Setup the datagram socket to send data to the next node
			int sockd;
			struct sockaddr_in my_addr, srv_addr;
			
			/* create a socket */
			Log::getInstance().entry(TAG, "Creating a socket");
			sockd = socket(AF_INET, SOCK_DGRAM, 0);
			if (sockd == -1)
			{
				Log::getInstance().entry(TAG, "ERROR socket creation failed!");
				return;
			}
			
			/* client address */
			my_addr.sin_family = AF_INET;
			my_addr.sin_addr.s_addr = INADDR_ANY;
			my_addr.sin_port = 0;
			
			Log::getInstance().entry(TAG, "Binding a socket");
			bind(sockd, (struct sockaddr*)&my_addr, sizeof(my_addr));
			
			/* server address */
			srv_addr.sin_family = AF_INET;
			inet_aton(host.c_str(), &srv_addr.sin_addr);
			srv_addr.sin_port = htons(port);
			
			Log::getInstance().entry(TAG, "Starting the write loop.");
			ssize_t sent;
			while (running) {
				guard.lock();
				if (!msgQueue.empty()) {
					Log::getInstance().entry(TAG, "Stuff in send queue!");
					Package p = msgQueue.front();
					const boost::uuids::uuid & uid = p.getUuid();
					currentlySending = boost::uuids::to_string(uid);
					currentlySending += Package::separator() + p.getTypeAsString();
					currentlySending += Package::separator() + p.getData();
					Log::getInstance().entry(TAG, "Sending: %s", currentlySending.c_str());
					msgQueue.pop();
					sent = sendto(sockd, currentlySending.c_str(), currentlySending.length()+1, 0,
									  (struct sockaddr*)&srv_addr, sizeof(srv_addr));
					if (sent == -1) {
						Log::getInstance().entry(TAG, "ERROR in sending data: %d", errno);
					}
					guard.unlock();
				} else {
					guard.unlock();
					Log::getInstance().entry(TAG, "Send queue empty, waiting...");
					std::unique_lock<std::mutex> ulock(guard);
					while (msgQueue.empty()) {
						condition.wait(ulock);
					}
				}
			}
			Log::getInstance().entry(TAG, "Shutting down the socket.");
			shutdown(sockd, SHUT_RDWR);
		}
	}
	
	/**
	 Starts the network writer.
	 Basically starting the writer starts the thread which is waiting for
	 notification of data arriving in the send queue in a separate thread.
	 */
	void NetworkWriter::start() {
		// Create and run in thread...
		// Set up the socket
		// start working
		if (!running) {
			running = true;
			threader = std::thread(&NetworkWriter::threadFunc, this);
		}
	}
	
	/** Stops the writer. In practise this ends the loop in the send thread. */
	void NetworkWriter::stop() {
		running = false;
	}
	
	
	/** Use write to send packages to the next ProcessorNode. The package is
	 put into a queue of packages to send and will be sent when all the previous packages
	 have been sent.
	 @param data The data package to send.
	 */
	void NetworkWriter::write(const Package & data)
	{
		guard.lock();
		msgQueue.push(data);
		guard.unlock();
		// Notify the writer thread there's something to send.
		condition.notify_one();
	}
	
	
} //namespace
