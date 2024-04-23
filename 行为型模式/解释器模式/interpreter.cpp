#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stack>
#include <regex>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::istringstream;
using std::istream_iterator;
using std::stack;
using std::runtime_error;

// 抽象表达式类
class Expression
{
public:
    virtual int interpret() = 0;
    virtual ~Expression() {}
};

// 终结符表达式类 - 数字
class NumberExpression : public Expression
{
private:
    int value;

public:
    NumberExpression(const int& value) : value(value) {}

    int interpret() override
    {
        return value;
    }
};

// 非终结符表达式类 - 加法操作
class AddExpression : public Expression
{
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret() override
    {
        return left->interpret() + right->interpret();
    }

    ~AddExpression() override
    {
        delete left; left = nullptr;
        delete right; right = nullptr;
    }
};

// 非终结符表达式类 - 乘法操作
class MultiplyExpression : public Expression
{
private:
    Expression* left;
    Expression* right;

public:
    MultiplyExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret() override
    {
        return left->interpret() * right->interpret();
    }

    ~MultiplyExpression() override
    {
        delete left; left = nullptr;
        delete right; right = nullptr;
    }
};

// 非终结符表达式类 - 操作符
class OperatorExpression : public Expression 
{
private:
    string oper;

public:
    OperatorExpression(const string& op) : oper(op) {}

    int interpret() override 
    {
        throw std::runtime_error("OperatorExpression does not support interpretation");
    }

    string getOperator() const 
    {
        return oper;
    }
};

// 解析表达式字符串
int parseExpression(const string& expressionStr)
{
    istringstream iss(expressionStr);
    // 从输入流 iss 中读取字符串，直到达到输入流的末尾，然后将这些字符串存储到 std::vector<std::string> 对象 elements 中
    vector<string> elements(istream_iterator<string>{iss}, istream_iterator<string>());

    stack<Expression*> st;
    

    for (const auto& element : elements)
    {
        // 正则表达式匹配是否是数组序列
        if (std::regex_match(element, std::regex("\\d+")))
        {
            st.push(new NumberExpression(std::stoi(element)));
        }
        else if (element == "+" || element == "*")
        {
            st.push(new OperatorExpression(element));
        }
        else
        {
            throw std::invalid_argument("Invalid element in expression: " + element); // 抛出异常
        }
    }

    while (st.size() > 1)
    {
        Expression* right = st.top();
        st.pop();
        Expression* operatorExp = st.top();
        st.pop();
        Expression* left = st.top();
        st.pop();

        // dynamic_cast安全的向下类型转换：基类指针转换为派生类指针
        // 成功则返回转换后的指针，失败则返回空指针
        if (auto* opExp = dynamic_cast<OperatorExpression*>(operatorExp))
        {
            string op = opExp->getOperator();
            if (op == "+")
            {
                st.push(new AddExpression(left, right));
            }
            else if (op == "*")
            {
                st.push(new MultiplyExpression(left, right));
            }
            else
            {
                throw std::invalid_argument("Invalid operator type in expression");
            }
        }
    }

    int result = st.top()->interpret();
    delete st.top();
    return result;
}

int main(int argc, char const *argv[])
{
    vector<string> input_lines;
    string line;

    while (getline(cin, line) && !line.empty())
    {
        input_lines.push_back(line);
    }

    for (size_t i = 0; i < input_lines.size(); i++)
    {
        try
        {
            int result = parseExpression(input_lines[i]);
            cout << result << endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error - " << e.what() << '\n';
        }
    }

    return 0;
}
