/*********************************/
/*   FT_PING          (  //      */
/*   logic             ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "e_ping.h"
#include "p_packets.h"
#include "u_time.h"
#include "u_err.h"
#include "u_helper.h"
#include "u_libft.h"

int
e_start(char *url, t_opts * opts)
{
    struct sockaddr_in * servaddr;
    struct addrinfo * res;
    t_pack pack;
    int sock = -1;
    struct addrinfo hints = {
        AI_CANONNAME, AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, NULL, NULL, NULL
    };
    char ipstr[4096];
    void * addr;
    t_time timer;
    t_ping ping;

    /*
    ** DNS resolution and address settings happen here
    ** */
    if ((getaddrinfo(url, NULL, &hints, &res)) < 0) {
        return (u_printerr(url, "Name or service not known"));
    }
    if (res != NULL)
    {
        servaddr = (struct sockaddr_in *)res->ai_addr;
        addr = &(servaddr->sin_addr);
        inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
        if (ft_strcmp(ipstr, url)) {
            opts->textaddr = 1;
            ping.url = url;
            /*
            ** reverse hostname if address is not in ipv4 format ???
             */
        } else {
            opts->textaddr = 0;
            ping.url = ipstr;
            /* return (u_printerr("invalid address", ipstr)); */
        }
        printf("PING %s (%s): %d data bytes\n", url, ipstr, DATA_SIZE);
    } else {
        return (1);
    }

    /*
    ** socket() and setsockopt()
    ** @ret > 0
    ** */
    sock = e_setsockets();
    if (sock < 0) {
        free(opts);
        return (1);
    }

    /* loop : seq is incremented on each ping/pong.
     ** time also needs to be managed each time a ping happens
     ** */
    u_inittimer(&timer);
    p_initping(&ping, &timer, &pack, ipstr);
    e_loop(&ping, servaddr, sock);

    /*
    ** print stats when exiting
    ** */
    e_output(&ping, opts->textaddr);
    freeaddrinfo(res);
    free(ping.reply);
    free(opts);
    return (0);
}

int
e_setsockets(void)
{
    const int hdr = 1;
    int sockfd;
    struct timeval rcv_timeout =
        {1, 1};
    (void)hdr;

    rcv_timeout.tv_sec = 1;
    rcv_timeout.tv_usec = 0;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    {
        return (u_printerr("failed to create socket", "socket"));
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout, sizeof(rcv_timeout)) != 0)
    {
        printf("%s %d\n", strerror(errno), errno);
        sockfd = -1;
        return (u_printerr("failed to set socket options", "setsockopt"));
    }
    return (sockfd);
}

/*
** sendto icmp header set by p_initpacket()
** recvfrom IP and ICMP headers and deserialize them
** t_reply->ip
** t_reply->icmp
 */
t_reply *
e_trytoreach(int sock, struct sockaddr_in * addr, t_ping * ping, int * ttl)
{
    socklen_t addrsize = sizeof(const struct sockaddr);
    char recvbuf[98];
    t_reply * full;
    t_pack * pack = ping->pack;
    t_time * timer = ping->timer;
    int ret = 42;
    struct sockaddr_in peer_addr;
    socklen_t peer_size = sizeof(peer_addr);
    char peer_addr_buf[INET_ADDRSTRLEN];
    const char * peer_name_char;

    ft_bzero(recvbuf, 98);
    /* update socket with increased ttl */
    if (setsockopt(sock, IPPROTO_IP, IP_TTL, ttl, sizeof(int)) < 0)
    {
        return ((t_reply*)0x0);
    }

    if (sendto(sock, pack, PACK_SIZE, 0, (struct sockaddr *)addr, addrsize) < 0) {
        u_printerr("socket error", "sendto()");
        return (NULL);
    }
    ping->sent++;
    timer->itv = u_timest();

    if ((ret = recvfrom(sock, &recvbuf, PACK_SIZE + IP_SIZE, 0, (struct sockaddr *)&peer_addr, &peer_size)) < 0) {
        u_updatetime(u_timest(), timer);
        return (NULL);
    }
    ping->received++;
    u_updatetime(u_timest(), timer);
    full = p_deserialize(recvbuf);
    if (full->hdr.type != ICMP_ECHOREPLY && full->hdr.type != ICMP_TIME_EXCEEDED)
    {
        return (NULL);
    }
    else
    {
        peer_name_char = inet_ntop(AF_INET, &peer_addr.sin_addr, peer_addr_buf, sizeof(peer_addr_buf));
        dprintf(1, "got: %s\nttl: %d\n", peer_name_char, *ttl);

    }
    return (full);
}

int
e_loop(t_ping * ping, struct sockaddr_in * servaddr, int sock)
{
    uint8_t running;
    long reptime = 0;
    uint8_t seq;
    int ttl = 0;

    /*
    ** set running semiglobal variable
    ** */
    running = 1;
    u_setrunning(0, &running);
    signal(SIGINT, u_handle_sigint);

    seq = 0;
    while (running == 1) {
        if ((reptime + 1000) > u_longtime())
        {
            continue; /* ping once every second */
        } else {
            p_initpacket(ping->pack, seq);
            ping->reply = e_trytoreach(sock, servaddr, ping, &ttl);
            seq++;
            ttl++;
        }
    }
    return (0);
}

int
e_output(t_ping * ping, uint8_t isstr)
{
    uint32_t ploss;
    char * str = (isstr ? ping->url : ping->ipstr);

    if (ping->received != 0) {
      ploss = u_ploss(ping->sent, ping->received);
    } else {
        ploss = 100;
    }

    printf("\n--- %s ft_ping statistics ---\n", str);
    dprintf(1, "%ld packets transmitted, %ld received,  %d%% packet loss\n",
            ping->sent, ping->received, ploss);
    if (ping->received != 0) {
        dprintf(1,
                "round-trip min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n",
                ping->timer->min, ping->timer->avg, ping->timer->max,
                u_mdev(1, 1.0f));
    }
    return (0);
}
