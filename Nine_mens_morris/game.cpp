#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>
#include <iostream>

field_t game::fields_[24];

available_field_t *game::head_player_1_ = nullptr;

available_field_t *game::head_player_2_ = nullptr;

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

field_line_t game::field_lines_[16] =
{
	{
		{0, 1, 2},
		false,
	},
	{
		{0, 9, 21},
		false,
	},	
	{
		{21, 22, 23},
		false,
	},	
	{
		{2, 14, 23},
		false,
	},	
	{
		{3, 4, 5},
		false,
	},	
	{
		{3, 10, 18},
		false,
	},	
	{
		{18, 19, 20},
		false,
	},	
	{
		{5, 13, 20},
		false,
	},	
	{
		{6, 7, 8},
		false,
	},	
	{
		{6, 11, 15},
		false,
	},	
	{
		{15, 16, 17},
		false,
	},	
	{
		{8, 12, 17},
		false,
	},
	{
		{1, 4, 7},
		false,
	},
	{
		{9, 10, 11},
		false,
	},
	{
		{16, 19, 22},
		false,
	},
	{
		{12, 13, 14},
		false,
	},
};

game::game()
{
	for(int i = 0; i < 24; ++i)
	{
		fields_[i].is_taken = false;
		fields_[i].id = -1;
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
	const int id = (rand() % 2) + 0;
	if (id == 0)
	{
		printf("White pawns were drawn by first player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id + 1);
	}else if(id == 1)
	{
		printf("White pawns were drawn by second player, he starts the game.\n");
		player1.set_id(id);
		player2.set_id(id - 1);
	}
}

void game::move(const int player_id, const int position)
{
	available_field_t *head = get_available_for_position(position);
	if(head == nullptr)
	{
		printf("Pick another position.\n");
		return;
	}
	print_available_for_position(position);
	while (!pick_field(position, player_id));
}

void game::print_available_for_position(const int position)
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

bool game::pick_field(const int position, const int player_id)
{
	printf("Pick field: ");
	int field;
	if(scanf_s("%d", &field)!=1)
	{
		printf("Not available.\n");
		return false;
	}
	available_field_t *head = get_available_for_position(position);
	available_field_t *current = head;
	while (current!=nullptr)
	{
		if(current->field == field)
		{
			fields_[position].id = -1;
			fields_[position].is_taken = false;
			fields_[field].is_taken = true;
			fields_[field].id = player_id;
			return true;
		}
		current = current->next;
	}
	return false;
}

available_field_t* game::get_available_for_position(const int position)
{
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
		}
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


bool game::set_pawn(player &plr, const int position)
{
	if (fields_[position].is_taken)
	{
		printf("Field is already taken.\n");
		return false;
	}

	fields_[position].is_taken = true;
	fields_[position].id = plr.get_id();
	plr.set_start_number(plr.get_start_number() - 1);
	return true;
}

bool game::is_ended(player& player1, player& player2)
{
	if (!player1.get_is_lost())
	{
		printf("first player loses the game.\n");
		return true;
	}
	if (!player2.get_is_lost())
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
	for(int i = 0; i < 24; i++)
	{
		if(!fields_[i].is_taken && head == nullptr)
		{
			head = (available_field_t*)(malloc(sizeof(available_field_t*)));
			head->field = i;
			current = head;
			current->next = nullptr;
		}
		else if(!fields_[i].is_taken)
		{
			current->next = (available_field_t*)malloc(sizeof(available_field_t*));
			current->next->field = i;
			current = current->next;
			current->next = nullptr;
		}
	}
	return head;
}

available_field_t* game::get_taken_fields(int player_id)
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 24; i++)
	{
		if(fields_[i].is_taken && fields_[i].id == player_id)
		{
			if (head == nullptr)
			{
				head = (available_field_t*)malloc(sizeof(available_field_t*));
				current = head;
				current->field = i;
				current->next = nullptr;
			}
			else 			
			{
				current->next = (available_field_t*)malloc(sizeof(available_field_t*));
				current = current->next;
				current->field = i;
				current->next = nullptr;
			}

		}
	}
	return head;
}

