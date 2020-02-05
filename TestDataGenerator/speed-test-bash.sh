echo "Run this in the build directory of TestDataGenerator."
echo "Removing output files..."
rm test-*.txt
echo "Running threaded tests..."
for value in {1..20}
do
 ./build/Debug/GenerateTestData -s 50000 -e 10 -b 500 >> test-par.txt
done
echo "Running sequential tests..."
for value in {1..20}
do
 ./build/Debug/GenerateTestData -zs 50000 -e 10 -b 500 >> test-seq.txt
done
echo "-- Tests done -- "
notepad test-*.txt
