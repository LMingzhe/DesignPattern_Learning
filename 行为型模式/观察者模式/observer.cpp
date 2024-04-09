#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;


// 观察者接口
class Subscriber
{
public:
    virtual void update(int hour) = 0;
    virtual ~Subscriber() {}
};

// 主题接口
class Publisher
{
public:
    virtual void registerSubscriber(Subscriber* sub) = 0;
    virtual void removeSubscriber(Subscriber* sub) = 0;
    virtual void notifySubscriber() = 0;
    virtual ~Publisher() {}
};

// 具体主题
class Clock : public Publisher
{
private:
    vector<Subscriber*> subs;
    int hour;

public:
    Clock() : hour(0) {}

    void registerSubscriber(Subscriber* sub) override
    {
        subs.push_back(sub);
    }

    void removeSubscriber(Subscriber* sub) override
    {
        auto it = std::find(subs.begin(), subs.end(), sub);
        if (it != subs.end())
        {
            subs.erase(it);
        }
    }

    void notifySubscriber() override
    {
        for (const auto sub: subs)
        {
            sub->update(hour);
        }
    }

    void tick()
    {
        hour = (hour + 1) % 24;
        notifySubscriber();
    }

    const vector<Subscriber*>& getSubscribers() const
    {
        return subs;
    }

    ~Clock() override
    {
        for (auto sub : subs)
        {
            delete sub;
        }
    }
};

// 具体观察者
class Student : public Subscriber
{
private:
    string name;

public:
    Student(string name) : name(name) {}

    void update(int hour) override
    {
        cout << name << " " << hour << endl;
    }
};

int main(int argc, char const *argv[])
{
    Clock clock;
    int cnt;
    int times;
    cin >> cnt;
    if (cnt < 1 || cnt > 20) 
    {
        cerr << "输入有误！" << endl;
        return 0;
    }
    while (cnt--)
    {
        string name;
        cin >> name;
        clock.registerSubscriber(new Student(name));
    }
    cin >> times;
    while (times--)
    {
        clock.tick();
    }

    return 0;
}


