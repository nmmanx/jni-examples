package jniexamples.factory;

class Factory {

    public static native Product buildFromNative(long id, String name, String desc, int price);

    public static Product buildFromJava(long id, String name, String desc, int price) {
        return new Product.Builder().setId(id)
                                    .setName(name)
                                    .setDesc(desc)
                                    .setPrice(price)
                                    .build();
    }

    static {
        //System.loadLibrary("factory");
    }
}