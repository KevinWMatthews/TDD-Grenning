#!/bin/bash

#Later I want to figure out how to put this in the share folder and make it work with any project.
#Will need to get the directory from the user, too

NAME=$1
while [ -z "$NAME" ]
do
  read -p "Please enter a test file name: " NAME
done

testPrefix=Test_
templateHFile=Templates/Test_Name.h
templateSrcFile=Templates/Test_Name.cpp
outputHFile=$testPrefix"$NAME".h
outputSrcFile=$testPrefix"$NAME".cpp

sedCommands="s/Name/$NAME/g"

GenerateFile()
{
  if [ -f $2 ]; then
    echo "$2 already exists! Skipping."
  else
    echo "Creating $2"
    sed $sedCommands <$1 >$2
  fi
}

GenerateFile $templateHFile $outputHFile
GenerateFile $templateSrcFile $outputSrcFile
