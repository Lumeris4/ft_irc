/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/04 14:31:02 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

// ssize_t send(int socket, const void *buf, size_t len, int flags);
// int bind(int socket, const struct sockaddr *address,
//        socklen_t address_len);


int main(int argc, char **argv)
{
	int socketfd;
	int erreur;
	int test2;
	std::string test[100];
	
	if (argc != 3)
	{
		std::cerr << "Please respect this format: './ircserv <port> <password>'\n";
		return -1;
	}
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // toutes les interfaces locales	
	serv_addr.sin_port = htons(atoi(argv[1]));          // port 8080	
	if (bind(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	    std::cerr << "bind failed" << std::endl;
	else 
	{
		int test4 = connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		std::cout << test4 << std::endl;
		test2 = send(socketfd, "test", 4, MSG_EOR);
		std::cout << test << std::endl;

		erreur = recv(socketfd, test, 100, MSG_PEEK);
		std::cout << erreur << std::endl;
	}
	close(socketfd);
}