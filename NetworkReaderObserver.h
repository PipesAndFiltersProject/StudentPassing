//
//  NetworkObserver.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef PipesAndFiltersFramework_NetworkObserver_h
#define PipesAndFiltersFramework_NetworkObserver_h

class NetworkReaderObserver {
public:
   virtual void receivedData() = 0;
};

#endif
