#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
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



//------------------------------------------------------------------------methods for DrunkardGoHomeAndSleepTilRested

DrunkardGoHomeAndSleepTilRested* DrunkardGoHomeAndSleepTilRested::Instance()
{
	static DrunkardGoHomeAndSleepTilRested instance;

	return &instance;
}

void DrunkardGoHomeAndSleepTilRested::Enter(Drunkard* pDrunkard)
{
	//cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "DrunkardGoHomeAndSleepTilRested Enter";
	if (pDrunkard->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Walkin' home";

		pDrunkard->ChangeLocation(shack);

	}
}

void DrunkardGoHomeAndSleepTilRested::Execute(Drunkard* pDrunkard)
{
	//if Drunkard is not fatigued go back to the saloon
	if (!pDrunkard->Fatigued())
	{
		pDrunkard->Speak("All mah fatigue has drained away. Time to go the saloon again!");

		pDrunkard->GetFSM()->ChangeState(DrunkardGoToSaloon::Instance());
	}

	else
	{
		//sleep
		pDrunkard->DecreaseFatigue();

		pDrunkard->Speak("ZZZZ... ");
	}
}

void DrunkardGoHomeAndSleepTilRested::Exit(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardGoHomeAndSleepTilRested Exit");
}


bool DrunkardGoHomeAndSleepTilRested::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------DrunkardGoToSaloon

DrunkardGoToSaloon* DrunkardGoToSaloon::Instance()
{
	static DrunkardGoToSaloon instance;

	return &instance;
}

void DrunkardGoToSaloon::Enter(Drunkard* pDrunkard)
{
	//cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "DrunkardGoToSaloon Enter";

	if (pDrunkard->Location() != saloon)
	{
		pDrunkard->ChangeLocation(saloon);

		pDrunkard->Speak("Boy, ah sure is thusty! Walking to the saloon");
	}
}

void DrunkardGoToSaloon::Execute(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardGoToSaloon Execute");
	pDrunkard->GetFSM()->ChangeState(DrunkardWaitADrink::Instance());
}


void DrunkardGoToSaloon::Exit(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardGoToSaloon Exit");
}


bool DrunkardGoToSaloon::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------DrunkardWaitADrink

DrunkardWaitADrink* DrunkardWaitADrink::Instance()
{
	static DrunkardWaitADrink instance;

	return &instance;
}


void DrunkardWaitADrink::Enter(Drunkard* pDrunkard)
{
	pDrunkard->Speak("I'm thirsty ! Barman, I want a drink !");
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,	//time delay
		pDrunkard->ID(),			//sender ID
		ent_Barman,					//receiver ID
		Msg_GiveMeADrink,			//msg
		NO_ADDITIONAL_INFO);
}

void DrunkardWaitADrink::Execute(Drunkard* pDrunkard)
{
	pDrunkard->Speak("I'm waiting my drink.");

}

void DrunkardWaitADrink::Exit(Drunkard* pDrunkard)
{
	pDrunkard->Speak("Thanks for the drink !");

}


bool DrunkardWaitADrink::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "\nMsg : " << msg.Msg << "\n";

	switch (msg.Msg)
	{
	case Msg_DrinkReady:
	{
		cout << "\n\nMessage Msg_DrinkReady (" << msg.Msg << ") handled by " << GetNameOfEntity(pDrunkard->ID()) << " send by " << GetNameOfEntity(msg.Sender) << " at time :  "
			<< Clock->GetCurrentTime() << "\n";


		pDrunkard->GetFSM()->ChangeState(DrunkardDrinkAGlass::Instance());
		return true;
	}
	case Msg_MinerAskTable:
	{
		cout << "\n\nMessage Msg_MinerAskTable (" << msg.Msg << ") handled by " << GetNameOfEntity(pDrunkard->ID()) << " send by " << GetNameOfEntity(msg.Sender) << " at time :  "
			<< Clock->GetCurrentTime() << "\n";

		if (pDrunkard->IsDrunk())
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
				pDrunkard->ID(),
				msg.Sender,
				Msg_DrunkardAccepts,
				NO_ADDITIONAL_INFO);
		}
		else
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
				pDrunkard->ID(),
				msg.Sender,
				Msg_DrunkardRefusesAndWantToFight,
				NO_ADDITIONAL_INFO);

			pDrunkard->GetFSM()->ChangeState(DrunkardFightWithMiner::Instance());
		}
		return true;
	}
	case Msg_ImBusy:
	{
		pDrunkard->Speak("I'm very thirsty :( Barman, I want a drink !");
		Dispatch->DispatchMessage(0.5, //time delay
			pDrunkard->ID(),           //sender ID
			ent_Barman,  //receiver ID
			Msg_GiveMeADrink,        //msg
			NO_ADDITIONAL_INFO);
		return true;
	}
	}
	return false;
}

