#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>
#include <iostream>
#include "linked_list.cpp "

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
		-1
	},
	{
		{0, 9, 21},
		false,
		-1
	},	
	{
		{21, 22, 23},
		false,
		-1
	},	
	{
		{2, 14, 23},
		false,
		-1
	},	
	{
		{3, 4, 5},
		false,
		-1
	},	
	{
		{3, 10, 18},
		false,
		-1
	},	
	{
		{18, 19, 20},
		false,
		-1
	},	
	{
		{5, 13, 20},
		false,
		-1
	},	
	{
		{6, 7, 8},
		false,
		-1
	},	
	{
		{6, 11, 15},
		false,
		-1
	},	
	{
		{15, 16, 17},
		false,
		-1
	},	
	{
		{8, 12, 17},
		false,
		-1
	},
	{
		{1, 4, 7},
		false,
		-1
	},
	{
		{9, 10, 11},
		false,
		-1
	},
	{
		{16, 19, 22},
		false,
		-1
	},
	{
		{12, 13, 14},
		false,
		-1
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

game::~game()
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
	linked_list<int> list = get_available_for_position(position);
	list.print();
	while (!pick_field(position, player_id));
}

void game::print_available_for_position(const int position)
{
	linked_list<int> list = get_available_for_position(position);
	list.print();
}

bool game::pick_field(const int position, const int player_id)
{
	printf("Pick field: ");
	int field;
	while(scanf_s("%d", &field)!=1 || is_available(field) || getchar()!='\n')
	{
		printf("Not available. Pick again:\n");
		while (getchar() != '\n');
	}
	linked_list<int> list = get_available_for_position(position);
	if(list.contains(field))
	{
		fields_[position].id = -1;
		fields_[position].is_taken = false;
		fields_[field].is_taken = true;
		fields_[field].id = player_id;
		return true;
	}
	return false;
}

linked_list<int> game::get_available_for_position(const int position)
{
	linked_list<int> list;
	for (int i = 0; i < 4; ++i)
	{
		if (field_moves_[position][i] == -1)
		{
			break;
		}
		if (is_available(field_moves_[position][i]))
		{
			list.add(field_moves_[position][i]);
		}
	}
	return list;
}


bool game::is_available(const int field)
{
	linked_list<int> list = get_available_fields();
	return list.contains(field);
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

linked_list<int> game::get_available_fields()
{
	linked_list<int> list;
	for(int i = 0; i < 24; i++)
	{
		if(!fields_[i].is_taken)
		{
			list.add(i);
		}
	}
	return list;
}

linked_list<int> game::get_taken_fields(int player_id)
{
	linked_list<int> list;
	for (int i = 0; i < 24; i++)
	{
		if(fields_[i].is_taken && fields_[i].id == player_id)
		{
			list.add(i);
		}
	}
	return list;
}

void game::print_taken_fields(int player_id)
{
	linked_list<int> list = get_taken_fields(player_id);
	printf("Your pawns are placed:\n");
	list.print();
}

bool game::is_taken_by_player(const int player_id, int position)
{
	linked_list<int> list = get_taken_fields(player_id);
	return list.contains(position);
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
	linked_list<int> list = get_available_fields();
	printf("Available fields:\n");
	list.print();
	printf("Pick a field: ");
	while (scanf_s("%d", &position) != 1 || !is_available(position) || !set_pawn(plr, position) || getchar() != '\n')
	{
		printf("Error, Field should be one of the following:\n");
		list.print();
		while (getchar() != '\n');
	}
}

void game::play(player& player1, player& player2)
{
	while (!is_ended(player1, player2))
	{
		available_field_t *head_lines;
		if (player1.get_start_number() == 0)
		{
			if (player1.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				check_lines(player1.get_id(), head_player_1_);
				head_lines = get_lines(player1.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player2);
				}
				head_player_1_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
				move(player2.get_id(), select_position(player2.get_id()));
				check_lines(player2.get_id(), head_player_2_);
				head_lines = get_lines(player2.get_id());
				printf("Black pawns turn:\n");
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player1);
				}
				head_player_2_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if(player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player2.get_id(), select_position(player2.get_id()));
				check_lines(player2.get_id(), head_player_2_);
				head_lines = get_lines(player2.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player1);
				}
				head_player_2_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				check_lines(player1.get_id(), head_player_1_);
				head_lines = get_lines(player1.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player2);
				}
				head_player_1_ = head_lines;
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
				check_lines(player1.get_id(), head_player_1_);
				head_lines = get_lines(player1.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player2);
				}
				head_player_1_ = head_lines;
				if (is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player2);
				check_lines(player2.get_id(), head_player_2_);
				head_lines = get_lines(player2.get_id());
				if(head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player1);
				}
				head_player_2_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if (player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				set_field(player2);
				check_lines(player2.get_id(), head_player_2_);
				head_lines = get_lines(player2.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player1);
				}
				head_player_2_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player1);
				check_lines(player1.get_id(), head_player_1_);
				head_lines = get_lines(player1.get_id());
				if (head_lines != nullptr)
				{
					remove_op_pawn(head_lines, player2);
				}
				head_player_1_ = head_lines;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
		}
	}
}

