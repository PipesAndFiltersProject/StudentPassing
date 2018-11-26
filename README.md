# README #

Software architectures course exercise work StudentPassing is an implementation of a distributed software architecture and various design patterns in C++14. Includes datagram networking using boost asio and JSON for handling data received and sent between components.

This project has been created for eaducational purposes and may have no other value to anyone.

## What is this repository for? ##

Anyone wishing to learn about software architectural patterns and design patterns, learning C++, creating and using libraries.

## Dependencies ##

Uses the following components and tools:

* A C++ compiler supporting C++ 14.
* boost 1.68.0 or newer. You need to build system library from boost. Build using c++14 (e.g. b2 cxxflags="-std=c++14".). For more information, see boost getting started guide.
* nlohmann::json for parsing and creating JSON.
* g3logger for logging events in all components of this software. Also requires C++ v 14.
* Qt for the GUI apps using the other components of the system.
* cmake for building the system in different platforms and with different compilers.

## How do I get set up? ##

What to do:

* git clone the code,then see the wiki page at https://wiki.oulu.fi/pages/viewpage.action?pageId=39977551
* Uses boost system library and boost asio, which needs to be build into a library.
  * use bootstrap.sh (.bat) to set up boost, then b2 cxxflags="-std=c++14" to build boost (system library at least), then b2 install to install boost headers and lib(s).
* Uses nlohmann::json, and cmake file is configured to integrate to that library.
  * Set up nlohmann::json using cmake or change cmake file accordingly.
* Uses also g3logger, which needs to be build and package made (make package)
* Check out the CMakeLists.txt files in different components of StudentPassing to see the package dependencies of the system. 

## Who do I talk to? ##

* Repo is owned by Antti Juustila (antti.juustila@oulu.fi)

## License ##

(c) Antti Juustila 2014-2018. This software is licensed in [GPL version 2 or later](https://opensource.org/licenses/gpl-2.0.php).

## Data structures

Packages are sent to network and received from network.

```JSON
{ 
  "package" : "package id as uuid",
  "type" : "command" | "data",
  "payload" : "command value" | "payload in json"
}
```

Payload is in data files and within packages in payload element

```JSON
{
   "id" : 12345,
   "name" : "Test Student",
   "studyprogram" : "TOL",
   "exampoints" : 15,
   "exercisepoints" : 8,
   "courseprojectpoints" : 16,
   "grade" : 3
}
```
And combined example (data sent/received):

```JSON
{ 
  "package" : "package id as uuid",
  "type" : "data",
  "payload" :
     {
        "id" : 12345,
        "name" : "Test Student",
        "studyprogram" : "TOL",
        "exampoints" : 15,
        "exercisepoints" : 8,
        "courseprojectpoints" : 16,
        "grade" : 3
    }
}
```

Note that in the data payload for student data, only student id is compulsory. Different nodes provide different data items, and combine data they received from previous node(s) to the data the node itself produces. This combined data is then sent ahead to the next node(s).

An example of a command:

```JSON
{
  "package" : "package id as uuid",
  "type" : "command",
  "payload" : "shutdown"
}
```
