/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:33:16 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/07 09:28:26 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class User;

class User
{
	private:
		std::string _username;
		std::string _nickname;
	
	public:
		User();
		User(std::string username, std::string nickname);
		~User();
		const std::string getUsername() const;
		const std::string getNickname() const; // lui est prioritaire on uttilise jamais l'username
};