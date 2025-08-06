/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/06 13:13:25 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "include.hpp"
#include "Channel.hpp"
#include "User.hpp"

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
	virtual ~Server();
	void	addUser(std::string name, std::string nickname);
};