void game::check_lines(const int player_id, available_field_t* head)
{
	available_field_t *current = head;
	available_field_t *head_temp = get_taken_lines(player_id);
	if (head == nullptr)
	{
		return;
	}
	if (head_temp == nullptr && head != nullptr)
	{
		while (current != nullptr)
		{
			field_lines_[current->field].is_changed = false;
			field_lines_[current->field].id = -1;
			current = current->next;
		}
	}
	else
	{
		current = head;
		while (current != nullptr)
		{
			if (!contains(head_temp, current->field))
			{
				field_lines_[current->field].is_changed = false;
				field_lines_[current->field].id = -1;
			}
			current = current->next;
		}
	}
}

available_field_t* game::get_taken_lines(const int player_id)
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		if(field_lines_[i].id == player_id)
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
				current->next = (available_field*)malloc(sizeof(available_field_t*));
				current = current->next;
				current->field = i;
				current->next = nullptr;
				
			}
		}
	}
	return head;
}

bool game::contains(available_field_t *head, const int field)
{
	available_field_t *current = head;
	while (current != nullptr)
	{
		if (current->field == field)
		{
			return true;
		}
	}
	return false;
}

int game::count_lines(const int player_id)
{
	int count = 0;
	for(int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for(int j = 0; j < 3; ++j)
		{
			if(fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && !field_lines_[i].is_changed)
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
			if (fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && !field_lines_[i].is_changed)
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
				field_lines_[i].id = player_id;
				current->next = nullptr;
			}
			else
			{
				current->next = (available_field_t*)malloc(sizeof(available_field_t*));
				current = current->next;
				current->field = i;
				field_lines_[i].id = player_id;
				current->next = nullptr;
			}
		}
	}
	return head;
}


void game::remove_op_pawn(available_field_t *head, player &plr)
{
	available_field_t *current = head;
	while (current != nullptr)
	{
		field_lines_[current->field].is_changed = true;
		print_removable_fields(plr.get_id());
		remove(plr);
		current = current->next;
	}
}

void game::remove(player &plr)
{
	int field;
	while (scanf_s("%d", &field) != 1 || !is_removable(field, plr.get_id()) || getchar() != '\n')
	{
		printf("A number should be one of the following:\n");
		print_removable_fields(plr.get_id());
		printf("Please select again:\n");
		while (getchar() != '\n');
	}
	fields_[field].id = -1;
	fields_[field].is_taken = false;
	plr.set_pawn_number(plr.get_pawn_number() - 1);
}

available_field_t* game::get_removable_fields(const int player_id)
{
	available_field_t *head = nullptr;
	available_field_t *current = nullptr;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (field_lines_[i].id == player_id)
			{
				if (head == nullptr)
				{
					head = (available_field_t*)malloc(sizeof(available_field_t*));
					current = head;
					current->field = -1;
					current->next = nullptr;
				}
				else
				{
					current->next = (available_field_t*)malloc(sizeof(available_field_t*));
					current = current->next;
					current->field = -1;
					current->next = nullptr;
				}
			}
			if (fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && !is_already_in(head, field_lines_[i].line[j]))
			{
				if (head == nullptr)
				{
					head = (available_field_t*)malloc(sizeof(available_field_t*));
					current = head;
					current->field = field_lines_[i].line[j];
					current->next = nullptr;
				}
				else
				{
					current->next = (available_field_t*)malloc(sizeof(available_field_t*));
					current = current->next;
					current->field = field_lines_[i].line[j];
					current->next = nullptr;
				}
			}
		}
		if (count_lines == 3)
		{
			for (int k = 0; k < 3; ++k)
			{
				current->field = -1;
				current = current->prev;
			}
			current = head;
			while (current->next != nullptr)
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
		if (current->field == field)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

void game::print_removable_fields(const int player_id)
{
	available_field_t *head = get_removable_fields(player_id);
	available_field_t *current = head;
	if(head == nullptr)
	{
		printf("There's nothing to remove.\n");
	}
	else
	{
		printf("Remove one of the available:\n");
		while (current != nullptr)
		{
			if (current->field == -1)
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

bool game::is_removable(const int field, const int player_id)
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







