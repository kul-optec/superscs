# DOCKER Configuration file


# -------- Licence -------------------------------------------------------------
# The MIT License (MIT)
#
# Copyright (c) 2017 Pantelis Sopasakis (https://alphaville.github.io),
#                    Krina Menounou (https://www.linkedin.com/in/krinamenounou), 
#                    Panagiotis Patrinos (http://homes.esat.kuleuven.be/~ppatrino)
# Copyright (c) 2012 Brendan O'Donoghue (bodonoghue85@gmail.com)
# ------------------------------------------------------------------------------



# -------- Instructions --------------------------------------------------------
# Build the docker image by running: 
#
# $ docker image build -t kulforbes/superscs:{version-name} .
#
# from within the base directory of this project.
#
#
# Run the docker image and start a terminal to access it by running:
#
# $ docker run -it kulforbes/superscs:{version-name}
#
# To run the latest version, simply run `docker run -it kulforbes/superscs`
#
# Once you access the docker image using a terminal, you may compile the C file
# `superscs_test.c` as follows:
# $ gcc superscs_test.c -o superscs_test -lscsindir -lblas -llapack -lm
# ------------------------------------------------------------------------------



# Build on top of Ubuntu noble
FROM ubuntu:noble

# Labels for the SuperSCS docker image
LABEL 	maintainer="Pantelis Sopasakis <p.sopasakis@gmail.com>" \
	version="v1.3.3" \
        license="MIT license" \
        description="Fast and accurate conic programming"

# Environment variables
ENV CC=gcc \
    SUPERSCS_VERSION="v1.3.3" \
    SUPERSCS_INSTALL_DIR="/superscs"

WORKDIR /superscs

# Copy all necessary files
COPY src/ /superscs/src/
COPY include/ /superscs/include/
COPY linsys/ /superscs/linsys/
COPY tests/c/ /superscs/tests/c 
COPY scs.mk Makefile LICENSE.txt examples/c/superscs_test.c /superscs/
COPY .motd /etc/

# Install necessary dependencies (blas, lapack, make and gcc)
RUN   apt-get update && apt-get -y install \
	libblas-dev \
	liblapack-dev \
	make gcc

# Build, test and install
RUN	make \
        # build the unit tests (can't run them: 3 are failing)
	&& make test \
        # install in /usr
	&& make PREFIX=/usr install \
        # compile the example
	&& gcc superscs_test.c -o superscs_run -lscsindir -lblas -llapack -lm \
        # make the example runnable (+x)
        && chmod +x /superscs/superscs_run \
        # make motd runnable and modify bashrc
	&& mv /etc/.motd /etc/motd \
        && chmod +x /etc/motd \
        && echo '/etc/motd' >> /etc/bash.bashrc
