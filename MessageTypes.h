#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_GiveMeADrink,
	Msg_DrinkReady,
	Msg_FightMaggot
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

	  return "GiveMeADrink";
  case 3:

	  return "DrinkReady";
  case 4:

	  return "FightMaggot";

  default:

    return "Not recognized!";
  }
}

#endif