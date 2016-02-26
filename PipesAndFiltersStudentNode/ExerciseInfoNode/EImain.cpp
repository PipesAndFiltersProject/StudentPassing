//
//  main.cpp
//  ExerciseInfoNode
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "ProcessorNode.h"
#include "StudentDataItem.h"
#include "StudentNetInputHandler.h"
#include "StudentNetOutputHandler.h"
#include "StudentHandler.h"
#include "Log.h"

int main(int argc, const char * argv[])
{
	using namespace OHARBase;
	
   Log::getInstance().entry("main", "Launching %s", argv[0]);
   Log::getInstance().entry("main", "Arguments: %d", argc);
	
	std::string configFile;
	if (argc > 1) {
		ProcessorNode * processor = new ProcessorNode(argv[0]);
		Log::getInstance().entry("main", "arg1: %s", argv[1]);
		configFile = argv[1];
		processor->configure(configFile);
		
		using namespace OHARStudent;
		processor->addHandler(new StudentNetInputHandler());
		processor->addHandler(new StudentHandler(*processor));
		processor->addHandler(new StudentNetOutputHandler(*processor));
		
		processor->start();
		delete processor;
	} else {
		std::cout << "No config file specified! Give config file name as startup parameter." << std::endl;
	}

	
   return 0;
}

