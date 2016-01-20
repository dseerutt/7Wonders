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
		MCTSImplementation(World* w);
		~MCTSImplementation();
		MCTSImplementation(const MCTSImplementation& c4) = default;
		MCTSImplementation& operator=(const MCTSImplementation& c4) = default;
		bool end_of_game() const;
		int value(uint8_t player) const;
		bool won(uint8_t player) const;
		bool lost(uint8_t player) const;
		bool draw(uint8_t player) const;
		std::uint8_t current_player() const;
		std::uint16_t number_of_moves() const;
		void play(std::uint16_t m);
		void undo(std::uint16_t m) {}
		std::string player_to_string(uint8_t player) const;
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
		unsigned int numberOfMoves(uint8_t player) const;

		const uint8_t CROSS = 0;
		const uint8_t CIRCLE = 1;

		GameState state;
		World* world;
		std::vector<Player*> players;

		static std::vector<std::vector<uint64_t>> cross_hash_values;
		static std::vector<std::vector<uint64_t>> circle_hash_values;
	};
	std::ostream& operator<<(std::ostream& os, const MCTSImplementation& c4);

}
