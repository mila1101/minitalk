/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoklova <msoklova@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:30:20 by msoklova          #+#    #+#             */
/*   Updated: 2024/07/27 16:27:32 by msoklova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
#include <signal.h>

void	end_message(pid_t pid)
{
	unsigned char	c;
	int				i;

	c = '\0';
	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		i--;
	}
}

void	send_message(char *str, pid_t pid)
{
	unsigned char	c;
	int				i;

	while (*str)
	{
		c = (unsigned char)*str;
		str++;
		i = 7;
		while (i >= 0)
		{
			if (((c >> i) & 1) == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			i--;
		}
	}
	end_message(pid);
}

int	pid_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc == 3 && pid_checker(argv[1]))
	{
		pid = ft_atoi(argv[1]);
		send_message(argv[2], pid);
	}
	else
	{
		if (pid_checker(argv[1]) == 0)
			write(1, "WRONG PID, DIGITS ONLY!!!", 25);
		write(1, "\nHow to use: \n", 14);
		write(1, "	./client <PID> <string>\n", 25);
	}
	return (0);
}
