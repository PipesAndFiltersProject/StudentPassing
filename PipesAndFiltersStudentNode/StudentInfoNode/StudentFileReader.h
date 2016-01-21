//
//  StudentFileReader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentFileReader__
#define __PipesAndFiltersFramework__StudentFileReader__

#include <string>
#include <list>

#include "DataFileReader.h"


namespace ohar_pipes {

	
class DataItem;

class StudentFileReader : public DataFileReader {
public:
   StudentFileReader(DataReaderObserver & obs);
   virtual ~StudentFileReader();
   
protected:
   DataItem * parse(const std::string & str, const std::string & contentType);
   
private:
   const std::string TAG;
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__StudentFileReader__) */
