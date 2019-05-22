#pragma once
class gamer{
	int pawn_number_ = 9;
	int start_number_ = 9;
public:
	gamer();
	int get_pawn_number();
	void set_pawn_number(int num);
	int get_start_number();
	void set_start_number(int num);
	
};