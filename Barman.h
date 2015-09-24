#ifndef BARMAN_H
#define BARMAN_H
//------------------------------------------------------------------------
//
//  Name: Soulard.h
//
//  Desc: class to implement the barman.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "BarmanOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

struct Telegram;

class Barman : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Barman>* m_pStateMachine;

	location_type   m_Location;

	int m_bottles;

	int m_customerIDToGiveADrink;

	int m_prepareDrinkTime;

	int m_iMoney;


public:

	Barman(int id) :m_Location(saloon),
		m_bottles(3),
		m_iMoney(0),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Barman>(this);

		m_pStateMachine->SetCurrentState(WaitingForCustomer::Instance());

		m_pStateMachine->SetGlobalState(BarmanGlobalState::Instance());

	}

	~Barman() { delete m_pStateMachine; }


	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Barman>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	int			  GetBottles()const { return m_bottles; }
	void          SetBottles(int val) { m_bottles = val; }
	void          IncreaseBottles() { m_bottles += 1; }
	void          SellOneBottle() { m_bottles -= 1; m_iMoney += 2; }
	bool          NeededBottles()const;

	int			  GetCustomerID()const { return m_customerIDToGiveADrink; }
	void          SetCustomerID(int val) { m_customerIDToGiveADrink = val; }

	int			  GetPrepareDrinkTime()const { return m_prepareDrinkTime; }
	void          SetPrepareDrinkTime(int val) { m_prepareDrinkTime = val; }
	void          IncreasePrepareDrinkTime() { m_prepareDrinkTime += 1; }
	bool          DrinkIsReady()const;

};

#endif
