#ifndef TRACEROUTE_H_
#define TRACEROUTE_H_

#include "u_libft.h"
#include "u_opts.h"

#include <netinet/ip_icmp.h>
#include <stdint.h>


#define IP_SIZE sizeof(struct icmphdr)
#define ICMP_SIZE sizeof(struct icmphdr)
#define DATA_SIZE 56
#define PACK_SIZE ICMP_SIZE + DATA_SIZE

typedef struct s_pack {
    struct icmphdr hdr;
    char load[DATA_SIZE];
} t_pack ;

typedef struct s_reply {
    struct iphdr ip;
    struct icmphdr hdr;
    char load[DATA_SIZE];
} t_reply;

typedef struct s_time {
    long double itv, ntv, avg, lapse, min, max, mdev, total, rtt;
} t_time ;

typedef struct s_ping {
    t_time * timer;
    t_pack * pack;
    t_reply * reply;
    unsigned long sent;
    unsigned long received;
    char url[sizeof "255.255.255.255"];
    bool_t reached;
} t_tracert;

int e_start(char * url, t_opts * opts);
int e_setsockets(void);
t_reply * e_trytoreach(int sock, struct sockaddr_in * addr, t_tracert * ping, int * ttl);
int e_loop(t_tracert * ping, struct sockaddr_in * servaddr, t_opts * options, int sock);

#endif
