# Use an official Ubuntu as a parent image
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV MY_INSTALL_DIR=/usr/local

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    autoconf \
    libtool \
    pkg-config \
    ninja-build \
    curl \
    protobuf-compiler \
    libprotobuf-dev \
    libpq-dev \
    zlib1g-dev \
    libssl-dev \
    libc-ares-dev

# Install gRPC and Protobuf from source
RUN git clone --recurse-submodules -b v1.40.0 https://github.com/grpc/grpc /grpc && \
    cd /grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DgRPC_ABSL_PROVIDER=package \
          -DgRPC_CARES_PROVIDER=package \
          -DgRPC_PROTOBUF_PROVIDER=package \
          -DgRPC_SSL_PROVIDER=package \
          -DgRPC_ZLIB_PROVIDER=package \
          -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
          ../.. && \
    make -j$(nproc) && \
    make install

# Copy the project files into the Docker image
COPY . /my_grpc_project
WORKDIR /my_grpc_project

# Configure and build the project
RUN cmake -G Ninja .
RUN cmake --build .

# Run the application (example)
CMD ["./MyGRPCProject"]