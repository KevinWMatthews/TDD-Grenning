#This makefile is currently rigged up to run the test executable ONLY.
#It will compile all of the source code in the process of doing this.

TESTS_TO_RUN=Default LowLevel MidLevel

.PHONY: $(TESTS_TO_RUN)

all: $(TESTS_TO_RUN)

test: $(TESTS_TO_RUN)

clean:
#TODO how to avoid repetition?
	make --file MakefileCppUTest.make clean
	make -C LowLevel --file MakefileCppUTest.make clean
	make -C MidLevel --file MakefileCppUTest.make clean

rebuild: clean all

rebuildt: clean test

# Compile and run production code
# run:
# 	make -C src --file MakefileCppUTest.make run


#Makefile debug options
#TODO make sure to point this to the folder that you want...
filelist:
	make -C MidLevel --file MakefileCppUTest.make filelist

dirlist:
	make -C MidLevel --file MakefileCppUTest.make dirlist

# flags:
# 	make -C src --file MakefileCppUTest.make flags

# colortest:
# 	make -C src --file MakefileCppUTest.make colortest

# help:
# 	make -C src --file MakefileCppUTest.make help


Default:
	make --file MakefileCppUTest.make test

LowLevel:
	make -C LowLevel --file MakefileCppUTest.make test

MidLevel:
	make -C MidLevel --file MakefileCppUTest.make test
