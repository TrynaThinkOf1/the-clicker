#ifdef DEBUG_TESTS
  #define CLICKER_ASSERT(expr, msg) (           \
    if (expr)                                   \
      ;                                         \
    else                                        \
      printf("\033[0;31m[ASSERTION ERROR] - %s\033[0m\n", msg);  \
    )
#else
  #define CLICKER_ASSERT(expr, msg)
#endif