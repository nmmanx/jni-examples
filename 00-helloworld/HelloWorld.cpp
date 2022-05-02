#include <iostream>

#include "HelloWorld.h"

JNIEXPORT void JNICALL Java_HelloWorld_helloNative(JNIEnv *, jclass)
{
    std::cout << "Hello world from C++!\n";
}