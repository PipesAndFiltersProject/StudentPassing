#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <thread>

#include "sarge.h"

/**
 This is test file generator app for StudentPassing.
 The app generates test data files for each of the four nodes.
 See accompanying README.md for build and usage instructions.
 Uses Sarge for command line option parsing. Get Sarge from
 https://github.com/MayaPosch/Sarge
 Sarge is Copyright (c) 2019, Maya Posch. All rights reserved.
 @author Antti Juustila, (c) 2019 All rights reserved.
 */

//MARK: - Global variables
bool verbose = false; // If true, print out detailed progress info on console.
std::vector<std::string> firstNames;
std::vector<std::string> lastNames;
std::vector<std::string> studyPrograms;
std::vector<int> generatedStudentNumbers;

std::random_device rd;
std::default_random_engine generator(rd());

//MARK: - Func declarations
void generateNames();
int  generateInt(int maxValue);
std::string generateStudentNumber();
const std::string & getFirstName();
const std::string & getLastName();
const std::string & getStudyProgram();
void saveBuffer(bool isFirstRound, const std::string &fileName, std::vector<std::string> & buffer);
std::mutex waitMutex;
std::condition_variable launch;

//void threadFunc() {
//   std::unique_lock<std::mutex> ulock(waitMutex);
//   launch.wait(ulock, [] {
//      
//   });
//}

