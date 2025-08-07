/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/07 11:14:15 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "parsing/Parsing.hpp"

int main(int argc, char **argv)
{
	int socketfd;
	char buffer[1024];
	int socket2 = 0;
	Parsing parser;
	
	if (argc != 3)
	{
		std::cerr << "Please respect this format: './ircserv <port> <password>" << std::endl;
		return -1;
	}
	std::string password = argv[2];
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
	{
	    std::cerr << strerror(errno) << std::endl;
		exit (1);
	}
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
	std::cout << "Client connected to the server" << std::endl;
	while (1)
	{
		struct pollfd fds[1];
    	fds[0].fd = socket2;
    	fds[0].events = POLLIN;     // on veut savoir si on peut lire
		int ret = poll(fds, 1, -1); // attend indefiniment
    	if (ret == -1)
			std::cerr << strerror(errno) << std::endl;
    	else
		{
        	if (fds[0].revents & POLLIN)
			{
            	ssize_t n = recv(socket2, buffer, sizeof(buffer) - 1, 0);
    			if (n > 0)
				{
        			buffer[n] = '\0';
					std::cout << buffer << std::endl;
        			if (parser.parsing(buffer, password) == -1)
					{
						std::cout << "invalid password detected : disconnecting user" << std::endl;
						return (-1);
					}
    			}
				else if (n == 0)
				{
					parser.setConnected(false);
        			std::cout << "Client déconnecté proprement." << std::endl;
					break;
				}
				else
				std::cerr << strerror(errno) << std::endl;
            }
        }
    }
	close(socketfd);
	close(socket2);
}