//------------------------------------------------------------------------DrunkardDrinkAGlass

DrunkardDrinkAGlass* DrunkardDrinkAGlass::Instance()
{
	static DrunkardDrinkAGlass instance;

	return &instance;
}


void DrunkardDrinkAGlass::Enter(Drunkard* pDrunkard)
{
	pDrunkard->Speak("I will start to drink");
	pDrunkard->SetNewDrink();
}

void DrunkardDrinkAGlass::Execute(Drunkard* pDrunkard)
{
	pDrunkard->Speak("That's a fine drink that I drink here !");

	if (pDrunkard->EmptyGlass())
		pDrunkard->GetFSM()->ChangeState(DrunkardWaitADrink::Instance());
	else
		pDrunkard->DrinkWhiskey();
}

void DrunkardDrinkAGlass::Exit(Drunkard* pDrunkard)
{
	pDrunkard->Speak("Oh f*ck ! My glass is already empty !");
}


bool DrunkardDrinkAGlass::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "\nMsg : " << msg.Msg << "\n";

	switch (msg.Msg)
	{
	case Msg_MinerAskTable:
	{
		if (msg.Sender == ent_Miner_Bob)
		{
			cout << "\n\nMessage Msg_MinerAskTable (" << msg.Msg << ") handled by " << GetNameOfEntity(pDrunkard->ID()) << " send by " << GetNameOfEntity(msg.Sender) << " at time :  "
				<< Clock->GetCurrentTime() << "\n";

			if (pDrunkard->IsDrunk())
			{
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
					pDrunkard->ID(),
					msg.Sender,
					Msg_DrunkardAccepts,
					NO_ADDITIONAL_INFO);
			}
			else
			{
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
					pDrunkard->ID(),
					msg.Sender,
					Msg_DrunkardRefusesAndWantToFight,
					NO_ADDITIONAL_INFO);

				pDrunkard->GetFSM()->ChangeState(DrunkardFightWithMiner::Instance());
			}
		}
		return true;
	}
	}
	return false;
}

//------------------------------------------------------------------------DrunkardFightWithMiner

DrunkardFightWithMiner* DrunkardFightWithMiner::Instance()
{
	static DrunkardFightWithMiner instance;

	return &instance;
}


void DrunkardFightWithMiner::Enter(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardFightWithMiner Enter");
}

void DrunkardFightWithMiner::Execute(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardFightWithMiner Execute");

	pDrunkard->IncreaseFatigue();
	if (pDrunkard->Fatigued())
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			pDrunkard->ID(),
			ent_Miner_Bob,
			Msg_StopFight,
			NO_ADDITIONAL_INFO);

		pDrunkard->GetFSM()->ChangeState(DrunkardGoHomeAndSleepTilRested::Instance());
	}
}

void DrunkardFightWithMiner::Exit(Drunkard* pDrunkard)
{
	pDrunkard->Speak("DrunkardFightWithMiner Exit");
}


bool DrunkardFightWithMiner::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StopFight:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		pDrunkard->GetFSM()->ChangeState(DrunkardWaitADrink::Instance());
		return true;
	}
	}
	return false;
}