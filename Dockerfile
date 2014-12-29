FROM ubuntu:14.10
MAINTAINER Filipe Varela <fcvarela@gmail.com>

ENV DEBIAN_FRONTEND noninteractive

# set locale
RUN locale-gen en_US en_US.UTF-8

# freshen up
RUN apt-get update
RUN apt-get -y upgrade

# install dependencies
RUN apt-get install -y clang cmake pkg-config wget zip libglfw3-dev libxinerama-dev libxi-dev opencl-headers ocl-icd-libopencl1 ocl-icd-opencl-dev libglew-dev libxrandr-dev libxcursor-dev cxxtest python2.7-dev libassimp-dev zlib1g-dev libboost-python-dev libboost-filesystem-dev libboost-system-dev libglm-dev

# add source folder
VOLUME /glsg/
WORKDIR /glsg/tmp

# run it
CMD cmake ..; make -j8

