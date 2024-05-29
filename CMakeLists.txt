cmake_minimum_required(VERSION 3.28.1)

# Set the CMake policy CMP0068 to NEW
if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()

project(POSIntegrate)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable RPATH settings
set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
set(CMAKE_INSTALL_NAME_DIR "@rpath")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(proto)
add_subdirectory(server)
#add_subdirectory(client)