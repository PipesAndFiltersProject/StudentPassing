//
//  DataFileReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 5.12.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <fstream>

#include "DataFileReader.h"
#include "DataReaderObserver.h"
#include "Log.h"


namespace ohar_pipes {

DataFileReader::DataFileReader(DataReaderObserver & obs)
: observer(obs), TAG("FileReader")
{
}

DataFileReader::~DataFileReader() {
}

bool DataFileReader::read(const std::string &fileName) {
   Log::getInstance().entry(TAG, "Starting to handle the file %s", fileName.c_str());
   std::ifstream file(fileName, std::ifstream::in);
   if (!file.is_open()) {
      Log::getInstance().entry(TAG, "Could not open the file!!");
      return false;
   }
   std::string str;
   std::string contentType;
   std::getline(file, contentType);
   do {
      std::getline(file, str);
      Log::getInstance().entry(TAG, "Read line: %s", str.c_str());
      if (file.good() && str.length() > 0) {
         DataItem * item = parse(str, contentType);
         if (item) {
            observer.handleNewItem(item);
         }
      }
   } while (file.good());
   file.close();
   return true;
}


} //namespace