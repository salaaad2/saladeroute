#ifndef U_OPTS_H_
# define U_OPTS_H_

#include <sys/param.h>
#include <sys/types.h>
#include <dirent.h>

typedef unsigned char bool_t;

#ifndef FALSE
# define FALSE 0
#endif
#ifndef TRUE
# define TRUE 1
#endif


typedef struct s_opts {
    int	max_hops;
    bool_t	verbose;
    bool_t	help;
    bool_t	noopt;
    bool_t	textaddr;
} t_opts;

t_opts* u_initopts( void );
int u_getopts(char *av[], t_opts * opts);

#endif
