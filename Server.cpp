/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:26:38 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 11:01:17 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

int Server::createUser()
{
	std::cout << "User created" << std::endl;
	_hasNickname = false;
	_hasUser = false;
	return (0);
}

int Server::setNickname(std::string nick)
{
	if (nick.length() > 9)
	{
		std::cout << "nick length has too long" << std::endl;
		return (-1);
	}
	std::map<std::string, User>::iterator it = _list_user.find(nick);
	{
        if (it != _list_user.end())
		{
			std::cout << "Nick already taken, please choose another one" << std::endl;
			return (-1);
		}
	}
	_hasNickname = true;
	return (0);
}

int Server::setUser()
{
	_hasUser = true;
	return (0);
}

int Server::init_server()
{
	int socketfd;
	char buffer[1024];
	int socket2 = 0;
	int i = -1;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
	{
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }
	struct sockaddr_in serv_addr, cli_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // toutes les interfaces locales	
	serv_addr.sin_port = htons(this->_port);          // port 8080	
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
					std::string input = buffer;
					std::stringstream ss(input);
					std::string cmd;
					while (std::getline(ss, cmd, '\n'))
					{
						_argument= "";
        				i = parsing(cmd);
						switch (i)
						{
							case 0:
								break;
							case 1:
							{
								setNickname(_argument);
								break;
							}
							case 2:
							{
								setUser();
								break;
							}
							default:
								break;
						}
						i = -1;
						if (_hasNickname && _hasUser)
							createUser();
					}
    			}
				else if (n == 0)
				{
        			std::cout << "Client déconnecté proprement." << std::endl;
					close(socket2);
				}
				else
				std::cerr << strerror(errno) << std::endl;
            }
        }
    }
	close(socketfd);
	close(socket2);
	return (0);
}

Server::Server(std::string password, int port): _password(password), _port(port)
{
	_hasNickname = false;
	_hasUser = false;
}

Server::~Server() {}

Server::Server(): _port(-1) {}

void	Server::addChannel(std::string name, User &proprio)
{
	Channel channel = Channel(name, proprio.getNickname());
	this->_list_channel.insert(std::pair<std::string, Channel>(name, channel));
}

void	Server::addUser(std::string name, std::string nickname)
{
	User user = User(name, nickname);
	this->_list_user.insert(std::pair<std::string, User>(nickname, user));
}

const std::map<std::string, User>	&Server::getListUser() const
{
	return this->_list_user;
}

const std::map<std::string, Channel>	&Server::getListChannel() const
{
	return this->_list_channel;
}