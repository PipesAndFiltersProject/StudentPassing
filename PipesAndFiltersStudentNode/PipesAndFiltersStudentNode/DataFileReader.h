//
//  DataFileReader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 5.12.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__DataFileReader__
#define __PipesAndFiltersFramework__DataFileReader__

#include <list>

namespace ohar_pipes {

	
class DataItem;
class DataReaderObserver;

class DataFileReader {
public:
   DataFileReader(DataReaderObserver & obs);
   virtual ~DataFileReader();
   
   virtual bool read(const std::string &fileName);
   
protected:
   DataFileReader(const DataFileReader &) = delete;
   const DataFileReader & operator = (const DataFileReader &) = delete;
   
   virtual DataItem * parse(const std::string & str, const std::string & contentType) = 0;
   
   DataReaderObserver & observer;
   
private:

   const std::string TAG;
};
	
	
} //namespace
#endif /* defined(__PipesAndFiltersFramework__DataFileReader__) */
