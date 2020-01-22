# StudentPassing Test Data Generator

This app generates test data for the StudentPassing system.

Generator generates four test files which are used by the StudentPassing Nodes:

* basic-student-info.txt
* exam-info.txt
* exercise-info.txt
* project-info.txt

See the StudentPassing documentation for details on the contents of each file.

The files are generated to the directory where the generator is executed. After generating the files, copy them to the directory where StudentPassing nodes have been configured to read the input data files.

## Building

GenerateTextData uses [Sarge](https://github.com/MayaPosch/Sarge) for parsing command line options. A version of Sarge is included in this project for convenience.

Test data generator CMake file can be used to build it. In the root directory of the TestDataGenerator, do:

1. mkdir build
2. cd build
3. cmake ..
4. make

Obviously you need to have the CMake and a C++17 compiler installed.

There are no other dependencies (e.g. boost, StudentPassing), only C++17 with STL is used in the implementation.

## Running

To generate the test data, run the generator after building it:

```bash
./GenerateTestData -s 50
```
After which you have four files containing test data for 50 students. Each run overwrites the previous data files.

For help on options, do `./GenerateTestData -h`:

```bash
$ ./GenerateTestData -h

A test data generator for StudentPassing system. (c) Antti Juustila, 2019.
Uses Sarge Copyright (c) 2019, Maya Posch All rights reserved.

Usage:
./GenerateTestData -[hv]s <number> [-e <number>]

Options: 
-h   --help          Display help for using GenerateTestData.
-v   --verbose       Display detailed messages of test data generation process.
-s   --students      Number of students to generate in test data files.
-e   --exercises     Number of exercises generated, default is 6 if option not provided.
-b   --bufsize       Size of the buffer used in generating data
```

You could e.g. generate test data for 5000 students with 10 exercises:

```bash
./GenerateTestData -v -s 5000 -e 10
```

Where you get data for *5000 students* and *ten (10) exercise points* for each student in the `exercise-info.txt` data file, with detailed log printed out. 

Then copy the generated data files to the directory where StudentPassing nodes have been configured to read them. In the StudentPassing's spgui app, press the "Read file" button to start processing the test data files.

Check the output file of the last Node to see if everything is there. It is easy to copy the tab separated results with grade to a spreadsheet app (Excel, Apple Numbers, Google Sheet) to check if all the students are there. A test bench should be created for this, which automatically compares the source and end files to see if all data passed all the Nodes until the end.

## Who to contact

(c) 2019-2020  Antti Juustila, firstname dot lastname at oulu dot fi

[Sarge](https://github.com/MayaPosch/Sarge)  is Copyright (c) 2019, Maya Posch, All rights reserved.
