/*  Port Scanner
Author:    Hades.y2k
Version:   1.0
Date:      21/10/2015
License:   OpenSource GPL v<2.0>
*/

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

void usage() 
{
	puts("[-] Provide Hostname");
}

void banner() 
{
	puts("╔═╗┌─┐┬─┐┌┬┐  ╔═╗┌─┐┌─┐┌┐┌┌┐┌┌─┐┬─┐");
	puts("╠═╝│ │├┬┘ │   ╚═╗│  ├─┤││││││├┤ ├┬┘");
	puts("╩  └─┘┴└─ ┴   ╚═╝└─┘┴ ┴┘└┘┘└┘└─┘┴└─");
	puts("                          Hades.y2k");
}

int main(int argc, char **argv)
{
	int sockfd;
	int port;
	struct hostent *host_ent;

	banner();

	if (argc != 2) {
		fprintf(stderr, "[-] No Hostname detected\n");
		usage();
		exit(1);
	}

	if ((host_ent=gethostbyname(argv[1])) == NULL) {
		fprintf(stderr, "[-] %s\n", strerror(errno));
		exit(1);
	}

	for (port=0; port<=1024; port++) {
		struct sockaddr_in addr_name;
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			fprintf(stderr, "[-] %s\n", strerror(errno));
			exit(1);
		}
		addr_name.sin_family = AF_INET;
		addr_name.sin_port = htons(port);
		addr_name.sin_addr = *((struct in_addr *)(*host_ent).h_addr);
		memset(&(addr_name.sin_zero), '\0', 8);
		if (connect(sockfd, (struct sockaddr *)&addr_name, sizeof(struct sockaddr)) == -1) {
			close(sockfd);
		}
		else {
			printf("[+] Port %i open\n", port);
			close(sockfd);
		}

	}
	puts("[!] Scanning Complete\n");
	return 0;
}
