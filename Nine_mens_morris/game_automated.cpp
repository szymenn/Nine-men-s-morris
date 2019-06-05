#include "game_automated.h"
#include <iostream>

game_automated::game_automated()
= default;

int game_automated::pick_random(linked_list<int> list)
{
	if(list.is_empty())
	{
		return -1;
	}
	const int rand_pick = rand() % list.length() + 0;
	return list[rand_pick];
}

void game_automated::set_auto(player& plr)
{
	plr.set_is_auto(true);
}

void game_automated::move_automated(const int player_id, const int position)
{
	const int rand_pick = pick_random(get_available_for_position(position));
	std::cout << "Opponent moves from " << position << " to " << rand_pick << "\n";
	fields_[position].id = -1;
	fields_[position].is_taken = false;
	fields_[rand_pick].id = player_id;
	fields_[rand_pick].is_taken = true;
}

void game_automated::remove_automated(player& plr, linked_list<int> &list)
{
	for (int i = 0; i < list.length(); ++i)
	{
		const int rand_pick = pick_random(get_removable_fields(plr.get_id()));
		std::cout << "Opponent removes your pawn placed at " << rand_pick << " field.\n";
 		field_lines_[list[i]].is_changed = true;
		fields_[rand_pick].id = -1;
		fields_[rand_pick].is_taken = false;
		plr.set_pawn_number(plr.get_pawn_number() - 1);
	}
}

void game_automated::set_automated_field(player &plr)
{
	int rand_pick = pick_random(get_available_fields());
	std::cout << "Opponent selects " << rand_pick << " field.\n";
	fields_[rand_pick].id = plr.get_id();
	fields_[rand_pick].is_taken = true;
	plr.set_start_number(plr.get_start_number() - 1);
}

linked_list<int> game_automated::get_movable_fields(const int player_id)
{	
	linked_list<int> taken_list = get_taken_fields(player_id);
	linked_list<int> list;
	for(int i = 0; i < taken_list.length(); ++i)
	{
		linked_list<int> temp_list = get_available_for_position(taken_list[i]);
		if(!temp_list.is_empty())
		{
			list.add(taken_list[i]);
		}
	}
	return list;
}



void game_automated::play(player& player1, player& player2)
{
	set_auto(player2);
	while (!is_ended(player1, player2))
	{
		linked_list<int> temp_list;
		if (player1.get_start_number() == 0)
		{
			if (player1.get_id() == 0)
			{
				std::cout << "White pawns turn:\n";
				move(player1.get_id(), select_position(player1.get_id()));
				log("First player moves.\n");
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
					log("Removing second player pawn.\n");
				}
				list_player_1_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
				std::cout << "Black pawns turn:\n";
				move_automated(player2.get_id(), pick_random(get_movable_fields(player2.get_id())));
				log("Second player moves.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_automated(player1, temp_list);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
			}
			if (player2.get_id() == 0)
			{
				std::cout << "White pawns turn:\n";
				move_automated(player2.get_id(), pick_random(get_movable_fields(player2.get_id())));
				log("Second player moves.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_automated(player1, temp_list);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
				std::cout << "Black pawns turn:\n";
				move(player1.get_id(), select_position(player1.get_id()));
				log("First player moves.\n");
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
					log("Removing second player pawn.\n");
				}
				list_player_1_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
			}
		}
		else
		{
			if (player1.get_id() == 0)
			{
				std::cout << "White pawns turn:\n";
				set_field(player1);
				log("First player selects field.\n");
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
					log("Removing second player pawn.\n");
				}
				list_player_1_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
				std::cout << "Black pawns turn:\n";
				set_automated_field(player2);
				log("Second player selects field.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_automated(player1, temp_list);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
			}
			if (player2.get_id() == 0)
			{
				std::cout << "White pawns turn:\n";
				set_automated_field(player2);
				log("Second player selects field.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_automated(player1, temp_list);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
				std::cout << "Black pawns turn:\n";
				set_field(player1);
				log("First player select field.\n");
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
					log("Removing second player pawn.\n");
				}
				list_player_1_ = temp_list;
				if (is_ended(player1, player2))
				{
					break;
				}
			}
		}
	}
}

