//
//  main.cpp
//  ExerciseWorkInfoNode
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <iostream>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>

#include <OHARStudentLayer/StudentNetInputHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentHandler.h>
#include <OHARStudentLayer/GradingHandler.h>
#include <OHARStudentLayer/StudentWriterHandler.h>

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
		processor->addHandler(new GradingHandler(*processor));
		processor->addHandler(new StudentWriterHandler(*processor));
		
		processor->start();
		delete processor;
	} else {
		std::cout << "No config file specified! Give config file name as startup parameter." << std::endl;
	}
	
   return 0;
}

