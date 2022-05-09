package jniexamples.factory;

public class Main {

    private static void showProduct(Product p) {
        System.out.printf("Product { id=%d, name=\"%s\", desc=\"%s\", price=%d }", 
                          p.getId(), p.getName(), p.getDesc(), p.getPrice());
    }
    
    public static void main(String[] args) {
        Product a = Factory.buildFromJava(0, "ProductA", "Product build from Java", 10);
        //Product b = Factory.buildFromNative(0, "ProductB", "Product build from native", 15);

        showProduct(a);
        //showProduct(b);
    }
}