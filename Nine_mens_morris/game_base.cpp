#include "game_base.h"
void game_base::print_board()
{

	printf("0 ------- 1 ------- 2\n|         |         |\n|  3 ---- 4 ---- 5  |\n|  |      |      |  |\n");
	printf("|  |  6-- 7 --8  |  |\n|  |  |       |  |  |\n9--10-11      12-13-14\n|  |  |       |  |  |\n");
	printf("|  |  15-16- 17  |  |\n|  |      |      |  |\n|  18---- 19 ---20  |\n|         |         |\n");
	printf("21------ 22 -------23\n");
}

bool game_base::is_ended(player& player1, player& player2)
{
	return false;
}

void game_base::print_available_for_position(int position)
{
	
}

void game_base::check_is_ended(player& plr)
{
	
}

void game_base::check_lines(int player_id, linked_list<int>& list)
{
	
}

int game_base::count_lines(int player_id)
{
	return -1;
}

linked_list<int> game_base::get_available_for_position(int position)
{
	const linked_list<int> list;
	return list;
}

void game_base::draw_color(player& player1, player& player2)
{
		
}

linked_list<int> game_base::get_taken_lines(int player_id)
{
	const linked_list<int> list;
	return list;
}

linked_list<int> game_base::get_available_fields()
{
	const linked_list<int> list;
	return list;
}

linked_list<int> game_base::get_lines(int player_id)
{
	const linked_list<int> list;
	return list;
}

linked_list<int> game_base::get_removable_fields(int player_id)
{
	const linked_list<int> list;
	return list;
}

linked_list<int> game_base::get_taken_fields(int player_id)
{
	const linked_list<int> list;
	return list;
}

bool game_base::is_already_in(linked_list<int> list, int field)
{
	return false;
}

bool game_base::is_available(int field)
{
	return false;
}

bool game_base::is_removable(int field, int player_id)
{
	return false;
}
bool game_base::is_taken_by_player(int player_id, int position)
{
	return false;
}

void game_base::log(std::string log_info)
{
	
}

void game_base::move(int player_id, int position)
{
	
}

bool game_base::pick_field(int position, int player_id)
{
	return false;
}

void game_base::play(player& player1, player& player2)
{
	
}

void game_base::print_removable_fields(int player_id)
{
	
}

void game_base::print_taken_fields(int player_id)
{
	
}

void game_base::remove(player& plr)
{
	
}

void game_base::remove_op_pawn(linked_list<int>& list, player& plr)
{
	
}

int game_base::select_position(int player_id)
{
	return -1;
}

void game_base::set_field(player& plr)
{
	
}

bool game_base::set_pawn(player& plr, int position)
{
	return false;
}
