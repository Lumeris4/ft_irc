/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/06 13:06:31 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(): Server() {}

User::User(std::string username, std::string nickname): _username(username), _nickname(nickname) {}

User::~User() {}

void User::addChannel(std::string name)
{
	Channel channel = Channel(name, this->_username);
	this->_list_channel[name] = channel;
}