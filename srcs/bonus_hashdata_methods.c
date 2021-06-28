/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hashdata_methods.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 23:20:33 by a18979859         #+#    #+#             */
/*   Updated: 2021/06/23 23:39:11 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			*init_hashdata()
{
	t_celldata	*dir_content;

	dir_content = (t_celldata*)ft_xmalloc(sizeof(t_celldata));
	return((void*)dir_content);
}

void			fill_hashdata(void **cell_data, t_args *list,
					size_t max_len, int argc)
{
	t_celldata	*dir_content;

	dir_content = (t_celldata*)(*cell_data);
	dir_content->list = list;
	dir_content->max_len = max_len;
	dir_content->argc = argc;
}

void			fill_hashdata_upperlist(void **cell_data,
					t_args *upper_list)
{
	t_celldata	*dir_content;

	dir_content = (t_celldata*)(*cell_data);
	dir_content->upper_list = upper_list;
}

void			clean_hashdata(void *cell_data)
{
	t_celldata	*dir_content;

	dir_content = (t_celldata*)cell_data;
	//освобождение выделенных листов нынешних
	dir_content->max_len = 0;
	dir_content->argc = 0;
}