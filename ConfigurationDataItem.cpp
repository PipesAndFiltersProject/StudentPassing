//
//  ConfigurationDataItem.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 25.2.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Log.h"
#include "ConfigurationDataItem.h"

namespace OHARBase {

	const std::string ConfigurationDataItem::TAG{"ConfigReader"};
	
	void ConfigurationDataItem::setItemName(const std::string &item) {
		itemName = item;
	}
	
	void ConfigurationDataItem::setItemValue(const std::string &value) {
		itemValue = value;
	}

	const std::string & ConfigurationDataItem::getItemName() const {
		return itemName;
	}

	const std::string & ConfigurationDataItem::getItemValue() const {
		return itemValue;
	}


	bool ConfigurationDataItem::parse(const std::string & fromString, const std::string & contentType) {
		std::vector<std::string> strings;
		boost::split(strings, fromString, boost::is_any_of("\t"));
		Log::getInstance().entry(TAG, "String item count: %d", strings.size());
		if (contentType == "nodeconfiguration") {
			setItemName(strings.at(1));
			setItemValue(strings.at(2));
			return true;
		}
		return false;
	}
	
	bool ConfigurationDataItem::addFrom(const DataItem & another) {
		// No need for this (?)
		return false;
	}

	DataItem * ConfigurationDataItem::copy() const {
		return new ConfigurationDataItem(*this);
	}
	
	
}
