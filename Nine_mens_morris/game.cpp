#include "game.h"
#include <cstdio>
game::game()
= default;

void game::print_state()
{
	printf("0 ------- 1 ------- 2\n|         |         |\n|  3 ---- 4 ---- 5  |\n|  |      |      |  |\n");
	printf("|  |  6-- 7 --8  |  |\n|  |  |       |  |  |\n9--10-11      12-13-14\n|  |  |       |  |  |\n");
	printf("|  |  15-16- 17  |  |\n|  |      |      |  |\n|  18---- 19 ---20  |\n|         |         |\n");
	printf("21------ 22 -------23\n");
}

void game::set_position(int position)
{
	if(position < 0 || position > 23)
	{
		printf("Nie istnieje takie pole w grze.\n");
	}
	else if(!positions_[position])
	{
		positions_[position] = true;
	}
	else
	{
		printf("To pole jest zajete.\n");
	}
}


