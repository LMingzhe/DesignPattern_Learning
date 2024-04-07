#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// 组成接口
class Component
{
public:
    virtual void display(int depth) = 0;
};

// 叶子结点
class Department : public Component
{
private:
    std::string name;
    std::vector<Component*> children; // 子部门或员工

public:
    Department(const std::string& name) : name(name) {}

    void add(Component* component)
    {
        children.push_back(component);
    }

    void display(int depth) override
    {
        std::string indent(depth * 2,' ');
        std::cout << indent << name << std::endl;
        for (Component* component : children)
        {
            component->display(depth + 1);
        }
    }
};

// 叶子结点
class Employee : public Component
{
private:
    std::string name;

public:
    Employee(const std::string& name) : name(name) {}

    void display(int depth) override
    {
        std::string indent((depth + 1) * 2, ' ');
        std::cout << indent << name << std::endl;
    }
};

// 组合结点
class Company
{
private:
    std::string name;
    Department* root;

public:
    Company(const std::string& name) : name(name), root(new Department(name)) {}

    void add(Component* component)
    {
        root->add(component);
    }

    void display()
    {
        std::cout<< "Company Structure:" << std::endl;
        root->display(0);
    }
};

int main(int argc, char const *argv[])
{
    std::string companyName;
    std::cin >> companyName;
    Company company(companyName);
    int cnt;
    std::cin >> cnt;
    if (cnt < 1 || cnt > 100) 
    {
        std::cout << "输入有误！" << std::endl;
        return 0;
    }
    std::string type, name;
    while (cnt--)
    {
        std::cin >> type >> name;
        if (type == "D")
        {
            Department* department = new Department(name);
            company.add(department);
        }
        else if (type == "E")
        {
            Employee* employee = new Employee(name);
            company.add(employee);
        }
        else
        {
            std::cout << "输入有误！" << std::endl;
            continue;
        }
    }

    company.display();

    return 0;
}
