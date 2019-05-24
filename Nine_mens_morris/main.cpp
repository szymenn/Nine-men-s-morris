#include "game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(0)); 
	game::print_board();
}
