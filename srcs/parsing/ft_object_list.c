/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:41:00 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/19 01:24:43 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_free_obj_list(t_obj *lst)
{
	t_obj	*obj;
	t_obj	*prev;

	if (lst == NULL)
		return ;
	obj = lst;
	prev = NULL;
	while (obj != NULL)
	{
		if (prev != NULL)
		{
			free(prev->sphere);
			free(prev->plane);
			free(prev->cylinder);
			free(prev);
		}
		prev = obj;
		obj = obj->next;
	}
	free(prev->sphere);
	free(prev->plane);
	free(prev->cylinder);
	free(prev);
}

void	ft_lstadd_back_obj_plane(t_obj **lst, t_pl **plane)
{
	t_obj	*element;
	t_obj	*obj;

	obj = (t_obj *) malloc(sizeof(t_obj));
	obj->next = NULL;
	obj->sphere = NULL;
	obj->cylinder = NULL;
	obj->plane = *plane;
	if (*lst == NULL)
	{
		*lst = obj;
		return ;
	}
	element = *lst;
	while (element->next)
		element = element->next;
	element->next = obj;
}

void	ft_lstadd_back_obj_sphere(t_obj **lst, t_sp **sphere)
{
	t_obj	*element;
	t_obj	*obj;

	obj = (t_obj *) malloc(sizeof(t_obj));
	obj->next = NULL;
	obj->plane = NULL;
	obj->cylinder = NULL;
	obj->sphere = *sphere;
	if (*lst == NULL)
	{
		*lst = obj;
		return ;
	}
	element = *lst;
	while (element->next)
		element = element->next;
	element->next = obj;
}

void	ft_lstadd_back_obj_cylinder(t_obj **lst, t_cy **cylinder)
{
	t_obj	*element;
	t_obj	*obj;

	obj = (t_obj *) malloc(sizeof(t_obj));
	obj->next = NULL;
	obj->plane = NULL;
	obj->sphere = NULL;
	obj->cylinder = *cylinder;
	if (*lst == NULL)
	{
		*lst = obj;
		return ;
	}
	element = *lst;
	while (element->next)
		element = element->next;
	element->next = obj;
}
