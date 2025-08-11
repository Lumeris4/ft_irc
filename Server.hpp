/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/11 10:52:57 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"
#include "Channel.hpp"
#include "User.hpp"

class Server;
class User;

class Server
{
	protected:
	std::string						_password;
	int								_port;
	std::map<std::string ,User>		_list_user;
	std::map<std::string, Channel>	_list_channel;
	std::string						_argument;
	bool							_hasNickname;
	bool							_hasUser;

	public:
	Server();
	Server(std::string password, int port);
	~Server();
	void	addUser(std::string name, std::string nickname);
	void	addChannel(std::string name, User &proprio);
	const std::map<std::string, User>		&getListUser() const;
	const std::map<std::string, Channel>	&getListChannel() const;
	int 	init_server();
	int check_password(std::string password);
	int parsing (std::string input);
	int setNickname(std::string nick);
	int setUser();
	int createUser();
};