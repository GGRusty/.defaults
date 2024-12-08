#!/bin/bash
project_name=$1
if [ -z "$project_name" ]; then
    echo "Usage: default_init <project_name>"
    exit 1
fi

# Create project directory
mkdir -p "$project_name"
cd "$project_name" || exit

# Create src directory
mkdir -p src

# Copy template files
cp -r ~/.defaults/cpp_template/* .
cp ~/.defaults/cpp_template/.clang* .

# Replace project name in CMakeLists.txt
sed -i '' "s/my_cpp_project/$project_name/g" CMakeLists.txt

# Create build directory and generate compile_commands.json
mkdir build
cd build || exit
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cd ..
ln -s build/compile_commands.json .

echo "Project '$project_name' has been initialized!"
echo "Project structure created and CMake configured."
echo "cd into $project_name and start writing bugs!"
