#include "game_base.h"
#include "linked_list.cpp"
#include <ctime>
#include <fstream>
#include<string>
#include <iostream>

field_t game_base::fields_[24];

linked_list<int> game_base::list_player_1_;

linked_list<int> game_base::list_player_2_;

int game_base::field_moves_[24][4] =
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

field_line_t game_base::field_lines_[16] =
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


void game_base::print_board()
{

	std::cout << "0 ------- 1 ------- 2\n|         |         |\n|  3 ---- 4 ---- 5  |\n|  |      |      |  |\n" 
	<< "|  |  6-- 7 --8  |  |\n|  |  |       |  |  |\n9--10-11      12-13-14\n|  |  |       |  |  |\n"
	<< "|  |  15-16- 17  |  |\n|  |      |      |  |\n|  18---- 19 ---20  |\n|         |         |\n" 
	<< "21------ 22 -------23\n";
}

void game_base::start_game()
{
	player player1;
	player player2;
	draw_color(player1, player2);
	play(player1, player2);
}


bool game_base::is_ended(player& player1, player& player2)
{
	check_is_ended(player1);
	check_is_ended(player2);
	if (!player1.get_is_lost())
	{
		std::cout << "first player loses the game.\n";
		log("Game over, first player loses the game.\n");
		return true;
	}
	if (!player2.get_is_lost())
	{
		std::cout << "second player loses the game.\n";
		log("Game over, second player loses the game.\n");
		return true;
	}
	return false;
}

void game_base::print_available_for_position(const int position)
{
	linked_list<int> list = get_available_for_position(position);
	list.print();
}

void game_base::check_is_ended(player& plr)
{
	if (plr.get_pawn_number() < 3)
	{
		plr.set_is_lost(true);
		return;
	}

	int count = 0;
	linked_list<int> list_taken = get_taken_fields(plr.get_id());
	for (int i = 0; i < list_taken.length(); ++i)
	{
		linked_list<int> list_available = get_available_for_position(list_taken[i]);
		if (!list_available.is_empty())
		{
			++count;
		}
	}
	if (count == 0)
	{
		plr.set_is_lost(true);
	}
}

void game_base::check_lines(int player_id, linked_list<int>& list)
{
	linked_list<int> temp_list = get_taken_lines(player_id);
	if (list.is_empty())
	{
		return;
	}
	if (temp_list.is_empty() && !list.is_empty())
	{
		for (int i = 0; i < list.length(); ++i)
		{
			field_lines_[i].is_changed = false;
			field_lines_[i].id = -1;
		}
	}
	else
	{
		for (int i = 0; i < list.length(); ++i)
		{
			if (!temp_list.contains(list[i]))
			{
				field_lines_[list[i]].is_changed = false;
				field_lines_[list[i]].id = -1;
			}
		}
	}
}

int game_base::count_lines(int player_id)
{
	int count = 0;
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
			++count;
		}
	}
	return count;
}

linked_list<int> game_base::get_available_for_position(int position)
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

void game_base::draw_color(player& player1, player& player2)
{
	const int id = (rand() % 2) + 0;
	if (id == 0)
	{
		std::cout << "White pawns were drawn by first player, he starts the game.\n";
		player1.set_id(id);
		player2.set_id(id + 1);
	}
	else if (id == 1)
	{
		std::cout << "White pawns were drawn by second player, he starts the game.\n";
		player1.set_id(id);
		player2.set_id(id - 1);
	}
}

linked_list<int> game_base::get_taken_lines(int player_id)
{
	linked_list<int> list;
	for (int i = 0; i < 16; ++i)
	{
		int count_lines = 0;
		if (field_lines_[i].id == player_id)
		{
			list.add(i);
		}
	}
	return list;
}

linked_list<int> game_base::get_available_fields()
{
	linked_list<int> list;
	for (int i = 0; i < 24; i++)
	{
		if (!fields_[i].is_taken)
		{
			list.add(i);
		}
	}
	return list;
}

linked_list<int> game_base::get_lines(int player_id)
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

linked_list<int> game_base::get_removable_fields(int player_id)
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

linked_list<int> game_base::get_taken_fields(int player_id)
{
	linked_list<int> list;
	for (int i = 0; i < 24; i++)
	{
		if (fields_[i].is_taken && fields_[i].id == player_id)
		{
			list.add(i);
		}
	}
	return list;
}

bool game_base::is_already_in(linked_list<int> list, int field)
{
	if (list.is_empty())
	{
		return false;
	}

	return list.contains(field);
}

bool game_base::is_available(int field)
{
	linked_list<int> list = get_available_fields();
	return list.contains(field);
}

