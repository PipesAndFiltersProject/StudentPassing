//
//  GraderFactory.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <random>

#include "GraderFactory.h"
#include "TheUsualGrader.h"
#include "CruelGrader.h"
#include "Log.h"


namespace ohar_pipes {

	
GradeCalculator * GraderFactory::makeGrader() {
   std::default_random_engine generator(time(0));
   std::uniform_int_distribution<int> distribution(0,1);
   int dice_roll = distribution(generator);
   
   if (dice_roll == 0) {
      Log::getInstance().entry("GradeFactory", "Created the usual grader.");
      return new TheUsualGrader();
   }
   Log::getInstance().entry("GradeFactory", "Created the cruel grader :/");
   return new CruelGrader();
}


} //namespace