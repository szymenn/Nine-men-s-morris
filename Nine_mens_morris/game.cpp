#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>

field_t game::fields_[24];

int game::field_moves_[24][4] = 
{
	{1, 9, -1, -1},
	{0, 2, 4, -1},
	{1, 14, -1, -1},
	{4, 10, -1, -1},
	{1, 3, 5, 7},
	{4, 13, -1, -1},
	{7, 11, -1, -1},
	{4, 6, 8, -1},
	{7, 12, -1, -1},
	{0, 10, 21, -1},
	{3, 9, 11, 18},
	{6, 10, 15, -1},
	{8, 13, 17, -1},
	{5, 12, 14, 20},
	{2, 13, 23, -1},
	{11, 16, -1, -1},
	{15, 17, 19, -1},
	{12, 16, -1, -1},
	{10, 19, -1, -1},
	{16, 18, 20, 22},
	{13, 19, -1, -1},
	{9, 22, -1, -1},
	{19, 21, 23, -1},
	{14, 22, -1, -1}
};

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

void game::move(int player_id, const int position)
{
	print_available_for_position(position);

}

void game::print_available_for_position(int position)
{
	available_field_t *head = get_available_for_position(position);
	if(head == nullptr)
	{
		printf("None.");
	}
	else
	{
		available_field_t *current = head;
		while(current!=nullptr)
		{
			printf("%d ", current->field);
			current = current->next;
		}
	}
	putchar('\n');
}

bool game::pick_field(int position)
{
	printf("Pick field: ");
	int field;
	bool is_valid = true;
	if(scanf_s("%d", &field)!=1)
	{
		return false;
	}
	available_field_t *head = get_available_for_position(position);
	available_field_t *current = head;
	while (current!=nullptr)
	{
		if(current->field == field)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

available_field_t* game::get_available_for_position(const int position)
{
	int j = 0;
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 4; ++i)
	{
		if (field_moves_[position][i] == -1)
		{
			break;
		}
		if (is_available(field_moves_[position][i]))
		{
			if (head == nullptr)
			{
				head = (available_field_t *)malloc(sizeof(available_field_t*));
				head->field = field_moves_[position][i];
				current = head;
				current->next = nullptr;
			}
			else
			{
				current->next = (available_field_t *)malloc(sizeof(available_field_t*));
				current = current->next;
				current->field = field_moves_[position][i];
				current->next = nullptr;
			}
			++j;
		}
	}
	if (j == 0)
	{
		return nullptr;
	}
	return head;
}


bool game::is_available(const int field)
{
	available_field_t *head = get_available_fields();
	available_field_t *current = head;
	while(current != nullptr)
	{
		if(current->field == field)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}


bool game::set_pawn(const int player_id, const int position)
{
	if(fields_[position].position)
	{
		printf("Fields is already taken.\n");
		return false;
	}

	fields_[position].position = true;
	fields_[position].id = player_id;
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
			head = (available_field_t*)(malloc(sizeof(available_field_t*)));
			head->field = i;
			current = head;
			current->next = nullptr;
		}
		else if(!fields_[i].position)
		{
			current->next = (available_field_t*)malloc(sizeof(available_field_t*));
			current->next->field = i;
			current = current->next;
			current->next = nullptr;
		}
	}
	return head;
}

void game::set_field(int player_id)
{
	int position;
	available_field_t *current = nullptr;
	current = get_available_fields();
	printf("Available fields:\n");
	while(current!=nullptr)
	{
		printf("%d ", current->field);
		current = current->next;
	}
	putchar('\n');
	printf("Pick a field: ");
	while (scanf_s("%d", &position) != 1 || position < 0 || position > 23 || getchar() != '\n')
	{
		printf("Error, Field should be an integer from 0 to 23. Pick field again:\n");
		while (getchar() != '\n');
	}
	set_pawn(player_id, position);
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
				set_field(player1.get_id());
				if (is_ended(player1, player2))
				{
					break;
				}
				set_field(player2.get_id());
			}
			if (player1.get_id() == 2)
			{
				set_field(player2.get_id());
				if (is_ended(player1, player2))
				{
					break;
				}
				set_field(player1.get_id());
			}
		}
	}
}



