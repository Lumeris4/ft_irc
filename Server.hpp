/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 12:16:11 by bfiquet          ###   ########.fr       */
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

	public:
	Server();
	Server(std::string password, int port);
	~Server();
	void	addUser(std::string name, std::string nickname);
	void	addChannel(std::string name, User &proprio);
	int 	init_server();
};
