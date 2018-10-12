# README #

Software architectures course exercise work implementation of a distributed software architecture and various design patterns in C++11. Includes datagram networking using boost asio and JSON handling using nlohmann::json.

This project has been created for eaducational purposes and may have no other value to anyone.

## What is this repository for? ##

Anyone wishing to learn about software architectural patterns and design patterns, learning C++.

## How do I get set up? ##

* git clone the code,then see the wiki page at https://wiki.oulu.fi/pages/viewpage.action?pageId=39977551
* Uses boost library and boost asio, which needs to be build into a library. Uses boost::system as lib, otherwise headers are enough.
* StudentLayer uses nlohmann::json, and cmake file is configured to integrate to that library. Set up nlohmann::json using cmake or change cmake file accordingly.

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
