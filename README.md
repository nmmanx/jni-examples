# jni-examples
This project gives you some examples of using the [JNI](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/) (Java Native Interface)

### How to build and run?
To build an example, run:
```bash
./gradlew build -p 00-helloworld
```
Then, run it with:
```bash
./gradlew run -p 00-helloworld
```

### Example list
|#| Example         | Aims          |
|-| --------------- | --------------- |
|1| 00-helloworld   | Using JNIEXPORT and JNICALL macros to declare native methods
|2| 01-fibonacci    | Using env->RegisterNatives() instead of JNIEXPORT & JNICALL macros
|3| 02-echo         | Work with many native types: jint, jshort, jlong, jfloat, jdouble, jstring, jboolean, jobject,...
|4| 03-factory      | Work with jmethodID and jfieldID, create a Java object in native code and return back to JVM |
|5| 04-exceptions   | Handle an exception thrown by JVM and throw a new exception to JVM |
|6| 05-work         | Demonstrate using thread in native code (*) |

(*) It's not recommended to spawn thread in native code, using Java Thread whenever it's possible.
