#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>

field_t game::fields_[24];

game::game()
{
	for(int i = 0; i < 24; i++)
	{
		fields_[i].position = false;
		fields_[i].id = 0;
	}
}

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
	play(player1, player2);

}

void game::draw_color(player &player1, player &player2)
{
	int id = (rand() % 2) + 1;
	if (id == 1)
	{
		printf("White pawns were drawn by first player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id + 1);
	}else if(id == 2)
	{
		printf("White pawns were drawn by second player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id - 1);
	}
}

void game::move(player &plr)
{
	if(plr.get_start_number() == 0)
	{
		printf("Move one of your pawns");
	}
	else
	{
		
	}
}


bool game::set_pawn(player &plr, const int position)
{
	if(fields_[position].position)
	{
		printf("Fields is already taken.\n");
		return false;
	}

	fields_[position].position = true;
	fields_[position].id = plr.get_id();
	return true;
}
 

bool game::is_ended(player& player1, player& player2)
{
	if (player1.get_is_lost())
	{
		printf("first player loses the game.\n");
		return true;
	}
	if (player2.get_is_lost())
	{
		printf("second player loses the game.\n");
		return true;
	}
	return false;
}

available_field_t* game::get_available_fields()
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for(int i = 0; i < 23; i++)
	{
		if(!fields_[i].position && head == nullptr)
		{
			head->field = i;
			current = head;
			current->next = nullptr;
		}
		else if(!fields_[i].position)
		{
			current->next->field = i;
			current = current->next;
			current->next = nullptr;
		}
	}
	return head;
}

void game::set_field(player &plr)
{
	int position;
	available_field_t *current = nullptr;
	current = get_available_fields();
	printf("Wolne pola:\n");
	while(current!=nullptr)
	{
		printf("%d ", current->field);
		current = current->next;
	}
	putchar('\n');
	printf("Wybierz pole ");
	while (scanf_s("%d", &position) != 1 || position < 0 || position > 23 || getchar() != '\n')
	{
		printf("Pole powinna byc liczba calowita z przedzialu od 0 do 23.\n");
		while (getchar() != '\n');
	}
	set_pawn(plr, position);
}

void game::play(player& player1, player& player2)
{
	while (!is_ended(player1, player2))
	{
		if (player1.get_pawn_number() == 0)
		{
			
		}
		else
		{
			if (player1.get_id() == 1)
			{
				set_field(player1);
				if (is_ended(player1, player2))
				{
					break;
				}
				set_field(player2);
			}
			if (player1.get_id() == 2)
			{
				set_field(player2);
				if (is_ended(player1, player2))
				{
					break;
				}
				set_field(player1);
			}
		}
	}
}



