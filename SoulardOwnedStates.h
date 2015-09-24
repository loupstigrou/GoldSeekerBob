#ifndef SOULARD_OWNED_STATES_H
#define SOULARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   SoulardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Soulard class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Soulard;
struct Telegram;


//------------------------------------------------------------------------
//
//  TODO
//------------------------------------------------------------------------
class TodoAction : public State<Soulard>
{
private:

	TodoAction() {}

	//copy ctor and assignment should be private
	TodoAction(const TodoAction&);
	TodoAction& operator=(const TodoAction&);

public:

	//this is a singleton
	static TodoAction* Instance();

	virtual void Enter(Soulard* pSoulard);

	virtual void Execute(Soulard* pSoulard);

	virtual void Exit(Soulard* pSoulard);

	virtual bool OnMessage(Soulard* agent, const Telegram& msg);
};





#endif