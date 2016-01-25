#include "display_node.hpp"
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

namespace util
{
  void display_node::node_to_ascii(std::ostream& os, const mcts::node* n, unsigned int depth, unsigned int prunning)
  {
    node_to_ascii(os, "", n, depth, prunning);
    os << endl;
  }
  
  void display_node::node_to_dot(std::ostream& os, const mcts::node* n, unsigned int depth, unsigned int prunning)
  {
    os << "digraph {" << endl;
    node_to_dot(os, 0, n, depth, prunning);
    os << "}" << endl;
  }

  int display_node::node_to_dot(ostream& os, int id, const mcts::node* n, unsigned int depth, unsigned int prunning)
  {
    stringbuf buffer;
    ostream o (&buffer);
    if (n->is_won())
      o << "\"won\"";
    else if (n->is_lost())
      o << "\"lost\"";
    else
      o << "\"" << n->get_statistics().count << "\\n" << setprecision(2) << n->get_statistics().value << "\"";
    string label = buffer.str();
    os << id << "[label=" << label << "]" << endl;
    if (depth == 0 || n->get_statistics().count < prunning || n->get_number_of_children() == 0) return id + 1;
    int cpt = id + 1;
    for (int i = 0; i < n->get_number_of_children(); ++i) 
      {
	os << id << "->" << cpt << endl;
	cpt = node_to_dot(os, cpt, n->get_children() + i, depth - 1, prunning);
      }
    return cpt + 1;
  }

  void display_node::node_to_ascii(ostream& os, string prefix, const mcts::node* n, unsigned int depth, unsigned int prunning)
  {
    string s;
    s = n->get_statistics().to_string();
    if (n->is_won()) s += "won";
    else if (n->is_lost()) s += "lost";
    //    else s = n->get_statistics().to_string();
    os << s;
    unsigned int w = s.size();
    string new_prefix = prefix + string(w + 1, ' ');
    if (depth == 0 || n->get_statistics().count < prunning || n->get_number_of_children() == 0) return;
    if (n->get_number_of_children() == 1)
      {
	os << "---";
	node_to_ascii(os, new_prefix + "  ", n->get_children(), depth - 1, prunning);
	return;
      }
    os << "-";
    children_to_ascii(os, new_prefix, n->get_number_of_children(), n->get_children(), depth, prunning);
  }

  void display_node::children_to_ascii(ostream& os, string prefix, unsigned int nb_children, const mcts::node* children, unsigned int depth, unsigned int prunning)
  {
    os << "+-";
    node_to_ascii(os, prefix + "| ", children, depth - 1, prunning);
    os << endl;
    os << prefix;
    for (unsigned int i = 1; i < nb_children - 1; ++i) 
      {
	os << "|-";
	node_to_ascii(os, prefix + "| ", children + i, depth - 1, prunning);
	os << endl;
	os << prefix;
      }
    os << "`-";
    node_to_ascii(os, prefix + "  ", children + nb_children - 1, depth - 1, prunning);
  }
}
