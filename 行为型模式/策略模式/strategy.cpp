#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

// 抽象策略类
class Strategy
{
public:
    virtual int compute(int price) = 0;
};

// 具体策略类
class Discount_A : public Strategy
{
public:
    int compute(int price) override
    {
        return price * 0.9;
    }
};

// 具体策略类
class Discount_B : public Strategy
{
public:
    int compute(int price) override
    {
        if (price >= 300) { return price - 40; }
        else if (price >= 200) { return price - 25; }
        else if (price >= 150) { return price - 15; }
        else if (price >= 100) { return price - 5; }
        else { return price; }
    }
};

// 上下文类
class Light
{
private:
    Strategy* discount;

public:
    Light(Strategy* discount) : discount(discount) {}

    void contextInterface(int price)
    {
        int priceDiscounted = discount->compute(price);
        cout << priceDiscounted << endl;
    }

    ~Light() { delete discount; }
};

int main(int argc, char const *argv[])
{
    int cnt;
    cin >> cnt;
    if (cnt < 1 || cnt > 20) 
    {
        cerr << "输入有误！" << endl;
        return 0;
    }
    while (cnt--)
    {
        int price, discountType;
        cin >> price >> discountType;
        if (discountType == 1)
        {
            Light* context = new Light(new Discount_A);
            context->contextInterface(price);
            delete context;
        }
        else 
        {
            Light* context = new Light(new Discount_B);
            context->contextInterface(price);
            delete context;
        }
    }
    return 0;
}
