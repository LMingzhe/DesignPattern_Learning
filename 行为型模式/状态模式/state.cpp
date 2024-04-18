#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

// 状态接口
class LightState
{
public:
    virtual void execute() = 0;
    virtual ~LightState() {}
};

// 具体状态类
class LightOn : public LightState
{
public:
    void execute() override
    {
        cout << "Light is ON" << endl;
    }
};

// 具体状态类
class LightOff : public LightState
{
public:
    void execute() override
    {
        cout << "Light is OFF" << endl;
    }
};

// 具体状态类
class LightBlink : public LightState
{
public:
    void execute() override
    {
        cout << "Light is Blinking" << endl;
    }
};

// 上下文类
class Light
{
private:
    LightState* lightState;

public:
    Light(LightState* lightState) : lightState(lightState) {}
    Light() {}

    void setLightState(LightState* lightState)
    {
        this->lightState = lightState;
    }
    
    void request()
    {
        lightState->execute();
    }

    ~Light()
    {
        delete lightState;
        lightState = nullptr;
    }
};

int main(int argc, char const *argv[])
{
    Light light;
    int cnt;
    cin >> cnt;
    while (cnt < 1 || cnt > 1000)
    {
        cout << "输入有误！请重新输入！" << endl;
        cin >> cnt;
    }
    while (cnt--)
    {
        string changeState;
        cin >> changeState;
        if (changeState == "ON")
        {
            light.setLightState(new LightOn());
            light.request();
        }
        else if (changeState == "OFF")
        {
            light.setLightState(new LightOff());
            light.request();
        }
        else if (changeState == "BLINK")
        {
            light.setLightState(new LightBlink());
            light.request();
        }
        else
        {
            cout << "操作有误，请重新输入！" << endl;
            cnt++;
        }
    }
    return 0;
}
