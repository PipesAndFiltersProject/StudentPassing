//
//  main.cpp
//  ExerciseWorkInfoNode
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <iostream>

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/StudentInputHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentHandler.h>
#include <OHARStudentLayer/GradingHandler.h>
#include <OHARStudentLayer/StudentWriterHandler.h>

int main(int argc, const char * argv[])
{
   std::unique_ptr<g3::LogWorker> logworker{ g3::LogWorker::createLogWorker() };
   auto defaultHandler = logworker->addDefaultLogger(argv[0], "./");
   g3::initializeLogging(logworker.get());
   
   using namespace OHARBase;
   static const std::string TAG("ProjInf ");
   
   LOG(INFO) << TAG << "Launching " << argv[0];
   LOG(INFO) << TAG << "Arguments: " << argc;
	
	std::string configFile;
	if (argc > 1) {
		ProcessorNode * processor = new ProcessorNode(argv[0]);
      
      LOG(INFO) << TAG << "arg1: " << argv[1];
		configFile = argv[1];
		processor->configure(configFile);
		
		using namespace OHARStudent;
		processor->addHandler(new StudentInputHandler());
		processor->addHandler(new StudentHandler(*processor));
		processor->addHandler(new GradingHandler(*processor));
		processor->addHandler(new StudentWriterHandler(*processor));
		
		processor->start();
		delete processor;
	} else {
      LOG(WARNING) << TAG << "No config file specified! Give config file name as startup parameter.";
	}
	LOG(INFO) << TAG << "--- Node closed ---";
   return 0;
}

