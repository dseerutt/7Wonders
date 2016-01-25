#include "mcts_two_players.hpp"
#include "test_mcts_two_players.hpp"
#include "HighestNumber.h"
#include <iostream>
#include <iomanip>
#include <map>

//#include <gperftools/profiler.h>

using namespace std;
using namespace game;

namespace mcts
{
  // test_mcts_two_players::test_mcts_two_players() : openings_(connect4())
  // {
  //   //self_play(1000);
  //   play();
  //   //test_openings(10000, 1000);
  // }

  // void test_mcts_two_players::test_openings(int nb_learning, int nb_testing)
  // {
  //   //    self_play(nb_testing);
  //   self_play_learn_openings(nb_learning);
  //   self_play(nb_testing, true);
  // }

  // template <typename Game>
  // int test_mcts_two_players::select_move(Game& game)
  // {
  //   cout << game.player_to_string(game.current_player()) << " move: ";
  //   map<string, int> m;
  //   for (int i = 0; i < game.number_of_moves(); ++i)
  //     {
  //       m[game.move_to_string(i)] = i;
  //     }
  //   string move;
  //   getline(cin, move);
  //   game.play(m[move]);
  //   return m[move];
  // }

  // void test_mcts_two_players::play()
  // {
  //   //    ProfilerStart("theturk.prof");
  //   connect4 c4;
  //   auto the_turk = make_mcts_two_players(c4, 5000, 0.3, 4);
  //   cout << "play one game" << endl;
  //   cout << "who's first? (h)uman/(c)omputer ";
  //   string ans;
  //   getline(cin, ans);
  //   cout << c4 << endl;
  //   int human_last_move = -1, computer_last_move = -1;
  //   while (!c4.end_of_game())
  //     {
  //       if ((ans == "h" && c4.current_player() == 0) || (ans == "c" && c4.current_player() == 1))
  // 	  {
  //           human_last_move = select_move(c4);
  // 	  }
  //       else
  // 	  {
  //           if (human_last_move != -1 && computer_last_move != -1)
  // 	      {
  //               the_turk.last_moves(computer_last_move, human_last_move);
  // 	      }
  //           uint16_t move = the_turk.select_move();
  //           computer_last_move = move;
  //           cout << c4.player_to_string(c4.current_player()) << " move: " << c4.move_to_string(move) << endl;
  //           c4.play(move);
  // 	  }
  //       cout << c4 << endl;
  //     }
  //   if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
  //   else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
  //   else cout << "draw";
  //   cout << endl;
  //   //    ProfilerStop();
  // }

  // void test_mcts_two_players::self_play_learn_openings(int n)
  // {
  //   connect4 c4;
  //   vector<uint16_t> moves(200);
  //   auto state = c4.get_state();
  //   auto the_turk_1 = make_mcts_two_players(c4, 1000, 0.6, 2);
  //   auto the_turk_2 = make_mcts_two_players(c4, 1000, 0.6, 2);
  //   map<set<int>, pair<uint32_t, double>> learning_examples;
  //   for (int i = 0; i < n; ++i)
  //     {
  //       cout << i << endl;
  //       cout << openings_ << endl << endl;
  //       moves.clear();
  //       c4.set_state(state);
  //       the_turk_1.reset();
  //       the_turk_1.init_with_openings(openings_);
  //       the_turk_2.reset();
  //       the_turk_2.init_with_openings(openings_);
  //       int the_turk_1_last_move = -1, the_turk_2_last_move = -1;
  //       int k = 0;
  //       while (!c4.end_of_game())
  // 	  {
  //           if (k == 1) the_turk_2.last_move(the_turk_1_last_move);
  //           if (k % 2 == 0)
  // 	      {
  //               if (the_turk_2_last_move != -1)
  // 		  {
  //                   the_turk_1.last_moves(the_turk_1_last_move, the_turk_2_last_move);
  // 		  }
  //               uint16_t move = the_turk_1.select_move();
  //               moves.push_back(move);
  //               the_turk_1_last_move = move;
  //               c4.play(move);
  // 	      }
  //           else
  // 	      {
  //               if (the_turk_2_last_move != -1)
  // 		  {
  //                   the_turk_2.last_moves(the_turk_2_last_move, the_turk_1_last_move);
  // 		  }
  //               uint16_t move = the_turk_2.select_move();
  //               moves.push_back(move);
  //               the_turk_2_last_move = move;
  //               c4.play(move);
  // 	      }
  //           ++k;
  // 	  }
  // 	std::cout << c4 << std::endl;
  //       int v = c4.value(0);
  //       cout << "value for first player " << v << endl;
  //       c4.set_state(state);
  //       openings_.update(c4, moves, v);
  // 	c4.set_state(state);
  // 	for (uint16_t m : moves) 
  // 	  {
  // 	    c4.play(m);
  // 	    v = -v;
  // 	    set<int> input_vector = std::move(c4.to_input_vector());
  // 	    auto it = learning_examples.find(input_vector);
  // 	    if (it == learning_examples.end())
  // 	      {
  // 		learning_examples[input_vector] = make_pair(1, v);
  // 	      }
  // 	    else
  // 	      {
  // 		it->second.second = (it->second.second * it->second.first + v) / (it->second.first + 1);
  // 		it->second.first += 1;
  // 	      }
  // 	  }
  //     }
  //   cout << "number of learning examples: " << learning_examples.size() << endl;
  //   ofstream output("learning_examples.txt");
  //   for (const auto& example : learning_examples) 
  //     {
  // 	output << example.second.second;
  // 	for (int index : example.first) 
  // 	  {
  // 	    output << " " << index << ":" << 1;
  // 	  }
  // 	output << endl;
  //     }
  //   output.close();
  // }

