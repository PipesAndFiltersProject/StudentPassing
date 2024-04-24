echo "Downloading boost 1.72.0..."
wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.zip
echo "Cloning nlohmann::json..."
git clone --depth 1 https://github.com/nlohmann/json.git
echo "Cloning g3log..."
git clone --depth 1 https://github.com/KjellKod/g3log.git
echo "Cloning ProcessorNode..."
git clone https://github.com/PipesAndFiltersProject/ProcessorNode
echo "Cloning StudentNodeElements..."
git clone https://github.com/PipesAndFiltersProject/StudentNodeElements
echo "Cloning StudentPassing..."
git clone https://github.com/PipesAndFiltersProject/StudentPassing
echo "Cloning StudentPassing Configurator..."
git clone https://github.com/PipesAndFiltersProject/SPConfigurator
echo "Cloning DirWatcher demo app..."
git clone https://github.com/PipesAndFiltersProject/DirWatcher
echo "------------------------------------------------------------------"
echo "DONE, all libraries and apps are here. Now you need to"
echo "1. Unzip, build and install Boost, see Boost getting started docs."
echo "2. Build and install g3log using CMake."
echo "3. Build and install nlohmann::json using CMake."
echo "4. Build and install ProcessorNode using CMake."
echo "5. Build and install StudentNodeElements using CMake."
echo "6. Build, configure and run StudentPassing app"
echo "Also you can generate IDE projects from 4-6 to view the code."
echo "------------------------------------------------------------------"

