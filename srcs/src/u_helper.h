#ifndef U_HELPER_H_
#define U_HELPER_H_

#include <signal.h>
#include <stdint.h>

#include "u_libft.h"

#include "traceroute.h"

uint32_t u_ploss(uint32_t sent, uint32_t received);
void u_handle_sigint(int dummy);
void u_setrunning(bool_t mode, bool_t * running);
int  u_help(void);
int  u_printerr(char * reason, char * value);

#endif
