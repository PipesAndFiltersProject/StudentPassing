//
//  TheUsualGrader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <random>

#include "TheUsualGrader.h"

namespace ohar_pipes {

	
int TheUsualGrader::calculate(const StudentDataItem & source) {
   std::default_random_engine generator(time(0));
   std::uniform_int_distribution<int> distribution(0,5);
   int dice_roll = distribution(generator);
   return dice_roll;
}

} //namespace