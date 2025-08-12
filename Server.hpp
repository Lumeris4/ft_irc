/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/12 12:43:44 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"
#include "Channel.hpp"
#include "User.hpp"

#define MAX_CLIENTS 10

class Server;
class User;

class Server
{
	protected:
	std::string						_password;
	int								_port;
	std::map<int, User>				_list_socket_user;
	std::map<std::string ,User>		_list_user;
	std::map<std::string, Channel>	_list_channel;
	std::string						_argument;
	std::string						_nickname;
	std::string						_user;

	public:
	Server();
	Server(std::string password, int port);
	~Server();
	void	addUser(int socketfd, std::string name, std::string nickname);
	void	addChannel(std::string name, std::string proprio);
	const std::map<std::string, User>		&getListUser() const;
	const std::map<std::string, Channel>	&getListChannel() const;
	int 	init_server();
	int 	check_password(std::string password);
	int 	parsing (std::string input, int i);
	int 	setNickname(std::string nick);
	int 	setUser(std::string nick);
	int 	createUser(int socketfd, int i);
	void	changeTopic(std::string channel, std::string topic);
	void	changePerm(std::string channel, bool perm, int socketfd);
	void	changePassword(std::string channel, std::string password, int socketfd);
	void	givePerm(std::string channel, std::string name, bool give, int socketfd);
	void	changeLimit(std::string channel, int limit, int socketfd);
	void	permTopic(std::string channel, bool perm, int socketfd);
	void	kick(std::string channel, std::string nickname, int socketfd);
	void	invite(std::string channel, std::string user, int socketfd);
	void	joinCanal(std::string channel, std::string password, int socketfd);
	void	sendMessage(std::string destination, std::string content, int socketfd);
	std::string	whatUser(int socketfd);
	bool		haveright(int socketfd, std::string channel);
};

void handle_mode(std::string argument);
void handle_topic(std::string argument);