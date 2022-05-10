#ifndef ELSASLOVER_OWNED_STATES_H
#define ELSASLOVER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   ElsasLoverGlobalState.h
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class ElsasLover;
struct Telegram;

//------------------------------------------------------------------------
//
//  Description
//------------------------------------------------------------------------
class ElsasLoverGlobalState : public State<ElsasLover>
{
private:

	ElsasLoverGlobalState() {}

	//copy ctor and assignment should be private
	ElsasLoverGlobalState(const ElsasLoverGlobalState&);
	ElsasLoverGlobalState& operator=(const ElsasLoverGlobalState&);

public:

	//this is a singleton
	static ElsasLoverGlobalState* Instance();

	virtual void Enter(ElsasLover* lover);

	virtual void Execute(ElsasLover* lover);

	virtual void Exit(ElsasLover* lover);

	virtual bool OnMessage(ElsasLover* agent, const Telegram& msg);

};

//
//  Description
//------------------------------------------------------------------------
class LiveHisLife : public State<ElsasLover>
{
private:

	LiveHisLife() {}

	//copy ctor and assignment should be private
	LiveHisLife(const LiveHisLife&);
	LiveHisLife& operator=(const LiveHisLife&);

public:

	//this is a singleton
	static LiveHisLife* Instance();

	virtual void Enter(ElsasLover* lover);

	virtual void Execute(ElsasLover* lover);

	virtual void Exit(ElsasLover* lover);

	virtual bool OnMessage(ElsasLover* agent, const Telegram& msg);

};

// Spend time with Elsa, his lover, at her home
//------------------------------------------------------------------------
class WithElsa : public State<ElsasLover>
{
private:

	WithElsa() {}

	//copy ctor and assignment should be private
	WithElsa(const WithElsa&);
	WithElsa& operator=(const WithElsa&);

public:

	//this is a singleton
	static WithElsa* Instance();

	virtual void Enter(ElsasLover* lover);

	virtual void Execute(ElsasLover* lover);

	virtual void Exit(ElsasLover* lover);

	virtual bool OnMessage(ElsasLover* agent, const Telegram& msg);

};

#endif
