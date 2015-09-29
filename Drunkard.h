#ifndef Drunkard_H
#define Drunkard_H
//------------------------------------------------------------------------
//
//  Name: Drunkard.h
//
//  Desc: class to implement the drunk guy.
//
//  Author: Thibaud Laurent 2015
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DrunkardOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

struct Telegram;

//above this value the Drunkard is sleepy
const int TirednessThresholdDrunkard = 5;

//above this value the Drunkard is drunk
const int DrunknessThresholdDrunkard = 5;

//number of sip in a drink
const int GlassContainedSips = 3;


class Drunkard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Drunkard>* m_pStateMachine;

	location_type   m_Location;

	// the higher the value, the drunker the drunkard
	int m_drunkness;

	// the higher the value; the slower the glass will be emptied
	int m_glassContainer;

	// the higher the value, the more tired the drunkard
	int m_iFatigue;


public:

	Drunkard(int id) :m_Location(saloon),
		m_drunkness(0),
		m_glassContainer(0),
		m_iFatigue(2),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Drunkard>(this);

		m_pStateMachine->SetCurrentState(DrunkardGoToSaloon::Instance());

	}

	~Drunkard() { delete m_pStateMachine; }


	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Drunkard>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

	void          DrinkWhiskey() { m_drunkness += 1; m_glassContainer -= 1; m_iFatigue += 1; }

	bool		  EmptyGlass()const;
	void          SetNewDrink() { m_glassContainer = 3; }

	bool          IsDrunk()const;

};

#endif