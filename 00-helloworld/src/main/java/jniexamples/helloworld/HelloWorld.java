package jniexamples.helloworld;

public class HelloWorld {

    static {
        System.loadLibrary("helloworld");
    }

    public static void main(String[] args) {
        helloJava();
        helloNative();
    }
    
    private static void helloJava() {
        System.out.println("Hello world from Java!");
    }

    private static native void helloNative();
}