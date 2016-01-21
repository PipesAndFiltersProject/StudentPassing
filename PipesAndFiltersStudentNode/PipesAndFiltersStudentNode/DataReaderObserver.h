//
//  DataReaderObserver.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 27.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef PipesAndFiltersFramework_DataReaderObserver_h
#define PipesAndFiltersFramework_DataReaderObserver_h

namespace ohar_pipes {

	
class DataItem;

class DataReaderObserver {
public:
   virtual void handleNewItem(DataItem * item) = 0;
};

	
} //namespace
#endif
