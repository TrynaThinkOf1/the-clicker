#ifdef DEBUG_TESTS
  #define CLICKER_ASSERT(expr, msg)                                      \
    do {                                                                 \
      if (expr) {                                                        \
        printf("\033[0;31m[ASSERTION ERROR] - %s\033[0m\n", msg);        \
      }                                                                  \
    } while (0)
#else
  #define CLICKER_ASSERT(expr, msg)
#endif