#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// using namespace std;

// 懒汉模式实现
class shoppingCart
{
public:
    ~shoppingCart() {}
    static shoppingCart* getCart();                        // 获取实例
    void add(const std::string& name, const int& cnt);     // 添加物品
    void checkList() const;                                // 打印清单

private:
    shoppingCart() {}
    std::unordered_map<std::string,int> list;              // 清单，使用unorder_map，查找为O(1)，但是存储是无序的
    std::vector<std::string> order;                        // 保持打印顺序
};

shoppingCart* shoppingCart::getCart()
{
    // 静态局部变量：静态局部变量在函数内部声明时只会被初始化一次，并且在整个程序运行期间保持其数值不变。
    static shoppingCart cart;
    return &cart;
}

void shoppingCart::add(const std::string& name, const int& cnt)
{
    if (name.empty() || cnt <= 0) return;
    if (list.find(name) == list.end())
    {
        order.push_back(name);
    }
    list[name] += cnt;
}

void shoppingCart::checkList() const 
{
    if (!list.size()) return;

    for (const auto& name : order)
    {
        std::cout << name << " " << list.at(name) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    shoppingCart* cart = shoppingCart::getCart();

    std::string name;
    int cnt = 0;
    while (std::cin >> name >> cnt)
    {
        cart->add(name, cnt);
    }

    cart->checkList();

    return 0;
}