void game::print_taken_fields(int player_id)
{
	available_field_t *head = get_taken_fields(player_id);
	if(head == nullptr)
	{
		printf("There's no fields taken by your pawns.\n");
		return;
	}
	available_field_t *current = head;
	printf("Your pawns are placed:\n");
	while(current!=nullptr)
	{
		printf("%d ", current->field);
		current = current->next;
	}
}

bool game::is_taken_by_player(const int player_id, int position)
{
	available_field_t *head = get_taken_fields(player_id);
	available_field_t *current = head;
	while(current!=nullptr)
	{
		if(position == current->field)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}


int game::select_position(const int player_id)
{
	printf("Please select one of your pawns to move:\n");
	print_taken_fields(player_id);
	int position;
	while(scanf_s("%d", &position)!=1 || !is_taken_by_player(player_id, position) || getchar()!='\n')
	{
		printf("Position of your pawn must have values printed above, select pawn again:\n");
		while (getchar() != '\n');
	}
	return position;
}

void game::set_field(player &plr)
{
	int position;
	available_field_t *current = get_available_fields();
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
	set_pawn(plr, position);
}

bool game::check_lines(int player_id, available_field_t* head)
{
	if(head == nullptr)
	{
		return true;
	}
	available_field_t *current = head;
	available_field_t *head_temp = get_lines(player_id);
	if(head_temp == nullptr)
	{
		while(current != nullptr)
		{
			field_lines_[current->field].is_changed = false;
			current = current->next;
		}
		return true;
	}
	available_field_t *current_temp = head_temp;
	current = head;
	while(current != nullptr)
	{
		if(!contains(head_temp, current->field))
		{
			field_lines_[current->field].is_changed = false;
		}
		current = current->next;
	}
	
}

bool game::contains(available_field_t *head, const int field)
{
	if(head == nullptr)
	{
		return false;
	}
	available_field_t *current = head;
	while(current != nullptr)
	{
		if(current->field == field)
		{
			return true;
		}
	}
	return false;
}

void game::play(player& player1, player& player2)
{
	while (!is_ended(player1, player2))
	{
		int lines;
		if (player1.get_start_number() == 0)
		{
			if(player1.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				if (check_lines(player1.get_id(), head_player_1_))
				{
					lines = count_lines(player1.get_id());
					if (lines > 0)
					{
						printf("Remove one of the available:\n");
						print_removable_fields(player2.get_id());
					}
					head_player_1_ = get_lines(player1.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
				move(player2.get_id(), select_position(player2.get_id()));
				printf("Black pawns turn:\n");
				if (check_lines(player2.get_id(), head_player_2_))
				{
					lines = count_lines(player2.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player1);
					}
					head_player_2_ = get_lines(player2.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if(player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player2.get_id(), select_position(player2.get_id()));
				if (check_lines(player2.get_id(), head_player_2_))
				{
					lines = count_lines(player2.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player1);
					}
					head_player_2_ = get_lines(player2.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				if (check_lines(player1.get_id(), head_player_1_))
				{
					remove_op_pawn(count_lines(player1.get_id()), player2);
					head_player_1_ = get_lines(player1.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
			}
		}
		else
		{
			if (player1.get_id() == 0)
			{
				printf("White pawns turn:\n");
				set_field(player1);
				if (check_lines(player1.get_id(), head_player_1_))
				{
					lines = count_lines(player1.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player2);
					}
					head_player_1_ = get_lines(player1.get_id());
				}
				if (is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player2);
				if (check_lines(player2.get_id(), head_player_2_))
				{
					lines = count_lines(player2.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player1);
					}
					head_player_2_ = get_lines(player2.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if (player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				set_field(player2);
				if (check_lines(player2.get_id(), head_player_2_))
				{
					lines = count_lines(player2.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player1);
					}
					head_player_2_ = get_lines(player2.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player1);
				if (check_lines(player1.get_id(), head_player_1_))
				{
					lines = count_lines(player1.get_id());
					if (lines > 0)
					{
						remove_op_pawn(lines, player2);
					}
					head_player_1_ = get_lines(player1.get_id());
				}
				if(is_ended(player1, player2))
				{
					break;
				}
			}
		}
	}
}

int game::count_lines(const int player_id)
{
	int count = 0;
	for(int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for(int j = 0; j < 3; ++j)
		{
			if(fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && field_lines_[i].is_changed)
			{
				++count_lines;
			}
		}
		if (count_lines == 3)
		{
			++count;
		}
	}
	return count;
}



available_field_t* game::get_lines(const int player_id)
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && field_lines_[i].is_changed)
			{
				++count_lines;
			}
		}
		if (count_lines == 3)
		{
			if(head == nullptr)
			{
				head = (available_field_t*)malloc(sizeof(available_field_t*));
				current = head;
				current->field = i;
				current->next = nullptr;
			}
			else
			{
				current->next = (available_field_t*)malloc(sizeof(available_field_t*));
				current = current->next;
				current->field = i;
				current->next = nullptr;
			}
		}
	}
	return head;
}


void game::remove_op_pawn(int num_pawns, player &plr)
{
	for(int i = 0; i < num_pawns; ++i)
	{
		printf("Remove one of the available: \n");
		print_removable_fields(plr.get_id());
		remove(plr);
	}
}

void game::remove(player &plr)
{
	int field;
	while(scanf_s("%d", &field)!=1||!is_removable(field, plr.get_id())||getchar()!='\n')
	{
		printf("A number should one of the following:\n");
		print_removable_fields(plr.get_id());
		printf("Please select again:\n");
		while (getchar() != '\n');
	}
	fields_[field].id = -1;
	fields_[field].is_taken = false;
	plr.set_pawn_number(plr.get_pawn_number() - 1);
}

available_field_t* game::get_removable_fields(int player_id)
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && !is_already_in(head, field_lines_[i].line[j]))
			{
				if(head == nullptr)
				{
					head = (available_field_t*)malloc(sizeof(available_field_t*));
					current = head;
					current->next = nullptr;
					current->prev = nullptr;
				}
				else
				{
					current->next = (available_field_t*)malloc(sizeof(available_field_t*));
					available_field_t* temp = current;
					current = current->next;
					current->next = nullptr;
					current->prev = temp;
				}
				current->field = field_lines_[i].line[j];
				++count_lines;
			}
		}
		if (count_lines == 3)
		{
			for(int k = 0; k < 3; ++k)
			{
				current->field = -1;
				current = current->prev;
			}
			current = head;
			while(current->next!=nullptr)
			{
				current = current->next;
			}
		}
	}
	return head;
}

bool game::is_already_in(available_field_t *head, const int field)
{
	if(head == nullptr)
	{
		return false;
	}
	available_field_t *current = head;
	while(current!=nullptr)
	{
		if (current->field == field || current->field == -1)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

void game::print_removable_fields(int player_id)
{
	available_field_t *head = get_removable_fields(player_id);
	available_field_t *current = head;
	if(head == nullptr)
	{
		printf("There's nothing to remove.\n");
	}
	else
	{
		while(current!=nullptr)
		{
			if(current->field == -1)
			{
				current = current->next;
				continue;
			}
			printf("%d ", current->field);
			current = current->next;
		}
	}
	putchar('\n');
}

bool game::is_removable(int field, int player_id)
{
	available_field_t *head = get_removable_fields(player_id);
	if (head == nullptr)
	{
		printf("There's nothing to remove.\n");
		return false;
	}
	available_field_t *current = head;
	while (current != nullptr)
	{
		if(current->field == field)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}







