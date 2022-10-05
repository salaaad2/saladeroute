/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   helpers           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "u_helper.h"
#include "traceroute.h"

#include <stdio.h>

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
u_handle_sigalrm(int dummy)
{
    (void)dummy;
}

void
u_setrunning(uint8_t mode, uint8_t * running)
{
    static uint8_t * r;

    if (mode == 0) {
        r = running;
    } else {
        *r = 0;
    }
}

int
u_help( void )
{
    printf("Usage\n./ft_tracert [options] <destination>\n\nOptions:\n");
    printf(" -v\tverbose output\n");
    return (0);
}

void
u_printsum(int ttl, bool_t status, t_tracert replies[3])
{
    char output[96];

    sprintf(output, "%d ", ttl);
    if (status == 0)
    {
        sprintf(output, "* * *\n");
    }
    else if (status == 11)
    {
        sprintf(output, "dummy_address, %.3Lfms %.3Lfms %.3Lfms\n", replies[0].timer->rtt, replies[1].timer->rtt, replies[2].timer->rtt);
    }

    dprintf(1, "%s\n", output);
}
