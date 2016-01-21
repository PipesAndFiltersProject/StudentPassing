//
//  PlainStudentFileHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include <sstream>

#include "PlainStudentFileHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "StudentFileReader.h"
#include "Package.h"
#include "Log.h"


namespace ohar_pipes {

	
PlainStudentFileHandler::PlainStudentFileHandler(ProcessorNode & myNode)
: node(myNode), TAG("PlainFileHandler")
{
}

PlainStudentFileHandler::~PlainStudentFileHandler() {
   
}

void PlainStudentFileHandler::readFile() {
   StudentFileReader reader(*this);
   reader.read(node.getDataFileName());
}

bool PlainStudentFileHandler::consume(Package & data) {
	if (data.getType() == Package::Control) {
      if (data.getData() == "readfile") {
         readFile();
      }
   }
   return false; // false: pass to next handler. true: do not pass to next handler.
}

void PlainStudentFileHandler::handleNewItem(DataItem * item) {
   // Check if the item is already in the container.
   Log::getInstance().entry(TAG, "One new file data item received");
   StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
   if (newStudent) {
      Log::getInstance().entry(TAG, "Creating a package to send ahead...");
      Package p;
		p.setType(Package::Data);
      p.setDataItem(newStudent);
      delete newStudent;
      Log::getInstance().entry(TAG, "Pass to next handler.");
      node.passToNextHandlers(this, p);
   }
}
	
	
} //namespace

