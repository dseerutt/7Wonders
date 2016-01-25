#ifndef __TEST_MONTE_CARLO_HPP__
#define __TEST_MONTE_CARLO_HPP__


namespace monte_carlo
{
  class test_monte_carlo
  {
    void play();
    template <typename Game>
    void select_move(Game& game);
  public:
    test_monte_carlo();
  };
}

#endif
