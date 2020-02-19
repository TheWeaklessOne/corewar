/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:02 by stross            #+#    #+#             */
/*   Updated: 2020/02/19 18:15:38 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	null_vars(int *i, bool *ex)
{
	*i = 0;
	*ex = 0;
}

static int	validate_it(char *str, t_command **command)
{
	char	*temp;
	int		i;
	bool	ex;

	null_vars(&i, &ex);
	temp = get_comm_label(str);
	while (command[i])
	{
		if (!command[i]->is_label)
		{
			i++;
			continue ;
		}
		else
		{
			if (ft_strequ(temp, command[i]->label))
				ex = true;
		}
		i++;
	}
	free(temp);
	if (ex)
		return (0);
	else
		return (1);
}

static void	label_validation(t_command **commands)
{
	int		i;
	char	*temp;

	i = 0;
	while (commands[i])
	{
		if (commands[i]->is_label)
		{
			i++;
			continue;
		}
		else
		{
			if ((temp = ft_strchr(commands[i]->command, LABEL_CHAR)))
				if (validate_it(temp, commands))
					no_label_error();
		}
		i++;
	}
}

void		check_lb(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	if (i > 0)
	{
		if (*(--str) != '\n')
		{
			write(2, "Syntax error - unexpected end of input", 38);
			write(2, " (Perhaps you forgot to end with a newline ?)\n", 46);
			exit(1);
		}
	}
}

void		validate_labels(t_asm_list *list)
{
	t_command	**commands;
	int			len;
	t_asm_list	*cpy;

	len = 0;
	cpy = list;
	while (cpy)
	{
		len++;
		cpy = cpy->next;
	}
	commands = (t_command**)ft_memalloc((len + 1) * sizeof(t_command*));
	len = 0;
	while (list)
	{
		commands[len] = list->command;
		len++;
		list = list->next;
	}
	label_validation(commands);
	free(commands);
}