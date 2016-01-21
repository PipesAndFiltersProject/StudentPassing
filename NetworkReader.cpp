//
//  NetworkReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>

#include "NetworkReader.h"
#include "NetworkReaderObserver.h"
#include "Log.h"

namespace ohar_pipes {
	
	/**
	 Constructor to create the reader with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName the host to reading data, including port number. In practise,
	 this should always be local host for reader, i.e. 127.0.0.1.
	 */
	NetworkReader::NetworkReader(const std::string & hostName, NetworkReaderObserver & obs)
	: Networker(hostName), observer(obs), TAG("NetworkReader")
	{
	}
	
	/**
	 Constructor to create the reader with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName the host to reading data. In practise,
	 this should always be local host for reader, i.e. 127.0.0.1.
	 @param portNumber The port to read data from.
	 */
	NetworkReader::NetworkReader(const std::string & hostName, int portNumber, NetworkReaderObserver & obs)
	: Networker(hostName, portNumber), observer(obs), TAG("NetworkReader")
	{
	}
	
	NetworkReader::~NetworkReader() {
		
	}
	
	
	/** The thread function doing most of the relevant work for receiving data. */
	void NetworkReader::threadFunc() {
		int sockd;
		struct sockaddr_in my_name, cli_name;
		ssize_t status;
		socklen_t addrlen;
		const size_t MAX_BUF=2048;
		char buf[MAX_BUF];
		
		// Show local ip to user for connecting filters.
		getPrimaryIp(buf, sizeof(buf));
		Log::getInstance().entry(TAG, ">>>>> Local address is: %s:%d <<<<<", buf, getPort());
		// create a socket
		Log::getInstance().entry(TAG, "Start creating a socket");
		sockd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sockd >= 0)
		{
			// server address
			Log::getInstance().entry(TAG, "Socket created, do bind().");
			my_name.sin_family = AF_INET;
			my_name.sin_addr.s_addr = INADDR_ANY;
			my_name.sin_port = htons(getPort());
			status = bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name));
			if (status == 0) {
				Log::getInstance().entry(TAG, "bind() succeeded");
				addrlen = sizeof(cli_name);
				while (running) {
					// Start reading for data...
					Log::getInstance().entry(TAG, "Start reading for data...");
					status = recvfrom(sockd, buf, MAX_BUF, 0, (struct sockaddr*)&cli_name, &addrlen);
					Log::getInstance().entry(TAG, "Received data: %s", buf);
					std::string str(buf);
					if (str.length()>0) {
						Package p;
						if (p.parse(str)) {
							guard.lock();
							msgQueue.push(p);
							guard.unlock();
						}
					}
					// And when data has been received, notify the observer.
					observer.receivedData();
				}
			} else {
				Log::getInstance().entry(TAG, "bind() failed with code: %d ", status);
				running = false;
			}
			Log::getInstance().entry(TAG, "Shutting down the socket.");
			shutdown(sockd, SHUT_RDWR);
		} else {
			Log::getInstance().entry(TAG, "socket() failed with code: %d ", sockd);
			running = false;
		}
	}
	
	
	/** Starts the reader. This basically creates a new thread which runs the threadFunc(). */
	void NetworkReader::start() {
		if (!running) {
			Log::getInstance().entry(TAG, "Start the thread...");
			running = true;
			threader = std::thread(&NetworkReader::threadFunc, this);
		}
	}
	
	/** Stops the reader by setting the running flag to false, effectively ending the thread
	 loop in the threadFunc(). */
	void NetworkReader::stop() {
		Log::getInstance().entry(TAG, "Stop the thread...");
		running = false;
	}
	
	/** Allows another object to read the package object received from the network.
	 This method should be called by the NetworkReaderObserver only when it has been notified
	 that data has arrived.
	 @return The Package containing the data received from the previous ProcessorNode.
	 */
	Package NetworkReader::read() {
		Log::getInstance().entry(TAG, "In read");
		guard.lock();
		Package result;
		if (!msgQueue.empty()) {
			result = msgQueue.front();
			msgQueue.pop();
		}
		guard.unlock();
		return result;
	}
	
	
	void NetworkReader::getPrimaryIp(char* buffer, socklen_t buflen)
	{
		assert(buflen >= 16);
		
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		assert(sock != -1);
		
		const char* kGoogleDnsIp = "8.8.8.8";
		uint16_t kDnsPort = 53;
		struct sockaddr_in serv;
		memset(&serv, 0, sizeof(serv));
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
		serv.sin_port = htons(kDnsPort);
		
		int err = connect(sock, (const sockaddr*) &serv, sizeof(serv));
		assert(err != -1);
		
		sockaddr_in name;
		socklen_t namelen = sizeof(name);
		err = getsockname(sock, (sockaddr*) &name, &namelen);
		assert(err != -1);
		
		const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, buflen);
		assert(p);
		
		close(sock);
	}
	
} //namespace