/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:26:41 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/06/17 14:05:31 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int		get_count_elem(char **s)
{
	int		count;
	char	**tmp;

	if (s == 0)
		return (0);
	count = 0;
	tmp = s;
	while (*tmp != 0)
	{
		count++;
		tmp++;
	}
	return (count);
}

int		ft_lstsize(t_strarr_list *lst)
{
	int		i;

	if (lst == 0)
		return (0);
	i = 1;
	while (lst->next != 0)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_add_newstrarr(t_strarr_list **start, char **s)
{
	t_strarr_list	*new;

	new = (t_strarr_list *)malloc(sizeof(t_strarr_list));
	new->next = *start;
	new->s = s;
	*start = new;
}

int		atoi_16(char *s)
{
	int		col;

	if (*s != '0' || *(++s) != 'x')
		return (16777215);
	col = 0;
	while (*(++s))
	{
		if (*s >= '0' && *s <= '9')
			col = col * 16 + *s - '0';
		else if (*s >= 'A' && *s <= 'F')
			col = col * 16 + *s - 55;
		else if (*s >= 'a' && *s <= 'f')
			col = col * 16 + *s - 87;
		else
			return (0xFFFFFF);
	}
	return (col);
}

void	free_str_map(t_strarr_list **strs)
{
	char			**tmp;
	t_strarr_list	*tmp2;
	char			*tmp3;
	t_strarr_list	*tmp4;

	tmp2 = *strs;
	while (tmp2 != 0)
	{
		tmp = (tmp2->s);
		while (*tmp != 0)
		{
			tmp3 = *(tmp++);
			free(tmp3);
		}
		free(tmp2->s);
		tmp4 = tmp2;
		tmp2 = tmp2->next;
		free(tmp4);
	}
	*strs = 0;
}
