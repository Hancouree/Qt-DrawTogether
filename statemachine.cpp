#include "statemachine.h"

StateMachine::StateMachine(QObject* parent) : QObject(parent),
    currentState(States::WAITING)
{
    transition = {
        {WAITING, {
          {STOP_WAITING, AUTHENTICATING},
          {START_WAITING, WAITING}
        }},
        {AUTHENTICATING, {
             {AUTHENTICATED, MENU},
             {START_WAITING, WAITING}
         }},
        {MENU, {
           {START_WAITING, WAITING}
        }}
    };
}

void StateMachine::applyEvent(Events e)
{
    auto stateIt = transition.find(currentState);
    if (stateIt != transition.end()) {
        auto eventIt = stateIt->second.find(e);
        if (eventIt != stateIt->second.end()) {
            currentState = eventIt->second;
            emit stateChanged();
        }
    }
}

StateMachine::~StateMachine()
{

}

