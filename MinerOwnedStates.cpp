#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
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


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
  if (pMiner->Location() != goldmine)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' to the goldmine";

    pMiner->ChangeLocation(goldmine);
  }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pickin' up a nugget";

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull())
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->GetFSM()->ChangeState(GoToSaloon::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Goin' to the bank. Yes siree";

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "Depositing gold. Total savings now: "<< pMiner->Wealth();

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
         << "WooHoo! Rich enough for now. Back home to mah li'lle lady";
      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }

  //otherwise get more gold
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
  if (pMiner->Location() != shack)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' home";

    pMiner->ChangeLocation(shack); 

    //let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Elsa,            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{ 
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued())
  {
     cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
          << "All mah fatigue has drained away. Time to find more gold!";

     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else 
  {
    //sleep
    pMiner->DecreaseFatigue();

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ... ";
  } 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{ 
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady:

     cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) 
     << " at time: " << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pMiner->ID()) 
          << ": Okay Hun, ahm a comin'!";

     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------GoToSaloon

GoToSaloon* GoToSaloon::Instance()
{
  static GoToSaloon instance;

  return &instance;
}

void GoToSaloon::Enter(Miner* pMiner)
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
  }
}

void GoToSaloon::Execute(Miner* pMiner)
{
  	pMiner->GetFSM()->ChangeState(WaitADrink::Instance());
}


void GoToSaloon::Exit(Miner* pMiner)
{ 
}


bool GoToSaloon::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Tastes real good too!";

  pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


//------------------------------------------------------------------------WaitADrink

WaitADrink* WaitADrink::Instance()
{
	static WaitADrink instance;

	return &instance;
}


void WaitADrink::Enter(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "I'm thirsty ! Barman, I want a drink !";
	Dispatch->DispatchMessage(0, //time delay
		pMiner->ID(),           //sender ID
		ent_Barman,  //receiver ID
		Msg_GiveMeADrink,        //msg
		NO_ADDITIONAL_INFO);
}

void WaitADrink::Execute(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "I'm waiting my drink.";
	
}

void WaitADrink::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thanks for the drink !";
	pMiner->BuyAndDrinkAWhiskey();

	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "That's mighty fine sippin' liquer";

}


bool WaitADrink::OnMessage(Miner* pMiner, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) << " at time: "
		<< Clock->GetCurrentTime();

	switch (msg.Msg)
	{
		case Msg_DrinkReady:
		{
			SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
			return true;
		}
		case Msg_FightMaggot:
		{
			SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			pMiner->GetFSM()->ChangeState(MinerFightWithDrunkard::Instance());
			return true;
		}
		case Msg_ImBusy:
		{
			SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "I'm very thirsty :( Barman, I want a drink !";
			Dispatch->DispatchMessage(0.5, //time delay
				pMiner->ID(),           //sender ID
				ent_Barman,  //receiver ID
				Msg_GiveMeADrink,        //msg
				NO_ADDITIONAL_INFO);
			return true;
		}
	}
	return false;
}


//------------------------------------------------------------------------MinerDrinkAGlass

MinerDrinkAGlass* MinerDrinkAGlass::Instance()
{
	static MinerDrinkAGlass instance;

	return &instance;
}


void MinerDrinkAGlass::Enter(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerDrinkAGlass Enter";

	pMiner->BuyAndDrinkAWhiskey();

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pMiner->ID(),           //sender ID
		ent_Drunkard,  //receiver ID
		Msg_MinerAskTable,        //msg
		NO_ADDITIONAL_INFO);
}

void MinerDrinkAGlass::Execute(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerDrinkAGlass Execute";
	//cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "I'm waiting my drink.";

	pMiner->DrinkWhiskey();
}

void MinerDrinkAGlass::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerDrinkAGlass Exit";
	//cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thanks for the drink !";
	//cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "That's mighty fine sippin' liquer";

}


bool MinerDrinkAGlass::OnMessage(Miner* pMiner, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_DrunkardAccepts:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	case Msg_DrunkardRefusesAndWantToFight:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		pMiner->GetFSM()->ChangeState(MinerFightWithDrunkard::Instance());
	}
	}
	return false;
}

//------------------------------------------------------------------------MinerFightWithDrunkard

MinerFightWithDrunkard* MinerFightWithDrunkard::Instance()
{
	static MinerFightWithDrunkard instance;

	return &instance;
}


void MinerFightWithDrunkard::Enter(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerFightWithDrunkard Enter";
	//
}

void MinerFightWithDrunkard::Execute(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerFightWithDrunkard Execute";

	pMiner->IncreaseFatigue();
	if (pMiner->Fatigued())
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			pMiner->ID(),
			pMiner->ID(),
			Msg_Fatigued,
			NO_ADDITIONAL_INFO);
	}
}

void MinerFightWithDrunkard::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "MinerFightWithDrunkard Exit";
	//
}


bool MinerFightWithDrunkard::OnMessage(Miner* pMiner, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Fatigued:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			pMiner->ID(),
			ent_Drunkard,
			Msg_StopFight,
			NO_ADDITIONAL_INFO);

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
		return true;
	}
	case Msg_StopFight:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		pMiner->GetFSM()->ChangeState(WaitADrink::Instance());
		return true;
	}
	}
	return false;
}
