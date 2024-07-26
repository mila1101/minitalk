/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoklova <msoklova@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:30:25 by msoklova          #+#    #+#             */
/*   Updated: 2024/07/26 18:11:51 by msoklova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
#include <signal.h>

void	decrypt_sig(int sig)
{
	static unsigned char	byte = 0;
	static int				bit = 0;
	static char				*msg = NULL;
	static int				i = 0;
	static int				msg_len = 0;
	static int				buff = 1000;
	char					*new_msg;

	if (msg == NULL)
	{
		msg = (char *)malloc(buff);
		if (msg == NULL)
			return ;
		msg[0] = '\0';
	}
	if (sig == SIGUSR1)
		byte = (byte << 1);
	else if (sig == SIGUSR2)
		byte = (byte << 1) | 1;
	bit++;
	if (bit == 8)
	{
		if (i > buff - 1)
		{
			buff *= 2;
			new_msg = (char *)malloc(buff);
			if (new_msg == NULL)
				return ;
			ft_memcpy(new_msg, msg, i);
			free(msg);
			msg = new_msg;
		}
		if (byte == '\0')
		{
			write(1, msg, i);
			write(1, "\n", 1);
			free(msg);
			msg = NULL;
			i = 0;
			msg_len = 0;
			buff = 1000;
		}
		else
		{
			msg[i++] = byte;
			msg[i] = '\0';
		}
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
