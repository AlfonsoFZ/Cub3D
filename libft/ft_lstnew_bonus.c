/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:29:40 by Alfofern          #+#    #+#             */
/*   Updated: 2022/12/22 10:21:10 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list_item;

	new_list_item = (t_list *)malloc(sizeof(t_list));
	if (!new_list_item)
		return (NULL);
	new_list_item->content = content;
	new_list_item->next = NULL;
	return (new_list_item);
}
