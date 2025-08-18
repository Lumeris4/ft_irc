/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/18 13:43:27 by lelanglo         ###   ########.fr       */
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
	std::string						_servername;
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
	void									addUser(int socketfd, std::string name, std::string nickname);
	void									addChannel(std::string name, std::string proprio, std::string password);
	const std::map<std::string, User>		&getListUser() const;
	const std::map<std::string, Channel>	&getListChannel() const;
	int 									init_server();
	int 									check_password(std::string password);
	int 									parsing (std::string input, int i);
	int 									setNickname(std::string nick, int socket);
	int 									setUser(std::string nick, int socket);
	int 									createUser(int socketfd, int i);
	void									changeTopic(std::string channel, std::string topic, int socketfd);
	void									changePerm(std::string channel, bool perm, int socketfd);
	void									changePassword(std::string channel, std::string password, int socketfd);
	void									givePerm(std::string channel, std::string name, bool give, int socketfd);
	void									changeLimit(std::string channel, std::string limit, int perm, int socketfd);
	void									permTopic(std::string channel, bool perm, int socketfd);
	void									kick(std::string channel, std::string nickname, std::string reason, int socketfd);
	void									invite(std::string channel, std::string user, int socketfd);
	void									joinCanal(std::string channel, std::string password, int socketfd);
	void									sendMessage(std::string destination, std::string content, bool user, int socketfd);
	void									sendToChannel(std::string channel, std::string message);
	std::string								whatUser(int socketfd);
	bool									exist(std::string nickname, int socketfd);
	bool									haveright(int socketfd, std::string channel);
	void 									handle_join(std::string argument, int socketfd);
	void									handle_mode(std::string argument, int socketfd);
	void									handle_topic(std::string argument, int socketfd);
	void									handle_invite(std::string argument, int socketfd);
	void									handle_kick(std::string argument, int socketfd);
	void 									handle_ping( std::string argument, int socketfd);
	void									handle_whois(std::string argument, int socketfd);
	void									handle_privmsg(std::string argument, int socketfd);
};