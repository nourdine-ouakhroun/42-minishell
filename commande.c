/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/25 20:46:04 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exicut_commande(t_all *my_struct, int i, int c_of_s, int *pipe_n)
{
	(void)pipe_n;
	// printf("ffff\n");
	execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, NULL);
}