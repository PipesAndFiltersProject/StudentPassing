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

#include "NetworkReader.h"
#include "NetworkReaderObserver.h"
#include "Log.h"

NetworkReader::NetworkReader(const std::string & hostName, int portNumber, NetworkReaderObserver & obs)
: Networker(hostName, portNumber), observer(obs), TAG("NetworkReader")
{
   
}

void NetworkReader::threadFunc() {
   int sockd;
   struct sockaddr_in my_name, cli_name;
   ssize_t status;
   socklen_t addrlen;
   const size_t MAX_BUF=2048;
   char buf[MAX_BUF];
   
   // create a socket
   Log::getInstance().entry(TAG, "Create the socket");
   sockd = socket(AF_INET, SOCK_DGRAM, 0);
   if (sockd >= 0)
   {
      // server address
      Log::getInstance().entry(TAG, "Socket created, do bind().");
      my_name.sin_family = AF_INET;
      my_name.sin_addr.s_addr = INADDR_ANY;
      my_name.sin_port = htons(port);
      status = bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name));
      if (status == 0) {
         Log::getInstance().entry(TAG, "bind() succeeded");
         addrlen = sizeof(cli_name);
         while (running) {
            // Start reading for data...
            Log::getInstance().entry(TAG, "Start reading for data...");
            status = recvfrom(sockd, buf, MAX_BUF, 0, (struct sockaddr*)&cli_name, &addrlen);
            Log::getInstance().entry(TAG, "Received data: " + std::string(buf));
            guard.lock();
            msgQueue.push(buf);
            guard.unlock();
            // And when data has been received, notify the observer.
            observer.receivedData();
         }
      } else {
         Log::getInstance().entry(TAG, "bind() failed with code: %d ", status);
         running = false;
      }
      shutdown(sockd, SHUT_RDWR);
   } else {
      Log::getInstance().entry(TAG, "socket() failed with code: %d ", sockd);
      running = false;
   }
}


void NetworkReader::start() {
   if (!running) {
      Log::getInstance().entry(TAG, "Start the thread...");
      running = true;
      threader = std::thread(&NetworkReader::threadFunc, this);
   } else {
      
   }
   
}

void NetworkReader::stop() {
   Log::getInstance().entry(TAG, "Stop the thread...");
   running = false;
}

std::string NetworkReader::read() {
   guard.lock();
   std::string result;
   if (!msgQueue.empty()) {
      result = msgQueue.front();
      msgQueue.pop();
   }
   guard.unlock();
   return result;
}