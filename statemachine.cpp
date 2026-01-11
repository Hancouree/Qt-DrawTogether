#include "statemachine.h"
#include "qdebug.h"

StateMachine::StateMachine(QObject* parent) : QObject(parent),
    currentState(States::CONNECTING)
{
    transition = {

    };
}

void StateMachine::applyEvent(Events e)
{
    if (transition.count(currentState)) {
        currentState = transition[currentState][e] ? transition[currentState][e] : currentState;
        emit stateChanged();
    }
}

StateMachine::~StateMachine()
{

}

