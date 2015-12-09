#include "omp_util.hpp"

namespace util
{
  int omp_util::get_num_threads()
  {
    int num_threads = 1;
#if defined(_OPENMP)
#pragma omp parallel
    num_threads = omp_get_num_threads();
#endif
    return num_threads;
  }

  int omp_util::get_thread_num()
  {
    int thread_num = 0;
#if defined(_OPENMP)
    thread_num = omp_get_thread_num();
#endif
    return thread_num;
  }
}
