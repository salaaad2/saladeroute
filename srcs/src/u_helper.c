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
u_printsum(int ttl, uint8_t status, long double rtts[])
{
    char output[96];
    int len;

    len = sprintf(output, "%d ", ttl);
    if (status == 0)
    {
        len = sprintf(output + len, "* * *");
    }
    else
    {
        len = sprintf(output + len, "dummy_address, %.3Lfms %.3Lfms %.3Lfms", rtts[0], rtts[1], rtts[2]);
    }

    dprintf(1, "%s\n", output);
}
