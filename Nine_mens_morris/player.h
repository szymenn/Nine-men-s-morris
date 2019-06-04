#pragma once
class player{
	int pawn_number_ = 9;
	int start_number_ = 9;
	int id_{};
	bool is_lost_;
	bool is_auto_;
	bool is_white_;
public:
	player();
	int get_pawn_number();
	void set_pawn_number(int num);
	int get_start_number();
	void set_start_number(int num);
	int get_id() const;
	void set_id(int id);
	bool get_is_lost();
	void set_is_lost(bool is_lost);
	bool get_is_auto();
	void set_is_auto(bool is_auto);
	void set_is_white(bool is_white);
	bool get_is_white();
};