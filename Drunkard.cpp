#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}







bool Drunkard::EmptyGlass()const
{
	if (m_glassContainer == 0)
	{
		return true;
	}

	return false;
}



bool Drunkard::Fatigued()const
{
	if (m_iFatigue > TirednessThresholdDrunkard)
	{
		return true;
	}

	return false;
}