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

void player::set_is_lost(const bool is_lost)
{
	is_lost_ = is_lost;
}

void player::set_pawn_number(const int num)
{
	pawn_number_ = num;
}

void player::set_start_number(const int num)
{
	start_number_ = num;
}

bool player::get_is_auto()
{
	return is_auto_;
}

void player::set_is_auto(const bool is_auto)
{
	is_auto_ = is_auto;
}

bool player::get_is_white()
{
	return is_white_;
}

void player::set_is_white(const bool is_white)
{
	is_white_ = is_white;
}





