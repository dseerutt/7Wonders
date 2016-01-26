#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <string>
#include <cstdint>
#include <random>
#include <memory>
#include <set>

namespace game
{
	template <typename State>
	struct game
	{
		virtual bool end_of_game() const = 0;
		virtual int value(std::uint8_t player) const = 0;
		int value_for_current_player() const;
		virtual bool won(std::uint8_t player) const = 0;
		virtual bool lost(std::uint8_t player) const = 0;
		virtual bool draw(std::uint8_t player) const = 0;
		virtual uint8_t current_player() const = 0;
		virtual std::uint16_t number_of_moves() const = 0;
		virtual void play(std::uint16_t m) = 0;
		virtual void undo(std::uint16_t m) = 0;
		virtual std::string player_to_string(std::uint8_t player) const = 0;
		virtual std::string move_to_string(std::uint16_t m) const = 0;
		virtual std::string to_string() const = 0;
		virtual void playout(std::mt19937& engine, int max_depth = -1);
		virtual std::set<int> to_input_vector() const = 0;
		virtual void from_input_vector(const std::set<int>& input) = 0;
		virtual State get_state() = 0;
		virtual void set_state(const State& state) = 0;
		virtual std::shared_ptr<game<State>> do_copy() const = 0;
		virtual std::uint64_t hash(std::uint16_t m) const = 0;
		virtual std::uint64_t hash() const = 0;
		virtual ~game() {}
	};
	template<typename Game> std::shared_ptr<Game> copy(const Game& g)
	{
		return std::dynamic_pointer_cast<Game>(g.do_copy());
	}
	template<typename State> int game<State>::value_for_current_player() const
	{
		return value(current_player());
	}
	template<typename State> void game<State>::playout(std::mt19937& engine, int max_depth)
	{
		while (!end_of_game())
		{
			std::uniform_int_distribution<uint16_t> distribution(0, number_of_moves() - 1);
			std::uint16_t move = distribution(engine);
			play(move);
		}
	}
}

#endif
