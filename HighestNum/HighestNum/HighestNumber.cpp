#include "HighestNumber.h"
#include "test_HN.h"

#include "test_two_players_game.hpp"

#include "test_monte_carlo.hpp"
#include "test_mcts_two_players.hpp"
//#include "test_fast_log.hpp"
//#include "test_allocator.hpp"
//#include "test_minmax.hpp"
//#include "test_bits.hpp"
//#include "learning.hpp"

#include <omp.h>


int main()
{
	//game::run_test_two_players_game(game::HighestNumber());
	mcts::run_test_mcts_two_players(game::HighestNumber());

	std::cout << "GAME OVER" << std::endl;

	getchar();
	getchar();

	return 0;
}

namespace game
{
	HighestNumber::HighestNumber()
	{
	}


	HighestNumber::~HighestNumber()
	{
	}

	bool HighestNumber::end_of_game() const
	{
		return state.turn == 1;
	}

	int HighestNumber::value(std::uint8_t player) const
	{
		if (won(player))
			return 1;
		else if (lost(player))
			return -1;
		else
			return 0;
	}

	bool HighestNumber::won(std::uint8_t player) const
	{
		if (player == 0)
			return state.player1_value > state.player2_value;
		else
			return state.player1_value < state.player2_value;
	}

	bool HighestNumber::lost(std::uint8_t player) const
	{
		if (player == 0)
			return state.player1_value < state.player2_value;
		else
			return state.player1_value > state.player2_value;
	}

	bool HighestNumber::draw(std::uint8_t player) const
	{
		return state.player1_value == state.player2_value;
	}

	uint8_t HighestNumber::current_player() const
	{
		return state.current_player;
	}

	uint16_t HighestNumber::number_of_moves() const
	{
		return 10;
	}

	void HighestNumber::play(std::uint16_t m)
	{
		uint8_t player = current_player();
		if (player == 0)
		{
			state.player1_value = move_to_value(m);
		}
		else
		{
			state.player2_value = move_to_value(m);
			state.turn++;
		}
		state.current_player = 1 - state.current_player;
	}

	std::string HighestNumber::player_to_string(std::uint8_t player) const
	{
		std::string res = std::to_string(player);
		return res;
	}

	std::string HighestNumber::move_to_string(std::uint16_t m) const
	{
		std::string res = std::to_string(m);
		return res;
	}

	std::string HighestNumber::to_string() const
	{
		std::string res = "turn " + std::to_string(state.turn) + ":";
		return res;
	}

	//virtual void playout(std::mt19937& engine, int max_depth = -1);
	std::set<int> HighestNumber::to_input_vector() const
	{
		std::set<int> res;
		return res;
	}

	void HighestNumber::from_input_vector(const std::set<int>& input)
	{

	}

	hn_state HighestNumber::get_state()
	{
		return state;
	}

	void HighestNumber::set_state(const hn_state& state)
	{
		this->state = state;
	}

	std::shared_ptr<game<hn_state>> HighestNumber::do_copy() const
	{
		return std::shared_ptr<HighestNumber>(new HighestNumber(*this));
	}

	std::uint64_t HighestNumber::hash(std::uint16_t m) const
	{

		return 0;
	}

	std::uint64_t HighestNumber::hash() const
	{

		return 0;
	}

	int HighestNumber::move_to_value(uint16_t m) const
	{
		return m + 1;
	}

	uint16_t HighestNumber::value_to_move(int v) const
	{
		return v - 1;
	}

	std::ostream& operator<<(std::ostream& os, const HighestNumber& c4)
	{
		os << c4.to_string() << std::endl;
		return os;
	}

}