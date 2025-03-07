#include "../include/help.h"
   
class Product {
public:
    virtual void show() = 0;

    virtual ~Product() = default;
};

class ProductA : public Product {
public:
    void show() override {
        std::cout << "ProductA" << std::endl;
    }
};

class ProductB : public Product {
public:
    void show() override {
        std::cout << "ProductB" << std::endl;
    }
};

class Factory {
public:
    virtual std::unique_ptr<Product> createProduct() = 0;

    virtual ~Factory() = default;
};

class FactoryA : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductA>();
    }
};

class FactoryB : public Factory {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ProductB>();
    }
};

int main(){
	auto factoryA = std::make_unique<FactoryA>();
    auto productA = factoryA->createProduct();
    productA->show();

    auto factoryB = std::make_unique<FactoryB>();
    auto productB = factoryB->createProduct();
    productB->show();
	return 0;
}