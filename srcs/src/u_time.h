#ifndef U_TIME_H_
#define U_TIME_H_

#include <stdint.h>
#include <sys/time.h>

#include "e_ping.h"

long double	u_timest(void);
long double	u_cmptime(long double time);
long double	u_avgtime(long double time);
long	u_longtime(void);
int	u_updatetime(long double val, t_time * timer);
void u_inittimer(t_time * timer);
long double u_mdev(uint8_t mode, long double time);

#endif
