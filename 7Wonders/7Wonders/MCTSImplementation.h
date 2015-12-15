#pragma once
#include "game.hpp"
#include <random>
#include <array>
#include <iostream>
#include <memory>
#include <stdint.h>

#include "CardSet.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
class HumanPlayer;
class ComputerPlayer;
class World;

namespace game
{
	struct GameState
	{
		unsigned int m_age;
		std::vector<HumanPlayer> m_humanPlayers;
		std::vector<ComputerPlayer> m_computerPlayers;
		CardSet m_deck;
		CardSet m_discard;

		CardSet moves;

		/*uint64_t cross_bitboard = 0;
		uint64_t circle_bitboard = 0;
		uint32_t moves = 0x1AC688;
		uint32_t free = 0;
		uint64_t hash_value = 0;
		uint16_t nb_moves = 7;
		uint8_t total_moves = 0;
		bool first_player_win = false;
		bool second_player_win = false;*/
	};

	class MCTSImplementation : public game<GameState>
	{
	public:
		MCTSImplementation();
		~MCTSImplementation();
		MCTSImplementation(const MCTSImplementation& c4) = default;
		MCTSImplementation& operator=(const MCTSImplementation& c4) = default;
		bool end_of_game() const;
		int value(const Player& player) const;
		bool won(const Player& player) const;
		bool lost(const Player& player) const;
		bool draw(const Player& player) const;
		std::uint8_t current_player() const;
		std::uint16_t number_of_moves() const;
		void play(std::uint16_t m);
		void undo(std::uint16_t m) {}
		std::string player_to_string(const Player& player) const;
		std::string move_to_string(std::uint16_t m) const;
		std::string to_string() const;
		void playout(std::mt19937& engine, int max_depth = -1);
		std::set<int> to_input_vector() const;
		void from_input_vector(const std::set<int>& input);
		GameState get_state();
		void set_state(const GameState& state);
		std::shared_ptr<game<GameState>> do_copy() const;
		std::uint64_t hash(std::uint16_t m) const;
		std::uint64_t hash() const;

	private:
		inline void update_win();
		inline bool has_won(uint64_t bitboard);
		inline void update_moves(uint16_t move);
		inline bool get(uint64_t bitboard, uint8_t i, uint8_t j) const;

		const uint8_t CROSS = 0;
		const uint8_t CIRCLE = 1;

		GameState state;
		World* world;

		static std::vector<std::vector<uint64_t>> cross_hash_values;
		static std::vector<std::vector<uint64_t>> circle_hash_values;
	};
	std::ostream& operator<<(std::ostream& os, const MCTSImplementation& c4);

}
