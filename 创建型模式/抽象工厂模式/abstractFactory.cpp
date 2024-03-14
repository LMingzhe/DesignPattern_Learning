#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 抽象椅子接口
class Chair
{
public:
    virtual void print() = 0;
};

// 抽象沙发接口
class Sofa
{
public:
    virtual void print() = 0;
};

// 现代风椅子具体实现
class ModernChair : public Chair
{
public:
    void print() override
    {
        std::cout << "modern chair" << std::endl;
    }
};

// 古典风椅子具体实现
class ClassicalChair : public Chair
{
public:
    void print() override
    {
        std::cout << "classical chair" << std::endl;
    }
};

// 现代风沙发具体实现
class ModernSofa : public Sofa
{
public:
    void print() override
    {
        std::cout << "modern sofa" << std::endl;
    }
};

// 古典风沙发具体实现
class ClassicalSofa : public Sofa
{
public:
    void print() override
    {
        std::cout << "classical sofa" << std::endl;
    }
};

// 抽象工厂
class AbstractFactory
{
public:
    virtual Chair* produceChair() = 0;
    virtual Sofa* produceSofa() = 0;
};

// 现代工厂具体实现
class ModernFactory : public AbstractFactory
{
public:
    Chair* produceChair() override
    {
        return new ModernChair();
    }

    Sofa* produceSofa() override
    {
        return new ModernSofa();
    }
};

// 古典工厂具体实现
class ClassicalFactory : public AbstractFactory
{
public:
    Chair* produceChair() override
    {
        return new ClassicalChair();
    }

    Sofa* produceSofa() override
    {
        return new ClassicalSofa();
    }
};

// 生产系统
class ProduceSystem
{
public:
    void produce(AbstractFactory* ab)
    {
        ab->produceChair()->print();
        ab->produceSofa()->print();
        delete ab;
    }
};

int main(int argc, char const *argv[])
{
    int cnt = 0;
    std::string type;
    ProduceSystem ps;
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100)
    {
        std::cout << "输入无效！" << std::endl;
    }

    while (cnt--)
    {
        std::cin >> type;
        if (type == "modern")
        {
            ps.produce(new ModernFactory());
        }
        else if (type == "classical")
        {
            ps.produce(new ClassicalFactory());
        }
        else
        {
            std::cout << "输入中存在错误！" << std::endl;
        }
    }
    return 0;
}
