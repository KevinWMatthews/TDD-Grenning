# Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE =
endif

#Can currently only nest three subdirectories (see clean_path in MakefileWorker.make)
#until I figure out how to loop it properly.

### Directory structure ###
ROOT_DIR=../..
TEST_DIR=.
TARGET_NAME=Example
TEST_TARGET_NAME=MidLevel


# List all production code folders
SRC_DIRS=$(ROOT_DIR)/src
INC_DIRS=$(ROOT_DIR)/inc
LIB_DIRS=
#Static library names without lib prefix and .a suffix
LIB_LIST=
OBJ_DIR=$(ROOT_DIR)/obj
TARGET_DIR=$(ROOT_DIR)/build

# List all user unit test folders
TEST_SRC_DIRS=$(TEST_DIR)/src
TEST_INC_DIR=$(TEST_DIR)/inc
TEST_LIB_DIRS=$(TEST_DIR)/lib
#Static library names without lib prefix and .a suffix
TEST_LIB_LIST=
TEST_TARGET_DIR=$(TEST_DIR)/build
TEST_OBJ_DIR=$(TEST_DIR)/obj


# CppUTest test harness source code
CPPUTEST_LIB_LIST=CppUTest CppUTestExt
OSTYPE:=$(shell uname -o)
ifeq ("$(OSTYPE)","Cygwin")
# Cygwin's linker can't seem to find CppUTest libraries even though they're in the PATH...
CPPUTEST_LIB_DIR=/usr/local/lib
endif

### Compiler tools ###
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++


# Do the real work
include $(ROOT_DIR)/test/MakefileWorker.make
