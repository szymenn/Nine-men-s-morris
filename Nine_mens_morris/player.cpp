#include "player.h"
player::player()
= default;

int player::get_id() const
{
	return id_;
}

void player::set_id(const int id)
{
	id_ = id;
}

int player::get_start_number()
{
	return start_number_;
}

int player::get_pawn_number()
{
	return pawn_number_;
}

bool player::get_is_lost()
{
	return is_lost_;
}

void player::set_is_lost(bool is_lost)
{
	is_lost_ = is_lost;
}

void player::set_pawn_number(int num)
{
	pawn_number_ = num;
}

void player::set_start_number(int num)
{
	start_number_ = num;
}

player::~player()
= default;



