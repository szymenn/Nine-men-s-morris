#pragma once
#include "player.h"
class gamer;

typedef struct field{
	bool is_taken;
	int id;
}field_t;
typedef struct available_field{
	int field;
	struct available_field *next;
	struct available_field *prev;
}available_field_t;
class game{
	static field_t fields_[24];
	static int field_moves_[24][4];
	static int field_lines_[16][3];
	static void draw_color(player &player1, player &player2);
	static bool is_ended(player &player1, player &player2);
	static bool set_pawn(player &plr, int position);
	static void move(int player_id, int position);
	static void print_available_for_position(int position);
	static bool pick_field(int position, int player_id);
	static available_field_t *get_available_fields();
	static available_field_t *get_taken_fields(int player_id);
	static void print_taken_fields(int player_id);
	static int select_position(int player_id);
	static bool is_available(int field);
	static void set_field(player &plr);
	static available_field_t *get_available_for_position(int position);
	static void play(player &player1, player &player2);
	static bool is_taken_by_player(int player_id, int position);
	static int check_lines(int player_id);
	static void remove_op_pawn(int num_pawns, int player_id);
	static available_field_t *get_removable_fields(int player_id);
	static void print_removable_fields(int player_id);
	static available_field_t *get_new_node(int field);
	static bool is_already_in(available_field_t *head, int field);
public:
	game();
	static void print_board();
	void start_game();
	
};