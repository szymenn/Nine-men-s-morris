#pragma once
#include "linked_list.h"
#include "player.h"

class game_base
{
protected:
	virtual void draw_color(player &player1, player &player2);
	virtual bool is_ended(player &player1, player &player2);
	virtual bool set_pawn(player &plr, int position);
	virtual void move(int player_id, int position);
	virtual void print_available_for_position(int position);
	virtual bool pick_field(int position, int player_id);
	virtual linked_list<int> get_available_fields();
	virtual linked_list<int> get_taken_fields(int player_id);
	virtual void print_taken_fields(int player_id);
	virtual int select_position(int player_id);
	virtual bool is_available(int field);
	virtual void set_field(player &plr);
	virtual linked_list<int> get_available_for_position(int position);
	virtual void play(player &player1, player &player2);
	virtual bool is_taken_by_player(int player_id, int position);
	virtual int count_lines(int player_id);
	virtual void remove_op_pawn(linked_list<int> &list, player &plr);
	virtual linked_list<int> get_lines(int player_id);
	virtual linked_list<int> get_removable_fields(int player_id);
	virtual void print_removable_fields(int player_id);
	virtual bool is_already_in(linked_list<int> list, int field);
	virtual void remove(player &plr);
	virtual bool is_removable(int field, int player_id);
	virtual void check_lines(int player_id, linked_list<int> &list);
	virtual linked_list<int> get_taken_lines(int player_id);
	virtual void check_is_ended(player &plr);
	virtual void log(std::string log_info);
public:
	virtual ~game_base() = default;
	void print_board();

};
