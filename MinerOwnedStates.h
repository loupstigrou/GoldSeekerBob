#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Miner;
struct Telegram;




//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to GoToSaloon
//------------------------------------------------------------------------
class EnterMineAndDigForNugget : public State<Miner>
{
private:
  
  EnterMineAndDigForNugget(){}

  //copy ctor and assignment should be private
  EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
  EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);
 
public:

  //this is a singleton
  static EnterMineAndDigForNugget* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

  virtual bool OnMessage(Miner* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  miner is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGold : public State<Miner>
{
private:
  
  VisitBankAndDepositGold(){}

  //copy ctor and assignment should be private
  VisitBankAndDepositGold(const VisitBankAndDepositGold&);
  VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);
 
public:

  //this is a singleton
  static VisitBankAndDepositGold* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

  virtual bool OnMessage(Miner* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  miner will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepTilRested : public State<Miner>
{
private:
  
  GoHomeAndSleepTilRested(){}

  //copy ctor and assignment should be private
  GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
  GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);
 
public:

  //this is a singleton
  static GoHomeAndSleepTilRested* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

  virtual bool OnMessage(Miner* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  miner changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the goldmine
//  and resumes his quest for nuggets.
//------------------------------------------------------------------------
class GoToSaloon : public State<Miner>
{
private:
  
  GoToSaloon(){}

  //copy ctor and assignment should be private
  GoToSaloon(const GoToSaloon&);
  GoToSaloon& operator=(const GoToSaloon&);
 
public:

  //this is a singleton
  static GoToSaloon* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

  virtual bool OnMessage(Miner* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The miner eats the stew, gives
//  Elsa some compliments and then returns to his previous state
//------------------------------------------------------------------------
class EatStew : public State<Miner>
{
private:
  
  EatStew(){}

  //copy ctor and assignment should be private
  EatStew(const EatStew&);
  EatStew& operator=(const EatStew&);
 
public:

  //this is a singleton
  static EatStew* Instance();

  virtual void Enter(Miner* miner);

  virtual void Execute(Miner* miner);

  virtual void Exit(Miner* miner);

  virtual bool OnMessage(Miner* agent, const Telegram& msg);
};



//------------------------------------------------------------------------
//
//  wait until the barman give the drink
//------------------------------------------------------------------------
class WaitADrink : public State<Miner>
{
private:

	WaitADrink() {}

	//copy ctor and assignment should be private
	WaitADrink(const WaitADrink&);
	WaitADrink& operator=(const WaitADrink&);

public:

	//this is a singleton
	static WaitADrink* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Fight with the drunkard
//------------------------------------------------------------------------
class FightWithDrunkard: public State<Miner>
{
private:

	FightWithDrunkard() {}

	//copy ctor and assignment should be private
	FightWithDrunkard(const FightWithDrunkard&);
	FightWithDrunkard& operator=(const FightWithDrunkard&);

public:

	//this is a singleton
	static FightWithDrunkard* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};
class MinerEatStew : public State<Miner>
{
private:

	MinerEatStew() {}

	//copy ctor and assignment should be private
	MinerEatStew(const MinerEatStew&);
	MinerEatStew& operator=(const MinerEatStew&);

public:

	//this is a singleton
	static MinerEatStew* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};



//------------------------------------------------------------------------
//
//  MinerAskATableToSit
//------------------------------------------------------------------------
class MinerAskATableToSit : public State<Miner>
{
private:

	MinerAskATableToSit() {}

	//copy ctor and assignment should be private
	MinerAskATableToSit(const MinerAskATableToSit&);
	MinerAskATableToSit& operator=(const MinerAskATableToSit&);

public:

	//this is a singleton
	static MinerAskATableToSit* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  DrinkAGlass
//------------------------------------------------------------------------
class MinerDrinkAGlass : public State<Miner>
{
private:

	MinerDrinkAGlass() {}

	//copy ctor and assignment should be private
	MinerDrinkAGlass(const MinerDrinkAGlass&);
	MinerDrinkAGlass& operator=(const MinerDrinkAGlass&);

public:

	//this is a singleton
	static MinerDrinkAGlass* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Fight with the drunkard
//------------------------------------------------------------------------
class MinerFightWithDrunkard : public State<Miner>
{
private:

	MinerFightWithDrunkard() {}

	//copy ctor and assignment should be private
	MinerFightWithDrunkard(const MinerFightWithDrunkard&);
	MinerFightWithDrunkard& operator=(const MinerFightWithDrunkard&);

public:

	//this is a singleton
	static MinerFightWithDrunkard* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

#endif