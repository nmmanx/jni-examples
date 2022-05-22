package jniexamples.exceptions;

public class Main {

    public static void main(String[] args) {
        Helper helper = new Helper();
        try {
            doSomething(helper);
        } catch (Exception e) {
            System.out.println("Main.doSomething() throw an exception:");
            e.printStackTrace();
        }
    }

    public static native void doSomething(Helper helper) throws Exception;

    static {
        System.loadLibrary("exceptions");
    }
}