int main(int argc, char ** argv) {
   
   std::chrono::system_clock::time_point started = std::chrono::system_clock::now();

   //MARK: Handling command line options.
   Sarge sarge;
   sarge.setUsage("./GenerateTestData -[hv]s <number> [-e <number>]");
   sarge.setDescription("A test data generator for StudentPassing system. (c) Antti Juustila, 2019.\nUses Sarge Copyright (c) 2019, Maya Posch All rights reserved.");
   sarge.setArgument("h", "help", "Display help for using GenerateTestData.", false);
   sarge.setArgument("v", "verbose", "Display detailed messages of test data generation process.", false);
   sarge.setArgument("s", "students", "Number of students to generate in test data files.", true);
   sarge.setArgument("e", "exercises", "Number of exercises generated, default is 6 if option not provided.", true);
   sarge.setArgument("b", "bufsize", "Size of the buffer used in generating data", true);
   if (!sarge.parseArguments(argc, argv)) {
      std::cout << "Could not parse arguments" << std::endl;
      return EXIT_FAILURE;
   }
   
   if (sarge.exists("help") || !sarge.exists("students")) {
      sarge.printHelp();
      return EXIT_SUCCESS;
   }
   if (sarge.exists("verbose")) {
      verbose = true;
   }
   int studentCount = 0;
   if (sarge.exists("students")) {
      std::string strValue;
      sarge.getFlag("students", strValue);
      try {
         studentCount = std::stoi(strValue);
         if (studentCount < 1) {
            std::cout << "Could not parse argument" << std::endl;
            return EXIT_FAILURE;
         }
      } catch (...) {
         std::cout << "Could not parse argument" << std::endl;
         return EXIT_FAILURE;
      }
   }
   int exerciseCount = 6;
   if (sarge.exists("exercises")) {
      std::string strValue;
      sarge.getFlag("exercises", strValue);
      try {
         exerciseCount = std::stoi(strValue);
         if (exerciseCount < 1) {
            std::cout << "Could not parse argument" << std::endl;
            return EXIT_FAILURE;
         }
      } catch (...) {
         std::cout << "Could not parse argument" << std::endl;
         return EXIT_FAILURE;
      }
   }
   // Buffer outgoing data to make it faster. Write to file when buffer is full
   // and at the end.
   int bufSize = std::min(studentCount, 100);
   if (sarge.exists("bufsize")) {
      std::string strValue;
      sarge.getFlag("bufsize", strValue);
      try {
         bufSize = std::stoi(strValue);
         if (bufSize < 1) bufSize = 1;
      } catch (...) {
         std::cout << "Could not parse argument" << std::endl;
         return EXIT_FAILURE;
      }
   }

   //MARK: Start generating data.
   std::cout << std::endl << "Generating test data for : " << studentCount << " students, " << exerciseCount << " exercises. " << std::endl;
   
   const std::string SEPARATOR = {"\t"};
   const std::string STUDENT_BASIC_INFO_FILE = {"basic-student-info.txt"};
   const std::string EXAM_INFO_FILE = {"exam-info.txt"};
   const std::string EXERCISE_INFO_FILE = {"exercise-info.txt"};
   const std::string PROJECT_INFO_FILE = {"project-info.txt"};
   
   if (verbose) std::cout << "Creating numbers for students..." << std::endl;
   generatedStudentNumbers.resize(studentCount);
   // Generate student numbers starting from one to studentCount.
   std::iota(generatedStudentNumbers.begin(), generatedStudentNumbers.end(), 1);
   // Shuffle the numbers randomly.
   std::shuffle(generatedStudentNumbers.begin(), generatedStudentNumbers.end(), std::mt19937{std::random_device{}()});
   if (verbose) std::cout << "Generating names used in data..." << std::endl;
   generateNames();
   
   std::vector<std::string> basicInfoBuffer;
   std::vector<std::string> examInfoBuffer;
   std::vector<std::string> exerciseInfoBuffer;
   std::vector<std::string> projectInfoBuffer;
   basicInfoBuffer.resize(bufSize);
   examInfoBuffer.resize(bufSize);
   exerciseInfoBuffer.resize(bufSize);
   projectInfoBuffer.resize(bufSize);

   if (verbose) std::cout << "Starting the test data generating process..." << std::endl;
   std::atomic<bool> isFirstWrite{true};
   int bufferCounter = 0;
   while (!generatedStudentNumbers.empty()) {
      
      if (bufferCounter >= bufSize) {
         if (verbose) std::cout << std::endl << "Saving basic info buffer " << std::endl;
         std::thread thread1( [&isFirstWrite, &STUDENT_BASIC_INFO_FILE, &basicInfoBuffer] {
            saveBuffer(isFirstWrite, STUDENT_BASIC_INFO_FILE, basicInfoBuffer);
         } );
         if (verbose) std::cout << "Saving exam info buffer " << std::endl;
         std::thread thread2( [&isFirstWrite, &EXAM_INFO_FILE, &examInfoBuffer] {
            saveBuffer(isFirstWrite, EXAM_INFO_FILE, examInfoBuffer);
         } );
         if (verbose) std::cout << "Saving exercise info buffer " << std::endl;
         std::thread thread3( [&isFirstWrite, &EXERCISE_INFO_FILE, &exerciseInfoBuffer] {
            saveBuffer(isFirstWrite, EXERCISE_INFO_FILE, exerciseInfoBuffer);
         } );
         if (verbose) std::cout << "Saving project info buffer " << std::endl;
         std::thread thread4( [&isFirstWrite, &PROJECT_INFO_FILE, &projectInfoBuffer] {
            saveBuffer(isFirstWrite, PROJECT_INFO_FILE, projectInfoBuffer);
         } );
         thread1.join(); thread2.join(); thread3.join(); thread4.join();
         isFirstWrite = false;
         basicInfoBuffer.clear();
         examInfoBuffer.clear();
         exerciseInfoBuffer.clear();
         projectInfoBuffer.clear();
         bufferCounter = 0;
         basicInfoBuffer.resize(bufSize);
         examInfoBuffer.resize(bufSize);
         exerciseInfoBuffer.resize(bufSize);
         projectInfoBuffer.resize(bufSize);
      } else {
         const std::string studentNumber(generateStudentNumber());
         if (verbose) std::cout << studentNumber << " ";
         std::string firstName = getFirstName();
         std::string lastName = getLastName();
         std::string studyProgram = getStudyProgram();
         
         // Generate basic info
         std::string entry = studentNumber + SEPARATOR + lastName + " " + firstName + SEPARATOR + studyProgram;
         basicInfoBuffer.push_back(entry);
         
         // Generate exam info
         entry = studentNumber + SEPARATOR + std::to_string(generateInt(5));
         examInfoBuffer.push_back(entry);
         
         // Generate exercise info
         entry = studentNumber;
         for (int count = 0; count < exerciseCount; count++) {
            entry += SEPARATOR + std::to_string(generateInt(5));
         }
         exerciseInfoBuffer.push_back(entry);
         
         // Generate project info
         entry = studentNumber + SEPARATOR + std::to_string(generateInt(5));
         projectInfoBuffer.push_back(entry);
         bufferCounter++;
      }
   }
   if (basicInfoBuffer.size() > 0) {
      if (verbose) std::cout << std::endl << "Saving basic info buffer " << std::endl;
      std::thread thread1( [&isFirstWrite, &STUDENT_BASIC_INFO_FILE, &basicInfoBuffer] {
         saveBuffer(isFirstWrite, STUDENT_BASIC_INFO_FILE, basicInfoBuffer);
      } );
      if (verbose) std::cout << "Saving exam info buffer " << std::endl;
      std::thread thread2( [&isFirstWrite, &EXAM_INFO_FILE, &examInfoBuffer] {
         saveBuffer(isFirstWrite, EXAM_INFO_FILE, examInfoBuffer);
      } );
      if (verbose) std::cout << "Saving exercise info buffer " << std::endl;
      std::thread thread3( [&isFirstWrite, &EXERCISE_INFO_FILE, &exerciseInfoBuffer] {
         saveBuffer(isFirstWrite, EXERCISE_INFO_FILE, exerciseInfoBuffer);
      } );
      if (verbose) std::cout << "Saving project info buffer " << std::endl;
      std::thread thread4( [&isFirstWrite, &PROJECT_INFO_FILE, &projectInfoBuffer] {
         saveBuffer(isFirstWrite, PROJECT_INFO_FILE, projectInfoBuffer);
      } );
      thread1.join(); thread2.join(); thread3.join(); thread4.join();
   }
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::cout <<std::endl << "***** Test data generation finished." << std::endl;
   std::cout << "      Generation took "
         << std::chrono::duration_cast<std::chrono::milliseconds>(now-started).count() << "ms" << std::endl << std::endl;
   return 0;
}

