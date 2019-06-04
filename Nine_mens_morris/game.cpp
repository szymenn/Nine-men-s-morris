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

void game::move(const int player_id, const int position)
{
	linked_list<int> list = get_available_for_position(position);
	while(list.is_empty())
	{
		printf("There's none available positions to move for this position.\n");
	}
	printf("List of available positions to move:\n");
	list.print();
	while (!pick_field(position, player_id));
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
				log("First player moves.\n");
				check_lines(player1.get_id(), list_player_1_);
				temp_list = get_lines(player1.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player2);
					log("Removing second player pawn.\n");
				}
				list_player_1_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				move(player2.get_id(), select_position(player2.get_id()));
				log("Second player moves.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				printf("Black pawns turn:\n"); 
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
					log("Removing first player pawn.\n");
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
				log("Second player moves.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
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
				printf("Black pawns turn:\n");
				set_field(player2);
				log("Second player selects field.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if(!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
					log("Removing first player pawn.\n");
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
				log("Second player selects field.\n");
				check_lines(player2.get_id(), list_player_2_);
				temp_list = get_lines(player2.get_id());
				if (!temp_list.is_empty())
				{
					remove_op_pawn(temp_list, player1);
					log("Removing first player pawn.\n");
				}
				list_player_2_ = temp_list;
				if(is_ended(player1, player2))
				{
					break;
				}
				printf("Black pawns turn:\n");
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
				if(is_ended(player1, player2))
				{
					break;
				}
			}
		}
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

