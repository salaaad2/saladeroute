/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   helpers           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "u_helper.h"

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

int
u_printpack(t_tracert *ping, uint64_t seq)
{
    dprintf(1, "%ld bytes from %s: seq=%ld ttl=%d time=%.3Lf\n", sizeof(t_pack), ping->ipstr, seq, ping->reply->ip.ttl, ping->timer->lapse);
    return (0);
}

void
u_printsum(int ttl, bool_t status)
{
    char * output;
    sprintf(output, "%d ", ttl);
    if (status == 0)
    {
        sprintf(output, "* * *\n");
    }
}
