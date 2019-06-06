#include "game.h"
#include <cstdlib>
#include <ctime>
#include "linked_list.cpp"
#include "game_automated.h"

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	int choice;
	std::cout << "1. Automated game\n2. Two players game\nPlease select one of the above:\n";
	while(scanf_s("%d", &choice) != 1 || choice < 1 || choice > 2 || getchar()!='\n')
	{
		std::cout << "Not available. Please select one of the above:\n";
		while (getchar() != '\n');
	}
	if (choice == 1)
	{
		game_automated game_automated;
		game_automated.print_board();
		game_automated.start_game();
	}
	if(choice == 2)
	{
		game game;
		game.print_board();
		game.start_game();
	}

	return 0;
}
