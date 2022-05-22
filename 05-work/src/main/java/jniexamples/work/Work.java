package jniexamples.work;

public final class Work implements IWorkListener {
    private static Work sInstance;

    private Work() {
    }

    synchronized public static Work getInstance() {
        if (sInstance == null) {
            sInstance = new Work();
        }
        return sInstance;
    }
    
    public native void start();
    public native void waitForCompleted();

    @Override
    public void onStart() {
        System.out.println("Work started on thread: " + Thread.currentThread().getName());
    }
    
    @Override
    public void onProgress(float percent) {
        System.out.println("Progress: " + String.valueOf((int)(percent * 100.0f)) + "%");
        System.out.flush();
    }

    @Override
    public void onCompleted(boolean success) {
        System.out.println("Done!");
    }
}
