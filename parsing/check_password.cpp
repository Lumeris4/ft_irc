/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_password.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:11:00 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 09:43:40 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

int check_password(std::string password, std::string real_password)
{
	if (password.compare(real_password) != 0)
		return (-1);
	std::cout << "Client has entered password. Accessing server" << std::endl;
	return (0);
}