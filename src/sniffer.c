#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include "link.h"
#include "sniffer.h"

#define clear() printf("\033[H\033[J")

void print_packet_info(uint8_t *packet) { print_ethhdr(packet); }

void sniff() {
  uint8_t packet[BUFF_SIZE] = {0};

  struct sockaddr_ll physical_addr;
  socklen_t physical_addr_len = sizeof(struct sockaddr_ll);

  int sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sd == -1) {
    printf("[Error] can't create socket descriptor\n");
    return;
  }

  ssize_t len = recvfrom(sd, packet, BUFF_SIZE - 1, MSG_PEEK,
                         (struct sockaddr *)&physical_addr, &physical_addr_len);
  if (len == -1) {
    printf("[Error] can't get raw packet\n");
    goto cleanup;
  }
  print_packet_info(packet);

cleanup:
  close(sd);
}

void start(unsigned int delay) {
  while (1) {
    sniff();
    sleep(delay);
    clear();
  }
}
