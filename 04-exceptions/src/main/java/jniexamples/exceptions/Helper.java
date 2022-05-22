package jniexamples.exceptions;

public class Helper {
    
    public void help() {
        throw new IllegalArgumentException("An IllegalArgumentException from JVM");
    }
}
