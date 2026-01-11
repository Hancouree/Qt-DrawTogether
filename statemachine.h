#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>

class StateMachine : public QObject
{
    Q_OBJECT
public:
    enum States {

    };
    Q_ENUM(States)

    enum Events {

    };
    Q_ENUM(Events)

    StateMachine(QObject* parent = nullptr);
    ~StateMachine();

    void applyEvent(Events e);

    States getState() { return currentState; }
signals:
    void stateChanged();
private:
    States currentState;

    std::map<States, std::map<Events, States>> transition;
};

#endif // STATEMACHINE_H
