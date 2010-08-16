#include "Managers/StateManager.hpp"
#include "Managers/LogManager.hpp"

void StateManager::push(State *state)
{
    mStates.push_back(StatePtr(state));
}

void StateManager::update()
{
    if (mStates.empty()) LOG("[State Manager → update] There aren't any states now. Maybe, you didn't push one.");
    if (mActiveState.get() == NULL) this->pop();

    mActiveState.get()->update();
}

StateManager::StateManager(): mAdvanceState(false) { }

StateManager::~StateManager()
{
    while (!mStates.empty())
    {
        mStates.pop_back();
    }
}

void StateManager::setAdvanceState(bool advance)
{
    mAdvanceState = advance;
}

State *StateManager::pop()
{
    if (mStates.empty()) return StatePtr().get();

    mActiveState = mStates.back();	// Store pointer for next state to use
    mStates.pop_back();				// And remove it from list

    LOG(FORMAT("[State Manager → pop] Activating '%1%' game state", mActiveState.get()->type()));

    return mActiveState.get();
}

State *StateManager::getActiveState()
{
    if (mActiveState.get() == NULL) LOG("[State Manager → getActiveState] There aren't any active state. Maybe, you didn't push one.");
    return mActiveState.get();
}
