#include<stdio.h>
#include<netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<iostream>
using namespace std;
	union  U {
		struct  {
			int a;
		} ;
		struct  {
			char b;
		} ;
	};
struct tcphdr
  {
    __extension__ union
    {
      struct
      {
	u_int16_t th_sport;		/* source port */
	u_int16_t th_dport;		/* destination port */
	u_int32_t th_seq;		/* sequence number */
	u_int32_t th_ack;		/* acknowledgement number */
# if __BYTE_ORDER == __LITTLE_ENDIAN
	u_int8_t th_x2:4;		/* (unused) */
	u_int8_t th_off:4;		/* data offset */
# endif
# if __BYTE_ORDER == __BIG_ENDIAN
	u_int8_t th_off:4;		/* data offset */
	u_int8_t th_x2:4;		/* (unused) */
# endif
	u_int8_t th_flags;
# define TH_FIN	0x01
# define TH_SYN	0x02
# define TH_RST	0x04
# define TH_PUSH	0x08
# define TH_ACK	0x10
# define TH_URG	0x20
	u_int16_t th_win;		/* window */
	u_int16_t th_sum;		/* checksum */
	u_int16_t th_urp;		/* urgent pointer */
      };
      struct
      {
	u_int16_t source;
	u_int16_t dest;
	u_int32_t seq;
	u_int32_t ack_seq;
# if __BYTE_ORDER == __LITTLE_ENDIAN
	u_int16_t res1:4;
	u_int16_t doff:4;
	u_int16_t fin:1;
	u_int16_t syn:1;
	u_int16_t rst:1;
	u_int16_t psh:1;
	u_int16_t ack:1;
	u_int16_t urg:1;
	u_int16_t res2:2;
# elif __BYTE_ORDER == __BIG_ENDIAN
	u_int16_t doff:4;
	u_int16_t res1:4;
	u_int16_t res2:2;
	u_int16_t urg:1;
	u_int16_t ack:1;
	u_int16_t psh:1;
	u_int16_t rst:1;
	u_int16_t syn:1;
	u_int16_t fin:1;
# else
#  error "Adjust your <bits/endian.h> defines"
# endif
	u_int16_t window;
	u_int16_t check;
	u_int16_t urg_ptr;
      };
    };
};
int main()
{
	tcphdr t = {80,80,0,0,0,5,2,0,0,0};
}
