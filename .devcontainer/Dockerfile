FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

# Install necessary build tools
RUN apt-get update 
RUN apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get -y install cmake

# Download and build Google Test (simplified)
RUN git clone https://github.com/google/googletest.git
WORKDIR googletest
RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make
RUN make install


