#include "MinersWife.h"
#include "EntityNames.h"

bool MinersWife::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void MinersWife::Update()
{
  //set text color to green
  SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
 
  m_pStateMachine->Update();
}

void MinersWife::Speak(std::string const &str1)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "\n" << GetNameOfEntity(ID()) << ": " << str1;
}
