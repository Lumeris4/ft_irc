/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:51 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socket): _socket(socket)
{
	capDone = false;
	connected = false;
}
User::User(): _socket(-1)
{
	connected = false;
	capDone = false;
}

User::User(int socketfd, std::string username, std::string nickname):_username(username), _nickname(nickname), _socket(socketfd)
{
	connected = false;
	capDone = false;
}

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

void User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void User::setUsername(std::string username)
{
	this->_username = username;
}

void User::setCap(bool cap)
{
	this->capDone = cap;
}

bool User::getCap()
{
	return this->capDone;
}

void User::setConnected(bool connected)
{
	this->connected = connected;
}

bool User::getConnected()
{
	return this->connected;
}

void User::setLeftover(std::string leftover)
{
	this->_leftover = leftover;
}

std::string	User::getLeftover()
{
	return this->_leftover;
}

int User::getSocket() const
{
	return this->_socket;
}
