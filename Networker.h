//
//  Networker.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 19.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef PipesAndFiltersFramework_Networker_h
#define PipesAndFiltersFramework_Networker_h

#include <string>
#include <thread>

class Networker {
public:
   
	Networker(const std::string & hostName, int portNumber);
	virtual ~Networker();
   
	virtual void start() = 0;
   virtual void stop() = 0;
	
private:
   Networker();
   Networker(const Networker &);
   const Networker & operator =(const Networker &);
   
protected:
   std::string host;
   int port;

   bool running;
   std::thread threader;
};

#endif
