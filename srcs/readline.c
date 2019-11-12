/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:24:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 20:40:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h" 

char			*read_commands(t_args *list)
{
	int			key;
	
	while (1)
	{
		key = key_hook();
		// ft_putnbr(key);
		if (key == '\033')
			return (NULL);
		if (key == 4283163 || key == 4348699 ||
				key == 4414235 || key == 4479771)
			make_movements(list, key);
		if (key == 32)
			select_element(list); //make unspace till the end
		
	}
}

int				key_hook(void)
{
	char		buffer[4];

	ft_bzero(buffer, 4);
	read(STDIN_FILENO, buffer, 3);
	//write(STDOUT_FILENO, buffer, 3); //delete
	return (*(unsigned int*)buffer);
}