//MARK: - Generators
void generateNames() {
   firstNames = {"Antti", "Tiina", "Pentti", "Risto", "Päivi", "Jaana", "Jani", "Esko", "Hanna", "Oskari"};
   lastNames = {"Virtanen", "Korhonen", "Putkonen", "Karjalainen", "Muttonen", "Suihkari", "Ali Baba", "Johnson", "Ingridsdottir", "Neponen", "Lumikasa"};
   studyPrograms = {"TOL","SO","TT","ENF","TUTA"};
}

int  generateInt(int maxValue) {
   std::uniform_int_distribution<int> distribution(0,maxValue);
   return distribution(generator);
}

std::string generateStudentNumber() {
   std::string theNumber;
   int studentNumber = generatedStudentNumbers.back();
   generatedStudentNumbers.pop_back();
   std::stringstream stream;
   stream << std::setw(5) << std::setfill('0') << studentNumber;
   theNumber = stream.str();
   return theNumber;
}

const std::string & getFirstName() {
   int index = generateInt(firstNames.size()-1);
   return firstNames[index];
}

const std::string & getLastName() {
   int index = generateInt(lastNames.size()-1);
   return lastNames[index];
}

const std::string & getStudyProgram() {
   int index = generateInt(studyPrograms.size()-1);
   return studyPrograms[index];
}


void saveBuffer(bool isFirstRound, const std::string &fileName, std::vector<std::string> & buffer) {
   std::ofstream datafile(fileName, isFirstRound ? std::ios::trunc : std::ios::app);

   if (isFirstRound) {
      if (fileName == "basic-student-info.txt") {
         datafile << "studentdata" << std::endl;
      } else if (fileName == "exam-info.txt") {
         datafile << "examdata" << std::endl;
      } else if (fileName == "exercise-info.txt") {
         datafile << "exercisedata" << std::endl;
      } else if (fileName == "project-info.txt") {
         datafile << "exerciseworkdata" << std::endl;
      }
   }
   // Shuffle the records randomly.
   std::shuffle(buffer.begin(), buffer.end(), std::mt19937{std::random_device{}()});
   auto save = [&datafile](const std::string & entry) { if (entry.length() > 0) datafile << entry << std::endl; };
   std::for_each(buffer.begin(), buffer.end(), save);
   datafile.close();
}
