//
//  GradingHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__GradingHandler__
#define __PipesAndFiltersFramework__GradingHandler__

#include "DataHandler.h"

namespace ohar_pipes {

	
class ProcessorNode;
class Package;

class GradingHandler : public DataHandler {
public:
   GradingHandler(ProcessorNode & myNode);
   virtual ~GradingHandler();
   
   bool consume(Package & data);
   
private:
   ProcessorNode & node;
   const std::string TAG;
};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__GradingHandler__) */
