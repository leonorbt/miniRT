/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:41:00 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/18 17:13:15 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_lstadd_back_obj_plane(t_obj **lst, t_pl **plane)
{
	t_obj	*element;
	t_obj	*obj;

	obj = (t_obj *) malloc(sizeof(t_obj));
	obj->next = NULL;;
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
