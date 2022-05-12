#include <fstream>
#include <thread>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "ElsasLover.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create Philippe, the lover of Elsa
  ElsasLover* Philippe = new ElsasLover(ent_ElsasLover);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Philippe);

  std::vector<std::thread> threads;
  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
    Philippe->Update();
	threads.push_back(Bob->UpdateThread());
	threads.push_back(Elsa->UpdateThread());
	threads.push_back(Philippe->UpdateThread());
	while (!threads.empty())
	{
		threads.back().join();
		threads.pop_back();
	}
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

        Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Philippe;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






