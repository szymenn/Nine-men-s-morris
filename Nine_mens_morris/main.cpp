#include "game.h"
#include <cstdlib>
#include <ctime>
#include "linked_list.cpp"
#include "game_automated.h"

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	game_automated game_automated;
	game_automated.print_board();
	game_automated.start_game();

	return 0;
}
