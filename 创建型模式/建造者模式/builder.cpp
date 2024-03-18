#include <iostream>
#include <string>

using namespace std;

// 自行车产品
class Bicycle
{
public:
    void setFrame(const std::string& frame)
    {
        this->frame = frame;
    }

    void setTires(const std::string& tires)
    {
        this->tires = tires;
    }

    friend std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle)
    {
        os << bicycle.frame << " " << bicycle.tires;
        return os;
    }

private:
    std::string frame;
    std::string tires;
};

// 自行车抽象建造者
class BicycleBuilder
{
public:
    virtual void buildFrame() = 0;
    virtual void buildTires() = 0;
    virtual Bicycle getresult() = 0;
};

// 山地车具体建造者
class MountainBuilder : public BicycleBuilder
{
public:
    void buildFrame() override
    {
        mountainBicycle.setFrame("Aluminum Frame");
    }

    void buildTires() override
    {
        mountainBicycle.setTires("Knobby Tires");
    }

    Bicycle getresult() override
    {
        return mountainBicycle;
    }
private:
    Bicycle mountainBicycle;
};

// 公路车具体建造者
class RoadBuilder : public BicycleBuilder
{
public:
    void buildFrame() override
    {
        RoadBicycle.setFrame("Carbon Frame");
    }

    void buildTires() override
    {
        RoadBicycle.setTires("Slim Tires");
    }

    Bicycle getresult() override
    {
        return RoadBicycle;
    }
private:
    Bicycle RoadBicycle;
};

// 自行车建造指导者
class BicycleDirector
{
public:
    Bicycle construct(BicycleBuilder& builder)
    {
        builder.buildFrame();
        builder.buildTires();
        return builder.getresult();
    }
};

int main(int argc, char const *argv[])
{
    // 指导者对象，负责指导产品生成
    BicycleDirector director;
    int cnt = 0;
    std::string type;

    std::cin >> cnt;
    if (cnt < 1 || cnt > 100)
    {
        std::cout << "输入有误！" << std::endl;
        return 0;
    }

    while (cnt--)
    {
        BicycleBuilder* builder;
        std::cin >> type;
        // 根据不同需求创建不同的具体建造者
        if (type == "mountain")
        {
            builder = new MountainBuilder();
        }
        else if (type == "road")
        {
            builder = new RoadBuilder();
        }
        else
        {
            std::cout << "输入有误！" << std::endl;
            cnt += 1;
            continue;
        }
        Bicycle bike = director.construct(*builder);
        std::cout << bike << std::endl;
        delete builder;
    }
    return 0;
}

