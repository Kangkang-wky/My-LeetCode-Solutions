#include "../include/help.h"

class AbstractProductA {
public:
    virtual void show() = 0;

    virtual ~AbstractProductA() = default;
};

class AbstractProductB {
public:
    virtual void show() = 0;

    virtual ~AbstractProductB() = default;
};

class ProductA1 : public AbstractProductA {
public:
    void show() override {
        std::cout << "ProductA1" << std::endl;
    }
};

class ProductA2 : public AbstractProductA {
public:
    void show() override {
        std::cout << "ProductA2" << std::endl;
    }
};

class ProductB1 : public AbstractProductB {
public:
    void show() override {
        std::cout << "ProductB1" << std::endl;
    }
};

class ProductB2 : public AbstractProductB {
public:
    void show() override {
        std::cout << "ProductB2" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProductA> createProductA() = 0;

    virtual std::unique_ptr<AbstractProductB> createProductB() = 0;

    virtual ~AbstractFactory() = default;
};

class Factory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() override {
        return std::make_unique<ProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() override {
        return std::make_unique<ProductB1>();
    }
};

class Factory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() override {
        return std::make_unique<ProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() override {
        return std::make_unique<ProductB2>();
    }
};

int main(){

	auto factory1 = std::make_unique<Factory1>();
    auto productA1 = factory1->createProductA();
    auto productB1 = factory1->createProductB();
    productA1->show();
    productB1->show();

    auto factory2 = std::make_unique<Factory2>();
    auto productA2 = factory2->createProductA();
    auto productB2 = factory2->createProductB();
    productA2->show();
    productB2->show();
	return 0;
}
