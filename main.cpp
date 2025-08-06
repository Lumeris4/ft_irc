/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/06 12:59:35 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

// ssize_t send(int socket, const void *buf, size_t len, int flags);
// int bind(int socket, const struct sockaddr *address,
//        socklen_t address_len);

int check_password(std::string password, std::string real_password)
{
	if (!password.compare(real_password))
		return (0);
	return (-1);
}


int parsing (char *buf, std::string password)
{
	std::string input = buf;
	std::stringstream ss(input);
	std::string cmds;
	std::string line;
	std::string array[] = {"CAP", "PASS", "NICK", "KICK", "MODE", "TOPIC", "USER", "JOIN", "INVITE"};
	int last_upper;
	int level;

	while (std::getline(ss, cmds, '\n'))
	{
		last_upper = 0;
        line = cmds;
		std::cout << line << std::endl;
		line.erase(line.size() - 1, 1);
		for (int i = 0; isupper(line[i]) && i < (int)line.size(); i++)
			last_upper = i + 1;
		std::string raw_cmd = line.substr(0, last_upper);
		std::string argument = line.substr(last_upper + 1);
		for (size_t i = 0; i < array->length(); i++)
		{
			if (!raw_cmd.compare(array[i]))
				level = i;
		}
		switch (level)
		{
			case 0:
				break;
			case 1:
			{
				if (check_password(argument, password) == -1)
					return (-1);
				break;
			}
			case 2:
			{
				std::cout << "command NICK found" << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "command KICK found" << std::endl;
				break;
			}
			case 4:
			{
				std::cout << "command MODE found" << std::endl;	
			break;
			}
			case 5:
			{
				std::cout <<  "command TOPIC found" << std::endl;
				break;
			}
			case 6:
			{
				std::cout << "command USER found" << std::endl;
				break;
			}
			case 7:
			{
				std::cout << "command JOIN found" << std::endl;
				break;
			}
			case 8:
			{
				std::cout << "command INVITE found" << std::endl;
				break;
			}
			default:
				std::cout << line << " is not a valid command" <<std::endl;
				break;
		}
	}	
	return (0);
}

// int parsing (char *buf, std::string password)
// {
// 	std::string input = buf;
// 	std::string cmp;

// 	std::stringstream line;

// 	std::cout << "parsing called" << std::endl;
// 	for (int i = 0; isupper(input[i]); i++)
// 	cmp = input.substr(0, i);
// 	std::cout << cmp << std::endl;
// 	//MODE
// 	if (cmp.compare("MODE"))
// 		return (1);
// 	//KICK
// 	if (cmp.compare("KICK"))
// 		return (1);
// 	//TOPIC
// 	if (cmp.compare("TOPIC"))
// 		return (1);
// 	//NICK
// 	if (cmp.compare("NICK"))
// 		return (1);
// 	//USER
// 	if (cmp.compare("USER"))
// 		return (1);
// 	//PASS
// 	if (cmp.compare("PASS"))
// 	{
// 		if (check_password(input.substr(5), password) == -1)
// 			return (-1);
// 		return (0);
// 	}
// 	//JOIN
// 	if (cmp.compare("JOIN"))
// 		return (1);
// 	//INVITE
// 	if (cmp.compare("INVITE"))
// 		return (1);
// 	else 
// 		std::cout << "invalid command" << std::endl;
// 	std::cout << "read in fd : " << input << std::endl;
// 	return (0);
// }

int main(int argc, char **argv)
{
	int socketfd;
	char buffer[1024];
	int socket2 = 0;
	
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
        			if (parsing(buffer, password) == -1)
					{
						std::cout << "invalid password detected : disconnecting user" << std::endl;
						return (-1);
					}
    			}
				else if (n == 0)
				{
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
