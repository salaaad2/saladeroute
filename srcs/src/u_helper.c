/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   helpers           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "u_helper.h"
#include "traceroute.h"
#include "u_libft.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t
u_ploss(uint32_t sent, uint32_t received)
{
    uint32_t ret;

    ret = 100;
    ret *= sent;
    ret /= received;
    return (ret - 100);
}

void
u_handle_sigint(int dummy)
{
    (void)dummy;
    u_setrunning(1, NULL);
}

void
u_setrunning(bool_t mode, bool_t * running)
{
    static bool_t * r;

    if (mode == 0) {
        r = running;
    } else {
        /* r is tracert->reached, set it to true to stop the execution */
        *r = TRUE;
    }
}

int
u_help( void )
{
    char output[4096];
    int len;

    bzero(output, sizeof(output));
    len =  sprintf(output, "Usage\n  ./ft_traceroute [options] <destination>\n\nOptions:\n");
    len += sprintf(output + len, "  -v\tverbose output\n");
    len += sprintf(output + len, "  -m <hops>\tmaximum hops\n");
    puts(output);
    return (0);
}

int
u_printerr(char * reason, char * value)
{
    dprintf(2, "ft_traceroute: %s: %s\n", reason, value);
    return (-1);
}
