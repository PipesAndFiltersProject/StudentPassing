# README #

Software architectures course exercise work implementation of Pipes & Filters architecture and various design patterns in C++11. Includes datagram networking using boost asio.

## What is this repository for? ###

Anyone wishing to know software architectural patterns and design patterns, learning C++.

## How do I get set up? ###

* Download the code, see the wiki page at https://wiki.oulu.fi/pages/viewpage.action?pageId=39977551
* Uses boost library and boost asio, which needs to be build into a library. Uses boost::system as lib, otherwise headers are enough.

## Who do I talk to? ###

* Repo is owned by Antti Juustila (antti.juustila@oulu.fi)

## Data structures

Packages are sent to network and received from network.

```
{ 
  "package" : "package id as uuid",
  "type" : "command" | "data",
  "payload" : "command value" | "payload in json"
}
```

Payload is in data files and within packages in payload element

```
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

```
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

An example of a command:

```
{
  "package" : "package id as uuid",
  "type" : "command",
  "payload" : "shutdown"
}
```
