#ifndef P_PACKETS_H_
#define P_PACKETS_H_

#include <netinet/ip_icmp.h>
#include <unistd.h>

#include "u_libft.h"

#include "e_ping.h"

int       p_initpacket(t_pack * pack, uint64_t seq);
int16_t   p_checksum(const void *data, uint64_t size);
t_reply * p_deserialize(char recvbuf[]);
void      p_initping(t_ping * ping, t_time *timer, t_pack * pack, char * ipstr);

#endif
