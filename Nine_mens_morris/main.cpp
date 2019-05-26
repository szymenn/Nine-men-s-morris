#include "game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	game game1;
	game::print_board();
	game1.start_game();
	return 0;
}
