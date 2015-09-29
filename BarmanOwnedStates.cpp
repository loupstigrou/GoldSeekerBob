#include "BarmanOwnedStates.h"
#include "Barman.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//-----------------------------------------------------------------------Global state

BarmanGlobalState* BarmanGlobalState::Instance()
{
	static BarmanGlobalState instance;

	return &instance;
}


void BarmanGlobalState::Execute(Barman* barman)
{
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	/*if ((RandFloat() < 0.1) && !barman->GetFSM()->isInState(*VisitBathroom::Instance()))
	{
	barman->GetFSM()->ChangeState(VisitBathroom::Instance());
	}*/


}
bool BarmanGlobalState::OnMessage(Barman* barman, const Telegram& msg)
{

	return false;
}







//-------------------------------------------------------------------------WaitingForCustomer

WaitingForCustomer* WaitingForCustomer::Instance()
{
	static WaitingForCustomer instance;

	return &instance;
}


void WaitingForCustomer::Enter(Barman* barman)
{
	cout << "\n" << GetNameOfEntity(barman->ID()) << ": Anybody want to drink ?! I have " << barman->GetBottles() << " bottles for you today !";
}


void WaitingForCustomer::Execute(Barman* barman)
{
	cout << "\n" << GetNameOfEntity(barman->ID()) << ": I'm still waiting for customers !";

	if (barman->NeededBottles())
	{
		barman->GetFSM()->ChangeState(SearchForBottles::Instance());
	}
}

void WaitingForCustomer::Exit(Barman* barman)
{
}

bool WaitingForCustomer::OnMessage(Barman* barman, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
		case Msg_GiveMeADrink:
		{
			cout << "\nMessage handled by " << GetNameOfEntity(barman->ID()) << " at time: "
				<< Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);


			barman->SetCustomerID(msg.Sender);

			cout << "\n" << GetNameOfEntity(barman->ID()) <<
				": Hi " << GetNameOfEntity(barman->GetCustomerID()) << " ! I will prepare your drink !";
			
			barman->GetFSM()->ChangeState(GiveADrink::Instance());
			return true;
		}
	}

	return false;
}


//-------------------------------------------------------------------------GiveADrink

GiveADrink* GiveADrink::Instance()
{
	static GiveADrink instance;

	return &instance;
}


void GiveADrink::Enter(Barman* barman)
{
	cout << "\n" << GetNameOfEntity(barman->ID()) << ": I will prepare a drink for " << GetNameOfEntity(barman->GetCustomerID()) << " !";
	barman->SetPrepareDrinkTime(0);
}


void GiveADrink::Execute(Barman* barman)
{
	barman->IncreasePrepareDrinkTime();
	switch (barman->GetPrepareDrinkTime())
	{
		case 1:
		{
			cout << "\n" << GetNameOfEntity(barman->ID()) << ": Let's grab a bottle !";
			barman->SellOneBottle();
		}
		case 2:
		{
			cout << "\n" << GetNameOfEntity(barman->ID()) << ": Pour the alcool into a nice glas !";
		}
		case 3:
		{
			cout << "\n" << GetNameOfEntity(barman->ID()) << ": Here we are ! Your glas is ready " << GetNameOfEntity(barman->GetCustomerID()) << " !";

			Dispatch->DispatchMessage(0,                  //time delay
				barman->ID(),           //sender ID
				barman->GetCustomerID(),           //receiver ID
				Msg_DrinkReady,        //msg
				NO_ADDITIONAL_INFO);

			if (barman->NeededBottles())
			{
				barman->GetFSM()->ChangeState(SearchForBottles::Instance());
			}
			else
			{
				barman->GetFSM()->ChangeState(WaitingForCustomer::Instance());
			}
			
		}
	}

}

void GiveADrink::Exit(Barman* barman)
{
	barman->SetPrepareDrinkTime(0);
	barman->SetCustomerID(0);
}

bool GiveADrink::OnMessage(Barman* barman, const Telegram& msg)
{
	return false;
}

//-------------------------------------------------------------------------SearchForBottles

SearchForBottles* SearchForBottles::Instance()
{
	static SearchForBottles instance;

	return &instance;
}


void SearchForBottles::Enter(Barman* barman)
{
	cout << "\n" << GetNameOfEntity(barman->ID()) << ": I'm going to find bottles !";
}


void SearchForBottles::Execute(Barman* barman)
{
	if (barman->GetBottles() < 3)
	{
		barman->IncreaseBottles();
		cout << "\n" << GetNameOfEntity(barman->ID()) << ": One more bottle !";
	}
	else
	{
		barman->GetFSM()->ChangeState(WaitingForCustomer::Instance());
	}
}

void SearchForBottles::Exit(Barman* barman)
{
	cout << "\n" << GetNameOfEntity(barman->ID()) << ": That's it for the moment ! I have a lot of bottles and I will come back to the saloon.";
}

bool SearchForBottles::OnMessage(Barman* barman, const Telegram& msg)
{
	return false;
}