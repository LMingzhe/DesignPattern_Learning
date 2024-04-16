#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

// 模板类
class CoffeeMakerSystem
{
private:
    string name;
    
public:
    CoffeeMakerSystem(const string& name) : name(name) {}

    virtual void grind()
    {
        cout << "Grinding coffee beans" << endl;
    }

    virtual void brew()
    {
        cout << "Brewing coffee" << endl;
    }    

    virtual void add()
    {
        cout << "Adding condiments" << endl;
    }

    virtual void makeCoffee()
    {
        cout << "Making " << name << ":" << endl;
        grind();
        brew();
        add();
        cout << endl;
    }
};

// 具体类
class AmericanCoffeeMaker : public CoffeeMakerSystem
{
public:
    AmericanCoffeeMaker() : CoffeeMakerSystem("American Coffee") {}
};

// 具体类
class LatteCoffeeMaker : public CoffeeMakerSystem
{
public:
    LatteCoffeeMaker() : CoffeeMakerSystem("Latte") {}

    void add() override
    {
        cout << "Adding milk" << endl;
        cout << "Adding condiments" << endl;
    }
};

int main(int argc, char const *argv[])
{
    int type;
    CoffeeMakerSystem* cms;
    while (cin >> type)
    {
        if (type == 1)
        {
            cms = new AmericanCoffeeMaker();
            cms->makeCoffee();
        }
        else if (type == 2)
        {
            cms = new LatteCoffeeMaker();
            cms->makeCoffee();
        }
        else
        {
            cout << "输入错误！请重新输入！" << endl;
            continue;
        }
    }
    delete cms;
    cms = nullptr;
    return 0;
}
