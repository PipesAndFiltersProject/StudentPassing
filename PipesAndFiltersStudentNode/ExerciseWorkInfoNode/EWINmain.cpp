//
//  main.cpp
//  ExerciseWorkInfoNode
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "ProcessorNode.h"
#include "StudentNetInputHandler.h"
#include "StudentDataItem.h"
#include "StudentHandler.h"
#include "GradingHandler.h"
#include "StudentWriterHandler.h"
#include "Log.h"

int main(int argc, const char * argv[])
{
	using namespace OHARBase;
	
   Log::getInstance().entry("main", "Launching %s", argv[0]);
   Log::getInstance().entry("main", "Arguments: %d", argc);
   ProcessorNode * processor = new ProcessorNode(argv[0]);
   
   std::string inputAddr;
   std::string outputAddr;
   std::string dataFile;
   std::string outputFile;
   if (argc > 1) {
      Log::getInstance().entry("main", "arg1: %s", argv[1]);
      inputAddr = argv[1];
      if (argc > 2) {
         Log::getInstance().entry("main", "arg2: %s", argv[2]);
         outputAddr = argv[2];
         if (argc > 3) {
            Log::getInstance().entry("main", "arg3: %s", argv[3]);
            dataFile = argv[3];
            if (argc > 4) {
               Log::getInstance().entry("main", "arg4: %s", argv[4]);
               outputFile = argv[4];
            }
         }
      }
   }
   if (inputAddr.length()>0) {
      processor->setInputSource(inputAddr);
   }
   if (outputAddr.length()>0) {
      processor->setOutputSink(outputAddr);
   }
   if (dataFile.length()>0) {
      processor->setDataFileName(dataFile);
   }
   if (outputFile.length()>0) {
      processor->setOutputFileName(outputFile);
   } else {
      processor->setOutputFileName("default.out.txt");
   }
	
	using namespace OHARStudent;
   processor->addHandler(new StudentNetInputHandler());
   processor->addHandler(new StudentHandler(*processor));
   processor->addHandler(new GradingHandler(*processor));
   processor->addHandler(new StudentWriterHandler(*processor));
      
   processor->start();
   
   delete processor;
   
   return 0;
}

