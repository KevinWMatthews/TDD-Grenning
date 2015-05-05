#This makefile is currently configure to ONLY run test code!
#Just so I can keep things separate for now :)

all: codeCppUTest
test: codeCppUTest

clean: cleanCodeCppUTest

rebuild: rebuildCodeCppUTest


###
codeCppUTest:
	make --file MakefileCppUTest.make test
# --ignore-errors ?

cleanCodeCppUTest:
	make --file MakefileCppUTest.make clean

#Test this
rebuildCodeCppUTest: cleanCodeCppUTest codeCppUTest
