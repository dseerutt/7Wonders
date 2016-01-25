#include "openings.hpp"

namespace mcts
{
  std::ostream& operator<<(std::ostream& os, const openings& op)
  {
    util::display_node::node_to_ascii(os, op.root_, 3);
    return os;
  }

  void openings::copy_to(node* root, allocator& alloc) const
  {
    copy(root_, root, alloc);
  }

  void openings::copy(node* src, node* dst, allocator& alloc) const
  {
    dst->set_statistics(src->get_statistics());
    const unsigned int nb_children = src->get_number_of_children();
    dst->set_number_of_children(nb_children);
    if (nb_children == 0) return;
    dst->set_children(alloc.allocate(nb_children));
    node* const src_children = src->get_children();
    node* const dst_children = dst->get_children();
    for (unsigned int i = 0; i < nb_children; ++i)
      {
        copy(src_children + i, dst_children + i, alloc);
      }
  }
}
