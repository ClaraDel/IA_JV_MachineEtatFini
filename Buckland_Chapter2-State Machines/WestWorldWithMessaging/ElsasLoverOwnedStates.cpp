#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "ElsasLoverOwnedStates.h"
#include "ElsasLover.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "Mutex.h"

#include <iostream>
using std::cout;
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

ElsasLoverGlobalState* ElsasLoverGlobalState::Instance()
{
	static ElsasLoverGlobalState instance;

	return &instance;
}

void ElsasLoverGlobalState::Execute(ElsasLover* lover)
{
	/*if ((RandFloat() < 0.1) &&
		!wife->GetFSM()->isInState(*VisitBathroom::Instance()))
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}*/
}

bool ElsasLoverGlobalState::OnMessage(ElsasLover* lover, const Telegram& msg)
{
	
	switch (msg.Msg)
	{
	case Msg_ComeToSeeMe:
	{

		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		M->Lock();

		

		cout << "\nMessage handled by " << GetNameOfEntity(lover->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(lover->ID()) <<
			": Ok Elsa, can't wait to see you.";
		M->Unlock();

		lover->GetFSM()->ChangeState(WithElsa::Instance());
	}

	return true;

	}//end switch

	return false;
}

void ElsasLoverGlobalState::Enter(ElsasLover* lover)
{
}

void ElsasLoverGlobalState::Exit(ElsasLover* lover)
{
	//cout << "\n" << GetNameOfEntity(lover->ID()) << ": Leavin' the Jon";
}

//-------------------------------------------------------------------------Live his life

LiveHisLife* LiveHisLife::Instance()
{
	static LiveHisLife instance;

	return &instance;
}


void LiveHisLife::Enter(ElsasLover* lover)
{
	M->Lock();
	//if Phillips is not already located in his house, he must change location 
	if (lover->Location() != PhilippesHome)
	{
		SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		cout << "\n" << GetNameOfEntity(lover->ID()) << ": " << "Walkin' to his home";
		

		lover->ChangeLocation(PhilippesHome);
	}
	SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\n" << GetNameOfEntity(lover->ID()) << ": Time to return to my business";
	M->Unlock();

}


void LiveHisLife::Execute(ElsasLover* lover)
{
	M->Lock();
	SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(lover->ID()) << ": Working at the mine";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(lover->ID()) << ": Sleeping";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(lover->ID()) << ": At home";

		break;
	}
	M->Unlock();

}

void LiveHisLife::Exit(ElsasLover* lover)
{
}

bool LiveHisLife::OnMessage(ElsasLover* lover, const Telegram& msg)
{
	return false;
}

//-------------------------------------------------------------------------With Elsa

WithElsa* WithElsa::Instance()
{
	static WithElsa instance;

	return &instance;
}


void WithElsa::Enter(ElsasLover* lover)
{
	//if Phillips is not already located in Elsa's house, he must change location 
	if (lover->Location() != shack)
	{
		M->Lock();
		SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		cout << "\n" << GetNameOfEntity(lover->ID()) << ": " << "Walkin' to Elsa's shack";
		M->Unlock();

		lover->ChangeLocation(shack);
	}
	M->Lock();
	SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\n" << GetNameOfEntity(lover->ID()) << ": Hello my dear Elsa !";
	M->Unlock();

}


void WithElsa::Execute(ElsasLover* lover)
{
	M->Lock();
	SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\n" << GetNameOfEntity(lover->ID()) << " *With Elsa*";
	M->Unlock();

}

void WithElsa::Exit(ElsasLover* lover)
{
	M->Lock();
	SetTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\n" << GetNameOfEntity(lover->ID()) << ": See you Elsa !";
	M->Unlock();

}

bool WithElsa::OnMessage(ElsasLover* lover, const Telegram& msg)
{


	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
	case Msg_BobIsBack:
	{
		M->Lock();
		cout << "\nMessage received by " << GetNameOfEntity(lover->ID()) <<
			" at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(lover->ID()) << "Whispering : Ok I'm going out the back of the house...";

		if (lover->Location() != PhilippesHome)
		{
			cout << "\n" << GetNameOfEntity(lover->ID()) << ": " << "Walkin' to his home";

			lover->ChangeLocation(PhilippesHome);
		}
		M->Unlock();

		lover->GetFSM()->ChangeState(LiveHisLife::Instance());
	}

	return true;

	}//end switch

	return false;
}