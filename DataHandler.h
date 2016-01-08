//
//  DataHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 14.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__DataHandler__
#define __PipesAndFiltersFramework__DataHandler__

#include <string>

class DataHandler {
public:
   DataHandler();
   virtual ~DataHandler();
   
   virtual void handleData(const std::string & data);
   
private:
   
};

#endif /* defined(__PipesAndFiltersFramework__DataHandler__) */
