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
    printf("Usage\n./ft_traceroute [options] <destination>\n\nOptions:\n");
    printf(" -v\tverbose output\n");
    return (0);
}

int
u_printerr(char * reason, char * value)
{
    dprintf(2, "ft_tracert: %s: %s\n", reason, value);
    return (-1);
}
