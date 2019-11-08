#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CONSTRAIN(x, a, b) MAX(MIN((x), (b)), (a))

#define _INTERNAL_LOG() (fprintf(stderr, "%s:%s:%d ", __FILE__, __FUNCTION__, __LINE__))
#define ELOG(str) (_INTERNAL_LOG(), perror(str))
#define LOGF(...) (_INTERNAL_LOG(), fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"))
#define LOG(str) (LOGF("%s", (str)))
#define HERE() (LOG("Point Reached"))
#define DIE(str) (LOG(str), exit(1))

