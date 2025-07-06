#include "game_loop.h"  
#include <stdlib.h>  
#include <time.h>  

int main()  
{  
	srand(time(NULL)); // Seed the random number generator   
	play_game();  
	return 0;  
}
