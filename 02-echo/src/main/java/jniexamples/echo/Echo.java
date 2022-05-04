package jniexamples.echo;

public class Echo {

    public static void main(String[] args) {
        sendInteger(1, (short)2, 3L);
        sendDecimal(1.5f, 5.3d);
        sendChar('m');
        sendString("Java string");
        sendBoolean(true);
        sendIntegerArray(new int[] { -1, 0, 1});
        sendObject(new JavaObject("java object"));
        sendObjectArray(new JavaObject[] { new JavaObject("obj1"), new JavaObject("obj2") });
    }
    
    public static native void sendInteger(int n1, short n2, long n3);

    public static native void sendDecimal(float f1, double f2);

    public static native void sendChar(char ch);

    public static native void sendString(String str);

    public static native void sendBoolean(boolean b);

    public static native void sendIntegerArray(int[] arr);

    public static native void sendObject(JavaObject obj);

    public static native void sendObjectArray(JavaObject[] objs);

    static {
        System.loadLibrary("echo");
    }
}
