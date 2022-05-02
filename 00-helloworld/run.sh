#!/bin/bash

set -e

JAVA_HOME=`readlink -f /usr/bin/java | xargs dirname | xargs dirname`
echo "JAVA_HOME: $JAVA_HOME"

# Compile java code
javac HelloWorld.java

# Compile cpp code
g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux HelloWorld.cpp -o HelloWorld.o
g++ -shared HelloWorld.o -o libhelloworld.so

# Run java code
echo "=== OUTPUT ==="
java -Djava.library.path=`pwd` HelloWorld