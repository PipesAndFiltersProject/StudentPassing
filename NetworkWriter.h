//
//  NetworkWriter.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetworkWriter__
#define __PipesAndFiltersFramework__NetworkWriter__

#include <queue>

#include "Networker.h"

class NetworkWriter : public Networker {
public:
   NetworkWriter(const std::string & hostName, int portNumber);
   ~NetworkWriter();
   
   virtual void start();
   virtual void stop();
   
   void write(const std::string & data);
   void threadFunc();
   
protected:
   
private:
   NetworkWriter();
   NetworkWriter(const NetworkWriter &);
   const NetworkWriter & operator =(const NetworkWriter &);

private:
   
   std::string currentlySending;
   std::queue<std::string> msgQueue; // TODO: change to fifo queue.
   std::mutex guard;

};


#endif /* defined(__PipesAndFiltersFramework__NetworkWriter__) */
