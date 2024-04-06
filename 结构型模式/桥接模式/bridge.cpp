#include <iostream>

using namespace std;

// 步骤1: 创建实现化接口
class TV
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void tuneChannel() = 0;
    virtual ~TV() {}
};

// 步骤2: 创建具体实现化类
class Sony : public TV
{
public:
    void on() override
    {
        std::cout << "Sony TV is ON" << std::endl;
    }

    void off() override
    {
        std::cout << "Sony TV is OFF" << std::endl;
    }

    void tuneChannel() override
    {
        std::cout << "Switching Sony TV channel" << std::endl;
    }
};

class TCL : public TV
{
public:
    void on() override
    {
        std::cout << "TCL TV is ON" << std::endl;
    }

    void off() override
    {
        std::cout << "TCL TV is OFF" << std::endl;
    }

    void tuneChannel() override
    {
        std::cout << "Switching TCL TV channel" << std::endl;
    }
};

// 步骤3: 创建抽象化接口
class RemoteControl
{
protected:
    TV* tv;
public:
    RemoteControl(TV* tv) : tv(tv) {}
    virtual void performOperation() = 0;
};

// 步骤4: 创建扩充抽象化类
class PowerOperation : public RemoteControl
{
public:
    PowerOperation(TV* tv) : RemoteControl(tv) {}
    void performOperation() override
    {
        tv->on();
    }
};

class OffOperation : public RemoteControl
{
public:
    OffOperation(TV* tv) : RemoteControl(tv) {}
    void performOperation() override
    {
        tv->off();
    }
};

class ChannelSwitchOperation : public RemoteControl
{
public:
    ChannelSwitchOperation(TV* tv) : RemoteControl(tv) {}
    void performOperation() override
    {
        tv->tuneChannel();
    }
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
    int brand, operation;
    while (cnt--)
    {
        std::cin >> brand >> operation;
        TV* tv;
        if (brand == 0)
        {
            tv = new Sony();
        }
        else if (brand == 1)
        {
            tv = new TCL();
        }
        else
        {
            std::cout << "输入有误!" << std::endl;
            continue;
        }

        RemoteControl* remoteControl;
        if (operation == 2)
        {
            remoteControl = new PowerOperation(tv);
        }
        else if (operation == 3)
        {
            remoteControl = new OffOperation(tv);
        }
        else if (operation == 4)
        {
            remoteControl = new ChannelSwitchOperation(tv);
        }
        else
        {
            std::cout << "输入有误！" << std::endl;
            continue;
        }

        remoteControl->performOperation();

        delete tv, remoteControl;
    }
    return 0;
}
