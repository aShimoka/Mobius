# Define the minimum required CMake version.
cmake_minimum_required(VERSION 3.15)

# Declare the Mobius project's target.
project(Mobius)

# Define the CXX standard.
set(CMAKE_CXX_STANDARD 14)


# Include the Headers/ folder to the include path.
include_directories(Headers)

# Add the sources to the compilation.
add_library(Mobius
        Sources/Test.cpp
        )