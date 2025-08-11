/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:08:11 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 10:15:21 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"
#include "Channel.hpp"

Channel::Channel(std::string name, std::string creator): _name(name), _limit(-1), _access(false), _access_topic(false)
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

void	Channel::remote(std::string nickname)
{
	std::vector<std::string>::iterator it;
	it = find(_list_user.begin(), _list_user.end(), nickname);
	if (it != _list_user.end())
		this->_chef_usernames.push_back(nickname);
}

void	Channel::demote(std::string nickname)
{
	std::vector<std::string>::iterator it;
	it = find(_chef_usernames.begin(), _chef_usernames.end(), nickname);
	if (it != _chef_usernames.end())
		this->_chef_usernames.erase(it);
}

void Channel::adduser(std::string nickname)
{
	this->_list_user.push_back(nickname);
}

void Channel::kickuser(std::string nickname)
{
	std::vector<std::string>::iterator it;
	it = find(_list_user.begin(), _list_user.end(), nickname);
	if(it != _list_user.end())
		this->_list_user.erase(it);
}

void Channel::addinvitation(std::string nickname)
{
	this->_invitate.push_back(nickname);
}

void	Channel::setAccessTopic(bool perm)
{
	this->_access_topic = perm;
}

bool Channel::getAccessTopic() const
{
	return this->_access_topic;
}
