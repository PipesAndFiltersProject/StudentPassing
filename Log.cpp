//
//  Log.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 21.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "Log.h"


Log & Log::getInstance() {
   static Log logInstance;
   return logInstance;
}

void Log::setStream(std::ostream & os) {
   stream = &os;
}


Log::Log()
: stream(&std::cout)
{

}

void Log::entry(const std::string & str)
{
   const char *s = str.c_str();
   while (*s) {
      if (*s == '%') {
         if (*(s + 1) == '%') {
            ++s;
         }
         else {
            throw std::runtime_error("invalid format string: missing arguments");
         }
      }
      *stream << *s++;
   }
}

template<typename... Args>
void Log::entry(const std::string & tag, const std::string & format, Args... args){
   *stream << tag << " ";
   const char *s = format.c_str();
   while (*s) {
      if (*s == '%') {
         if (*(s + 1) == '%') {
            ++s;
         }
         else {
            printf(s + 1, args...); // call even when *s == 0 to detect extra arguments
            return;
         }
      }
      std::cout << *s++;
   }
   throw std::logic_error("extra arguments provided to printf");
}