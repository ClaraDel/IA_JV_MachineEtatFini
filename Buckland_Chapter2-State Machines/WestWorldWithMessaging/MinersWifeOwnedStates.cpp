#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "Mutex.h"

#include <iostream>

using std::cout;
std::mutex w;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
  static WifesGlobalState instance;

  return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife)
{
  //0.5 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.05) && 
       !wife->GetFSM()->isInState(*VisitBathroom::Instance()) )
  {
    wife->GetFSM()->ChangeState(VisitBathroom::Instance());
  }
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg)
{
   

    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  
  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome:
   {
      M->Lock();
       cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: " 
       << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(wife->ID()) << 
          ": Hi honey. Let me make you some of mah fine country stew";
    M->Unlock();
     wife->GetFSM()->ChangeState(CookStew::Instance());
   }
  case Msg_Goodbye:
  {
      M->Lock();
      cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
          << Clock->GetCurrentTime();

      SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

      cout << "\n" << GetNameOfEntity(wife->ID()) <<
          ": Bye honey.";
     M->Unlock();
      //tell her lover he can come
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,                  //time delay
          wife->ID(),           //sender ID
          ent_ElsasLover,           //receiver ID
          Msg_ComeToSeeMe,        //msg
          NO_ADDITIONAL_INFO);
      M->Lock();
      SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(wife->ID()) << ": Hello my love, It's good to see you. I'm tired of doing housework all day like a servant. ";
      M->Unlock();
      wife->GetFSM()->ChangeState(WithPhilippe::Instance());
     
  }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
  static DoHouseWork instance;

  return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
    M->Lock();
    SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": Time to do some more housework!";
 M->Unlock();
}


void DoHouseWork::Execute(MinersWife* wife)
{
    M->Lock();
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": Moppin' the floor";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": Washin' the dishes";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": Makin' the bed";

    break;
  }
 M->Unlock();
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{  
    M->Lock();
    SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
     cout << "\n" << GetNameOfEntity(wife->ID()) << ": Walkin' to the can. Need to powda mah pretty li'lle nose"; 
 M->Unlock();
}


void VisitBathroom::Execute(MinersWife* wife)
{
    M->Lock();
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": Ahhhhhh! Sweet relief!";
 M->Unlock();
  wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
    M->Lock();
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": Leavin' the Jon";
 M->Unlock();
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
  static CookStew instance;

  return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
  //if not already cooking put the stew in the oven
  if (!wife->Cooking())
  {
      M->Lock();
      SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "\n" << GetNameOfEntity(wife->ID()) << ": Putting the stew in the oven";
    M->Unlock();
    //send a delayed message myself so that I know when to take the stew
    //out of the oven

    Dispatch->DispatchMessage(1.5,                  //time delay
                              wife->ID(),           //sender ID
                              wife->ID(),           //receiver ID
                              Msg_StewReady,        //msg
                              NO_ADDITIONAL_INFO); 
  
    wife->SetCooking(true);
  }
}


void CookStew::Execute(MinersWife* wife)
{
    M->Lock();
    SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": Fussin' over food";
 M->Unlock();
}

void CookStew::Exit(MinersWife* wife)
{
    M->Lock();
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": Puttin' the stew on the table";
 M->Unlock();
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
   
  switch(msg.Msg)
  {
    case Msg_StewReady:
    {
        M->Lock();
      
      cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
           " at time: " << Clock->GetCurrentTime();

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(wife->ID()) << ": StewReady! Lets eat";
     M->Unlock();
      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                wife->ID(),
                                ent_Miner_Bob,
                                Msg_StewReady,
                                NO_ADDITIONAL_INFO);

      wife->SetCooking(false);

      wife->GetFSM()->ChangeState(DoHouseWork::Instance());               
    }

    return true;

  }//end switch

  return false;
}

//------------------------------------------------------------------------With Philippe (cheating on her husband)

WithPhilippe* WithPhilippe::Instance()
{
    static WithPhilippe instance;

    return &instance;
}


void WithPhilippe::Enter(MinersWife* wife)
{
    //if not already with philippe
    if (!wife->WithLover())
    {
        wife->SetWithLover(true);
    }
}


void WithPhilippe::Execute(MinersWife* wife)
{
    M->Lock();
    cout << "\n" << GetNameOfEntity(wife->ID()) << ": *With Philippe*";
   M->Unlock();
}

void WithPhilippe::Exit(MinersWife* wife)
{
    wife->SetWithLover(false);
}


bool WithPhilippe::OnMessage(MinersWife* wife, const Telegram& msg)
{
    
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_HiHoneyImHome:
    {
        M->Lock();
        
        cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(wife->ID()) << "Whispers to Philippe : Bob is here ! Go, GO !";
        M->Unlock();
        //tell Philippe to run away
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            wife->ID(),
            ent_ElsasLover,
            Msg_BobIsBack,
            NO_ADDITIONAL_INFO);

        wife->SetWithLover(false);

        //cout << "\n" << GetNameOfEntity(wife->ID()) << ": By lover, can't wait to see you again.";
        M->Lock();
        cout << "\n" << GetNameOfEntity(wife->ID()) <<
            ": Hi honey. Let me make you some of mah fine country stew";
       M->Unlock();
        wife->GetFSM()->ChangeState(CookStew::Instance());
    }

    return true;

    }//end switch

    return false;
}