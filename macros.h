#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CONSTRAIN(x, a, b) MAX(MIN((x), (b)), (a))

#define LOG(str) (fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, str))
#define ELOG(str) (fprintf(stderr, "%s:%d:", __FILE__, __LINE__), perror(str))
#define LOGF(...) (fprintf(stderr, "%s:%d: ", __FILE__, __LINE__), fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"))

