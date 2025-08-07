/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:26:38 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/07 09:46:44 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string password, int port): _password(password), _port(port) {}

Server::~Server() {}

Server::Server(): _port(-1) {}

void	Server::addChannel(std::string name, User &proprio)
{
	Channel channel = Channel(name, proprio.getUsername());
	this->_list_channel.insert(std::pair<std::string, Channel>(name, channel));
}

void	Server::addUser(std::string name, std::string nickname)
{
	User user = User(name, nickname);
	this->_list_user.insert(std::pair<std::string, User>(nickname, user));
}