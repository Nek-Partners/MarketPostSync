# Use the latest Windows Server Core image with CMake and Visual Studio Build Tools
FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Install Chocolatey
RUN powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

# Install CMake, Visual Studio Build Tools, and additional packages
RUN choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System' && \
    choco install -y visualstudio2019buildtools --package-parameters "--includeRecommended --includeOptional --add Microsoft.VisualStudio.Workload.VCTools" && \
    choco install -y git && \
    choco install -y grpc && \
    choco install -y mysql-connector-cpp

# Set the working directory
WORKDIR /app

# Copy the project files to the container
COPY . .

# Create the build directory
RUN mkdir build

# Configure the project with the necessary libraries
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -DgRPC_DIR="C:/Program Files (x86)/grpc" -DMySQL_DIR="C:/Program Files/MySQL/MySQL Connector C++ 8.0"

# Build the project
RUN cmake --build build --config Release

# Set the entrypoint to the built application (assuming the executable is named 'app.exe')
ENTRYPOINT ["build\\Release\\app.exe"]
