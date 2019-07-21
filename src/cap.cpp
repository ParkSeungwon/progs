#include <sys/time.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <pcap/pcap.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <map>
#include <iostream>
#include <netdb.h>

#define PROMISCUOUS 1
#define NONPROMISCUOUS 0

struct ip *iph;
struct tcphdr *tcph;

using namespace std;

map<string, int> addrs;
void callback(u_char *useless, const struct pcap_pkthdr *pkthdr, 
                const u_char *packet)
{
    static int count = 1;
    struct ether_header *ep;
    unsigned short ether_type;    
    int chcnt =0;
    int length=pkthdr->len;

    ep = (struct ether_header *)packet;
    packet += sizeof(struct ether_header);

    ether_type = ntohs(ep->ether_type);

    if (ether_type == ETHERTYPE_IP) {
        iph = (struct ip *)packet;
		addrs[inet_ntoa(iph->ip_dst)]++;
	}
}    

int main(int argc, char **argv)
{
    char *dev, *net, *mask;
    bpf_u_int32 netp, maskp;
    char errbuf[PCAP_ERRBUF_SIZE];
    int ret;
    struct pcap_pkthdr hdr;
    struct in_addr net_addr, mask_addr;
    struct ether_header *eptr;
    const u_char *packet;
    struct bpf_program fp;     
    pcap_t *pcd;  // packet capture descriptor

    // 사용중인 디바이스 이름을 얻어온다. 
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        printf("%s\n", errbuf);
        exit(1);
    }
    printf("DEV : %s\n", dev);

    // 디바이스 이름에 대한 네트웍/마스크 정보를 얻어온다. 
    ret = pcap_lookupnet(dev, &netp, &maskp, errbuf);
    if (ret == -1) {
        printf("%s\n", errbuf);
        exit(1);
    }

    // 네트웍/마스트 정보를 점박이 3형제 스타일로 변경한다. 
    net_addr.s_addr = netp;
    net = inet_ntoa(net_addr);
    printf("NET : %s\n", net);

    mask_addr.s_addr = maskp;
    mask = inet_ntoa(mask_addr);
    printf("MSK : %s\n", mask);
    printf("=======================\n");

    // 디바이스 dev 에 대한 packet capture 
    // descriptor 를얻어온다.   
    pcd = pcap_open_live(dev, BUFSIZ,  NONPROMISCUOUS, -1, errbuf);
    if (pcd == NULL) {
        printf("%s\n", errbuf);
        exit(1);
    }    

    // 컴파일 옵션을 준다.
    if (pcap_compile(pcd, &fp, argv[2], 0, netp) == -1) {
        printf("compile error\n");    
        exit(1);
    }
    // 컴파일 옵션대로 패킷필터 룰을 세팅한다. 
    if (pcap_setfilter(pcd, &fp) == -1) {
        printf("setfilter error\n");
        exit(0);    
    }

    // 지정된 횟수만큼 패킷캡쳐를 한다. 
    // pcap_setfilter 을 통과한 패킷이 들어올경우 
    // callback 함수를 호출하도록 한다. 
    pcap_loop(pcd, atoi(argv[1]), callback, NULL);

	char hostname[260];
	char service[260];
	sockaddr_in address;
	for(auto& a : addrs) {
		const char* ip = a.first.data();
		cout << ip << " : " << a.second << " --- ";

		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(ip);
		int response = getnameinfo((sockaddr*)&address, sizeof(address), 
				hostname, 260, service, 260, 0);
		if(response == 0) {
			cout << hostname << "\n";
		} else cout << endl;
	}
}
