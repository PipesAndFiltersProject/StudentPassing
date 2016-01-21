//
//  ExerciseInfoHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include "NetInputHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"

namespace ohar_pipes {

	
NetInputHandler::NetInputHandler(ProcessorNode & myNode)
: node(myNode), TAG("NetInputHandler")
{
}

NetInputHandler::~NetInputHandler() {
   
}

bool NetInputHandler::consume(Package & data) {
	if (data.getType() == Package::Data && data.getData().length() > 0) {
      Log::getInstance().entry(TAG, "** data received, handling! **");
      // parse data to a student data object
      StudentDataItem * item = new StudentDataItem;
      if (item->parse(data.getData(), "summarydata")) {
         data.setDataItem(item);
         data.setData("");
      } else {
         // could not parse.
         delete item;
      }
   }
   return false; // Always let others handle this data package too.
}

} //namespace