/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/06 11:26:52 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "include.hpp"
#include "Channel.hpp"
#include "User.hpp"

class Server
{
	private:
	std::string _password;
	int _port;
	std::map<std::string ,User> list_user;
	std::map<std::string, Channel> list_channel;

	public:
	Server(std::string password, int port);
	~Server();
	void	addChannel(std::string name);
	void	deleteChannel(std::string name);
	void	addUser(std::string name, std::string nickname);
};
