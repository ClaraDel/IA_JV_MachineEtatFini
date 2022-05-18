#ifndef MUTEX_H
#define MUTEX_H
//------------------------------------------------------------------------
//
//  Name:   Mutex.h
//
//  Desc:   Base class for a game object
//
//------------------------------------------------------------------------
#include <mutex>
#include <string>

#define M Mutex::Instance()
class Mutex
{
	private:
		std::mutex m;
		Mutex() {};
		~Mutex() {};
		Mutex(const Mutex&) {};
		Mutex& operator=(const Mutex&);

	
	public:
		static Mutex* Instance();
		void Lock();
		void Unlock();
};

#endif
