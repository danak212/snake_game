#include "States.h"

Engine::State::State(const StateType& t): type(t) {}

Engine::States::States() : add(false), replace(false), remove(false) {}

Engine::States::~States() {}

void Engine::States::Add(std::unique_ptr<State> toAdd, bool replace)
{
    add = true;
    newState = std::move(toAdd);
    replace = replace;
}

void Engine::States::PopCurrent() { remove = true; }

void Engine::States::ProcessChange()
{
    if (remove && (!packOfStates.empty()))
    {
        packOfStates.pop();
        if (!packOfStates.empty()) { packOfStates.top()->Start(); }
        remove = false;
    }
    if (add)
    {
        if (replace && (!packOfStates.empty()))
        {
            packOfStates.pop();
            replace = false;
        }
        if (!packOfStates.empty()) { packOfStates.top()->Pause(); }
        packOfStates.push(std::move(newState));
        packOfStates.top()->Initial();
        packOfStates.top()->Start();
        add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::States::CurrentState() { return packOfStates.top(); }
