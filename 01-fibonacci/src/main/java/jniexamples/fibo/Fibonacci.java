package jniexamples.fibo;

public class Fibonacci {
    
    public static final int ALGO_RECURSION  = 1;
    public static final int ALGO_DYNAMIC    = 2;

    public static native int fibo(int n, int algo);

    static {
        System.loadLibrary("fibonacci");
    }
}