echo "Run this in the build directory of TestDataGenerator."
echo "Removing output files..."
rm test-*.txt
echo "Running threaded tests..."
for ((i = 0; i < 20; i++)); do ./GenerateTestData -s 50000 -e 10 -b 500 >> test-par.txt; done
echo "Running sequential tests..."
for ((i = 0; i < 20; i++)); do ./GenerateTestData -zs 50000 -e 10 -b 500 >> test-seq.txt; done
echo "-- Tests done -- "
open test-*.txt
