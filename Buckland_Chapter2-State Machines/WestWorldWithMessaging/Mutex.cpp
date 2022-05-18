#include "Mutex.h"
#include "Time/CrudeTimer.h"
Mutex* Mutex::Instance()
{
	static Mutex instance;
	return &instance;
}
void Mutex::Lock() {
	while (!m.try_lock()) {
		Sleep(100);
	}
}
void Mutex::Unlock() {
	m.unlock();
}