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



//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested
//
//GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
//{
//	static GoHomeAndSleepTilRested instance;
//
//	return &instance;
//}
//
//void GoHomeAndSleepTilRested::Enter(Drunkard* pDrunkard)
//{
//	if (pDrunkard->Location() != shack)
//	{
//		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Walkin' home";
//
//		pDrunkard->ChangeLocation(shack);
//
//	}
//}
//
//void GoHomeAndSleepTilRested::Execute(Drunkard* pDrunkard)
//{
//	//if Drunkard is not fatigued go back to the saloon
//	if (!pDrunkard->Fatigued())
//	{
//		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
//			<< "All mah fatigue has drained away. Time to go the saloon again!";
//
//		pDrunkard->GetFSM()->ChangeState(GoToSaloon::Instance());
//	}
//
//	else
//	{
//		//sleep
//		pDrunkard->DecreaseFatigue();
//
//		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ... ";
//	}
//}
//
//void GoHomeAndSleepTilRested::Exit(Drunkard* pDrunkard)
//{
//}
//
//
//bool GoHomeAndSleepTilRested::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
//{
//	return false;
//}

//------------------------------------------------------------------------GoToSaloon
//
//GoToSaloon* GoToSaloon::Instance()
//{
//	static GoToSaloon instance;
//
//	return &instance;
//}
//
//void GoToSaloon::Enter(Drunkard* pDrunkard)
//{
//	if (pDrunkard->Location() != saloon)
//	{
//		pDrunkard->ChangeLocation(saloon);
//
//		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
//	}
//}
//
//void GoToSaloon::Execute(Drunkard* pDrunkard)
//{
//	pDrunkard->GetFSM()->ChangeState(WaitADrink::Instance());
//}
//
//
//void GoToSaloon::Exit(Drunkard* pDrunkard)
//{
//}
//
//
//bool GoToSaloon::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
//{
//	//send msg to global message handler
//	return false;
//}

//------------------------------------------------------------------------WaitADrink
//
//WaitADrink* WaitADrink::Instance()
//{
//	static WaitADrink instance;
//
//	return &instance;
//}
//
//
//void WaitADrink::Enter(Drunkard* pDrunkard)
//{
//	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I'm thirsty ! Barman, I want a drink !";
//	Dispatch->DispatchMessage(0, //time delay
//		pDrunkard->ID(),           //sender ID
//		ent_Barman,  //receiver ID
//		Msg_GiveMeADrink,        //msg
//		NO_ADDITIONAL_INFO);
//}
//
//void WaitADrink::Execute(Drunkard* pDrunkard)
//{
//	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I'm waiting my drink.";
//}
//
//void WaitADrink::Exit(Drunkard* pDrunkard)
//{
//	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Thanks for the drink !";
//	pDrunkard->BuyAndDrinkAWhiskey();
//
//	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "That's mighty fine sippin' liquer";
//
//}
//
//
//bool WaitADrink::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
//{
//	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//
//	switch (msg.Msg)
//	{
//	case Msg_DrinkReady:
//	{
//		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
//			<< Clock->GetCurrentTime();
//
//		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//
//		pDrunkard->GetFSM()->ChangeState(Drink::Instance());
//		return true;
//	}
//	case Msg_FightMaggot:
//	{
//		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
//			<< Clock->GetCurrentTime();
//
//		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//		pDrunkard->GetFSM()->ChangeState(FightWithDrunkard::Instance());
//		return true;
//	}
//	}
//	return false;
//}

//------------------------------------------------------------------------DrinkAGlass
//
//DrinkAGlass* DrinkAGlass::Instance()
//{
//	static DrinkAGlass instance;
//
//	return &instance;
//}
//
//
//void DrinkAGlass::Enter(Drunkard* pDrunkard)
//{
//	pDrunkard->SetNewDrink();
//}
//
//void DrinkAGlass::Execute(Drunkard* pDrunkard)
//{
//	cout << "\n" "That's a fine drink !";
//	pDrunkard->DrinkWhiskey();
//	
//		//DRINKDRINKDRINKDRINKDRINKDRINK another
//
//}
//
//void DrinkAGlass::Exit(Drunkard* pDrunkard)
//{
//	//fight ou bois
//
//}
//
//
//bool DrinkAGlass::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
//{
//	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//
//	switch (msg.Msg)
//	{
//	case Msg_DrinkReady:
//	{
//		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
//			<< Clock->GetCurrentTime();
//
//		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//
//		pDrunkard->GetFSM()->ChangeState(DrinkAGlass::Instance());
//		return true;
//	}
//	case Msg_FightMaggot:
//	{
//		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) << " at time: "
//			<< Clock->GetCurrentTime();
//
//		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//		pDrunkard->GetFSM()->ChangeState(FightWithMiner::Instance());
//		return true;
//	}
//	}
//	return false;
//}
