/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 10:03:05 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() {}

User::User(std::string username, std::string nickname): _username(username), _nickname(nickname) {}

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

const std::string User::getSocket() const
{
	return this->_socket;
}