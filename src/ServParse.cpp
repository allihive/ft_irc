/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServParse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:32:10 by alli              #+#    #+#             */
/*   Updated: 2025/02/13 11:11:39 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serv.hpp"

int Serv::parse_command(int fd, const std::string& line) {
	// std::cout << line << std::endl;
	std::istringstream lss(line);
	std::vector<std::string> tokens;
	
	std::string token;
	std::string cmd;
	
	if (lss)
	{
		lss >> cmd;
	}
	while (lss >> token)
	{
		tokens.push_back(token);
	}
	if (cmd == "QUIT")
	{
		std::cout << "Thank you for using irSEE" << std::endl;
		close (fd);
		//exit(0); //close fds and exit function
	}
	// if (tokens.empty())
	// {
	// 	std::cerr << "Please add another parameter" << std::endl;
	// 	return 1;
	// }
	if (cmd == "CAP")
	{
		std::string cap = tokens[0] + "\r\n";
		return 0;
	}
	else if (cmd == "PASS")
	{
		if (authenticate_password(fd, tokens) == true)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if (cmd == "NICK")
	{
		if (token.empty())
		{
 			std::cerr << "No nick given" << std::endl;
			sendError(fd, "ERR_NONICKNAMEGIVEN : No nick given",  431);
        	return 1;
		}
		if (tokens.size() > 1)
		{
			std::string error_nick = std::string("please only input 1 nickname ") + "\r\n";
			send(fd, error_nick.c_str(), error_nick.size(), 0);
    	}
		else if (addNickname(fd, tokens[0]) == true)
		{
			// std::cout << "nick added" << std::endl;
			return 0;
		}
		else
		{
        std::cerr << "Nick in use" << std::endl;
		sendError(fd, "ERR_NICKNAMEINUSE : Nick name in use",  433);
        	return 1;
		}
	}
	else if (cmd == "USER")
	{
		if (addUser(fd, tokens) == true)
		{
			std::string user = "Username " + tokens[0] + " added \r\n";
			send(fd, user.c_str(), user.size(), 0);
		}
		else
		{
			std::string error_username = "No username added \r\n";
			send(fd, error_username.c_str(), error_username.size(), 0);
			return 1;
		}
	}
	if (cmd == "PING")
	{
		std::string pong = std::string("PONG") + "\r\n";
		send(fd, pong.c_str(), pong.size(), 0);
	}

	if (cmd == "PRIVMSG")
	{
		std::cout << "entered privmsg" << std::endl;
		if (tokens.size() < 2)
		{
			std::string notEnoughParams = "Not enough parameters: <user> <msg> \r\n";
			send(fd, notEnoughParams.c_str(), notEnoughParams.size(), 0);
		}
		else if (message(fd, tokens) == true)
		{
			return 0;
		}
	}
	// if (cmd == "JOIN")
	if (cmd == "JOIN")
	{
		if (cmdJOIN(fd, tokens) == 1)
			return 1;
	}
	if (cmd == "TOPIC")
	{
		if (cmdTOPIC(fd, tokens) == 1)
			return 1;
	}
	if (cmd == "MODE")
	{
		// std::cout << "entered mode " << std::endl;
		if (cmdMODE(fd, tokens) == 1)
		{
			return 1;
		}
	}
	if (cmd == "KICK")
	{
		if (cmdKICK(fd, tokens) == 1)
		{
			return 1;
		}
	}
	if (cmd == "INVITE")
	{
		if (cmdINVITE(fd, tokens) == 1)
			return 1;
	}
	if (cmd == "PART")
	{
		if (cmdPART(fd, tokens) == 1)
			return(1);
	}
	return 0;
}
