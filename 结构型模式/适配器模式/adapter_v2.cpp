#include <iostream>

using namespace std;

// USB接口
class USB
{
public:
    virtual void chargeWithUSB() = 0;
    virtual ~USB() {}
};

// TypeC接口
class TypeC
{
public:
    virtual void chargeWithTypeC() = 0;
    virtual ~TypeC() {}
};

// TypeC接口适配USB充电器
class USBAdapter : public USB
{
public:
    void chargeWithUSB() override
    {
        std::cout << "USB Adapter" << std::endl;
    }

};

// 电脑自带实现TypeC接口，拥有一个适配器
class Computer : public TypeC
{
public:
    Computer(USBAdapter* adapter) : adapter(adapter) {}

    void chargeWithTypeC() override
    {
        std::cout << "TypeC" << std::endl;
    }

    void chargeWithUSB()
    {
        adapter->chargeWithUSB();
    }

    ~Computer() { delete adapter; }

private:
    USBAdapter* adapter;
};


int main(int argc, char const *argv[])
{
    int cnt;
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100) 
    {
        std::cout << "输入有误！" << std::endl;
        return 0;
    }
    int type;
    Computer* computer = new Computer(new USBAdapter());
    while (cnt--)
    {
        std::cin >> type;
        if (type == 1) 
        {
            computer->chargeWithTypeC();   
        } 
        else if (type == 2) 
        {
            computer->chargeWithUSB();
        } 
        else 
        {
            std::cout << "输入有误！" << std::endl;
        }
    }
    delete computer;
    return 0;
}