#ifndef U_TIME_H_
#define U_TIME_H_

#include <stdint.h>
#include <sys/time.h>

#include "traceroute.h"

long double	u_timest(void);
long double	u_cmptime(long double time);
long double	u_avgtime(long double time);
int	u_updatetime(long double val, t_time * timer);
void	u_inittimer(t_time * timer);

#endif
