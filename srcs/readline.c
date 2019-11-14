/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:24:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/14 15:19:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// if (key == 3)
// 	printf("key SIGINT\n");
// if (key == 4)
// 	printf("key SIGTERM\n");
// if (key == 28)
// 	printf("key SIGQUIT\n");
// if (key == 26)
// 	printf("key SIGTSTP\n");

char			*read_commands(t_args **list, int argc)
{
	int			key;
	char		*result;

	result = NULL;
	while (1)
	{
		key = key_hook();
		//ft_putnbr(key);
		if (key == '\033')
			return (NULL);
		if (key == '\n')
		{
			result = generate_selected_line(*list, argc, result);
			return (result);
		}
		if (key == 126)
			if ((*list = delete_element(*list)) == NULL)
				return (NULL);
		if (key == 127)
		{
			if ((*list = backspace_element(*list)) == NULL)
				return (NULL);
		}
		else
			read_commands_and_signals(*list, key);
	}
}

void			read_commands_and_signals(t_args *list, int key)
{
	if (key == 4283163 || key == 4348699 ||
				key == 4414235 || key == 4479771)
		make_movements(list, key);
	(key == 32) ? select_element(list) : 0;
}

int				key_hook(void)
{
	char		buffer[4];

	ft_bzero(buffer, 4);
	read(STDIN_FILENO, buffer, 3);
	//write(STDOUT_FILENO, buffer, 3); //delete
	return (*(unsigned int*)buffer);
}
