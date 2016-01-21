//
//  PlainStudentFileHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__PlainStudentFileHandler__
#define __PipesAndFiltersFramework__PlainStudentFileHandler__

#include <list>

#include "DataHandler.h"
#include "DataReaderObserver.h"


namespace ohar_pipes {

	
class ProcessorNode;
class Package;

class PlainStudentFileHandler : public DataHandler, public DataReaderObserver {
public:
   PlainStudentFileHandler(ProcessorNode & myNode);
   virtual ~PlainStudentFileHandler();
   
   bool consume(Package & data);
   
   // From DataReaderObserver
   void handleNewItem(DataItem * item);
   
private:
   void readFile();
   
   ProcessorNode & node;
   const std::string TAG;
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__PlainStudentFileHandler__) */
