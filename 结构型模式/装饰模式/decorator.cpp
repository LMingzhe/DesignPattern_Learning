#include <iostream>
#include <memory>

// 咖啡接口
class Coffee
{
public:
    virtual void brew() = 0;
    virtual ~Coffee() {}
};

// 具体的黑咖啡类
class BlackCoffee : public Coffee
{
public:
    void brew() override
    {
        std::cout << "Brewing Black Coffee" << std::endl;
    }
};

// 具体的拿铁类
class Latte : public Coffee
{
public:
    void brew() override
    {
        std::cout << "Brewing Latte" << std::endl;
    }
};

// 装饰者抽象类
class Decorator : public Coffee
{
public:
    Decorator(std::unique_ptr<Coffee> coffee) : coffee(std::move(coffee)) {}

    void brew() override
    {
        if (coffee) coffee->brew();
    }

protected:
    std::unique_ptr<Coffee> coffee; 
};

// 具体的牛奶装饰者类
class MilkDecorator : public Decorator
{
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() override
    {
        Decorator::brew();
        std::cout << "Adding Milk" << std::endl;
    }
};

// 具体的糖装饰者类
class SugarDecorator : public Decorator
{
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() override
    {
        Decorator::brew();
        std::cout << "Adding Sugar" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    int coffeeType, condimentType;
    while (std::cin >> coffeeType >> condimentType)
    {
        std::unique_ptr<Coffee> coffee;

        if (coffeeType == 1)
        {
            coffee = std::make_unique<BlackCoffee>();
        }
        else if (coffeeType == 2)
        {
            coffee = std::make_unique<Latte>();
        }
        else
        {
            std::cout << "输入错误！" << std::endl;
            continue;
        }

        if (condimentType == 1)
        {
            coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        }
        else if (condimentType == 2)
        {
            coffee = std::make_unique<SugarDecorator>(std::move(coffee));
        }
        else
        {
            std::cout << "输入错误！" << std::endl;
            continue;
        }

        coffee->brew();
    }

    return 0;
}
