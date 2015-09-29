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
class DrunkardGoHomeAndSleepTilRested : public State<Drunkard>
{
private:

	DrunkardGoHomeAndSleepTilRested() {}

	//copy ctor and assignment should be private
	DrunkardGoHomeAndSleepTilRested(const DrunkardGoHomeAndSleepTilRested&);
	DrunkardGoHomeAndSleepTilRested& operator=(const DrunkardGoHomeAndSleepTilRested&);

public:

	//this is a singleton
	static DrunkardGoHomeAndSleepTilRested* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

// ------------------------------------------------------------------------
//
//  Drunkard changes location to the saloon and keeps buying Whiskey until
//  he is dead drunk.
//------------------------------------------------------------------------
class DrunkardGoToSaloon : public State<Drunkard>
{
private:

	DrunkardGoToSaloon() {}

	//copy ctor and assignment should be private
	DrunkardGoToSaloon(const DrunkardGoToSaloon&);
	DrunkardGoToSaloon& operator=(const DrunkardGoToSaloon&);

public:

	//this is a singleton
	static DrunkardGoToSaloon* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  wait until the barman give the drink
//------------------------------------------------------------------------
class DrunkardWaitADrink : public State<Drunkard>
{
private:

	DrunkardWaitADrink() {}

	//copy ctor and assignment should be private
	DrunkardWaitADrink(const DrunkardWaitADrink&);
	DrunkardWaitADrink& operator=(const DrunkardWaitADrink&);

public:

	//this is a singleton
	static DrunkardWaitADrink* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  Drink his glass
//------------------------------------------------------------------------
class DrunkardDrinkAGlass : public State<Drunkard>
{
private:

	DrunkardDrinkAGlass() {}

	//copy ctor and assignment should be private
	DrunkardDrinkAGlass(const DrunkardDrinkAGlass&);
	DrunkardDrinkAGlass& operator=(const DrunkardDrinkAGlass&);

public:

	//this is a singleton
	static DrunkardDrinkAGlass* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  Fight with the miner
//------------------------------------------------------------------------
class DrunkardFightWithMiner : public State<Drunkard>
{
private:

	DrunkardFightWithMiner() {}

	//copy ctor and assignment should be private
	DrunkardFightWithMiner(const DrunkardFightWithMiner&);
	DrunkardFightWithMiner& operator=(const DrunkardFightWithMiner&);

public:

	//this is a singleton
	static DrunkardFightWithMiner* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

#endif