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

class Memento
{
private:
    int state;

public:
    Memento(int& state) : state(state) {}

    int getState() const
    {
        return state;
    }
};

class Caretaker
{
private:

public:

};

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
        state--;
    }

    void Undo()
    {

    }

    void Redo()
    {

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
    
    return 0;
}
