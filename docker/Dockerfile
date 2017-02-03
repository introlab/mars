FROM ubuntu:16.04

# Install build dependencies
RUN apt-get update && apt-get install -y \
      build-essential \
      cmake \
      git \
      libasound2-dev \
      libconfig++-dev \
      libfftw3-dev

# Clone source code
WORKDIR /root/
RUN git clone -b dev https://github.com/introlab/mars.git

# Build MARS project
WORKDIR /root/mars
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)
