#pragma once
#ifndef ELSASLOVER_H
#define ELSASLOVER_H

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "ElsasLoverOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"


class ElsasLover : public BaseGameEntity 
{
private :

	//an instance of the state machine class
	StateMachine<ElsasLover>* m_pStateMachine;

    location_type   m_Location;

public :
    
ElsasLover(int id):m_Location(shack),
                     BaseGameEntity(id)
                                        
  {
    //set up the state machine
    m_pStateMachine = new StateMachine<ElsasLover>(this);

    m_pStateMachine->SetCurrentState(LiveHisLife::Instance());

    m_pStateMachine->SetGlobalState(ElsasLoverGlobalState::Instance());
  }

  ~ElsasLover(){delete m_pStateMachine;}

  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<ElsasLover>* GetFSM()const { return m_pStateMachine; }

  //----------------------------------------------------accessors
  location_type Location()const { return m_Location; }
  void          ChangeLocation(location_type loc) { m_Location = loc; }


};

#endif
