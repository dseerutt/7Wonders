#include "node.hpp"
#include <sstream>
#include "display_node.hpp"

using namespace std;

namespace mcts
{
  string node::to_string() const
  {
    stringbuf buffer;
    ostream os(&buffer);
    util::display_node::node_to_ascii(os, this);
    os << endl;
    return buffer.str();
  }

  ostream& operator<<(ostream& os, const node& n)
  {
    util::display_node::node_to_ascii(os, &n);
    os << endl;
    return os;
  }
}
