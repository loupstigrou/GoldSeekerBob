#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,
	
  ent_Drunkard,

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
  case ent_Drunkard:
	  return "Drunkard";
  case ent_Barman:

	  return "Barman";

  default:

    return "UNKNOWN!";
  }
}

#endif