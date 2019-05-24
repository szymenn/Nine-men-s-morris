#pragma once
class player{
	int pawn_number_ = 9;
	int start_number_ = 9;
	int id_{};
public:
	player();
	int get_pawn_number();
	void set_pawn_number(int num);
	int get_start_number();
	void set_start_number(int num);
	int get_id() const;
	void set_id(int id);
	
};