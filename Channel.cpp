/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:08:11 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/06 13:04:19 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"
#include "Channel.hpp"

Channel::Channel(std::string name, std::string creator): _name(name), _access(false), _limit(-1)
{
	this->_chef_usernames.push_back(creator);
	this->_list_user.push_back(creator);
}

Channel::~Channel() {};

void	Channel::setPassword(std::string password)
{
	this->_password = password;
}

const std::string Channel::getPassword() const
{
	return this->_password;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

const std::string Channel::getTopic() const
{
	return this->_topic;
}

void	Channel::setLimit(int limit)
{
	this->_limit = limit;
}

int Channel::getLimit() const
{
	return this->_limit;
}

void	Channel::setAccess(bool n)
{
	this->_access = n;
}

bool Channel::getAccess() const
{
	return this->_access;
}

const std::vector<std::string> &Channel::getListUser() const
{
	return this->_list_user;
}

const std::vector<std::string> &Channel::getListChef() const
{
	return this->_chef_usernames;
}

const std::vector<std::string> &Channel::getListInvitation() const
{
	return this->_invitate;
}

void	Channel::remote(std::string name)
{
	this->_chef_usernames.push_back(name);
}

void	Channel::demote(std::string name)
{
	std::vector<std::string>::iterator it;
	it = find(_chef_usernames.begin(), _chef_usernames.end(), name);
	if (it != _chef_usernames.end())
		this->_chef_usernames.erase(it);
}

void Channel::adduser(std::string name)
{
	this->_list_user.push_back(name);
}

void Channel::addinvitation(std::string name)
{
	this->_invitate.push_back(name);
}