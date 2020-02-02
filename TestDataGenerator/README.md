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

There are no other dependencies (e.g. Boost, StudentPassing), only C++17 with STL is used in the implementation.

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

## About threading

The generator uses threads to write to the data files. This is absolutely *not* needed: generating 5000 students takes about 250ms using my MacBook Pro (13-inch, 2018), 2,3 GHz four core Intel Core i5, 1 Tb SSD disk. Machines with HDDs would be slower.

However, I wanted to see how much of that 250ms I can squeeze off with four threads, each writing  to their own data file from the RAM buffers.

When the code was not using threads, I run test runs with parameters ` ./GenerateTestData -s 5000 -e 10 -b 500`. On average, the time to generate the data took around 250ms.

When I implemented the four data writing threads, it took around 170ms in average to run the tool. So this was about 30% faster. 

*But* -- I had an implementation where the threads were *created* and executed when the memory buffer was full, and saving the file done in a lambda function:

```C++
if (bufferCounter >= bufSize) {
   std::thread thread1( [&isFirstWrite, &STUDENT_BASIC_INFO_FILE, &basicInfoBuffer] {
     saveBuffer(isFirstWrite, STUDENT_BASIC_INFO_FILE, basicInfoBuffer);
   });
// ...
```
With these parameters, it meant that for each file, with 5000 students and memory buffer size of 500 == 10 threads were created and executed, totalling 40 (10 for each four files) threads were created when running the tool.

Creating a thread *takes time*. Lots of time, thousands of processor cycles, depending on your setup (see e.g. this [blog post](https://lemire.me/blog/2020/01/30/cost-of-a-thread-in-c-under-linux/).

I changed the implementation to create the four threads *only once*, and then woken up every time the data buffers were full.

```C++
std::vector<std::thread> savers;
savers.push_back(std::thread(&threadFuncSavingData, std::ref(threadsFinished), std::cref(STUDENT_BASIC_INFO_FILE), std::ref(basicInfoBuffer)));

//...

if (bufferCounter >= bufSize) {
   if (verbose) std::cout << std::endl << "Activating buffer writing threads..." << std::endl;
   startWriting = true;
   threadsFinished = 0;
   int currentlyFinished = 0;
   launchWrite.notify_all(); // <<<< Activating the threads waiting for the condition variable...

```
And then the main thread waits for the writers to finish their job before filling the memory buffers again.

```C++
   // Wait for the writer threads to finish.
   while (threadsFinished < 4) {
      std::unique_lock<std::mutex> ulock(fillBufferMutex);
      writeFinished.wait(ulock, [&] {
         return currentlyFinished != threadsFinished;
      });
   currentlyFinished = threadsFinished;
   }
```
Obviously the file saving threads notify the main thread about them finishing the file ops using a condition variable.

Condition variables and mutexes were used for this. This resulted in more complicated but still faster implementation, taking usually less than 130ms to execute the tool. Another 25% off execution time, compared to first implementation using threads, and 50% faster compared to the original, one thread implementation doing all file writing in sequence.

| Execution | Time | Faster than sequential |
|---------|----------|---------|
| Sequential | ~250ms |   n/a  |
| Threads, created | ~170ms | ~30% |
| Threads, created once | <130ms | ~50% |

Summarizing; I surely managed to make it faster with threads, but at least with these data numbers and machine, it actually doesn't matter.

## Who to contact

(c) 2019-2020  Antti Juustila, firstname dot lastname at oulu dot fi

[Sarge](https://github.com/MayaPosch/Sarge)  is Copyright (c) 2019, Maya Posch, All rights reserved.
