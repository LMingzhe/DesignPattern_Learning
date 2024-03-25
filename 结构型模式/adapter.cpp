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
};

// 实现USB接口的充电功能
class USBCharger : public USB
{
public:
    void chargeWithUSB() override
    {
        std::cout << "USB Adapter" << std::endl;
    }
};

// 实现TypeC接口的充电功能
class TypeCCharger : public TypeC
{
public:
    void chargeWithTypeC() override
    {
        std::cout << "TypeC" << std::endl;
    }
};

// TypeC接口适配USB充电器
class TypeCAdapter : public USB
{
public:
    TypeCAdapter(USB* usbcharger) : usbCharger(usbcharger) {}

    void chargeWithUSB() override
    {
        usbCharger->chargeWithUSB();
    }

    ~TypeCAdapter() { delete usbCharger; }

private:
    USB* usbCharger;
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
    while (cnt--)
    {
        std::cin >> type;
        if (type == 1) 
        {
            TypeC* typeCcharger = new TypeCCharger();
            typeCcharger->chargeWithTypeC();
            delete typeCcharger;
        } 
        else if (type == 2) 
        {
            USB* typeCadapter = new TypeCAdapter(new USBCharger());
            typeCadapter->chargeWithUSB();
            delete typeCadapter;
        } 
        else 
        {
            std::cout << "输入有误！" << std::endl;
        }
    }
    return 0;
}