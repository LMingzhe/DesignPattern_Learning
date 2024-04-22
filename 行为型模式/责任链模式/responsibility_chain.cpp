#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

// 处理者接口
class Handler
{
public:
    virtual void handle(const string& name, const int& days) = 0;
    virtual void request(const string& name, const int& days) = 0;
    virtual void setNextHandler(Handler* nextHandler) = 0;
    virtual ~Handler() {}
};

// 具体处理者
class Supervisor : public Handler
{
private:
    Handler* nextHandler;

public:
    Supervisor(Handler* nextHandler) : nextHandler(nextHandler) {}
    Supervisor() {}

    void handle(const string& name, const int& days) override
    {
        if (days <= 3)
        {
            cout << name << " Approved " << "by " << "Supervisor." << endl;
        }
        else if (nextHandler != nullptr)
        {
            request(name, days);
        }
        else 
        {
            cout << name << " Denied " << "by " << "Supervisor." << endl;
        }
    }

    void request(const string& name, const int& days) override
    {
        nextHandler->handle(name, days);
    }

    void setNextHandler(Handler* nextHandler) override
    {
        this->nextHandler = nextHandler;
    }

    ~Supervisor() override
    {
        delete nextHandler;
        nextHandler = nullptr;
    }
};

// 具体处理者
class Manager : public Handler
{
private:
    Handler* nextHandler;

public:
    Manager(Handler* nextHandler) : nextHandler(nextHandler) {}
    Manager() {}

    void handle(const string& name, const int& days) override
    {
        if (days <= 7)
        {
            cout << name << " Approved " << "by " << "Manager." << endl;
        }
        else if (nextHandler != nullptr)
        {
            request(name, days);
        }
        else 
        {
            cout << name << " Denied " << "by " << "Manager." << endl;
        }
    }

    void request(const string& name, const int& days) override
    {
        nextHandler->handle(name, days);
    }

    void setNextHandler(Handler* nextHandler) override
    {
        this->nextHandler = nextHandler;
    }

    ~Manager() override
    {
        delete nextHandler;
        nextHandler = nullptr;
    }
};

// 具体处理者
class Director : public Handler
{
private:
    Handler* nextHandler;

public:
    Director(Handler* nextHandler) : nextHandler(nextHandler) {}
    Director() {}

    void handle(const string& name, const int& days) override
    {
        if (days <= 10)
        {
            cout << name << " Approved " << "by " << "Director." << endl;
        }
        else if (nextHandler != nullptr)
        {
            request(name, days);
        }
        else 
        {
            cout << name << " Denied " << "by " << "Director." << endl;
        }
    }

    void request(const string& name, const int& days) override
    {
        nextHandler->handle(name, days);
    }

    void setNextHandler(Handler* nextHandler) override
    {
        this->nextHandler = nextHandler;
    }

    ~Director() override
    {
        delete nextHandler;
        nextHandler = nullptr;
    }
};

// 客户端代码
int main(int argc, char const *argv[])
{
    int cnt;
    cin >> cnt;
    while (cnt < 1 || cnt > 1000)
    {
        cout << "输入有误！请重新输入！" << endl;
        cin >> cnt;
    }
    Handler* handler = new Supervisor(new Manager(new Director()));
    while (cnt--)
    {
        string name;
        int days;
        cin >> name >> days;
        handler->handle(name, days);
    }
    delete handler;
    handler = nullptr;
    return 0;
}