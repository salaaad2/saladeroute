/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   logic             ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "traceroute.h"
#include "p_packets.h"
#include "u_opts.h"
#include "u_time.h"
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
    t_tracert tracert;

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
            tracert.url = url;
            /*
            ** reverse hostname if address is not in ipv4 format ???
             */
        } else {
            opts->textaddr = 0;
            tracert.url = ipstr;
        }
        printf("traceroute to %s (%s): 30 hops max, %d byte packets\n", url, ipstr, DATA_SIZE);
    } else {
        return (u_printerr("invalid address", ipstr));
    }

    /*
    ** socket() and setsockopt()
    ** */
    sock = e_setsockets();
    if (sock < 0) {
        free(opts);
        return (1);
    }

    /*
     ** init timers and structures; then send them to e_loop(), where
     ** ttl is incremented to actually get the route
     ** */
    u_inittimer(&timer);
    p_init_main_structs(&tracert, &timer, &pack, ipstr);
    e_loop(&tracert, servaddr, sock);

    freeaddrinfo(res);
    free(tracert.reply);
    free(opts);
    return (0);
}

int
e_setsockets(void)
{
    int sockfd;
    struct timeval rcv_timeout =
        {1, 1};

    rcv_timeout.tv_sec = 1;
    rcv_timeout.tv_usec = 0;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    {
        return (u_printerr("failed to create socket", "socket"));
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout, sizeof(rcv_timeout)) != 0)
    {
        sockfd = -1;
        return (u_printerr("failed to set socket options", "setsockopt"));
    }
    return (sockfd);
}

/*
** sendto and recvfrom, ttl is modified by the caller (e_loop())
** recvfrom IP and ICMP headers and deserialize them
** t_reply->ip
** t_reply->icmp
 */
t_reply *
e_trytoreach(int sock, struct sockaddr_in * addr, t_tracert * tracert, int * ttl)
{
    struct sockaddr_in peer_addr;
    socklen_t peer_size = sizeof(peer_addr);
    socklen_t addrsize = sizeof(const struct sockaddr);
    t_reply * full;
    long double rtt;
    char peer_addr_buf[INET_ADDRSTRLEN];
    char recvbuf[98];

    ft_bzero(recvbuf, 98);
    /* update socket with increased ttl */
    if (setsockopt(sock, IPPROTO_IP, IP_TTL, ttl, sizeof(int)) < 0)
    {
        u_printerr("failed to set ttl", "ttl");
        return ((t_reply*)0x0);
    }

    tracert->timer->itv = u_timest();
    if (sendto(sock, tracert->pack, PACK_SIZE, 0, (struct sockaddr *)addr, addrsize) < 0) {
        u_printerr("socket error", "sendto()");
        return (NULL);
    }
    tracert->sent++;

    if ((recvfrom(sock, &recvbuf, PACK_SIZE + IP_SIZE, 0, (struct sockaddr *)&peer_addr, &peer_size)) < 0) {
        u_updatetime(u_timest(), tracert->timer);
        return (NULL);
    }
    rtt = (u_timest() - tracert->timer->itv);
    tracert->timer->rtt = rtt;
    tracert->received++;
    u_updatetime(u_timest(), tracert->timer);
    full = p_deserialize(recvbuf);
    if (full->hdr.type == ICMP_ECHOREPLY)
    {
        /*
         * reached destination, stop execution
         **/
        tracert->reached = 1;
    }
    tracert->url = strdup(inet_ntop(AF_INET, &peer_addr.sin_addr, peer_addr_buf, sizeof(peer_addr_buf)));
    return (full);
}

int
e_loop(t_tracert * tracert, struct sockaddr_in * servaddr, int sock)
{
    int ttl;
    int probe_nb;
    char output[96];
    int len;
    bool_t print_addr;

    /*
    ** set running semiglobal variable
    ** */
    print_addr = 0;
    probe_nb = 0;
    u_setrunning(0, &tracert->reached);
    signal(SIGINT, u_handle_sigint);

    ttl = 1;
    while (tracert->reached == 0 && ttl >= 0 && ttl < 30) {
        len = sprintf(output, "%-3d", ttl);
        while (probe_nb < 3)
        {
            /* this should be parallelized but there is no suitable function in the subject :/ */
            p_initpacket(tracert->pack);
            u_timest();
            tracert->reply = e_trytoreach(sock, servaddr, tracert, &ttl);
            probe_nb++;
            if (tracert->reply != NULL)
            {
                if (!print_addr)
                {
                    len += sprintf(output + len, " %s, ", tracert->url);
                    print_addr = 1;
                }
                len += sprintf(output + len, " %.3Lfms ", tracert->timer->rtt);
            }
            else
            {
                len += sprintf(output + len, " * ");
            }
            /* copy full struct */
        }
        dprintf(1, "%s\n", output);
        free(tracert->url);
        tracert->url = NULL;
        probe_nb = 0;
        print_addr = 0;
        ttl++;
    }
    return (0);
}
