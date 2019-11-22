/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:24:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/20 15:04:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char			*read_commands(t_args **dirs, int *level, int *flag)
{
	int			key;
	char		*result;

	result = NULL;
	while (1)
	{
		if (*flag != 1)
		{
			bell_sound();
			continue;
		}
		key = key_hook();
		//ft_putnbr(key);
		if (key == '\033')
			return (NULL);
		if (key == '\n')
		{
			result = generate_selected_line(dirs[*level], result);
			return (result);
		}
		else
		{
			if (read_commands_and_signals(dirs, level, key, flag) == NULL)
				return (NULL);
		}
	}
}

char			*read_commands_and_signals(t_args **dirs, int *level, int key, int *flag)
{
	t_args		*under;
	
	under = dirs[*level];
	if (*flag != 1)
		return ("wait");
	if (key == 4283163 || key == 4348699 ||
			key == 4414235 || key == 4479771)
		make_movements(dirs[*level], key);
	(key == 32) ? select_element(dirs[*level]) : 0;
	
	if (key == 9)
		make_tab_new_directory(dirs, level, flag);
	if (key == 'q')
		make_back_parent_directory(dirs, level, flag);
	if (key == 126)
	{
		if (*level > 0 && (dirs[*level] = delete_element(dirs[*level])) == NULL)
			(*level)--;
		if (*level == 0 && (dirs[0] = delete_element(dirs[0])) == NULL)
			return (NULL);
	}
	if (key == 127)
	{
		if (*level > 0 && (dirs[*level] = backspace_element(dirs[*level])) == NULL)
			(*level)--;
		if (*level == 0 && (dirs[0] = backspace_element(dirs[0])) == NULL)
			return (NULL);
	}
	return ("ok");
}

int				key_hook(void)
{
	char		buffer[4];

	ft_bzero(buffer, 4);
	read(STDIN_FILENO, buffer, 3);
	return (*(unsigned int*)buffer);
}
