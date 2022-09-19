/*********************************/
/*   FT_PING          (  //      */
/*   errs              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdio.h>

#include "u_err.h"

int
u_printerr(char * reason, char * value)
{
    dprintf(2, "ft_ping: %s: %s\n[perror:%s]\n", reason, value, strerror(errno));
    return (1);
}
