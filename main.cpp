/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/05 12:07:47 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

// ssize_t send(int socket, const void *buf, size_t len, int flags);
// int bind(int socket, const struct sockaddr *address,
//        socklen_t address_len);


int main(int argc, char **argv)
{
	int socketfd;
	// int erreur;
	// int test2;
	void *test[100];
	int socket2 = 0;
	
	if (argc != 3)
	{
		std::cerr << "Please respect this format: './ircserv <port> <password>'\n";
		return -1;
	}
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
	{
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }
	struct sockaddr_in serv_addr, cli_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // toutes les interfaces locales	
	serv_addr.sin_port = htons(atoi(argv[1]));          // port 8080	
	if (bind(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	    std::cerr << strerror(errno) << std::endl;
	while (1)
	{
		if (listen(socketfd, 10) < 0)
		{
        	std::cerr << strerror(errno) << std::endl;
        	close(socketfd);
        	exit(1);
    	}
		socklen_t clilen = sizeof(cli_addr);
		socket2 = accept(socketfd, (struct sockaddr *)&cli_addr, &clilen);
		if (socket2 < 0)
		{
        	std::cerr << strerror(errno) << std::endl;
        	close(socketfd);
        	exit(1);
    	}
		send(socket2, "test", 4, MSG_EOR);
		recv(socketfd, test, 4, MSG_PEEK);
	}
	close(socketfd);
	close(socket2);
}