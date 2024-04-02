#include <iostream>

using namespace std;

class Switch
{
public:
    virtual void close() = 0;
    virtual ~Switch() {}
};

class AirConditionerSwitch : public Switch
{
public:
    void close() override
    {
        std::cout << "Air Conditioner is turned off." << std::endl;
    }

    ~AirConditionerSwitch() override {}
};

class DeskLampSwitch : public Switch
{
public:
    void close() override
    {
        std::cout << "Desk Lamp is turned off." << std::endl;
    }

    ~DeskLampSwitch() override {}
};

class TelevisionSwitch : public Switch
{
public:
    void close() override
    {
        std::cout << "Television is turned off." << std::endl;
    }

    ~TelevisionSwitch() override {}
};

class AllSwitch : public Switch
{
public:
    void close() override
    {
        std::cout << "All devices are off." << std::endl;
    }

    ~AllSwitch() override {}
};

class Facade
{
public:
    Facade(Switch* sw) : sw(sw) {}

    void close()
    {
        sw->close();
    }

    ~Facade() { delete sw; }
private:
    Switch* sw;
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
    int code;
    Facade* facade;
    while (cnt--)
    {
        std::cin >> code;
        if (code == 1)
        {
            facade = new Facade(new AirConditionerSwitch());
            facade->close();
        }
        else if (code == 2)
        {
            facade = new Facade(new DeskLampSwitch());
            facade->close();
        }
        else if (code == 3)
        {
            facade = new Facade(new TelevisionSwitch());
            facade->close();
        }
        else if (code == 4)
        {
            facade = new Facade(new AllSwitch());
            facade->close();
        }
        else
        {
            std::cout << "Invalid device code." << std::endl;
            continue;
        }
    }
    delete facade;
    return 0;
}
