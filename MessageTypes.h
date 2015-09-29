#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_GiveMeADrink,
	Msg_DrinkReady,
	Msg_MinerAskTable,
	Msg_DrunkardAccepts,
	Msg_DrunkardRefusesAndWantToFight,
	Msg_Fatigued,
	Msg_FightMaggot,
	Msg_StopFight,
	Msg_ImBusy
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
		return "MinerAskTable";
	case 5:
		return "DrunkardAccepts";
	case 6:
		return "DrunkardRefusesAndWantToFight";
	case 7:
		return "Fatigued";
	case 8:
		return "FightMaggot";
	case 9:
		return "StopFight";
	case 10:
		return "ImBusy";

	default:
		return "Not recognized!";
	}
}

#endif