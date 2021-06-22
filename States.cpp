#include "States.h"

Engine::States_::States_() : add(false), replace(false), remove(false) {}

Engine::States_::~States_() {}

void Engine::States_::Add(std::unique_ptr<States> toAdd, bool replace)
{
    add = true;
    newState = std::move(toAdd);
    replace = replace;
}

void Engine::States_::PopCurrent() { remove = true; }

void Engine::States_::ProcessChange()
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

std::unique_ptr<Engine::States>& Engine::States_::CurrentState() { return packOfStates.top(); }