  // void test_mcts_two_players::self_play(int n, bool with_openings)
  // {
  //   connect4 c4;
  //   auto state = c4.get_state();
  //   auto the_turk_v1 = make_mcts_two_players(c4, 1000, 0.6, 2);
  //   auto the_turk_v2 = make_mcts_two_players(c4, 1000, 0.6, 2);
  //   int nb_win_v1 = 0, nb_win_v2 = 0, nb_draw = 0;
  //   for (int i = 0; i < n; ++i)
  //     {
  //       cout << i << endl;
  //       c4.set_state(state);
  //       the_turk_v1.reset();
  //       the_turk_v2.reset();
  // 	if (with_openings) the_turk_v2.init_with_openings(openings_);
  //       int the_turk_v1_last_move = -1, the_turk_v2_last_move = -1;
  // 	int k = 0;
  //       while (!c4.end_of_game())
  // 	  {
  //           if (with_openings && k == 1 && i % 2 == 0) the_turk_v2.last_move(the_turk_v1_last_move);
  // 	    ++k;
  //           //	    cout << c4 << endl;
  //           if ((i % 2 == 0 && c4.current_player() == 0) || (i % 2 == 1 && c4.current_player() == 1))
  // 	      {
  //               if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
  // 		  {
  //                   the_turk_v1.last_moves(the_turk_v1_last_move, the_turk_v2_last_move);
  // 		  }
  //               uint16_t move = the_turk_v1.select_move();
  //               the_turk_v1_last_move = move;
  //               c4.play(move);
  // 	      }
  //           else
  // 	      {
  //               if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
  // 		  {
  //                   the_turk_v2.last_moves(the_turk_v2_last_move, the_turk_v1_last_move);
  // 		  }
  //               uint16_t move = the_turk_v2.select_move();
  //               the_turk_v2_last_move = move;
  //               c4.play(move);
  // 	      }
  // 	  }
  //       if (c4.value(0) == 1)
  // 	  {
  //           if (i % 2 == 0)
  // 	      {
  //               /*cout << "v1 won" << endl;*/ ++nb_win_v1;
  // 	      }
  //           else
  // 	      {
  //               /*cout << "v2 won" << endl;*/ ++nb_win_v2;
  // 	      }
  // 	  }
  //       else if (c4.value(1) == 1)
  // 	  {
  //           if (i % 2 == 0)
  // 	      {
  //               /*cout << "v2 won" << endl;*/ ++nb_win_v2;
  // 	      }
  //           else
  // 	      {
  //               /*cout << "v1 won" << endl;*/ ++nb_win_v1;
  // 	      }
  // 	  }
  //       else
  // 	  {
  //           /*cout << "draw" << endl;*/ ++nb_draw;
  // 	  }
  //       cout << setw(10) << "v1 nb wins: " << nb_win_v1 << " v2 nb wins: " << nb_win_v2 << " nb draws: " << nb_draw << endl;
  //     }
  // }

  // void test_mcts_two_players::self_play()
  // {
  //   connect4 c4;
  //   auto the_turk_v1 = make_mcts_two_players(c4, 1000, 1.2, 2);
  //   auto the_turk_v2 = make_mcts_two_players(c4, 1000, 1.2, 2);
  //   cout << "play one game" << endl;
  //   cout << "who's first? the_turk_(v1)/the_turk_(v2) ";
  //   string ans;
  //   getline(cin, ans);
  //   cout << c4 << endl;
  //   int the_turk_v1_last_move = -1, the_turk_v2_last_move = -1;
  //   while (!c4.end_of_game())
  //     {
  //       if ((ans == "v1" && c4.current_player() == 0) || (ans == "v2" && c4.current_player() == 1))
  // 	  {
  //           if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
  // 	      {
  //               the_turk_v1.last_moves(the_turk_v1_last_move, the_turk_v2_last_move);
  // 	      }
  //           uint16_t move = the_turk_v1.select_move();
  //           the_turk_v1_last_move = move;
  //           cout << c4.player_to_string(c4.current_player()) << " move: " << c4.move_to_string(move) << endl;
  //           c4.play(move);
  // 	  }
  //       else
  // 	  {
  //           if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
  // 	      {
  //               the_turk_v2.last_moves(the_turk_v2_last_move, the_turk_v1_last_move);
  // 	      }
  //           uint16_t move = the_turk_v2.select_move();
  //           the_turk_v2_last_move = move;
  //           cout << c4.player_to_string(c4.current_player()) << " move: " << c4.move_to_string(move) << endl;
  //           c4.play(move);
  // 	  }
  //       cout << c4 << endl;
  //     }
  //   if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
  //   else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
  //   else cout << "draw";
  //   cout << endl;
  // }

}
