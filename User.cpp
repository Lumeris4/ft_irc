/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:13 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/07 09:27:26 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() {}

User::User(std::string username, std::string nickname): _username(username), _nickname(nickname) {}

User::~User() {}

const std::string User::getUsername() const
{
	return this->_username;
}

const std::string User::getNickname() const
{
	return this->_nickname;
}