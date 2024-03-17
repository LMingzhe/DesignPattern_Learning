#include <iostream>
#include <string>

using namespace std;

class Bicycle
{
public:
    void setFrame(std::string frame)
    {
        frame = frame;
    }

    void setTires(std::string tires)
    {
        tires = tires;
    }

private:
    std::string frame;
    std::string tires;
};

class BicycleBuilder
{
public:
    virtual void buildFrame() = 0;
    virtual void buildTires() = 0;
    virtual Bicycle* getresult() = 0;
};

class MountainBuilder : public BicycleBuilder
{
public:
    void buildFrame() override
    {
        mountainBicycle->setFrame("Aluminum Frame");
    }

    void buildTires() override
    {
        mountainBicycle->setTires("Knobby Tires");
    }

    Bicycle* getresult() override
    {
        return mountainBicycle;
    }
private:
    Bicycle* mountainBicycle;
};

class RoadBuilder : public BicycleBuilder
{
public:
    void buildFrame() override
    {
        RoadBicycle->setFrame("Carbon Frame");
    }

    void buildTires() override
    {
        RoadBicycle->setTires("Slim Tries");
    }

    Bicycle* getresult() override
    {
        return RoadBicycle;
    }
private:
    Bicycle* RoadBicycle;
};

class BicycleDirector
{
public:
    Bicycle* construct(BicycleBuilder* builder)
    {
        builder->buildFrame();
        builder->buildTires();
        return builder->getresult();
    }
};
