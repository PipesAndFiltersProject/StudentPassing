//
//  Package.cpp
//  PipesAndFiltersStudentNode
//
//  Created by Antti Juustila on 28.11.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <boost/uuid/uuid_generators.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

#include "Package.h"
#include "Log.h"
#include "DataItem.h"


namespace ohar_pipes {
	
	
	const std::string Package::separatorStr("\\");
	const std::string Package::controlStr = "control";
	const std::string Package::dataStr = "data";
	
	/** Default constructor for Package. Generates a random uuid for the Package. */
	Package::Package()
	: uid(boost::uuids::random_generator()()), dataItem(0)
	{
	}
	
	/** Copy constructor for Package. Copies the passed object.
	 @param p The package to copy from. */
	Package::Package(const Package & p)
	: uid(p.uid), type(p.type), data(p.data), dataItem(0)
	{
		setDataItem(p.getDataItem());
	}
	
	/** A constructor giving an uuid for the otherwise empty package.
	 @param id The uuid for the package. */
	Package::Package(const boost::uuids::uuid & id)
	: uid(id), dataItem(0)
	{
	}
	
	/** A constructor giving type and data for the package. Uuid is generated.
	 @param id The uuid for the package.
	 @param data The data contents of the package. */
	Package::Package(Type ptype, const std::string & d)
	: uid(boost::uuids::random_generator()()), type(ptype), data(d), dataItem(0)
	{
	}
	
	/** A constructor giving several parameters for the package.
	 @param id The uuid for the package.
	 @param ptype The type of the data (control or data package).
	 @param data The data contents of the package. */
	Package::Package(const boost::uuids::uuid & id, Type ptype, const std::string & d)
	: uid(id), type(ptype), data(d), dataItem(0)
	{
	}
	
	/** Destructor deletes the contained dataItem. */
	Package::~Package() {
		delete dataItem;
	}
	
	
	/** For querying the uuid of the package. */
	const boost::uuids::uuid & Package::getUuid() const {
		return uid;
	}
	
	/** For setting the uuid for the package.
	 @param id The uuid for the package. */
	void Package::setUuid(const boost::uuids::uuid & id) {
		uid = id;
	}
	
	/** Can be used to check what kind of a data package is.
	 @return The type of the data package. See type member variable for details. */
	Package::Type Package::getType() const {
		return type;
	}
	
	/** Sets the type of the package.
	 @param t The type for this package. See the documentation of the
	 member variable type for more information about the possible package types. */
	void Package::setType(Type t) {
		type = t;
	}
	
	const std::string & Package::getTypeAsString() const {
		static const std::string empty = "";
		switch (type) {
			case Control: {
				return controlStr;
			}
			case Data: {
				return dataStr;
			}
			default: {
				return empty;
			}
		}
	}
	

	const std::string Package::getData() const {
		return data;
	}
	
	void Package::setData(const std::string & d) {
		data = d;
	}
	
	const DataItem * Package::getDataItem() const {
		return dataItem;
	}
	
	DataItem * Package::getDataItem() {
		return dataItem;
	}
	
	void Package::setDataItem(const DataItem * item) {
		if (dataItem) {
			delete dataItem;
			dataItem = 0;
		}
		if (item) {
			dataItem = item->copy();
		}
	}
	
	
	bool Package::isEmpty() const {
		return (type == NoType && dataItem == 0);
	}
	
	const Package & Package::operator = (const Package & p) {
		uid = p.uid;
		type = p.type;
		data = p.data;
		this->setDataItem(p.getDataItem());
		return *this;
	}
	
	bool Package::operator == (const Package & pkg) const {
		return (uid == pkg.uid);
	}
	
	bool Package::operator == (const std::string & str) const {
		return data == str;
	}
	
	
	const std::string & Package::separator() {
		return separatorStr;
	}
	
	bool Package::parse(const std::string & buffer) {
		std::vector<std::string> strs;
		boost::split(strs, buffer, boost::is_any_of(Package::separator()));
		
		switch (strs.size()) {
			case 3: {
				data = strs.at(2);
				// fallthrough!
			}
			case 2: {
				if (strs.at(1) == controlStr) {
					type = Control;
				} else if (strs.at(1) == dataStr) {
					type = Data;
				} else {
					type = NoType; // Unknown package type, shouldn't happen.
				}
			} // fallthrough!
			case 1: {
				boost::uuids::string_generator gen;
				uid = gen(strs.at(0));
				return true;
			}
		}
		return false;
	}
	
	
} //namespace