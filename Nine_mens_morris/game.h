#pragma once
#include "player.h"
#include "linked_list.h"
#include "game_base.h"
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
class game : public game_base{
	static field_t fields_[24];
	static available_field_t *head_player_1_;
	static available_field_t *head_player_2_;
	static linked_list<int> list_player_1_;
	static linked_list<int> list_player_2_;
	static int field_moves_[24][4];
	static field_line_t field_lines_[16];
	void draw_color(player &player1, player &player2) override;
	bool is_ended(player &player1, player &player2) override;
	bool set_pawn(player &plr, int position) override;
	void move(int player_id, int position) override;
	void print_available_for_position(int position) override;
	bool pick_field(int position, int player_id) override;
	linked_list<int> get_available_fields() override;
	linked_list<int> get_taken_fields(int player_id) override;
	void print_taken_fields(int player_id) override;
	int select_position(int player_id) override;
	bool is_available(int field) override;
	void set_field(player &plr) override;
	linked_list<int> get_available_for_position(int position) override;
	void play(player &player1, player &player2) override;
	bool is_taken_by_player(int player_id, int position) override;
	int count_lines(int player_id) override;
	void remove_op_pawn(linked_list<int> &list, player &plr) override;
	linked_list<int> get_lines(int player_id) override;
	linked_list<int> get_removable_fields(int player_id) override;
	void print_removable_fields(int player_id) override;
	bool is_already_in(linked_list<int> list, int field) override;
	void remove(player &plr) override;
	bool is_removable(int field, int player_id) override;
	void check_lines(int player_id, linked_list<int> &list) override;
	linked_list<int> get_taken_lines(int player_id) override;
	void check_is_ended(player &plr) override;
	void log(std::string log_info) override;
public:
	game();
	~game();
	void start_game();
	
};