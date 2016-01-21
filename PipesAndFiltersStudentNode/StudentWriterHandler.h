//
//  StudentWriterHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentWriterHandler__
#define __PipesAndFiltersFramework__StudentWriterHandler__

#include "DataHandler.h"


namespace ohar_pipes {

	
class ProcessorNode;
class Package;
class StudentFileWriter;

class StudentWriterHandler : public DataHandler {
public:
   StudentWriterHandler(ProcessorNode & myNode);
   virtual ~StudentWriterHandler();
   
   bool consume(Package & data);
   
private:
   ProcessorNode & node;
   StudentFileWriter * writer;
   const std::string TAG;
};


} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentWriterHandler__) */
