//
//  NetworkWriter.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetworkWriter__
#define __PipesAndFiltersFramework__NetworkWriter__

#include <queue>
#include <condition_variable>

#include "Networker.h"
#include "Package.h"

namespace ohar_pipes {
	
	/** NetworkWriter handles the sending of the data packages to the next node.
	 It contains a queue of data packages to send. Sending happens in a separate thread
	 in order to keep the main thread of the processornode responsive to user actions as well
	 as to enable handling and receiving the data from other node separately.
	 @author Antti Juustila
	 @version $Revision $
	 */
	class NetworkWriter : public Networker {
	public:
		NetworkWriter(const std::string & hostName);
		NetworkWriter(const std::string & hostName, int portNumber);
		~NetworkWriter();
		
		virtual void start();
		virtual void stop();
		
		void write(const Package & data);
		
	private:
		NetworkWriter() = delete;
		NetworkWriter(const NetworkWriter &) = delete;
		const NetworkWriter & operator =(const NetworkWriter &) = delete;
		
		void threadFunc();
		
	private:
		
		/** Contains the data which is currenty being sent, in a string. */
		std::string currentlySending;
		/** The queue of data packages to send. */
		std::queue<Package> msgQueue;
		/** The mutex used to guard access to the package queue. */
		std::mutex guard;
		/** The condition variable used to signal the sending thread that new data is available
		 in the queue. */
		std::condition_variable condition;
		/** Logging tag. */
		const std::string TAG;
	};
	
}


#endif /* defined(__PipesAndFiltersFramework__NetworkWriter__) */
