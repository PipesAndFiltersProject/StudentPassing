//
//  DataItem.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 5.12.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "DataItem.h"

namespace ohar_pipes {

	
DataItem::DataItem() {
}

DataItem::DataItem(const DataItem &d)
: id(d.id)
{
}

DataItem::~DataItem() {
   
}

const std::string & DataItem::getId() const {
   return id;
}

void DataItem::setId(const std::string & theId) {
   id = theId;
}

bool DataItem::operator == (const DataItem & item) const {
   return id == item.id;
}

bool DataItem::operator != (const DataItem & item) const {
   return id != item.id;
}


} //namespace