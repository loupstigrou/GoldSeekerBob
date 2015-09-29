#ifndef Drunkard_OWNED_STATES_H
#define Drunkard_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunkard;
struct Telegram;


//------------------------------------------------------------------------
//
//  TODO
//------------------------------------------------------------------------
class TodoAction : public State<Drunkard>
{
private:

	TodoAction() {}

	//copy ctor and assignment should be private
	TodoAction(const TodoAction&);
	TodoAction& operator=(const TodoAction&);

public:

	//this is a singleton
	static TodoAction* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  Drunkard will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
//class GoHomeAndSleepTilRested : public State<Drunkard>
//{
//private:
//
//	GoHomeAndSleepTilRested(){}
//
//	//copy ctor and assignment should be private
//	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
//	GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);
//
//public:
//
//	//this is a singleton
//	static GoHomeAndSleepTilRested* Instance();
//
//	virtual void Enter(Drunkard* drunkard);
//
//	virtual void Execute(Drunkard* drunkard);
//
//	virtual void Exit(Drunkard* drunkard);
//
//	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
//};

// ------------------------------------------------------------------------
//
//  Drunkard changes location to the saloon and keeps buying Whiskey until
//  he is dead drunk.
//------------------------------------------------------------------------
//class GoToSaloon : public State<Drunkard>
//{
//private:
//
//	GoToSaloon(){}
//
//	//copy ctor and assignment should be private
//	GoToSaloon(const GoToSaloon&);
//	GoToSaloon& operator=(const GoToSaloon&);
//
//public:
//
//	//this is a singleton
//	static GoToSaloon* Instance();
//
//	virtual void Enter(Drunkard* drunkard);
//
//	virtual void Execute(Drunkard* drunkard);
//
//	virtual void Exit(Drunkard* drunkard);
//
//	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
//};

//------------------------------------------------------------------------
//
//  wait until the barman give the drink
//------------------------------------------------------------------------
//class WaitADrink : public State<Drunkard>
//{
//private:
//
//	WaitADrink() {}
//
//	//copy ctor and assignment should be private
//	WaitADrink(const WaitADrink&);
//	WaitADrink& operator=(const WaitADrink&);
//
//public:
//
//	//this is a singleton
//	static WaitADrink* Instance();
//
//	virtual void Enter(Drunkard* drunkard);
//
//	virtual void Execute(Drunkard* drunkard);
//
//	virtual void Exit(Drunkard* drunkard);
//
//	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
//};

//------------------------------------------------------------------------
//
//  Drink his glass
//------------------------------------------------------------------------
//class DrinkAGlass : public State<Drunkard>
//{
//private:
//
//	DrinkAGlass() {}
//
//	//copy ctor and assignment should be private
//	DrinkAGlass(const DrinkAGlass&);
//	DrinkAGlass& operator=(const DrinkAGlass&);
//
//public:
//
//	//this is a singleton
//	static DrinkAGlass* Instance();
//
//	virtual void Enter(Drunkard* drunkard);
//
//	virtual void Execute(Drunkard* drunkard);
//
//	virtual void Exit(Drunkard* drunkard);
//
//	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
//};

//------------------------------------------------------------------------
//
//  Fight with the miner
//------------------------------------------------------------------------
class FightWithMiner : public State<Drunkard>
{
private:

	FightWithMiner() {}

	//copy ctor and assignment should be private
	FightWithMiner(const FightWithMiner&);
	FightWithMiner& operator=(const FightWithMiner&);

public:

	//this is a singleton
	static FightWithMiner* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

#endif