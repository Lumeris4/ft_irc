/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/05 14:45:12 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"

class Server
{
	private:
	std::string _password;
	int _port;
	typedef std::vector<std::string> List;
	List _nickname;
	List _username;

	public:
	Server(std::string password, int port);
	~Server();
};
