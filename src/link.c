#include "link.h"
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <stdint.h>
#include <stdio.h>
#include "network.h"

void print_ethhdr(uint8_t *packet) {
  struct ethhdr *eth = (struct ethhdr *)packet;
  uint16_t proto = ntohs(eth->h_proto);

  printf("======================== Ethernet Header ========================\n");
  printf("              Source     : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
         eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3],
         eth->h_source[4], eth->h_source[5]);
  printf("              Destination: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
         eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3],
         eth->h_dest[4], eth->h_dest[5]);
  printf("              Type       : 0x%.4X\n", proto);
  printf("\n");

  uint8_t *next_packet = packet + sizeof(struct ethhdr);

  switch (proto) {
    case ETH_P_IP:
      print_iphdr(next_packet);
      break;
    case ETH_P_IPV6:
      print_ip6hdr(next_packet);
      break;
  }
}