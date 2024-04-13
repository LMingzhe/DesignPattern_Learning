#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::list;
using std::vector;

// 抽象用户
class User
{
public:
    virtual string getName() const = 0;
    virtual void sendMessage(const string& message) = 0;
    virtual void receiveMessage(const string& sender, const string& message) = 0;
    virtual void addReceivedMessage(const string& message) = 0;
    virtual ~User() {}
};

// 抽象中介者
class Mediator
{
public:
    virtual void reg(User* user) = 0;
    virtual void sendMessage(const string& sender, const string& message) = 0;
    virtual map<string, User*> getUsers() = 0;
    virtual ~Mediator() {}
};

// 具体中介者
class CharRoomMediator : public Mediator
{
private:
    map<string, User*> users;

public:
    void reg(User* user) override
    {
        users[user->getName()] = user;
    }

    void sendMessage(const string& sender, const string& message) override
    {
        for (const auto& user : users)
        {
            if (user.first != sender)
            {
                user.second->receiveMessage(sender, message);
            }
        }
    }

    map<string, User*> getUsers() override
    {
        return users;
    }
};

// 具体用户
class CharUser : public User
{
private:
    string name;
    Mediator* mediator;
    list<string> receivedMessages;

public:
    CharUser(const string& name, Mediator* mediator) : name(name), mediator(mediator)
    {
        mediator->reg(this);
    }

    string getName() const override
    {
        return name;
    }

    void sendMessage(const string& message) override
    {
        mediator->sendMessage(name, message);
    }

    void addReceivedMessage(const string& message) override
    {
        receivedMessages.push_back(message);
    }

    void receiveMessage(const string& sender, const string& message) override
    {
        string receivedMessage = name + " received " + message;
        addReceivedMessage(receivedMessage);
        cout << receivedMessage << endl;
    }
};

int main(int argc, char const *argv[])
{
    int cnt;
    vector<string> userNames;
    cin >> cnt;
    while(cnt--)
    {
        string name;
        cin >> name;
        userNames.push_back(name);
    }

    Mediator* mediator = new CharRoomMediator();

    for (auto& userName : userNames)
    {
        new CharUser(userName, mediator);
    }

    string sender, message;
    while (cin >> sender >> message)
    {
        User* user = mediator->getUsers()[sender];
        if (user != nullptr)
        {
            user->sendMessage(message);
        }
    }

    delete mediator;

    return 0;
}


