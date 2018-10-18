//
//  main.cpp
//  ExerciseInfoNode
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <iostream>

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentNetInputHandler.h>
#include <OHARStudentLayer/StudentNetOutputHandler.h>
#include <OHARStudentLayer/StudentHandler.h>

int main(int argc, const char * argv[])
{
   std::unique_ptr<g3::LogWorker> logworker{ g3::LogWorker::createLogWorker() };
   auto defaultHandler = logworker->addDefaultLogger(argv[0], "./");
   g3::initializeLogging(logworker.get());
   
	using namespace OHARBase;
   static const std::string TAG("ExerInf ");
   LOG(INFO) << TAG << "Launching " << argv[0];
   LOG(INFO) << TAG << "Arguments: " << argc;
   
	std::string configFile;
	if (argc > 1) {
      try {
         ProcessorNode * processor = new ProcessorNode(argv[0]);
         LOG(INFO) << TAG << "arg1: " << argv[1];
         configFile = argv[1];
         processor->configure(configFile);
         
         using namespace OHARStudent;
         processor->addHandler(new StudentNetInputHandler());
         processor->addHandler(new StudentHandler(*processor));
         processor->addHandler(new StudentNetOutputHandler(*processor));
         
         processor->start();
         LOG(INFO) << TAG << "Returned from processor->start(), now deleting processor";
         delete processor;
         LOG(INFO) << TAG << "processor deleted";
      } catch (std::exception & e) {
         LOG(WARNING) << "EXCEPTION: " << e.what();
      }
	} else {
      LOG(WARNING) << TAG << "No config file specified! Give config file name as startup parameter.";
	}
   LOG(INFO) << TAG << "--- Node closed ---";
   return 0;
}

