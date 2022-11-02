#ifndef P_PACKETS_H_
#define P_PACKETS_H_

#include <netinet/ip_icmp.h>
#include <unistd.h>

#include "u_libft.h"

#include "traceroute.h"

int       p_initpacket(t_pack * pack, int seq);
int16_t   p_checksum(const void *data, uint64_t size);
t_reply * p_deserialize(char recvbuf[]);
void      p_init_main_structs(t_tracert * ping, t_time *timer, t_pack * pack);

#endif
