/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:26:38 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:37 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

bool is_user[MAX_CLIENTS];

int Server::createUser(int socketfd, int i)
{
	if (is_user[i])
		return (0);
	addUser(socketfd, _nickname, _user);
	is_user[i] = true;
	std::cout << "User created " << socketfd << std::endl;
	_user = "";
	_nickname = "";
	return (0);
}

int Server::setNickname(std::string nick)
{
	if (nick.empty())
	{
		std::cout << "Nickname cannot be empty";
		return (-1);
	}
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
	_nickname = nick;
	return (0);
}

int Server::setUser(std::string nick)
{
	if (nick.empty())
	{
		std::cout << "Username cannot be empty";
		return (-1);
	}
	_user = nick;
	return (0);
}

int Server::init_server()
{
	int servsocket;
	int new_socket;
	char buffer[1024];
	int j = -1;
	_servername = "ircserv";
	servsocket = socket(AF_INET, SOCK_STREAM, 0);
	
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
						std::cout << buffer;
						std::string input = buffer;
						std::stringstream ss(input);
						std::string cmd;
						while (std::getline(ss, cmd, '\n'))
						{
							_argument= "";
    		 				j = parsing(cmd, i, fds[i].fd);
							if (is_user[i] == false && j > 2)
								j = 20;
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
									setUser(_argument);
									break;
								}
								case 3:
								{
									handle_mode(_argument, fds[i].fd);
									break;
								}
								case 4:
								{
									handle_topic(_argument, fds[i].fd);
									break;
								}
								case 5:
								{
									handle_invite(_argument, fds[i].fd);
									break;
								}
								case 6:
								{
									handle_kick(_argument, fds[i].fd);
									break;
								}
								case 7:
								{
									handle_join(_argument, fds[i].fd);
									break;
								}
								case 8:
								{
									//msg ici
									break;
								}
								case 9:
								{
									handle_ping(_argument, fds[i].fd);
									break;
								}
								case 10: 
								{
									handle_whois(_argument, fds[i].fd);
								}
								case 20:
								{
									std::cout << "Cannot execute command if clients is not a user" << std::endl;
								}
								default:
									break;
							}
							j = -1;
							if (_nickname.compare("") && _user.compare(""))
								createUser(fds[i].fd, i);
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
	_nickname = "";
	_user = "";
}

Server::~Server() {}

Server::Server(): _port(-1) {}

std::string Server::whatUser(int socketfd)
{
	std::string nickname;
	std::map<int, User>::iterator it;
	for (it = _list_socket_user.begin(); it != _list_socket_user.end(); it++)
	{
		if (it->first == socketfd)
		{
			nickname = it->second.getNickname();
		}
	}
	if (nickname.empty())
		return NULL;
	return nickname;
}

bool Server::haveright(int socketfd, std::string channel)
{
	std::string nickname;
	std::map<int, User>::iterator it;
	for (it = _list_socket_user.begin(); it != _list_socket_user.end(); it++)
	{
		if (it->first == socketfd)
		{
			nickname = it->second.getNickname();
		}
	}
	std::map<std::string, Channel>::iterator itt = _list_channel.find(channel);
	if (itt != _list_channel.end())
	{
		std::vector<std::string> copy = itt->second.getListChef();
		std::vector<std::string>::iterator itp = find(copy.begin(), copy.end(), nickname);
		if (itp != copy.end())
			return true;
		std::string response = "482 " + nickname + " " + channel + " :You're not the channel operator\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
	else
	{
		std::string response = "403 " + nickname + " " + channel + " :No such Channel\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
	return false;
}

void	Server::addChannel(std::string name, std::string proprio)
{
	Channel channel = Channel(name, proprio);
	this->_list_channel.insert(std::pair<std::string, Channel>(name, channel));
	std::map<std::string, Channel>::iterator it;
	for (it = _list_channel.begin(); it != _list_channel.end(); it++)
		std::cout << "(" << it->first << ")\n";
}

void	Server::addUser(int socketfd, std::string name, std::string nickname)
{
	User user = User(socketfd, name, nickname);
	this->_list_user.insert(std::pair<std::string, User>(nickname, user));
	this->_list_socket_user.insert(std::pair<int, User>(socketfd, user));
}

const std::map<std::string, User>	&Server::getListUser() const
{
	return this->_list_user;
}

const std::map<std::string, Channel>	&Server::getListChannel() const
{
	return this->_list_channel;
}

void	Server::changeTopic(std::string channel, std::string topic, int socketfd)
{
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		if (topic == "")
			send(socketfd, ito->second.getTopic().c_str(), ito->second.getTopic().size(), 0);
		else
			ito->second.setTopic(topic);
	}
}

void	Server::changePerm(std::string channel, bool perm, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setAccess(perm);
	}
}

