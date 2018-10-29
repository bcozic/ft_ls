/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:07:08 by bcozic            #+#    #+#             */
/*   Updated: 2018/10/29 20:21:10 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		cmp_time(time_t time1, time_t time2, t_option *option)
{
	if ((time1 > time2 && !(option->flag & REVERS)) ||
			(time1 < time2 && (option->flag & REVERS)))
		return (1);
	if (time1 == time2)
		return (0);
	return (-1);
}

t_file			*insert_time(char *str, t_option *option,
						t_file **list, t_time time_spec)
{
	t_file	*current;
	int		cmp;

	current = *list;
	if (*list == NULL || (cmp = cmp_time(time_spec.tv_sec,
			current->time.tv_sec, option)) == 1)
		return (add_file(NULL, str, option, list));
	else if (cmp == 0)
		if (cmp_name(current->name, str, option))
			return (add_file(NULL, str, option, list));
	while (current->next != option->next_dir && current->next)
	{
		cmp = cmp_time(time_spec.tv_sec, current->next->time.tv_sec, option);
		if (cmp == 1)
			return (add_file(current, str, option, list));
		else if (cmp == 0)
		{
			if (cmp_name(current->next->name, str, option))
				return (add_file(current, str, option, list));
		}
		current = current->next;
	}
	return (add_file(current, str, option, list));
}
