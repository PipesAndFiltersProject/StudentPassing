//
//  ProcessorNode.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 19.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "ProcessorNode.h"
#include "NetworkReader.h"
#include "NetworkWriter.h"
#include "DataHandler.h"

ProcessorNode::ProcessorNode(const std::string & aName)
: name(aName), handler(0), netInput(0), netOutput(0)
{
}

ProcessorNode::~ProcessorNode() {
   netData.clear();
   delete handler;
   delete netInput;
   delete netOutput;
}

void ProcessorNode::setInputSource(const std::string & hostName, int portNumber) {
   if (netInput) {
      delete netInput;
      netInput = 0;
   }
   netInput = new NetworkReader(hostName, portNumber, *this);
}

void ProcessorNode::setOutputSource(const std::string & hostName, int portNumber) {
	// Create a new Network object for sending data to the datagram socket.
   if (netOutput) {
      delete netOutput;
      netOutput = 0;
   }
   netOutput = new NetworkWriter(hostName, portNumber);
}

void ProcessorNode::setSourceFile(const std::string & fileName) {
	// Create a new FileReader object reading data from the data file.
}


const std::string & ProcessorNode::getName() const {
	return name;
}


void ProcessorNode::start() {
	// Start the listening network reader
	// Start the sending network object
	// Start the file reader
}


void ProcessorNode::stop() {
	// Close all, destroy all.
}

void ProcessorNode::receivedData() {
   if (netInput) {
      std::string data = netInput->read();
   }
}