void	Server::changePassword(std::string channel, std::string password, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setPassword(password);
	}
}

void	Server::givePerm(std::string channel, std::string name, bool give, int socketfd)
{
	std::string nickname = whatUser(socketfd);
	if (nickname.empty())
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		std::vector<std::string> list = ito->second.getListChef();
		std::vector<std::string>::iterator itt = find(list.begin(), list.end(), nickname);
		if (itt != list.end())
		{
			if (give)
				ito->second.remote(name);
			else
				ito->second.demote(name);
		}
		else
		{
			std::string response = "482 " + nickname + " " + channel + " :You're not the channel operator\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
}

void Server::changeLimit(std::string channel, int limit, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setLimit(limit);
	}
}

void Server::permTopic(std::string channel, bool perm, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setAccessTopic(perm);
	}
}

void Server::kick(std::string channel, std::string nickname, std::string reason, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::string whoami = whatUser(socketfd);
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	ito->second.kickuser(nickname);
	std::vector<std::string> copy = ito->second.getListUser();
	std::vector<std::string>::iterator ivector;
	std::map<std::string, User>::iterator imap;
	int socketmember;
	std::string message = nickname + " was banned by " + whoami + " (" + reason + ")\n";
	for (ivector = copy.begin(); ivector != copy.end(); ++ivector)
	{
		imap = _list_user.find(*ivector);
		socketmember = imap->second.getSocket();
		send(socketmember, message.c_str(), message.size(), 0);
	}
}

void Server::invite(std::string channel, std::string user, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	std::vector<std::string>::iterator it;
	if (ito != _list_channel.end())
	{
		ito->second.addinvitation(user);
	}
}

void	Server::joinCanal(std::string canal, std::string password, int socketfd)
{
	std::string nickname = whatUser(socketfd);
	std::map<std::string, Channel>::iterator it = _list_channel.find(canal);
	if (it != _list_channel.end())
	{
		bool a = it->second.getAccess();
		if (password.compare(it->second.getPassword()) == 0)
		{
			if (a)
			{	
				std::vector<std::string> copy = it->second.getListInvitation();
				std::vector<std::string>::iterator itp = find(copy.begin(), copy.end(), nickname);
				if (itp != copy.end())
					it->second.adduser(nickname);
				else
				{
					std::string response = "473 " + nickname + " " + canal + " :Cannot join channel (+i)"; 
					send(socketfd, response.c_str(), response.size(), 0);
				}
			}
			else
			{
					it->second.adduser(nickname);
					std::cout << nickname << "add to " << it->first  << "\n";
			}
		}
		else
		{
			std::string response = "475 " + nickname + " " + canal + " :Cannot join channel (+k)\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
	else
	{
		this->addChannel(canal, nickname);
		std::cout << canal << " add\n";
	}
	
}

void Server::sendMessage(std::string destination, std::string content, bool user, int socketfd)
{
	std::string nickname = whatUser(socketfd);
	int socket_destinate;
	if (user)
	{
		std::map<std::string, User>::iterator itt;
		itt = _list_user.find(destination);
		socket_destinate = itt->second.getSocket();
		std::string message = nickname + ": " + content + "\n";
		send(socket_destinate, message.c_str(), message.size(),0);
	}
	else
	{
		std::string operato = "";
		std::vector<std::string>::iterator it;
		std::map<std::string, User>::iterator itp;
		std::map<std::string, Channel>::iterator itt = _list_channel.find(destination);
		if (itt != _list_channel.end())
		{
			std::vector<std::string> copy = itt->second.getListUser();
			it = find(copy.begin(), copy.end(), nickname);
			if (it == copy.end())
			{
				std::string message = "404 " + nickname + " " + destination  + " :Cannot send to channel\n";
				send(socketfd, message.c_str(), message.size(),0);
				return; //gestion erreur;
			}
			std::vector<std::string> copy2 = itt->second.getListChef();
			it = find(copy2.begin(), copy2.end(), nickname);
			if (it != copy2.end())
				operato = "@";
			for (it = copy.begin(); it != copy.end(); ++it)
			{
				if (*it != nickname)
				{
					itp = _list_user.find(*it);
					socket_destinate = itp->second.getSocket();
					std::string message = operato + nickname + ": " + content + "\n";
					send(socket_destinate, message.c_str(), message.size(),0);
				}
			}
		}
		else
		{
			std::string response = "403 " + nickname + " " + destination + " :No such Channel\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
}
