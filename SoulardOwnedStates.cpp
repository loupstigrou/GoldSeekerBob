#include "SoulardOwnedStates.h"
#include "fsm/State.h"
#include "Soulard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------ TodoAction

TodoAction* TodoAction::Instance()
{
	static TodoAction instance;

	return &instance;
}


void TodoAction::Enter(Soulard* pSoulard)
{
}

void TodoAction::Execute(Soulard* pSoulard)
{
	cout << "\n" << GetNameOfEntity(pSoulard->ID()) << ": JE SUIS BOURRE LOL LOL LOL LOL MDR PTDR HAHA HIHI OHOH XPTDR LOOOOL !";
}

void TodoAction::Exit(Soulard* pSoulard)
{

}


bool TodoAction::OnMessage(Soulard* pSoulard, const Telegram& msg)
{
	return false;
}


