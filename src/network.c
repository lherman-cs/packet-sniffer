#include "network.h"

#include <arpa/inet.h>
#include <linux/if_arp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <stdio.h>

#define IP6_LEN 128

void print_iphdr(uint8_t *packet) {
  struct iphdr *hdr = (struct iphdr *)packet;
  struct protoent *proto = getprotobynumber(hdr->protocol);
  struct in_addr ip_addr;

  printf("========================== IP Header ==========================\n");
  printf("              Version      : %u\n", hdr->version);
  printf("              Protocol     : %s\n", proto->p_name);
  ip_addr.s_addr = hdr->saddr;
  printf("              Source       : %s\n", inet_ntoa(ip_addr));
  ip_addr.s_addr = hdr->daddr;
  printf("              Destination  : %s\n", inet_ntoa(ip_addr));
  printf("\n");
}

void print_ip6hdr(uint8_t *packet) {
  struct ip6_hdr *hdr = (struct ip6_hdr *)packet;
  struct ip6_hdrctl *meta = &hdr->ip6_ctlun.ip6_un1;
  uint8_t version = (meta->ip6_un1_flow >> 28);
  uint8_t traffic_class = (meta->ip6_un1_flow >> 20) & 0xf;
  uint32_t flow_label = ntohl(meta->ip6_un1_flow & 0xfffff);
  struct protoent *proto = getprotobynumber(meta->ip6_un1_nxt);
  char src[IP6_LEN + 1] = {0};
  char dst[IP6_LEN + 1] = {0};
  inet_ntop(AF_INET6, (void *)&hdr->ip6_src, src, IP6_LEN);
  inet_ntop(AF_INET6, (void *)&hdr->ip6_dst, dst, IP6_LEN);

  printf("========================== IP Header ==========================\n");
  printf("              Version      : %u\n", version);
  printf("              Protocol     : %s\n", proto->p_name);
  printf("              Traffic Class: %u\n", traffic_class);
  printf("              Flow Label   : %u\n", flow_label);
  printf("              Source       : %s\n", src);
  printf("              Destination  : %s\n", dst);
  printf("\n");
}
