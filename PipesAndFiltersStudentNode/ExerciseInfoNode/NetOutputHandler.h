//
//  NetOutputHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetOutputHandler__
#define __PipesAndFiltersFramework__NetOutputHandler__

#include "DataHandler.h"


namespace ohar_pipes {

	
class ProcessorNode;
class Package;

class NetOutputHandler : public DataHandler {
public:
   NetOutputHandler(ProcessorNode & myNode);
   virtual ~NetOutputHandler();
   
   bool consume(Package & data);
   
private:
   ProcessorNode & node;
   const std::string TAG;
};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__NetOutputHandler__) */
