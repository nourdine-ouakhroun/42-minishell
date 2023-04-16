/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/16 22:07:05 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IN_DCOTE 0
#define IN_COTE 1
#define VAR 3
#define WORD 4
#define OUTSIDE 5



char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = 0;
    free((char *)s1);
    free((char *)s2);
	return (b);
}


// int count_2d(t_all *my_struct)
// {
//     my_struct->command_len = -1;
//     while(my_struct->fix_cmd[++my_struct->command_len]);
//     return my_struct->command_len;
// }


// int     ft_strcher_v2(char *str,char c,int i)
// {
    
//     while(str[i])
//     {
//         if(str[i] == c)
//         {
//             return i;
//         }
//         i++;
//     }

//     return -1;
// }
// char  *checker(char *cmd, t_all *my_struct)
// {
//     int i = 0;
//     int j = 0;
//     my_struct->error = 0;

//     char *str = ft_calloc(ft_strlen(cmd) + 1, 1);
//     while(cmd[i] && my_struct->error == 0)
//     {
        
//         if(cmd[i] == 34)
//         {
//             j = ft_strcher_v2(cmd, 34, i + 1);
//             if(j == -1)
//                     my_struct->error = 1;

//             str = ft_strjoin_v2(str, ft_substr(cmd, i + 1, j - i - 1));
//             i = j;
//         }
//         else if(cmd[i] == 39)
//         {
//             j = ft_strcher_v2(cmd, 39, i + 1);
//             if(j == -1)
//                 my_struct->error = 1;
//             str = ft_strjoin_v2(str, ft_substr(cmd, i + 1, j - i - 1));
//             i = j;
//         }
//         else
//         {
//             str = ft_strjoin_v2(str, ft_substr(cmd, i,1));
//         }
//         i++;
//     }
//     return str;
// }

// char *check_inve(char **split,int i)
// {
//     int x;
//     x = 0;
//     char *backup = ft_strdup("");
//     while(--i >= 0)
//     {
//         if(ft_strchr(split[i],'$'))
//         {
//             if(getenv(&split[i][1]) != NULL)
//             {
//                 backup = ft_strjoin(backup,getenv(&split[i][1]));
//             }
//         }
//         else
// 		    backup = ft_strjoin(backup,split[i]);

//     }
//     return backup;
// }


// int counter_malloc(char *cmd)
// {
//     char *dst = ft_strdup(cmd);
//     int i;
//     int x;
//     x = 0;
//     i = ft_strlen(dst)-1;
//     while(i >= 0)
//     {
//         if(dst[i] == '$' || i == 0 || dst[i] == 34 || dst[i] == 39)
//         {
//             dst[i] = '\0';
//             x++;
//         }
//         i--;
//     }
//     return (x);
// }

// char *split_dollar(char *cmd)
// {
//     char **split;
//     char *dst;
//     int i;
//     int x;
//     x = 0;
//     i = ft_strlen(cmd)-1;
//     split = calloc(sizeof(char *)* counter_malloc(cmd) + 1 , 1);
//     while(i >= 0)
//     {
//         if(cmd[i] == '$' || i == 0 || cmd[i] == 34 || cmd[i] == 39)
//         {
//             split[x] = ft_strdup(&cmd[i]);
//             cmd[i] = '\0';
//             x++;
//         }
//         i--;
//     }
//     dst = check_inve(split,x);
//     return (dst);
// }
// char    *dollar_handle(char *cmd)
// {
//     cmd = split_dollar(cmd);
//     return cmd;
// }

// void    fill(t_all *my_struct)
// {
//     int i;
//     i = 0;

//     while(my_struct->fix_cmd[i])
//     {
//         my_struct->fix_cmd[i] = checker(my_struct->fix_cmd[i], my_struct);
//         i++;
//     }             
// }

// int mini_checker(char *cmd)
// {
//     if(cmd[0] == 34 && cmd[ft_strlen(cmd)-1] == 34)
//         return 0;
//     else if(cmd[0] == 39 && cmd[ft_strlen(cmd)-1] == 39)
//         return 1;
//     return -1;
// }

