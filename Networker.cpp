//
//  Networker.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "Networker.h"

Networker::Networker(const std::string & hostName, int portNumber)
: host(hostName), port(portNumber), running(false)
{
}

Networker::~Networker() {
}


