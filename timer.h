#include "time.h"

//starts a timer

namespace Timer
{

unsigned long time_initial;

void start()
{
	time_initial = clock() / CLOCKS_PER_SEC;
}

//returns the number of seconds since start() was called
int time()
{
	unsigned long time_final = clock() / CLOCKS_PER_SEC;
	return time_final - time_initial;
}

};
