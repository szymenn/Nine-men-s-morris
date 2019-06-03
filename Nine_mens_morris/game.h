#pragma once
#include "player.h"
#include "linked_list.h"
class gamer;

typedef struct field{
	bool is_taken;
	int id;
}field_t;

typedef struct field_line{
	int line[3];
	bool is_changed;
	int id;
}field_line_t;
typedef struct available_field{
	int field;
	struct available_field *next;
	struct available_field *prev;
}available_field_t;
class game{
	static field_t fields_[24];
	static available_field_t *head_player_1_;
	static available_field_t *head_player_2_;
	static linked_list<int> list_player_1_;
	static linked_list<int> list_player_2_;
	static int field_moves_[24][4];
	static field_line_t field_lines_[16];
	static void draw_color(player &player1, player &player2);
	static bool is_ended(player &player1, player &player2);
	static bool set_pawn(player &plr, int position);
	static void move(int player_id, int position);
	static void print_available_for_position(int position);
	static bool pick_field(int position, int player_id);
	static  linked_list<int> get_available_fields();
	static linked_list<int> get_taken_fields(int player_id);
	static void print_taken_fields(int player_id);
	static int select_position(int player_id);
	static bool is_available(int field);
	static void set_field(player &plr);
	static linked_list<int> get_available_for_position(int position);
	static void play(player &player1, player &player2);
	static bool is_taken_by_player(int player_id, int position);
	static int count_lines(int player_id);
	static void remove_op_pawn(linked_list<int> &list, player &plr);
	static linked_list<int> get_lines(int player_id);
	static linked_list<int> get_removable_fields(int player_id);
	static void print_removable_fields(int player_id);
	static bool is_already_in(linked_list<int> list, int field);
	static void remove(player &plr);
	static bool is_removable(int field, int player_id);
	static void check_lines(int player_id, linked_list<int> &list);
	static linked_list<int> get_taken_lines(int player_id);
	static void check_is_ended(player &plr);
	static void log(std::string log_info);
public:
	game();
	~game();
	static void print_board();
	void start_game();
	
};