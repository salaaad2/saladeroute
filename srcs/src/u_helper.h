#ifndef U_HELPER_H_
#define U_HELPER_H_

#include <signal.h>
#include <stdint.h>

#include "u_libft.h"

#include "traceroute.h"

uint32_t u_ploss(uint32_t sent, uint32_t received);
void u_handle_sigint(int dummy);
void u_handle_sigalrm(int dummy);
void u_setrunning(uint8_t mode, uint8_t * running);
int u_help( void );
int u_printpack(t_tracert *ping, uint64_t seq);

#endif
