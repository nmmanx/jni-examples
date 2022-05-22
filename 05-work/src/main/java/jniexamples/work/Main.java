package jniexamples.work;

public class Main {

    public static void main(String[] args) {
        System.out.println("Main thread: " + Thread.currentThread().getName());
        Work work = Work.getInstance();
        work.start();
        work.waitForCompleted();
    }

    static {
        System.loadLibrary("work");
    }
}