#ifndef P_MAIN_H_
#define P_MAIN_H_

#include <sys/param.h>
#include <sys/types.h>
#include <dirent.h>

typedef unsigned char bool_t;

typedef struct s_opts {
    bool_t	verbose;
    bool_t	help;
    bool_t	noopt;
    bool_t	textaddr;
} t_opts;

#endif
