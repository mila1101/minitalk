/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoklova <msoklova@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:30:20 by msoklova          #+#    #+#             */
/*   Updated: 2024/07/26 18:16:09 by msoklova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
#include <signal.h>

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
			usleep(50);
			i--;
		}
	}
	c = '\0';
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

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_message(argv[2], pid);
	}
	else
	{
		write(1, "\nHow to use: \n", 14);
		write(1, "	./client <PID> <string>\n", 25);
	}
	return (0);
}
