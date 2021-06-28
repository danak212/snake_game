#ifndef STATES_H
#define STATES_H
#pragma once

#include <memory>
#include <stack>

namespace Engine
{

    enum class StateType {MAINMENU, GAMEOVER, PAUSE, GAMEPROCESS};

    class State
    {
    public:
        StateType type;
        State(const StateType& t);
        virtual ~State() {};

        virtual void Start() {};
        virtual void Pause() {};
        virtual void Draw() = 0;
        virtual void Initial() = 0;
        virtual void StartingProcess() = 0;
    };

    class States
    {
    public:
        States();
        ~States();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessChange();
        std::unique_ptr<State>& CurrentState();

    private:
        std::stack<std::unique_ptr<State>> packOfStates;
        std::unique_ptr<State> newState;
        bool add;
        bool replace;
        bool remove;
    };

} // namespace Engine

#endif // STATES_H
