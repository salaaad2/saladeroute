#include "p_packets.h"
#include "u_err.h"

#include <sys/time.h>


int16_t
p_checksum(const void *data, size_t size)
{
    register long sum = 0;
    int i;

    i = 0;
    while( size > 1 )  {
        sum += ((uint16_t*) data)[i];
        i++;
        size -= 2;
    }

    if( size > 0 )
        sum += * (uint8_t *) data;

    while (sum>>16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ((int16_t)~sum);
}

int
p_initpacket(t_pack * pack, uint64_t seq)
{
    uint16_t i = 0;

    ft_bzero(pack, sizeof(pack));

    pack->hdr.type = ICMP_ECHO;
    pack->hdr.code = 0;
    pack->hdr.checksum = 0;
    pack->hdr.un.echo.id = getpid();
    pack->hdr.un.echo.sequence = seq;

    while (i < (DATA_SIZE - 1))
    {
        pack->load[i] = i + '9';
        i++;
    }
    pack->load[i] = '\0';
    pack->hdr.checksum = p_checksum(pack, PACK_SIZE);
    return (0);
}

/*
** recvfrom 98 bytes after sending 64.
** this increased size allows us to get the ip header from the received packet.
** very cool.
*/
t_reply *
p_deserialize(char recvbuf[])
{
    static t_reply * reply;

    if (reply == NULL) {
        reply = ft_calloc(1, sizeof(t_reply));
        if (reply == NULL) {
            u_printerr("fatal errorr", "calloc()");
            return (reply);
        }
    }

    ft_memcpy(&reply->ip, recvbuf, 20);
    ft_memcpy(&reply->hdr, recvbuf + 20, 64);
    return (reply);
}

/*
** set all t_ping fields
*/
void
p_initping(t_ping * ping, t_time *timer, t_pack * pack, char * ipstr)
{
    ping->timer = timer;
    ping->pack = pack;
    ping->reply = NULL;
    ping->sent = 0;
    ping->received = 0;                         \
    ft_memcpy(ping->ipstr, ipstr, 15);
}
