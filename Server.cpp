/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:26:38 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 14:04:58 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

bool connected[MAX_CLIENTS];

int Server::createUser()
{
	std::cout << "User created" << std::endl;
	_hasNickname = false;
	_hasUser = false;
	return (0);
}

int Server::setNickname(std::string nick)
{
	std::cout << nick << std::endl;
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
	int servsocket;
	int new_socket;
	char buffer[1024];
	int j = -1;

	servsocket = socket(AF_INET, SOCK_STREAM, 0);
	for (int i = 0; i < MAX_CLIENTS; i++)
		connected[i] = false;
	if (servsocket < 0)
	{
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }
	struct sockaddr_in serv_addr, cli_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // toutes les interfaces locales	
	serv_addr.sin_port = htons(this->_port);          // port 8080	
	if (bind(servsocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	{
	    std::cerr << strerror(errno) << std::endl;
		exit (1);
	}
	if (listen(servsocket, MAX_CLIENTS) < 0)
	{
       	std::cerr << strerror(errno) << std::endl;
       	close(servsocket);
       	exit(1);
    }
	
	struct pollfd fds[1 + MAX_CLIENTS];
	int nfds = 1;
    fds[0].fd = servsocket;
    fds[0].events = POLLIN;
	while (1)
	{
		int ret = poll(fds, nfds, -1); // attend indefiniment
    	if (ret == -1)
			std::cerr << strerror(errno) << std::endl;
    	else
		{
        	if (fds[0].revents & POLLIN)
			{
				socklen_t clilen = sizeof(cli_addr);
				new_socket = accept(servsocket, (struct sockaddr *)&cli_addr, &clilen);
				if (new_socket < 0)
				{
    			   	std::cerr << strerror(errno) << std::endl;
    			   	close(servsocket);
    			   	exit(1);
				}
				if (nfds - 1 < MAX_CLIENTS)
				{
            	    fds[nfds].fd = new_socket;
            	    fds[nfds].events = POLLIN;
            	    nfds++;
            	    std::cout << "Client connected to the server" << std::endl;
            	} 
				else
				{
                	std::cout << "Too many clients connected." << std::endl;
                	close(new_socket);
            	}
				
			}
			for (int i = 1; i < nfds; i++)
			{
				if (fds[i].revents & POLLIN)
				{
    		     	ssize_t n = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
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
    		 				j = parsing(cmd, connected[i]);
							switch (j)
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
							j = -1;
							if (_hasNickname && _hasUser)
								createUser();
						}
					}
					else if (n == 0)
					{
    		 			std::cout << "Client déconnecté proprement." << std::endl;
						close(fds[i].fd);
						fds[i] = fds[nfds - 1];
						nfds--;
						i--;
					}
					else
					{
						close(fds[i].fd);
						fds[i] = fds[nfds - 1];
						nfds--;
						i--;
						std::cerr << strerror(errno) << std::endl;
					}
    			}
			}		
        }
	}
	close(servsocket);
	for (int i = 1; i < nfds; i++)
		close(fds[i].fd);
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

void	Server::changeTopic(std::string channel, std::string topic)
{
	//check user have right
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setTopic(topic);
	}
}

void	Server::changePerm(std::string channel, bool perm)
{
	//check user right
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setAccess(perm);
	}
}

void	Server::changePassword(std::string channel, std::string password)
{
	//check user right
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setPassword(password);
	}
}

void	Server::givePerm(std::string channel, std::string name, bool give)
{
	//check user right
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		if (give)
			ito->second.remote(name);
		else
			ito->second.demote(name);
	}
}

void Server::changeLimit(std::string channel, int limit)
{
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setLimit(limit);
	}
}

void Server::permTopic(std::string channel, bool perm)
{
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setAccessTopic(perm);
	}
}

void Server::kick(std::string channel, std::string nickname)
{
	//check user right
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
			ito->second.kickuser(nickname);
	}
}