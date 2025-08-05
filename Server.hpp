/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/05 15:30:22 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "include.hpp"
#include "Channel.hpp"

class Server
{
	private:
	std::string _password;
	int _port;
	typedef std::vector<std::string> List;
	List _nickname;
	List _username;
	std::map<std::string, Channel> list_channel;

	public:
	Server(std::string password, int port);
	~Server();
};