void    fix_arg(t_all *my_struct)
{
    int i = 0;
    int j = 0;
    int c = -1;
    int var;
    char		*variable;
    char splite[2];
    splite[0] = 3; 
    splite[1] = '\0';
    int			status;
    i = 0;
    my_struct->number_of_pipes = 1;
    my_struct->the_commande = ft_calloc(1, 1);
    while(my_struct->fix_cmd[i])
    {
        j = 0;
        c = -1;
        status = OUTSIDE;
        while (my_struct->fix_cmd[i][j])
        {
            if((my_struct->fix_cmd[i][j] == 34) && status != IN_COTE)
            {
                c++;
                if(my_struct->fix_cmd[i][j] == 34 && status == IN_DCOTE)
                    status = OUTSIDE;
                else
                    status = IN_DCOTE;
                my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                c = j;
            }
            if((my_struct->fix_cmd[i][j] == 39)&& status != IN_DCOTE)
            {
                c++;
                if(my_struct->fix_cmd[i][j] == 39 && status == IN_COTE)
                    status = OUTSIDE;
                else
                    status = IN_COTE;
                my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                c = j;
            }
            if(my_struct->fix_cmd[i][j] == '|' && status == OUTSIDE)
            {
                my_struct->fix_cmd[i][j] = 4;
                my_struct->number_of_pipes++;
            }
            if(my_struct->fix_cmd[i][j] == '>' && status == OUTSIDE)
                my_struct->fix_cmd[i][j] = 2;
            if(my_struct->fix_cmd[i][j] == '<' && status == OUTSIDE)
                my_struct->fix_cmd[i][j] = 5;
            if(my_struct->fix_cmd[i][j] == '$' && my_struct->fix_cmd[i][j + 1])
            {
                if(my_struct->fix_cmd[i][j + 1] != 39 && my_struct->fix_cmd[i][j + 1] != 34)
                {
                    if(ft_isalpha(my_struct->fix_cmd[i][j + 1]))
                    {
                        c++;
                        var = j + 1;
                        my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                        while (my_struct->fix_cmd[i][var]  && (ft_isalpha(my_struct->fix_cmd[i][var]) || ft_isdigit(my_struct->fix_cmd[i][var])))
                            var++;
                        if(status == IN_DCOTE || status == OUTSIDE)
                        {
                            variable = ft_substr(my_struct->fix_cmd[i], j + 1, (var - (j + 1)));
                            if(getenv(variable))
                                my_struct->the_commande = ft_strjoin(my_struct->the_commande, getenv(variable));
                            j = var - 1;
                        }
                        if(status == IN_COTE)
                        {
                            variable = ft_substr(my_struct->fix_cmd[i], j, (var - j));
                            my_struct->the_commande = ft_strjoin(my_struct->the_commande, variable);
                            j = var - 1;
                        }
                        c = j;
                    }
                    else
                    {
                        j++;
                        c = j;
                    }
                }
                else if(status == OUTSIDE && (my_struct->fix_cmd[i][j + 1] == 39 || my_struct->fix_cmd[i][j + 1] == 34))
                {
                    my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c + 1, j - (c + 1)));
                    c = j;
                }
            }
            j++;
        }
        if(status == OUTSIDE)
        {
            if(status == OUTSIDE)
                c++;
            my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
        }
        my_struct->the_commande = ft_strjoin(my_struct->the_commande, splite);
        free(my_struct->fix_cmd[i]);
        my_struct->fix_cmd[i] = 0;
        i++;
    }
    free(my_struct->fix_cmd);
    my_struct->splite_pipe = ft_split(my_struct->the_commande, 4);
    free(my_struct->the_commande);
    my_struct->the_commande = 0;
    i = 0; 
    j = 0;
    int c_of_s = 0;
    while(my_struct->splite_pipe[i])
    {
        j = 0;
        var = 0;
        my_struct->the_commande = ft_calloc(1, 1);
        while(my_struct->splite_pipe[i][j])
        {
            if (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 5)
            {
                while (my_struct->splite_pipe[i][j] == 2)
                    j++;
                var++;
            }
            j++;
        }
        my_struct->each_cmd[i].files = ft_calloc(sizeof(t_files), (var + 1));
        j = 0;
        while (my_struct->splite_pipe[i][j])
        {
            if(my_struct->splite_pipe[i][j] == 2)
            {
	            my_struct->each_cmd[i].files[c_of_s].OUTPUT = 0;
	            my_struct->each_cmd[i].files[c_of_s].APPEND = 0;
	            my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_O = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_I = 0;
                while (my_struct->splite_pipe[i][j] && (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 3 || my_struct->splite_pipe[i][j] == 5))
                {
                    if(my_struct->splite_pipe[i][j] == 2)
                        my_struct->each_cmd[i].files[c_of_s].number_of_O++;
                    if(my_struct->splite_pipe[i][j] == 5)
                        my_struct->each_cmd[i].files[c_of_s].number_of_I++;
                    j++;
                }
                var = j;
                while (my_struct->splite_pipe[i][var] && my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5 && my_struct->splite_pipe[i][var] != 3)
                    var++;
                if(my_struct->each_cmd[i].files[c_of_s].number_of_O && my_struct->each_cmd[i].files[c_of_s].number_of_I)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O == 2)
	                my_struct->each_cmd[i].files[c_of_s].APPEND = 2;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O == 1)
	                my_struct->each_cmd[i].files[c_of_s].OUTPUT = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O > 2)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 1;
                my_struct->each_cmd[i].files[c_of_s].files = ft_substr(my_struct->splite_pipe[i], j, var - j);
                // printf("{%s}\n", my_struct->each_cmd[i].files[c_of_s].files);
                c_of_s++;
                j = var - 1;
            }
            else if(my_struct->splite_pipe[i][j] == 5)
            {
                
	            my_struct->each_cmd[i].files[c_of_s].INPUT = 0;
	            my_struct->each_cmd[i].files[c_of_s].HERDOC = 0;
	            my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_O = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_I = 0;
                while (my_struct->splite_pipe[i][j] && (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 3 || my_struct->splite_pipe[i][j] == 5))
                {
                    if(my_struct->splite_pipe[i][j] == 2)
                        my_struct->each_cmd[i].files[c_of_s].number_of_O++;
                    if(my_struct->splite_pipe[i][j] == 5)
                        my_struct->each_cmd[i].files[c_of_s].number_of_I++;
                    j++;
                }
                var = j;
                while (my_struct->splite_pipe[i][var] && my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5 && my_struct->splite_pipe[i][var] != 3)
                    var++;
                if(my_struct->each_cmd[i].files[c_of_s].number_of_O && my_struct->each_cmd[i].files[c_of_s].number_of_I)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I == 1)
	                my_struct->each_cmd[i].files[c_of_s].INPUT = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I == 2)
	                my_struct->each_cmd[i].files[c_of_s].HERDOC = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I > 2)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 1;
                my_struct->each_cmd[i].files[c_of_s].files = ft_substr(my_struct->splite_pipe[i], j, var - j);
                // printf("(%s)\n", my_struct->each_cmd[i].files[c_of_s].files);
                c_of_s++;
                j = var - 1;
            }
            else if(my_struct->splite_pipe[i][j] != 5 && my_struct->splite_pipe[i][j] != 2)
            {
                var = j;
                while (my_struct->splite_pipe[i][var] && (my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5))
                    var++;
                my_struct->the_commande  = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->splite_pipe[i], j, var - j));
                j = var - 1;
            }
            j++;
        }
        my_struct->each_cmd[i].cmd = ft_split(my_struct->the_commande, 3);
        free(my_struct->splite_pipe[i]);
        my_struct->the_commande = 0;
        my_struct->splite_pipe[i] = 0;;
        i++;
    }
    free(my_struct->splite_pipe);
}