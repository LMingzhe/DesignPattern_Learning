#include <iostream>

using namespace std;

class HomePurchase
{
public:
    virtual void requestPurchase(int area) = 0;
    virtual ~HomePurchase() {}
};

class HomeBuyer : public HomePurchase
{
public:
    void requestPurchase(int area) override
    {
        std::cout <<  "YES" << std::endl;
    }
};

class HomeProxy : public HomePurchase
{
public:
    HomeProxy(HomeBuyer* homeBuyer) : homeBuyer(homeBuyer) {}

    void requestPurchase(int area) override
    {
        if (area > 100) homeBuyer->requestPurchase(area);
        else std::cout << "NO" << std::endl;
    }

    ~HomeProxy() { delete homeBuyer; }

private:
    HomeBuyer* homeBuyer;
};

int main(int argc, char const *argv[])
{
    int cnt;
    HomePurchase* homePurchase = new HomeProxy(new HomeBuyer());
    int area;
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100) 
    {
        std::cout << "输入有误！" << std::endl;
        return 0;
    }
    while (cnt--)
    {
        std::cin >> area;
        homePurchase->requestPurchase(area);
    }
    delete homePurchase;

    return 0;
}
