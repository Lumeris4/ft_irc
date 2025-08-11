/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 14:44:00 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socket): _socket(socket) {}
User::User(): _socket(-1) {}

User::User(int socketfd, std::string username, std::string nickname):_username(username), _nickname(nickname), _socket(socketfd) {}

User::~User() {}

User &User::operator=(User &other)
{
	(void)other;
	return *this;
}

const std::string User::getUsername() const
{
	return this->_username;
}

const std::string User::getNickname() const
{
	return this->_nickname;
}

int User::getSocket() const
{
	return this->_socket;
}