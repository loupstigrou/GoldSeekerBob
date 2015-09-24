#ifndef SOULARD_H
#define SOULARD_H
//------------------------------------------------------------------------
//
//  Name: Soulard.h
//
//  Desc: class to implement the drunk guy.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "SoulardOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

struct Telegram;

//above this value the soulard is sleepy
const int TirednessThresholdSoulard = 5;

//above this value the soulard is drunk
const int DrunknessThresholdSoulard = 5;


class Soulard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Soulard>* m_pStateMachine;

	location_type   m_Location;

	int m_drunkness;

	int m_glassContainer;

	int m_tiredness;


public:

	Soulard(int id) :m_Location(saloon),
		m_drunkness(0),
		m_glassContainer(0),
		m_tiredness(0),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Soulard>(this);

		m_pStateMachine->SetCurrentState(TodoAction::Instance());

		m_pStateMachine->SetGlobalState(TodoAction::Instance());

	}

	~Soulard() { delete m_pStateMachine; }


	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Soulard>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

};

#endif
