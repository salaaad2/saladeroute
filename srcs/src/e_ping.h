#ifndef E_PING_H_
#define E_PING_H_

#include "u_libft.h"

#include "p_main.h"

#include <netinet/ip_icmp.h>


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
    long double itv, ntv, avg, lapse, min, max, mdev, total;
} t_time ;

typedef struct s_ping {
    t_time * timer;
    t_pack * pack;
    t_reply * reply;
    unsigned long sent;
    unsigned long received;
    char ipstr[16];
    char * url;
} t_ping;

int e_start(char * url, t_opts * opts);
int e_setsockets(void);
t_reply * e_trytoreach(int sock, struct sockaddr_in * addr, t_ping * ping, int * ttl);
int e_loop(t_ping * ping, struct sockaddr_in * servaddr, int sock);
int e_output(t_ping * ping, uint8_t isstr);

#endif
