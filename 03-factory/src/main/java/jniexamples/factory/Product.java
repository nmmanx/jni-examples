package jniexamples.factory;

public class Product {
    private long mId;
    private String mName;
    private String mDesc;
    private int mPrice;

    private Product() {}

    public static class Builder {
        private long mId;
        private String mName;
        private String mDesc;
        private int mPrice;

        public Builder() {
            this.mId = 0;
            this.mName = "";
            this.mDesc = "";
            this.mPrice = 0;
        }

        Builder setId(long id) {
            this.mId = id;
            return this;
        }

        Builder setName(String name) {
            this.mName = name;
            return this;
        }

        Builder setDesc(String desc) {
            this.mDesc = desc;
            return this;
        }

        Builder setPrice(int price) {
            this.mPrice = price;
            return this;
        }

        Product build() {
            Product product = new Product();
            product.mId = this.mId;
            product.mName = this.mName;
            product.mDesc = this.mDesc;
            product.mPrice = this.mPrice;
            return product;
        }
    }

    public long getId() {
        return this.mId;
    }

    public String getName() {
        return this.mName;
    }

    public String getDesc() {
        return this.mDesc;
    }

    public int getPrice() {
        return this.mPrice;
    }
}
