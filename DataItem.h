//
//  DataItem.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 5.12.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__DataItem__
#define __PipesAndFiltersFramework__DataItem__

#include <ostream>
#include <map>
#include <vector>

namespace ohar_pipes {


/**
 An abstract class, representing the data items the applications can use.
 Application developers should subclass the DataItem class and reimplement
 the abstract methods.
 This class implements the Prototype design pattern.
 @author Antti Juustila
 @version $Revision $
 */
class DataItem {
public:
   DataItem();
   DataItem(const DataItem &d);
   virtual ~DataItem();
   
   virtual const std::string & getId() const;
   virtual void setId(const std::string & theId);

   virtual bool parse(const std::string & fromString, const std::string & contentType) = 0;
   virtual bool addFrom(const DataItem & another) = 0;
   
   virtual DataItem * copy() const = 0;
   
   bool operator == (const DataItem & item) const;
   bool operator != (const DataItem & item) const;

protected:
   std::string id;
private:
};
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__DataItem__) */
