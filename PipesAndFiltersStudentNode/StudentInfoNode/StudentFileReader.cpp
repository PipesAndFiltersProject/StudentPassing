//
//  StudentFileReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include "StudentFileReader.h"
#include "StudentDataItem.h"
#include "Log.h"


namespace ohar_pipes {

	
StudentFileReader::StudentFileReader(DataReaderObserver & obs)
: DataFileReader(obs), TAG("SFileReader") {
   
}

StudentFileReader::~StudentFileReader() {
   
}
   
DataItem * StudentFileReader::parse(const std::string & str, const std::string & contentType) {
   StudentDataItem * item = 0;
   if (str.length() > 0) {
      Log::getInstance().entry(TAG, "Parsing line: %s", str.c_str());
      item = new StudentDataItem();
      if (!item->parse(str, contentType)) {
         Log::getInstance().entry(TAG, "SDataItem failed to parse!");
         delete item;
         item = 0;
      }
   }
   return item;
}


} //namespace