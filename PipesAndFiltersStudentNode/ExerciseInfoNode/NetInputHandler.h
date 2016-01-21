//
//  ExerciseInfoHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__ExerciseInfoHandler__
#define __PipesAndFiltersFramework__ExerciseInfoHandler__

#include "DataHandler.h"


namespace ohar_pipes {

	
class ProcessorNode;
class Package;

class NetInputHandler : public DataHandler {
public:
   NetInputHandler(ProcessorNode & myNode);
   virtual ~NetInputHandler();
   
   bool consume(Package & data);
   
private:
   ProcessorNode & node;
   const std::string TAG;
};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__ExerciseInfoHandler__) */
