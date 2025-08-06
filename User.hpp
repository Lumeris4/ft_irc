/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:33:16 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/06 13:43:20 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"
#include "Channel.hpp"

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
		void	addChannel(std::string name);
};