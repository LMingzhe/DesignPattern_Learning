#include <iostream>
#include <string>

class Prototype
{
public:
    virtual Prototype* clone() const = 0;
    virtual void print() const = 0;
    virtual ~Prototype() {}
};

class Rectangle : public Prototype
{
public:
    Rectangle() {}
    Rectangle(const std::string& color, const int& width, const int& height)
    {
        this->color = color;
        this->width = width;
        this->height = height;
    }

    Prototype* clone() const override
    {
        return new Rectangle(*this);
    }

    void print() const override
    {
        std::cout << "Color: "  << color  << ", "
                  << "Width: "  << width  << ", "
                  << "Height: " << height << std::endl;
    }
private:
    std::string color;
    int height;
    int width;
};

int main(int argc, char const *argv[])
{   
    int cnt;
    std::string color;
    int width;
    int height;
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100) 
    {
        std::cout << "输入有误！" << std::endl;
        return 0;
    }
    while (cnt--)
    {   
        std::cin >> color >> width >> height;
        Prototype* origin = new Rectangle(color, width, height);
        Prototype* clone = origin->clone();
        clone->print();

        delete origin;
        delete clone;
    }
    return 0;
}
