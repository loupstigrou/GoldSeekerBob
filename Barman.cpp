#include "Barman.h"

bool Barman::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Barman::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
//
	m_pStateMachine->Update();
}


bool Barman::NeededBottles()const
{
	return m_bottles < 1;
}
bool Barman::DrinkIsReady()const
{
	return m_prepareDrinkTime > 3;
}