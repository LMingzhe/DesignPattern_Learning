#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

const double PI = 3.14;

class Ground;
class CircleGround;
class RectangleGround;

// 抽象访问者
class Visitor
{
public:
    virtual void visit(CircleGround* cg) = 0;
    virtual void visit(RectangleGround* rg) = 0;
    virtual ~Visitor() {}
};

// 抽象被访问对象
class Ground
{
private:
    string type;
public:
    Ground(string& type) : type(type) {}
    string getType() { return type; }
    virtual void accept(Visitor* vistor) = 0;
    virtual ~Ground() {}
};

// 具体被访问对象
class CircleGround : public Ground
{
private:
    int radius;

public:
    CircleGround(string& type, int& radius) : Ground(type), radius(radius) {}
    
    void accept(Visitor* vistor) override
    {
        vistor->visit(this);
    }

    int getRadius() { return radius; }
};

// 具体被访问对象
class RectangleGround : public Ground
{
private:
    int length;
    int width;

public:
    RectangleGround(string& type, int& length, int& width) : Ground(type), length(length), width(width) {}

    void accept(Visitor* visitor) override
    {
        visitor->visit(this);
    }

    int getLength() { return length; }

    int getWidth() { return width; }
};

// 具体访问者
class Reckoner : public Visitor
{
public:
    void visit(CircleGround* cg) override
    {
        double area = PI * cg->getRadius() * cg->getRadius();
        cout << area << endl;
    }

    void visit(RectangleGround* rg) override
    {
        int area = rg->getLength() * rg->getWidth();
        cout << area << endl;
    }
};

// 对象结构
class VisitInterface
{
private:
    vector<Ground*> grounds;
    Visitor* visitor;

public:
    VisitInterface(Visitor* visitor) : visitor(visitor) {}
    VisitInterface() {}

    void add(Ground* ground)
    {
        grounds.push_back(ground);
    }

    void visit()
    {
        for (auto* ground : grounds)
        {
            if (ground->getType() == "Circle")
            {
                CircleGround* cg = dynamic_cast<CircleGround*>(ground);
                cg->accept(visitor);
            }
            else if (ground->getType() == "Rectangle")
            {
                RectangleGround* rg = dynamic_cast<RectangleGround*>(ground);
                rg->accept(visitor);
            }
            else 
            {
                throw std::invalid_argument("Invalid type: " + ground->getType());
            }
        }
    }

    ~VisitInterface()
    {
        delete visitor;
        visitor = nullptr;
        for (auto* ground : grounds)
        {
            delete ground;
            ground = nullptr;
        }
    }
};

int main(int argc, char const *argv[])
{
    int cnt;
    cin >> cnt;
    while (cnt < 1 || cnt > 100)
    {
        cout << "输出有误！请重新输入！" << endl;
        cin >> cnt;
    }

    VisitInterface vi(new Reckoner());

    while (cnt--)
    {
        string type;
        cin >> type;
        if (type == "Circle")
        {
            int radius;
            cin >> radius;
            vi.add(new CircleGround(type, radius));
        }
        else if (type == "Rectangle")
        {
            int length;
            int width;
            cin >> length >> width;
            vi.add(new RectangleGround(type, length, width));
        }
        else
        {
            cout << "输出有误！请重新输入！" << endl;
            cnt++;
        }
    }
    try
    {
        vi.visit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error - " << e.what() << '\n';
    }
    
    return 0;
}
