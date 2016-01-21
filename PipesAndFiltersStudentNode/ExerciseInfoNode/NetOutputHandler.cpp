//
//  NetOutputHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include "NetOutputHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"


namespace ohar_pipes {

	
NetOutputHandler::NetOutputHandler(ProcessorNode & myNode)
: node(myNode), TAG("NetOutputHandler")
{
}

NetOutputHandler::~NetOutputHandler() {
   
}

bool NetOutputHandler::consume(Package & data) {
   Log::getInstance().entry(TAG, "Starting to send a package");
	if (data.getType() == Package::Data) {
      DataItem * item = data.getDataItem();
      if (item) {
         const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
         if (student) {
            Log::getInstance().entry(TAG, "It is a student so creating payload");
            std::stringstream stream;
            std::string payload;
            stream << *(student);
            payload = stream.str();
            data.setData(payload);
            data.setDataItem(0);
            Log::getInstance().entry(TAG, "And telling the processornode to send.");
            node.sendData(data);
         }
      }
      return true; // data consumed, sent away. No need to pass along anymore.
   } else {
      node.sendData(data);
   }
   return false;
}
	
	
} //namespace
