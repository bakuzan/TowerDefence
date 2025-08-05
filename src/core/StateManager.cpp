#include <iostream>

#include "StateManager.h"

StateManager::StateManager()
    : pendingChange(PendingChange::NONE)
{
    // Constructor
}

StateManager::~StateManager()
{
    // Destructor
}

// Publics

void StateManager::handleEvent(const sf::Event &event)
{
    if (!states.empty())
    {
        std::cerr << "[Loop] handleEvent" << std::endl;
        states.back()->handleEvent(event);
    }
}

void StateManager::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    if (!states.empty())
    {
        std::cerr << "[Loop] update" << std::endl;
        states.back()->update(deltaTime, window);
    }

    applyPendingStateChange();
}

void StateManager::render(sf::RenderWindow &window)
{
    std::cerr << "[Loop] render" << std::endl;
    for (auto &state : states)
    {
        state->render(window);
    }
}

// Transition methods

void StateManager::pushState(std::unique_ptr<State> state)
{
    pendingChange = PendingChange::PUSH;
    pendingState = std::move(state);
}

void StateManager::popState()
{
    pendingChange = PendingChange::POP;
}

void StateManager::changeState(std::unique_ptr<State> state)
{
    pendingChange = PendingChange::CHANGE;
    pendingState = std::move(state);
}

void StateManager::replaceStates(std::unique_ptr<State> state)
{
    pendingChange = PendingChange::REPLACE;
    pendingState = std::move(state);
}

// Internal queue processing

void StateManager::applyPendingStateChange()
{
    if (pendingChange == PendingChange::NONE)
    {
        return;
    }

    std::cerr << "[StateManager] Applying pending state change\n";

    switch (pendingChange)
    {
    case PendingChange::PUSH:
        states.push_back(std::move(pendingState));
        break;
    case PendingChange::POP:
        if (!states.empty())
        {
            states.pop_back();
        }
        break;
    case PendingChange::CHANGE:
        if (!states.empty())
        {
            states.pop_back();
        }
        states.push_back(std::move(pendingState));
        break;
    case PendingChange::REPLACE:
        states.clear();
        states.push_back(std::move(pendingState));
        break;
    default:
        break;
    }

    pendingChange = PendingChange::NONE;
    pendingState.reset();
}
