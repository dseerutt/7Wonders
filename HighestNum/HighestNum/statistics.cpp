#include "statistics.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

namespace mcts
{
  std::string statistics::to_string() const
  {
    stringbuf buffer;
    ostream os(&buffer);
    os << "(count: " << count << ", value: " << setprecision(2) << value << ")";
    return buffer.str();
  }
}
