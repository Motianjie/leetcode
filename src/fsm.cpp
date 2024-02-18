#include <iostream>
enum class State {
    State1,
    State2,
    State3,
    // 添加更多状态...
};

class BaseState {
public:
    virtual void enterState() = 0;
    virtual void updateState() = 0;
    virtual void exitState() = 0;
};

class State1 : public BaseState {
public:
    void enterState() override {
        // 进入状态1的逻辑
        std::cout << "enter state1" << std::endl;
    }

    void updateState() override {
        // 更新状态1的逻辑
        std::cout << "update state1" << std::endl;
    }

    void exitState() override {
        // 退出状态1的逻辑
        std::cout << "exit state1" << std::endl;
    }
};

class State2 : public BaseState {
public:
    void enterState() override {
        // 进入状态2的逻辑
        std::cout << "enter state2" << std::endl;
    }

    void updateState() override {
        std::cout << "update state2" << std::endl;
        // 更新状态2的逻辑
    }

    void exitState() override {
        // 退出状态2的逻辑
        std::cout << "exit state2" << std::endl;
    }
};

// 添加更多具体状态类...
class StateMachine {
private:
    BaseState* currentState;

public:
    StateMachine() : currentState(nullptr) {}

    void setState(BaseState* state) {
        if (currentState) {
            currentState->exitState();
        }
        currentState = state;
        if (currentState) {
            currentState->enterState();
        }
    }

    void update() {
        if (currentState) {
            currentState->updateState();
        }
    }
};


int test11_1() 
{
    StateMachine stateMachine;

    State1 state1;
    State2 state2;

    stateMachine.setState(&state1);  // 设置初始状态为State1

    while (true) {
        // 根据具体逻辑判断是否需要切换状态
        static uint8_t cnt = 0;
        cnt++;
        if (cnt % 2 == 0) 
        {
            stateMachine.setState(&state1);  // 切换到State1
        }else
        {
            stateMachine.setState(&state2);  // 切换到State2
        }

        // 更新状态机
        stateMachine.update();
    }

    return 0;
}

