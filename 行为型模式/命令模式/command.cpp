#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// 抽象命令类
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// 命令执行者类
class BeverageMaker
{
public:
    void make (const string& name)
    {
        cout << name << " is ready!" << endl;
    }
};

// 具体命令类
class BeverageMake : public Command
{
private:
    BeverageMaker* maker;
    string name;
public:
    BeverageMake(BeverageMaker* maker, const string& name) : maker(maker), name(name) {}

    void execute() override
    {
        maker->make(name);
    }

    ~BeverageMake() override
    {
        delete maker;
    }
};

// 调用者类
class OrderMachine
{
private:
    Command* beverageMake;

public:
    void setCommand(Command* command)
    {
        this->beverageMake = command;
    }

    void executeOrder()
    {
        beverageMake->execute();
    }

    ~OrderMachine()
    {
        delete beverageMake;
    }
};

int main(int argc, char const *argv[])
{
    int cnt;
    cin >> cnt;
    if (cnt < 1 || cnt > 100)
    {
        cerr << "输入有误！" << endl;
    }

    while (cnt--)
    {
        string name;
        cin >> name;
        OrderMachine orderMachine;
        orderMachine.setCommand(new BeverageMake(new BeverageMaker(), name));
        orderMachine.executeOrder();
    }
    return 0;
}

