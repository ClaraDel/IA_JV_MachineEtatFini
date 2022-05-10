#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,
  ent_Elsa,
  ent_ElsasLover
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 

  case ent_ElsasLover:

      return "Elsa's lover";

  default:

    return "UNKNOWN!";
  }
}

#endif