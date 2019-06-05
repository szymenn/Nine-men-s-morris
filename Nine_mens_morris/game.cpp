#include "game.h"
#include <cstdio>
#include "player.h"
#include <cstdlib>
#include "linked_list.cpp "
#include <ctime>

game::game()
{
	for(int i = 0; i < 24; ++i)
	{
		fields_[i].is_taken = false;
		fields_[i].id = -1;
	}
	log("New game.\n");
}

game::~game()
= default;

void game::play(player& player1, player& player2)
{
	while (!is_ended(player1, player2))
	{
		linked_list<int> temp_list;
		if(player1.get_is_white())
		{
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
					move(player2.get_id(), select_position(player2.get_id()));
					log("Second player moves.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					move(player2.get_id(), select_position(player2.get_id()));
					log("Second player moves.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					set_field(player2);
					log("Second player selects field.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					set_field(player2);
					log("Second player selects field.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
		else
		{
			if (player2.get_start_number() == 0)
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
					move(player2.get_id(), select_position(player2.get_id()));
					log("Second player moves.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					move(player2.get_id(), select_position(player2.get_id()));
					log("Second player moves.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					set_field(player2);
					log("Second player selects field.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
					set_field(player2);
					log("Second player selects field.\n");
					check_lines(player2.get_id(), list_player_2_);
					temp_list = get_lines(player2.get_id());
					if (!temp_list.is_empty())
					{
						remove_op_pawn(temp_list, player1);
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
}


