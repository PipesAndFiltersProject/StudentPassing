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

#include "NetworkWriter.h"

NetworkWriter::NetworkWriter(const std::string & hostName, int portNumber)
: Networker(hostName, portNumber)
{
   
}

void NetworkWriter::stop() {
   running = false;
}

void NetworkWriter::threadFunc() {
   if (host.length() > 0 && port > 0) {
      // Setup the datagram socket to send data to the next node
      int sockd;
      struct sockaddr_in my_addr, srv_addr;
      
      /* create a socket */
      sockd = socket(AF_INET, SOCK_DGRAM, 0);
      if (sockd == -1)
      {
         return;
      }
      
      /* client address */
      my_addr.sin_family = AF_INET;
      my_addr.sin_addr.s_addr = INADDR_ANY;
      my_addr.sin_port = 0;
      
      bind(sockd, (struct sockaddr*)&my_addr, sizeof(my_addr));
      
      /* server address */
      srv_addr.sin_family = AF_INET;
      inet_aton(host.c_str(), &srv_addr.sin_addr);
      srv_addr.sin_port = htons(port);
      
      while (running) {
         guard.lock();
         if (!msgQueue.empty()) {
            currentlySending = msgQueue.front();
            guard.unlock();
            sendto(sockd, currentlySending.c_str(), currentlySending.length()+1, 0,
                   (struct sockaddr*)&srv_addr, sizeof(srv_addr));
            
            msgQueue.pop();
         } else {
            guard.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
         }
      }
      shutdown(sockd, SHUT_RDWR);
   }
}

void NetworkWriter::start() {
   // Create and run in thread...
   // Set up the socket
   // start working
   if (!running) {
      running = true;
      threader = std::thread(&NetworkWriter::threadFunc, this);
   }
   
}

void NetworkWriter::write(const std::string & data)
{
   msgQueue.push(data);
   // Notify the writer thread there's something to send.
}