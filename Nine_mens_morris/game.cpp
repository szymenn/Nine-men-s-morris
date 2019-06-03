#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>
#include <iostream>
#include "linked_list.cpp "

field_t game::fields_[24];



linked_list<int> game::list_player_1_;

linked_list<int> game::list_player_2_;

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
	check_is_ended(player1);
	check_is_ended(player2);
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

bool game::is_taken_by_player(const int player_id, const int position)
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
		linked_list<int> temp_list;
		if (player1.get_start_number() == 0)
		{
			if (player1.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
				}
				list_player_1_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				move(player2.get_id(), select_position(player2.get_id()));
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				printf("Black pawns turn:\n"); 
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if(player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				move(player2.get_id(), select_position(player2.get_id()));
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				move(player1.get_id(), select_position(player1.get_id()));
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
				}
				list_player_1_ = temp_list;
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
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
				}
				list_player_1_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player2);
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if(!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
			if (player2.get_id() == 0)
			{
				printf("White pawns turn:\n");
				set_field(player2);
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
				set_field(player1);
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
				}
				list_player_1_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
			}
		}
	}
}

void game::check_lines(const int player_id, linked_list<int> &list)
{
	linked_list<int> temp_list = get_taken_lines(player_id);
	if (list.is_empty())
	{
		return;
	}
	if (temp_list.is_empty() && !list.is_empty())
	{
		for(int i = 0; i < list.length(); ++i)
		{
			field_lines_[i].is_changed = false;
			field_lines_[i].id = -1;
		}
	}
	else
	{
		for(int i = 0; i < list.length(); ++i)
		{
			if(!temp_list.contains(list[i]))
			{
				field_lines_[list[i]].is_changed = false;
				field_lines_[list[i]].id = -1;
			}
		}
	}
}

linked_list<int> game::get_taken_lines(const int player_id)
{
	linked_list<int> list;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		if(field_lines_[i].id == player_id)
		{
			list.add(i);
		}
	}
	return list;
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

linked_list<int> game::get_lines(const int player_id)
{
	linked_list<int> list;
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
			list.add(i);
			field_lines_[i].id = player_id;
		}
	}
	return list;
}


void game::remove_op_pawn(linked_list<int> &list, player &plr)
{
	for (int i = 0; i < list.length(); ++i)
	{
		field_lines_[list[i]].is_changed = true;
		print_removable_fields(plr.get_id());
		remove(plr);
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

linked_list<int> game::get_removable_fields(const int player_id)
{
	linked_list<int> list;
	linked_list<int> temp_list;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (fields_[field_lines_[i].line[j]].is_taken && fields_[field_lines_[i].line[j]].id == player_id && !is_already_in(temp_list, field_lines_[i].line[j]))
			{
				list.add(field_lines_[i].line[j]);
				temp_list.add(field_lines_[i].line[j]);
				++count_lines;
			}
		}
		if (count_lines >= 3)
		{
			for (int j = 0; j < 3; ++j)
			{
				list.pop();
			}
		}
	}
	return list;
}

bool game::is_already_in(linked_list<int> list, const int field)
{
	if (list.is_empty())
	{
		return false;
	}

	return list.contains(field);
}

void game::print_removable_fields(const int player_id)
{
	linked_list<int> list = get_removable_fields(player_id);
	if(list.is_empty())
	{
		printf("There's nothing to remove.\n");
	}
	else
	{
		printf("Remove one of the available:\n");
		for (int i = 0; i < list.length(); ++i)
		{
			printf("%d ", list[i]);
		}
	}
	putchar('\n');
}

bool game::is_removable(const int field, const int player_id)
{
	linked_list<int> list = get_removable_fields(player_id);
	if (list.is_empty())
	{
		printf("There's nothing to remove.\n");
		return false;
	}
	return list.contains(field);
}

void game::check_is_ended(player &plr)
{
	if(plr.get_pawn_number() < 3)
	{
		plr.set_is_lost(true);
		return;
	}

	int count = 0;
	linked_list<int> list_taken = get_taken_fields(plr.get_id());
	for(int i = 0; i < list_taken.length(); ++i)
	{
		linked_list<int> list_available = get_available_for_position(list_taken[i]);
		if(!list_available.is_empty())
		{
			++count;
		}
	}
	if(count == 0)
	{
		plr.set_is_lost(true);
	}

}





