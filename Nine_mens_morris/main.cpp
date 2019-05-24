#include "game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(nullptr)); 
	game::print_board();
}
