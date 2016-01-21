//
//  GraderFactory.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__GraderFactory__
#define __PipesAndFiltersFramework__GraderFactory__

namespace ohar_pipes {

	
class GradeCalculator;

class GraderFactory {
public:
   static GradeCalculator * makeGrader();
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__GraderFactory__) */
