#pragma once
#include "linked_list.h"
#include "player.h"
typedef struct field {
	bool is_taken;
	int id;
}field_t;

typedef struct field_line {
	int line[3];
	bool is_changed;
	int id;
}field_line_t;
class game_base
{
protected:
	static field_t fields_[24];
	static linked_list<int> list_player_1_;
	static linked_list<int> list_player_2_;
	static int field_moves_[24][4];
	static field_line_t field_lines_[16];
	void draw_color(player &player1, player &player2);
	bool is_ended(player &player1, player &player2);
	bool set_pawn(player &plr, int position);
	void move(int player_id, int position);
	void print_available_for_position(int position);
	bool pick_field(int position, int player_id);
	linked_list<int> get_available_fields();
	linked_list<int> get_taken_fields(int player_id);
	void print_taken_fields(int player_id);
	int select_position(int player_id);
	bool is_available(int field);
	void set_field(player &plr);
	linked_list<int> get_available_for_position(int position);
	virtual void play(player &player1, player &player2);
	bool is_taken_by_player(int player_id, int position);
	int count_lines(int player_id);
	void remove_op_pawn(linked_list<int> &list, player &plr);
	linked_list<int> get_lines(int player_id);
	linked_list<int> get_removable_fields(int player_id);
	void print_removable_fields(int player_id);
	bool is_already_in(linked_list<int> list, int field);
	void remove(player &plr);
	bool is_removable(int field, int player_id);
	void check_lines(int player_id, linked_list<int> &list);
	linked_list<int> get_taken_lines(int player_id);
	void check_is_ended(player &plr);
	void log(std::string log_info);
	//linked_list<int> get_movable_fields(int player_id);
public:
	virtual ~game_base() = default;
	void start_game();
	void print_board();

};
