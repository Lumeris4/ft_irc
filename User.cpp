/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/09/15 13:42:29 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socket): _socket(socket)
{
	capDone = false;
	first_mode = true;
	connected = false;
	registered = false;
}
User::User(): _socket(-1)
{
	connected = false;
	capDone = false;
	first_mode = true;
	registered = false;
}

User::User(int socketfd, std::string hostname, std::string username, std::string nickname):_username(username), _nickname(nickname), _hostname(hostname), _socket(socketfd)
{
	connected = false;
	capDone = false;
	first_mode = true;
	registered = false;
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

const std::string	User::getHostname() const
{
	return this->_hostname;
}

void User::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}

void User::setCap(bool cap)
{
	this->capDone = cap;
}

bool User::getCap()
{
	return this->capDone;
}

void User::setRegistered(bool cap)
{
	this->registered = cap;
}

bool User::getRegistered()
{
	return this->registered;
}

void User::setConnected(bool connected)
{
	this->connected = connected;
}

bool User::getConnected()
{
	return this->connected;
}

void User::setFirstmode(bool first)
{
	this->first_mode = first;
}

bool User::getFirstmode()
{
	return this->first_mode;
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
