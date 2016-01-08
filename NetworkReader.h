//
//  NetworkReader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetworkReader__
#define __PipesAndFiltersFramework__NetworkReader__

#include <queue>

#include "Networker.h"

class NetworkReaderObserver;

class NetworkReader : public Networker {
public:
   
   NetworkReader(const std::string & hostName, int portNumber, NetworkReaderObserver & obs);
   ~NetworkReader();
   
   virtual void start();
   virtual void stop();

   std::string read();
   
protected:
   virtual void threadFunc();
   
private:
   NetworkReader();
   NetworkReader(const NetworkReader &);
   const NetworkReader & operator =(const NetworkReader &);
   
private:
   std::queue<std::string> msgQueue;
   std::mutex guard;

   NetworkReaderObserver & observer;
   
   const std::string TAG;
};


#endif /* defined(__PipesAndFiltersFramework__NetworkReader__) */
