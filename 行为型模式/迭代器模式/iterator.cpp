#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

// 迭代目标对象
class Student
{
private:
    string name;
    string id;

public:
    Student(const string& name, const string& id) : name(name), id(id) {}

    void print()
    {
        cout << name << " " << id << endl;
    }
};

// 迭代器接口
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual Student* getNext() = 0;
    virtual ~Iterator() {}
};

// 具体迭代器对象
class StudentIterator : public Iterator
{
private:
    vector<Student*> elements;
    int index;

public:
    StudentIterator(vector<Student*>& elements) : elements(elements) { index = 0; }

    bool hasNext() override
    {
        return index < elements.size();
    }

    Student* getNext() override
    {
        return elements[index++];
    }

    ~StudentIterator() override
    {
        for (auto student: elements)
        {
            delete student;
            student = nullptr;
        }
    }
};

// 聚合类
class StudentListSystem
{
private:
    vector<Student*> elements;

public:
    StudentListSystem(vector<Student*>& elements) : elements(elements) {}

    Iterator* createIterator()
    {
        return new StudentIterator(elements);
    }
};

int main(int argc, char const *argv[])
{
    vector<Student*> students;
    int cnt;
    cin >> cnt;
    while (cnt < 1 || cnt > 100)
    {
        cout << "输入有误！请重新输入" << endl;
        cin >> cnt;
    }
    while (cnt--)
    {
        string name;
        string id;
        cin >> name >> id;
        students.push_back(new Student(name, id));
    }
    StudentListSystem sls(students);
    Iterator* studentIterator = sls.createIterator();
    while (studentIterator->hasNext())
    {
        Student* student = studentIterator->getNext();
        student->print();
    }
    delete studentIterator;
    studentIterator = nullptr;
    return 0;
}
