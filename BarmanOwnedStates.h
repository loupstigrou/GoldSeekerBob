#ifndef BARMAN_OWNED_STATES_H
#define BARMAN_OWNED_STATES_H

#include "fsm/State.h"


class Barman;
struct Telegram;


class BarmanGlobalState : public State<Barman>
{
private:

	BarmanGlobalState() {}

	//copy ctor and assignment should be private
	BarmanGlobalState(const BarmanGlobalState&);
	BarmanGlobalState& operator=(const BarmanGlobalState&);

public:

	//this is a singleton
	static BarmanGlobalState* Instance();

	virtual void Enter(Barman* barman) {}

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman) {}

	virtual bool OnMessage(Barman* barman, const Telegram& msg);
};
//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class WaitingForCustomer : public State<Barman>
{
private:

	WaitingForCustomer() {}

	//copy ctor and assignment should be private
	WaitingForCustomer(const WaitingForCustomer&);
	WaitingForCustomer& operator=(const WaitingForCustomer&);

public:

	//this is a singleton
	static WaitingForCustomer* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};
//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class GiveADrink : public State<Barman>
{
private:

	GiveADrink() {}

	//copy ctor and assignment should be private
	GiveADrink(const GiveADrink&);
	GiveADrink& operator=(const GiveADrink&);

public:

	//this is a singleton
	static GiveADrink* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};
//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class SearchForBottles : public State<Barman>
{
private:

	SearchForBottles() {}

	//copy ctor and assignment should be private
	SearchForBottles(const SearchForBottles&);
	SearchForBottles& operator=(const SearchForBottles&);

public:

	//this is a singleton
	static SearchForBottles* Instance();

	virtual void Enter(Barman* barman);

	virtual void Execute(Barman* barman);

	virtual void Exit(Barman* barman);

	virtual bool OnMessage(Barman* agent, const Telegram& msg);

};

#endif