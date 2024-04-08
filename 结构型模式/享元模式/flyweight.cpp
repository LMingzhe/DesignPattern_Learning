#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::unordered_map;
using std::istringstream;

// 枚举类型
enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE};

// 枚举类型转字符串
string shapeTypeToString(ShapeType type)
{
    switch (type)   
    {
    case CIRCLE:
        return "CIRCLE";
    case RECTANGLE:
        return "RECTANGLE";
    case TRIANGLE:
        return "TRIANGLE";
    default:
        return "UNKNOW";
    }
}

// 图形坐标(x,y)类
class Position
{
private:
    int x;
    int y;
    
public:
    Position(int x, int y) : x(x), y(y) {}

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }
};

// 享元接口
class Shape
{
public:
    virtual void draw(const Position& pos) = 0;
    virtual ~Shape() {}
};

// 具体享元对象
class ConcreteShape : public Shape
{
private:
    ShapeType shapeType;
    bool isFirstTime;

public:
    ConcreteShape(ShapeType shapeType) : shapeType(shapeType), isFirstTime(true) {}

    void draw(const Position& pos) override
    {
        cout << shapeTypeToString(shapeType) << " " << (isFirstTime ? "drawn at " : "shared at ")
             << "(" << pos.getX() << ", " << pos.getY() << ")" << endl;
    }

    void setFirstTime(bool FirstTime)
    {
        isFirstTime = FirstTime;
    }
};

// 享元工厂
class ShapeFactory
{
private:
    unordered_map<ShapeType, Shape*> map;

public:
    Shape* getShape(ShapeType type)
    {
        if (map.find(type) == map.end())
        {
            map[type] = new ConcreteShape(type);
        }

        return map[type];
    }

    ~ShapeFactory()
    {
        for (const auto entry : map)
        {
            delete entry.second;
        }
    }
};

// 客户端代码
int main(int argc, char const *argv[])
{
    string command;
    string shapeTypeStr;
    int x, y;
    ShapeFactory factory;
    while (getline(std::cin, command))
    {
        istringstream iss(command);
        iss >> shapeTypeStr >> x >> y;
        ShapeType type;
        if (shapeTypeStr == "CIRCLE")
        {
            type = CIRCLE;
        }
        else if (shapeTypeStr == "RECTANGLE")
        {
            type = RECTANGLE;
        }
        else if (shapeTypeStr == "TRIANGLE")
        {
            type = TRIANGLE;
        }
        else
        {
            cerr << "Invalid shape type: " << shapeTypeStr << endl;
            return 0;
        }

        Shape* shape = factory.getShape(type);
        shape->draw(Position(x, y));
        
        // dynamic_cast 类型转换运算符，它用于在运行时进行类型检查和转换。它通常用于将基类指针或引用转换为派生类指针或引用。
        // 将指针shape转化为ConcreteShape类型
        dynamic_cast<ConcreteShape*>(shape)->setFirstTime(false);
    }

    return 0;
}

