//
//  main.cpp
//  PipesAndFiltersStudentNode
//
//  Created by Antti Juustila on 21.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>
#include <memory>

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentNetOutputHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>

/**
 This is the application for the 1st Node in the student data handling application.
 This node is the first in the chain of nodes in the Pipes & Filters architecture.
 This Node does not have an input connection (NetworkReader object) for receiving 
 data over the network. The node reads basic student information from a file
 and then sends data over to the next Node using NetworkWriter object.
 The file structure looks like this:
 <pre>
 studentdata
 123456  Antti Juustila  TOL
 123457  Tiina Tomera    SO
 </pre>
 Here, the first line is the contentType of the file (see classes StudentFileReader and
 PlainStudentFileHandler). The content includes the:
 <ul><li>Student id</li>
 <li>Student's name</li>
 <li>The department of the student</li></ul>
 These data items must be separated by a tabulator. File data parser separates the
 data elements from each other by using the tabulator. A student object is then
 created and send over the network to next Node which adds more elements to the
 basic student data.
*/

int main(int argc, const char * argv[])
{
   std::unique_ptr<g3::LogWorker> logworker{ g3::LogWorker::createLogWorker() };
   auto defaultHandler = logworker->addDefaultLogger(argv[0], "./");
   g3::initializeLogging(logworker.get());
   
	using namespace OHARBase;
   const static std::string TAG = "StudInf ";
      
   LOG(INFO) << TAG << "Launching " << argv[0];
   LOG(INFO) << TAG << "Arguments: " << argc;

   std::string configFile;
   if (argc > 1) {
		ProcessorNode * processor = new ProcessorNode(argv[0]);
      configFile = argv[1];
		processor->configure(configFile);
		
		using namespace OHARStudent;
		processor->addHandler(new OHARStudent::PlainStudentFileHandler(*processor));
		processor->addHandler(new OHARStudent::StudentNetOutputHandler(*processor));
		
		processor->start();
		delete processor;
	} else {
      LOG(WARNING) << TAG << "No config file specified! Give config file name as startup parameter.";
	}
   LOG(INFO) << TAG << "--- Node closed ---";
   return 0;
}

