package jniexamples.work;

public interface IWorkListener {
    public void onStart();
    public void onProgress(float percent);
    public void onCompleted(boolean success);
}
