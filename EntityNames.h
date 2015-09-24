#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,
	
  ent_Soulard,

  ent_Barman
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 
  case ent_Soulard:
	  return "Soulard";
  case ent_Barman:

	  return "Barman";

  default:

    return "UNKNOWN!";
  }
}

#endif