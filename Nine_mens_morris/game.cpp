#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>
game::game()
= default;

void game::print_board()
{
	printf("0 ------- 1 ------- 2\n|         |         |\n|  3 ---- 4 ---- 5  |\n|  |      |      |  |\n");
	printf("|  |  6-- 7 --8  |  |\n|  |  |       |  |  |\n9--10-11      12-13-14\n|  |  |       |  |  |\n");
	printf("|  |  15-16- 17  |  |\n|  |      |      |  |\n|  18---- 19 ---20  |\n|         |         |\n");
	printf("21------ 22 -------23\n");
}

void game::start_game()
{
	player player1;
	player player2;
	draw_color(player1, player2);

}

void game::draw_color(player &player1, player &player2)
{
	int id = (rand() % 2) + 0;
	if (id == 0)
	{
		printf("White pawns were drawn by first player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id + 1);
	}else
	{
		printf("White pawns were drawn by second player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id - 1);
	}
}

void game::move(player &player1, player &player2)
{
	
}






