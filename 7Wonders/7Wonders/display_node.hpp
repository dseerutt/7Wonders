#ifndef __DISPLAY_NODE_HPP__
#define __DISPLAY_NODE_HPP__

#include "node.hpp"
#include <iostream>
#include <limits>

namespace util
{
  class display_node
  {
  public:
    static void node_to_ascii(std::ostream& os, const mcts::node* n, unsigned int depth = std::numeric_limits<unsigned int>::max(), unsigned int prunning = 0);
    static void node_to_dot(std::ostream& os, const mcts::node* n, unsigned int depth = std::numeric_limits<int>::max(), unsigned int prunning = 0);
  private:
    static void node_to_ascii(std::ostream& os, std::string prefix, const mcts::node* n, unsigned int depth, unsigned int prunning);
    static void children_to_ascii(std::ostream& os, std::string prefix, unsigned int nb_children, const mcts::node* children, unsigned int depth, unsigned int prunning);
    static int node_to_dot(std::ostream& os, int id, const mcts::node* n, unsigned int depth, unsigned int prunning);
  };
}

#endif
