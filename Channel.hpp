/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:46:43 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/05 14:54:37 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "include.hpp"

class Channel
{
	private:
	std::string					_password;
	std::string					_name;
	int							_limit;
	std::string					_topic;
	bool						_invitation;
	std::vector<std::string>	_chef_usernames;
	std::vector<std::string>	_list_user;
	std::vector<std::string>	_invitate;
};