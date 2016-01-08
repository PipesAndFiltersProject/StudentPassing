//
//  ProcessorNode.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 19.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef PipesAndFiltersFramework_ProcessorNode_h
#define PipesAndFiltersFramework_ProcessorNode_h

#include <string>
#include <vector>

#include "NetworkReaderObserver.h"

class NetworkReader;
class NetworkWriter;
class FileReader;
class DataHandler;

class ProcessorNode : public NetworkReaderObserver {
public:
	ProcessorNode(const std::string & aName);
   virtual ~ProcessorNode();
   
	void setInputSource(const std::string & hostName, int portNumber);
	void setOutputSource(const std::string & hostName, int portNumber);
	void setSourceFile(const std::string & fileName);
	
	const std::string & getName() const;
	
	void start();
	void stop();
	
   // From NetworkReaderObserver:
   void receivedData();
   
private:
	std::string name;
   std::string host;
   int port;
   
	std::vector<std::string> netData;
	
	NetworkReader * netInput;
	NetworkWriter * netOutput;
	FileReader * fileReader;
	DataHandler * handler;
};

#endif
