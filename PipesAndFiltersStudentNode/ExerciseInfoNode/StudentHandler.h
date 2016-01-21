//
//  ExerciseMergerHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__ExerciseMergerHandler__
#define __PipesAndFiltersFramework__ExerciseMergerHandler__

#include <list>

#include "DataHandler.h"
#include "DataReaderObserver.h"


namespace ohar_pipes {

	
class ProcessorNode;
class Package;
class StudentDataItem;

class StudentHandler : public DataHandler, public DataReaderObserver {
public:
   StudentHandler(ProcessorNode & myNode);
   virtual ~StudentHandler();
   
   bool consume(Package & data);

   // From DataReaderObserver
   void handleNewItem(DataItem * item);
   
private:
   void readFile();
   
   StudentDataItem * findStudent(const StudentDataItem & which) const;
   
   ProcessorNode & node;
   const std::string TAG;
   std::list<DataItem*> dataItems;
   
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__ExerciseMergerHandler__) */
