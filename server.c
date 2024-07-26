/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoklova <msoklova@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:30:25 by msoklova          #+#    #+#             */
/*   Updated: 2024/07/26 14:16:57 by msoklova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
#include <signal.h>

void	decrypt_sig(int sig)
{
	static unsigned char	byte = 0;
	static int				bit = 0;

	if (sig == SIGUSR1)
		byte = (byte << 1);
	else if (sig == SIGUSR2)
		byte = (byte << 1) | 1;
	bit++;
	if (bit == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		bit = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	if (pid_str != NULL)
	{
		ft_putstr_fd(pid_str, 1);
		ft_putstr_fd("\n", 1);
		free(pid_str);
	}
	signal(SIGUSR1, decrypt_sig);
	signal(SIGUSR2, decrypt_sig);
	while (1)
		pause();
	return (0);
}
