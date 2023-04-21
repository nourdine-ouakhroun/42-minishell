/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:05:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/20 20:09:48 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_list *list, t_list *head, int x)
{
	t_list	*back;

	if (x == 1)
	{
		back = head;
		while (back)
		{
			if (back->next->content == list->content)
				break ;
			back = back->next;
		}
		free(list->content);
		back->next = list->next;
	}
}

void	unset_checker(t_list *list, char *cmd, t_list *head)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (list != NULL)
	{
		while (cmd[i])
		{
			if (((char *)list->content)[i]
				&& ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if (((char *)list->content)[i] == '='
					|| ((char *)list->content)[i] == 0)
					x = 1;
			}
			else
				break ;
		}
		if (x == 1)
			break ;
		list = list->next;
	}
	delete_node(list, head, x);
}

void	unset_command(t_all *my_struct, int c_of_s)
{
	t_list	*ptr;
	int		i;

	ptr = my_struct->list;
	i = 0;
	while (my_struct->each_cmd[c_of_s].cmd[i])
	{
		if (mini_check_export(my_struct->each_cmd[c_of_s].cmd[i], 1) == 1
			|| ft_strchr(my_struct->each_cmd[c_of_s].cmd[i], '='))
		{
			printf("export: `%s': not a valid identifier\n",
				my_struct->each_cmd[c_of_s].cmd[i]);
			i++;
		}
		else
		{
			unset_checker(my_struct->list, my_struct->each_cmd[c_of_s].cmd[i],
				ptr);
			i++;
		}
	}
	my_struct->list = ptr;
}