//
//  StudentWriterHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include "StudentWriterHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"
#include "StudentFileWriter.h"


namespace ohar_pipes {


StudentWriterHandler::StudentWriterHandler(ProcessorNode & myNode)
: node(myNode), TAG("StudentWriterHandler")
{
   writer = new StudentFileWriter(node.getOutputFileName());
}

StudentWriterHandler::~StudentWriterHandler() {
   delete writer;
}

bool StudentWriterHandler::consume(Package & data) {
   Log::getInstance().entry(TAG, "Starting to write a package");
	if (data.getType() == Package::Data) {
      DataItem * item = data.getDataItem();
      if (item) {
         const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
         if (student) {
            writer->write(student);
         }
      }
   }
   return false; // Don't let others handle this data package since it is now passed along.
}


} //namespace