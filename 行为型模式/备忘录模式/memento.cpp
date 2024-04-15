#include <iostream>
#include <string>
#include <vector>
#include <stack>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::stack;

// 备忘录
class Memento
{
private:
    int state;

public:
    Memento(int state) : state(state) {}

    int getState() const
    {
        return state;
    }
};

// 备忘录管理者
class Caretaker
{
private:
    vector<Memento> mementos;

public:
    void addMemento(Memento memento)
    {
        mementos.push_back(memento);
    }
};

// 发起人
class Calculator
{
private:
    int state = 0;
    stack<Memento> undoStack;
    stack<Memento> redoStack;

public:
    void increment()
    {
        redoStack = stack<Memento>();
        undoStack.push(Memento(state));
        state++;
    }

    void decrement()
    {
        redoStack = stack<Memento>();
        undoStack.push(Memento(state));
        state--;
    }

    void undo()
    {
        if (!undoStack.empty())
        {
            redoStack.push(Memento(state));
            state = undoStack.top().getState();
            undoStack.pop();
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            undoStack.push(Memento(state));
            state = redoStack.top().getState();
            redoStack.pop();
        }
    }

    int getState() const
    {
        return state;
    }

    void setState(int& state)
    {
        state = state;
    }
};

int main(int argc, char const *argv[])
{
    string operation;
    Calculator calculator;
    Caretaker caretaker;
    while (cin >> operation)
    {
        if (operation == "Increment")
        {
            calculator.increment();
        }
        else if (operation == "Decrement")
        {
            calculator.decrement();
        }
        else if (operation == "Undo")
        {
            calculator.undo();
        }
        else if (operation == "Redo")
        {
            calculator.redo();
        }
        else
        {
            cout << "输入有误！请重新输入" << endl;
            continue;
        }

        caretaker.addMemento(Memento(calculator.getState()));

        cout << calculator.getState() << endl;
    }
    return 0;
}
