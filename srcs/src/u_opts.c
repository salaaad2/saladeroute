/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   opts              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdlib.h>
#include "u_opts.h"

t_opts *
u_initopts( void ) {
    t_opts * ret = malloc(sizeof(t_opts));

    if (ret != NULL) {
        ret->verbose = 0;
        ret->help = 0;
        ret->textaddr = 0;
    }
    return (ret);
}

int
u_getopts(char *av[], t_opts *opts) {
    int i, j;
    char c;

    i = 1;
    j = -1;
    while (av[i][++j])
    {
        c = av[i][j];
        if (c == 'v')
            opts->verbose = 1;
        else if (c == 'h')
            opts->help = 1;
    }
    return (opts->noopt);
}
