//
//  Log.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 21.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__Log__
#define __PipesAndFiltersFramework__Log__

#include <iostream>
#include <string>

class Log {
public:
   static Log & getInstance();
   void setStream(std::ostream & os);
   
   void entry(const std::string & str);
   
   template<typename... Args>
   void entry(const std::string & tag, const std::string & format, Args... args);
   
private:
   Log();
   Log(const Log &);
   Log & operator = (const Log&);
   
private:
   std::ostream * stream;
   
};

#endif /* defined(__PipesAndFiltersFramework__Log__) */
