#ifndef STATES_H
#define STATES_H
#pragma once

#include <SFML/System/Time.hpp>
#include <memory>
#include <stack>

namespace Engine
{

    class States
    {
    public:
        States() {};
        virtual ~States() {};

        virtual void Start() {};
        virtual void Pause() {};
        virtual void Update(sf::Time incTime) = 0;
        virtual void Draw() = 0;
        virtual void Initial() = 0;
        virtual void StartingProcess() = 0;
    };

    class States_
    {
    public:
        States_();
        ~States_();

        void Add(std::unique_ptr<States> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessChange();
        std::unique_ptr<States>& CurrentState();

    private:
        std::stack<std::unique_ptr<States>> packOfStates;
        std::unique_ptr<States> newState;
        bool add;
        bool replace;
        bool remove;
    };

} // namespace Engine

#endif // STATES_H