bool game_base::is_removable(int field, int player_id)
{
	linked_list<int> list = get_removable_fields(player_id);
	if (list.is_empty())
	{
		std::cout << "There's nothing to remove.\n";
		return false;
	}
	return list.contains(field);
}
bool game_base::is_taken_by_player(int player_id, int position)
{
	linked_list<int> list = get_taken_fields(player_id);
	return list.contains(position);
}

void game_base::log(std::string log_info)
{
	std::ofstream logger;
	logger.open("log.txt", std::ofstream::out | std::ofstream::app);
	struct tm current;
	time_t currentTime;
	time(&currentTime);
	localtime_s(&current, &currentTime);
	logger << current.tm_year + 1900 << "-"
		<< current.tm_mon + 1 << "-" << current.tm_mday
		<< " " << current.tm_hour << ":" << current.tm_min << ":" << current.tm_sec << " " << log_info;
	logger.close();
}

void game_base::move(int player_id, int position)
{
	linked_list<int> list = get_available_for_position(position);
	while (list.is_empty())
	{
		std::cout << "There's none available positions to move for this position.\n";
	}
	std::cout << "List of available positions to move:\n";
	list.print();
	while (!pick_field(position, player_id));
}

bool game_base::pick_field(int position, int player_id)
{
	std::cout << "Pick field: ";
	int field;
	while (scanf_s("%d", &field) != 1 || !is_available(field) || getchar() != '\n')
	{
		std::cout << "Not available. Pick again:\n";
		while (getchar() != '\n');
	}
	linked_list<int> list = get_available_for_position(position);
	if (list.contains(field))
	{
		fields_[position].id = -1;
		fields_[position].is_taken = false;
		fields_[field].is_taken = true;
		fields_[field].id = player_id;
		return true;
	}
	return false;
}

void game_base::play(player& player1, player& player2)
{
	
}

void game_base::print_removable_fields(int player_id)
{
	linked_list<int> list = get_removable_fields(player_id);
	if (list.is_empty())
	{
		std::cout << "There's nothing to remove.\n";
	}
	else
	{
		std::cout << "Remove one of the available:\n";
		for (int i = 0; i < list.length(); ++i)
		{
			printf("%d ", list[i]);
		}
	}
	putchar('\n');
}

void game_base::print_taken_fields(const int player_id)
{
	linked_list<int> list = get_taken_fields(player_id);
	std::cout << "You can move one of those pawns:\n";
	linked_list<int> temp_list;
	for (int i = 0; i < list.length(); ++i)
	{
		temp_list = get_available_for_position(list[i]);
		if (!temp_list.is_empty())
		{
			printf("%d ", list[i]);
		}
	}
}

void game_base::remove(player& plr)
{
	int field;
	while (scanf_s("%d", &field) != 1 || !is_removable(field, plr.get_id()) || getchar() != '\n')
	{
		std::cout << "A number should be one of the following:\n";
		print_removable_fields(plr.get_id());
		std::cout << "Please select again:\n";
		while (getchar() != '\n');
	}
	fields_[field].id = -1;
	fields_[field].is_taken = false;
	plr.set_pawn_number(plr.get_pawn_number() - 1);
}

void game_base::remove_op_pawn(linked_list<int>& list, player& plr)
{
	for (int i = 0; i < list.length(); ++i)
	{
		field_lines_[list[i]].is_changed = true;
		print_removable_fields(plr.get_id());
		remove(plr);
	}
}

int game_base::select_position(int player_id)
{
	std::cout << "Please select one of your pawns to move:\n";
	print_taken_fields(player_id);
	putchar('\n');
	int position;
	while (scanf_s("%d", &position) != 1 || !is_taken_by_player(player_id, position) || getchar() != '\n')
	{
		std::cout << "Position of your pawn must have values printed above, select pawn again:\n";
		while (getchar() != '\n');
	}
	return position;
}

void game_base::set_field(player& plr)
{
	int position;
	linked_list<int> list = get_available_fields();
	std::cout << "Available fields:\n";
	list.print();
	std::cout << "Pick a field: ";
	while (scanf_s("%d", &position) != 1 || !is_available(position) || !set_pawn(plr, position) || getchar() != '\n')
	{
		std::cout << "Error, Field should be one of the following:\n";
		list.print();
		while (getchar() != '\n');
	}
}

bool game_base::set_pawn(player& plr, int position)
{
	if (fields_[position].is_taken)
	{
		std::cout << "Field is already taken.\n";
		return false;
	}

	fields_[position].is_taken = true;
	fields_[position].id = plr.get_id();
	plr.set_start_number(plr.get_start_number() - 1);
	return true;
}
