/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:26:38 by lelanglo          #+#    #+#             */
/*   Updated: 2025/09/15 21:19:46 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

bool is_registered[MAX_CLIENTS];

int Server::createUser(int socketfd, int i, User &user)
{
	if (is_registered[i])
		return (0);
	addUser(socketfd, user.getHostname(), user.getUsername(), user.getNickname());
	is_registered[i] = true;
	return (0);
}

int stop = 0;

void handler(int sig)
{
	(void) sig;
	std::cout << "\nClosing server" << std::endl;
    stop = 1;
}

int Server::init_server()
{
	int servsocket;
	int new_socket;
	char buffer[1024];
	std::string input;
	int j = -1;
	_servername = "ircserv";
	servsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servsocket < 0)
        return (-1);
	struct sockaddr_in serv_addr, cli_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // toutes les interfaces locales	
	serv_addr.sin_port = htons(this->_port);          // port	
	if (bind(servsocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	{
	    std::cout << "Adress already in use" << std::endl;
		return (-1);
	}
	if (listen(servsocket, MAX_CLIENTS) < 0)
	{
       	close(servsocket);
       	return (-1);
    }	
	struct pollfd fds[1 + MAX_CLIENTS];
	int nfds = 1;
    fds[0].fd = servsocket;
    fds[0].events = POLLIN;
	fds[0].revents = 0;
	while (1 && !stop)
	{
		signal(SIGINT, handler);
		int ret = poll(fds, nfds, -1);
    	if (ret == -1)
			return (-1);
    	else
		{
        	if (fds[0].revents & POLLIN)
			{
				socklen_t clilen = sizeof(cli_addr);
				new_socket = accept(servsocket, (struct sockaddr *)&cli_addr, &clilen);
				if (new_socket < 0)
				{
    			   	close(servsocket);
    			   	return (-1);
				}
				if (nfds - 1 < MAX_CLIENTS)
				{
            	    fds[nfds].fd = new_socket;
            	    fds[nfds].events = POLLIN;
					fds[nfds].revents = 0;
            	    nfds++;
					_list_socket_user.insert(std::make_pair(new_socket, User(new_socket)));
					std::string message = "You are now connected to server.\n";
					send(new_socket, message.c_str(), message.length(), 0);
					std::cout << "client connected to server" << std::endl;
            	} 
				else
				{
					std::string message = "Too many clients connected.\n";
					send(new_socket, message.c_str(), message.length(), 0);
                	close(new_socket);
            	}
			}
			for (int i = 1; i < nfds; i++)
			{
				if (fds[i].revents & POLLIN)
				{
    		     	ssize_t n = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
					User &user = _list_socket_user[fds[i].fd];
    				if (n > 0)
					{	
    		 			buffer[n] = '\0';
						input = user.getLeftover() + buffer;
						user.setLeftover("");
						std::stringstream ss(input);
						std::string cmd;
						while (std::getline(ss, cmd, '\n'))
						{
							if (ss.eof() && !input.empty() && input[input.length() - 1] != '\n')
   							{
	       						user.setLeftover(cmd);
     						    break;
    						}
							_argument= "";
    		 				j = parsing(cmd, user);
							if (!is_registered[i] && (j > 2 && j < 9))
								j = 20;
							switch (j)
							{
								case 0:
								{
									handle_cap(_argument, user, fds[i].fd);
									break;
								}		
								case 1:
								{
									setNickname(_argument, fds[i].fd, user);
									break;
								}
								case 2:
								{
									setUser(_argument, fds[i].fd, user);
									break;
								}
								case 3:
								{
									if (user.getFirstmode() != true)
										handle_mode(_argument, fds[i].fd, user);
									if (user.getFirstmode() == true)
										user.setFirstmode(false);
									break;
								}
								case 4:
								{
									handle_topic(_argument, fds[i].fd, user);
									break;
								}
								case 5:
								{
									handle_invite(_argument, fds[i].fd, user);
									break;
								}
								case 6:
								{
									handle_kick(_argument, fds[i].fd, user);
									break;
								}
								case 7:
								{
									handle_join(_argument, fds[i].fd, user);
									break;
								}
								case 8:
								{
									handle_privmsg(_argument, fds[i].fd, user);
									break;
								}
								case 9:
								{
									handle_ping(_argument, fds[i].fd);
									break;
								}
								case 10: 
								{
									handle_whois(_argument, fds[i].fd, user);
									break;
								}
								case 11:
								{
									std::cout << "Client disconnected." << std::endl;
									deleteUser(fds[i].fd);
									is_registered[i] = false;
									user.setLeftover("");
									user.setNickname("");
									user.setUsername("");
									user.setConnected(false);
									user.setFirstmode(true);
									user.setCap(false);
									close(fds[i].fd);
									i--;
									break;
								}
								case 20:
								{
									std::string message = "Cannot execute command if client is not a user.\n";
									send(fds[i].fd, message.c_str(), message.length(), 0);
								}
								default:
									break;
							}
							j = -1;
							if (!user.getNickname().empty() && !user.getUsername().empty() && !is_registered[i])
								createUser(fds[i].fd, i, user);
							if (user.getCap() && (!user.getNickname().empty() && !user.getUsername().empty() && !is_registered[i]))
							{
								std::string servername = "ircserv";
								std::string message = ":" + servername + " 001 " + user.getNickname() + " :Welcome to the IRC Network " + user.getNickname() + "!* @lelanglo&@bfiquet\r\n";
								send(fds[i].fd, message.c_str(), message.length(), 0);
								break;
							}
						}
					}
					else
					{
						deleteUser(fds[i].fd);
						close(fds[i].fd);
						is_registered[i] = false;
						user.setLeftover("");
						user.setNickname("");
						user.setUsername("");
						user.setConnected(false);
						user.setFirstmode(true);
						user.setCap(false);
						_list_socket_user.erase(fds[i].fd);
						nfds--;
						fds[i] = fds[nfds];
						i--;
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

Server::Server(std::string password, int port): _password(password), _port(port) {}

Server::~Server() {}

Server::Server(): _port(-1) {}

std::string Server::whatUser(int socketfd)
{
	std::string nickname;
	std::map<int, User>::iterator it;
	for (it = _list_socket_user.begin(); it != _list_socket_user.end(); it++)
	{
		if (it->first == socketfd)
			nickname = it->second.getNickname();
	}
	if (nickname.empty())
		return "";
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
		std::string response = ":" + _servername + " 482 " + nickname + channel + " :You're not the channel operator\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
	else
	{
		std::string response = ":" + _servername + " 403 " + nickname + " " + channel + " :No such Channel\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
	return false;
}

bool Server::IntheChannel(std::string channel, std::string user, int socketfd)
{
	std::string me = whatUser(socketfd);
	std::map<std::string, Channel>::iterator it = _list_channel.find(channel);
	if (it == _list_channel.end())
	{
		std::string response = ":" + _servername +  " 403 " + me + channel + " :No such Channel\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
		return false;
	}
	std::vector<std::string> copy = it->second.getListUser();
	std::vector<std::string>::iterator itv = find(copy.begin(), copy.end(), user);
	if (itv == copy.end())
	{
		std::string response = ":" + _servername + " 441 " + me + " " + user + " " + channel + " :They aren't on that channel\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
		return false;
	}
	return true;
}

void Server::deleteUser(int socket)
{
	std::string user = whatUser(socket);
	if (user.empty())
		return;
	std::vector<std::string> channels_to_kick;
	for (std::map<std::string, Channel>::iterator itp = _list_channel.begin(); itp != _list_channel.end(); ++itp)
	{
		std::vector<std::string> copy = itp->second.getListInvitation();
		std::vector<std::string>::iterator iv = find(copy.begin(), copy.end(), user);
		if (iv != copy.end())
			itp->second.baninvitation(user);
		copy = itp->second.getListUser();
		iv = find(copy.begin(), copy.end(), user);
		if (iv != copy.end())
			channels_to_kick.push_back(itp->first);
	}
	for (std::vector<std::string>::iterator it = channels_to_kick.begin(); it != channels_to_kick.end(); ++it)
		kick(*it, user, "", socket);
	std::map<std::string, User>::iterator it = _list_user.find(user);
	if (it != _list_user.end())
		_list_user.erase(it);
}

void Server::sendToChannel(std::string channel, std::string message)
{
	std::map<std::string, Channel>::iterator it = _list_channel.find(channel);
	if (it == _list_channel.end())
		return;
	std::vector<std::string> users = it->second.getListUser();
	std::vector<std::string>::iterator itp;
	for (itp = users.begin(); itp != users.end(); ++itp)
	{
		std::map<std::string, User>::iterator itt = _list_user.find(*itp);
		if (itt == _list_user.end())
			continue;
		int socket_destinate = itt->second.getSocket();
		send(socket_destinate, message.c_str(), message.size(), 0);
	}
}


bool	Server::exist(std::string nickname, int socketfd)
{
	std::string whoami = whatUser(socketfd);
	std::map<std::string, User>::iterator it = _list_user.find(nickname);
	if (it != _list_user.end())
		return true;
	std::string message = ":" + _servername + " 401 " + whoami + " " + nickname + " :No such Nick/Channel\r\n";
	send(socketfd, message.c_str(), message.size(), 0);
	return false;
}

void	Server::addChannel(std::string name, std::string proprio, std::string password)
{
	Channel channel = Channel(name, proprio);
	channel.setPassword(password);
	this->_list_channel.insert(std::pair<std::string, Channel>(name, channel));
}

void	Server::addUser(int socketfd, std::string hostname, std::string name, std::string nickname)
{
	User user = User(socketfd, hostname,  name, nickname);
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
	std::string user = whatUser(socketfd);
	std::vector<std::string>::iterator it;
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		std::vector<std::string> copy2 = ito->second.getListUser();
		it = find(copy2.begin(), copy2.end(), user);
		if (it == copy2.end())
		{
			std::string message = ":" + _servername + " 442 " + user + " " +  channel + " :You're not on that channel\r\n";
			send(socketfd, message.c_str(), message.size(), 0);
				return;
		}
		if (topic == "")
		{
			send(socketfd, ito->second.getTopic().c_str(), ito->second.getTopic().size(), 0);
			return;
		}
		std::vector<std::string> copy = ito->second.getListChef();
		it = find(copy.begin(), copy.end(), user);
		if (it != copy.end() && ito->second.getAccessTopic() == true)
		{
			std::string message = ":" + user + "!user@host TOPIC " + channel + " :" + topic + "\r\n";
			ito->second.setTopic(topic);
			for (it = copy2.begin(); it != copy2.end(); it++)
			{
				std::map<std::string, User>::iterator itp = _list_user.find(*it);
				send(itp->second.getSocket(), message.c_str(), message.size(), 0);
			}
		}
		else if (ito->second.getAccessTopic() == false)
		{
			std::string message = ":" + user + "!user@host TOPIC " + channel + " :" + topic + "\r\n";
			ito->second.setTopic(topic);
			for (it = copy2.begin(); it != copy2.end(); it++)
			{
				std::map<std::string, User>::iterator itp = _list_user.find(*it);
				send(itp->second.getSocket(), message.c_str(), message.size(), 0);
			}
		}
		else
		{
			std::string response = ":" + _servername  + " 482 " + user + channel + " :You're not the channel operator\r\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
	else
	{
		std::string response = ":" + _servername + " 403 " + user + channel + " :No such Channel\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
}

void	Server::changePerm(std::string channel, bool perm, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::string whoami = whatUser(socketfd);
	std::string mode;
	if (perm)
		mode = "+i";
	else
		mode = "-i";
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		std::string message =  ":" + whoami + "!ident@host MODE " + channel + " " + mode + "\r\n";
		ito->second.setAccess(perm);
		sendToChannel(channel, message);
	}
}

void	Server::changePassword(std::string channel, std::string password, bool perm, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::string nickname = whatUser(socketfd);
	std::string mode;
	if (perm)
		mode = "+k";
	else
		mode = "-k";
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		ito->second.setPassword(password);
		std::string message = ":" + nickname + "!ident@host MODE " + channel + " " + mode + " " + password + "\r\n";
		sendToChannel(channel, message);
	}
}

void	Server::givePerm(std::string channel, std::string name, bool give, int socketfd)
{
	std::string nickname = whatUser(socketfd);
	std::string mode;
	if (give)
		mode = "+o";
	else
		mode = "-o";
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		std::vector<std::string> list = ito->second.getListChef();
		std::vector<std::string>::iterator itt = find(list.begin(), list.end(), nickname);
		if (itt != list.end())
		{
			if (!exist(name, socketfd) || !IntheChannel(channel, name, socketfd))
				return;
			std::string message =  ":" + nickname + "!ident@host MODE " + channel + " " + mode + " " + name + "\r\n";
			itt = find(list.begin(), list.end(), name);
			if (give)
			{
				if (itt != list.end())
					return;
				ito->second.remote(name);
			}
			else
			{
				if (itt == list.end())
					return;
				ito->second.demote(name);
			}
			sendToChannel(channel, message);
		}
		else
		{
			std::string response = ":" + _servername +  " 482 " + nickname + channel + " :You're not the channel operator\r\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
}

void Server::changeLimit(std::string channel, std::string limit, int perm ,int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	int new_limit = atoi(limit.c_str());
	std::string whoami = whatUser(socketfd);
	std::string mode;
	if (perm)
		mode = "+l";
	else
		mode = "-l";
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		int clients = ito->second.getMembers();
		if (perm == false && clients == MAX_CLIENT)
			return;
		if (ito->second.getMembers() <= new_limit || limit.empty())
		{
			std::string message =  ":" + whoami + "!ident@host MODE " + channel + " " + mode + " " + limit + "\r\n";
			if (perm)
				ito->second.setLimit(new_limit);
			else
				ito->second.setLimit(MAX_CLIENTS);
			sendToChannel(channel, message);
		}
		else
		{
			std::string response = ":" + _servername +  " 471 " + whoami + channel + " :Cannot set channel limit\r\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
}

void Server::permTopic(std::string channel, bool perm, int socketfd)
{
	if (!haveright(socketfd, channel))
		return;
	std::string whoami = whatUser(socketfd);
	std::string mode;
	if (perm)
		mode = "+t";
	else
		mode = "-t";
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		bool perm_topic = ito->second.getAccessTopic();
		if (perm_topic == perm)
			return;
		std::string message =  ":" + whoami + "!ident@host MODE " + channel + " " + mode + "\r\n";
		ito->second.setAccessTopic(perm);
		sendToChannel(channel, message);
	}
}

void Server::kick(std::string channel, std::string nickname, std::string reason, int socketfd)
{
	if (!haveright(socketfd, channel) || !exist(nickname, socketfd) || !IntheChannel(channel, nickname, socketfd))
		return;
	std::string whoami = whatUser(socketfd);
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	std::vector<std::string> copy = ito->second.getListUser();
	std::vector<std::string>::iterator ivector;
	std::map<std::string, User>::iterator imap;
	int socketmember;
	std::string message = ":" + whoami + "!user@host KICK " + channel + " " + nickname + " :" + reason + "\r\n";
	for (ivector = copy.begin(); ivector != copy.end(); ++ivector)
	{
		imap = _list_user.find(*ivector);
		socketmember = imap->second.getSocket();
		send(socketmember, message.c_str(), message.size(), 0);
	}
	ito->second.kickuser(nickname);
	int members = ito->second.getMembers();
	if (members == 0)
	{
		ito->second.setTopic("");
		_list_channel.erase(ito);
	}
}

void Server::invite(std::string channel, std::string user, int socketfd)
{
	if (!exist(user, socketfd))
		return;
	std::string whoami = whatUser(socketfd);
	std::map<std::string, Channel>::iterator ito = this->_list_channel.find(channel);
	if (ito != _list_channel.end())
	{
		std::vector<std::string> copy = ito->second.getListUser();
		std::vector<std::string>::iterator ity = find(copy.begin(), copy.end(), user);
		if (ity != copy.end())
			return; 
		if (ito->second.getAccess() == true && !haveright(socketfd, channel))
			return;
		std::map<std::string, User>::iterator itp = this->_list_user.find(user);
		std::string message = ":" + whoami + "!ident@host INVITE " + user + " :" + channel + "\r\n";
		ito->second.addinvitation(user);
		send(itp->second.getSocket(), message.c_str(), message.size(), 0);
	}
	else
	{
		std::string response = ":" + _servername +  " 403 " + whoami + " " + channel + " :No such Channel\r\n";
		send(socketfd, response.c_str(), response.size(), 0);
	}
}

std::string getNamesList(const Channel &channel) {
    std::string names;
    bool first = true;
	std::vector<std::string> chefs = channel.getListChef();
	for (size_t i = 0; i < chefs.size(); ++i)
	{	
    	if (!first) names += " ";
    	names += "@" + chefs[i];
    	first = false;
	}
	std::vector<std::string> users = channel.getListUser();
	for (size_t i = 0; i < users.size(); ++i)
	{
		if (!first) names += " ";
		names += users[i];
	    first = false;
	}
    return names;
}

void	Server::joinCanal(std::string canal, std::string password, int socketfd)
{
	std::string message;
	std::string nickname = whatUser(socketfd);
	std::map<std::string, Channel>::iterator it = _list_channel.find(canal);
	if (it != _list_channel.end())
	{
		bool a = it->second.getAccess();
		if (password.compare(it->second.getPassword()) == 0)
		{
			if (it->second.getLimit() == it->second.getMembers())
			{
				std::string message = ":" + _servername +  " 471 " + nickname + " " + canal + " :Cannot join channel (+l)\r\n";
				send(socketfd, message.c_str(), message.size(), 0);
				return;
			}
			if (a)
			{	
				std::vector<std::string> copy = it->second.getListInvitation();
				std::vector<std::string>::iterator itp = find(copy.begin(), copy.end(), nickname);
				if (itp != copy.end())
				{
					message = ":" + nickname + "!ident@host JOIN :" + canal + "\r\n";
					sendToChannel(canal, message);
					it->second.adduser(nickname);
					std::string topic = it->second.getTopic();
					if (topic.empty())
    					message = ":" + _servername + " 331 " + canal + " :No topic is set\r\n";
					else
    					message = ":" + _servername + " 332 " + nickname + " " + canal + " :" + topic + "\r\n";
					send(socketfd, message.c_str(), message.size(), 0);
					std::string names = getNamesList(it->second);
					message = + ":" + _servername + " 353 " + nickname + " = " + canal + " :"  + names + "\r\n";
					message = message + ":" + _servername + " 366 " + nickname + " " + canal + " :End of /NAMES list\r\n";
					send(socketfd, message.c_str(), message.length(), 0);
					
				}
				else
				{
					std::string response = ":" + _servername +  " 473 " + nickname + " " + canal + " :Cannot join channel (+i)\r\n"; 
					send(socketfd, response.c_str(), response.size(), 0);
				}
			}
			else
			{
					message = ":" + nickname + "!ident@host JOIN :" + canal + "\r\n";
					sendToChannel(canal, message);
					std::string topic = it->second.getTopic();
					if (topic.empty())
    					message = ":" + _servername + " 331 " + canal + " :No topic is set\r\n";
					else
    					message = ":" + _servername + " 332 " + nickname + " " + canal + " :" + topic + "\r\n";
					send(socketfd, message.c_str(), message.size(), 0);
					std::string names = getNamesList(it->second);
					message = ":" + _servername + " 353 " + nickname + " = " + canal + " :"  + names + "\r\n";
					message = message + ":" + _servername + " 366 " + nickname + " " + canal + " :End of /NAMES list\r\n";
					send(socketfd, message.c_str(), message.length(), 0);
					it->second.adduser(nickname);
			}
		}
		else
		{
			std::string response = ":" + _servername +  " 475 " + nickname + " " + canal + " :Cannot join channel (+k)\r\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
	else
	{
		this->addChannel(canal, nickname, password);
		it = _list_channel.find(canal);
		std::string topic = it->second.getTopic();
		if (topic.empty())
    		message = ":" + _servername + " 331 " + canal + " :No topic is set\r\n";
		else
    		message = ":" + _servername + " 332 " + nickname + " " + canal + " :" + topic + "\r\n";
		send(socketfd, message.c_str(), message.size(), 0);
		message = ":" + _servername + " 353 " + nickname + " = " + canal + " :@" + nickname + "\r\n";
		message = message + ":" + _servername + " 366 " + nickname + " " + canal + " :End of /NAMES list\r\n";
		message += ":" + nickname + "!ident@host MODE " + canal + " +t\r\n";
		message += ":" + nickname + "!ident@host MODE " + canal + " +o\r\n";
		send(socketfd, message.c_str(), message.length(), 0);
	}
}

void Server::sendMessage(std::string destination, std::string content, bool user, int socketfd)
{
	std::string nickname = whatUser(socketfd);
	int socket_destinate;
	if (!user)
	{
		if (!exist(destination, socketfd))
			return;
		std::map<std::string, User>::iterator itt;
		itt = _list_user.find(destination);
		socket_destinate = itt->second.getSocket();
		std::string message = ":" + nickname + "!ident@host PRIVMSG " + destination + " :" + content + "\r\n";
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
				std::string message = "404 " + nickname + " " + destination  + " :Cannot send to channel\r\n";
				send(socketfd, message.c_str(), message.size(),0);
				return;
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
					if (itp == _list_user.end())
						return;
					socket_destinate = itp->second.getSocket();
					std::string message = ":" + operato + nickname + "!ident@host PRIVMSG " + destination + " :" + content + "\r\n";
					send(socket_destinate, message.c_str(), message.size(),0);
				}
			}
		}
		else
		{
			std::string response = ":" + _servername +  " 403 " + nickname + destination + " :No such Channel\r\n";
			send(socketfd, response.c_str(), response.size(), 0);
		}
	}
}

