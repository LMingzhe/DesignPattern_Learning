#include <iostream>
#include <vector>
#include <string>

// using namespace std;

// 抽象积木接口
class Shape
{
public:
    virtual void draw() = 0;
};

// 抽象工厂接口
class Factory
{
public:
    virtual Shape* createShape() = 0;
};

// 具体圆形积木实现
class Circle : public Shape
{
public:
    void draw() override
    {
        std::cout << "Circle Block" << std::endl;
    }
};

// 具体方形积木实现
class Square : public Shape
{
public:
    void draw() override
    {
        std::cout << "Square Block" << std::endl;
    }     
};

// 具体圆形积木工厂实现
class CircleFactory : public Factory
{
public:
    Shape* createShape() override
    {
        return new Circle();
    }
};

// 具体方形积木工厂实现
class SquareFactory : public Factory
{
public:
    Shape* createShape() override
    {
        return new Square();
    }
};

// 工厂系统
class FactorySystem
{
public:
    void produceShape(Factory* factory, int num)
    {
        while (num--)
        {
            Shape* shape = factory->createShape();
            list.push_back(shape);
            shape->draw();
        }
    }

    const std::vector<Shape*>& getList() const
    {
        return list;
    }

    // 析构函数释放内存
    ~FactorySystem()
    {
        for (auto shape : list)
        {
            delete shape;
        }
    }

private:
    std::vector<Shape*> list;
};

int main(int argc, char const *argv[])
{
    FactorySystem factorySystem;

    int cnt = 0;               // 生产次数
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100)
    {
        std::cout << "输入无效！" << std::endl;
        return 0;
    }

    std::string shape;
    int num = 0;
    while (cnt--)
    {
        std::cin >> shape >> num;
        if (num <= 0) continue;

        if (shape == "Circle")
        {
            factorySystem.produceShape(new CircleFactory(), num);
        }
        else if (shape == "Square")
        {
            factorySystem.produceShape(new SquareFactory(), num);
        }

    }

    return 0;
}

/* --- 封装改进一下 ----
int main(int argc, char const *argv[])
{
    std::vector<Shape*> list;   // 存储不同形状的积木
    Factory* factory_v;

    int cnt = 0;               // 生产次数
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100)
    {
        std::cout << "输入无效！" << std::endl;
        return 0;
    }

    std::string shape;
    int num = 0;
    while (cnt--)
    {
        std::cin >> shape >> num;
        if (num <= 0) continue;
        while (num--)
        {
            if (shape == "Circle")
            {
                factory_v = new CircleFactory();            // 先有生产具体形状积木的工厂，再生产对应形状积木
                Shape* shape_v = factory_v->createShape();
                list.push_back(shape_v);
            }
            else if (shape == "Square")
            {
                factory_v = new SquareFactory();
                Shape* shape_v = factory_v->createShape();
                list.push_back(shape_v);
            }
        }
    }

    for (auto shape : list)
    {
        shape->draw();
        delete shape;
    }
    
    delete factory_v;

    return 0;
}
*/
