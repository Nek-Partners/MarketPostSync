# Use a base image with a cross-compilation toolchain for Windows
FROM ubuntu:20.04

# Set environment variables to prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary tools
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    git \
    curl \
    zip \
    unzip \
    mingw-w64 \
    gcc-mingw-w64-x86-64 \
    g++-mingw-w64-x86-64 \
    tzdata

# Set environment variables for cross-compilation
ENV CC=x86_64-w64-mingw32-gcc
ENV CXX=x86_64-w64-mingw32-g++
ENV CMAKE_C_COMPILER=x86_64-w64-mingw32-gcc
ENV CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

# Set environment variables for vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
ENV VCPKG_DEFAULT_TRIPLET=x64-windows
ENV VCPKG_ROOT=/vcpkg
ENV PATH=$VCPKG_ROOT:$PATH
ENV VCPKG_FORCE_CMAKE_GENERATOR="Unix Makefiles"

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg
WORKDIR /vcpkg

# Bootstrap vcpkg
RUN ./bootstrap-vcpkg.sh -disableMetrics

# Install project dependencies
COPY vcpkg.json /vcpkg/
RUN ./vcpkg install --triplet x64-windows

# Copy the project files
COPY . /project
WORKDIR /project

# Configure and build the project using Unix Makefiles
RUN cmake -B build -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_BUILD_WITH_INSTALL_RPATH=TRUE
RUN cmake --build build --config Release
