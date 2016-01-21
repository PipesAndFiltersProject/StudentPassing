//
//  GradingHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include "GradingHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"
#include "GraderFactory.h"

namespace ohar_pipes {

	
GradingHandler::GradingHandler(ProcessorNode & myNode)
: node(myNode), TAG("GradingHandler")
{
   StudentDataItem::setGradeCalculator(GraderFactory::makeGrader());
}

GradingHandler::~GradingHandler() {
   StudentDataItem::setGradeCalculator(0);
}

bool GradingHandler::consume(Package & data) {
	if (data.getType() == Package::Data) {
      DataItem * item = data.getDataItem();
      if (item) {
         StudentDataItem * student = dynamic_cast<StudentDataItem*>(item);
         if (student) {
            Log::getInstance().entry(TAG, "Calculating a grade for the student.");
            student->calculateGrade();
         }
      }
   }
   return false; // Always let others handle this data package too.
}


} //namespace