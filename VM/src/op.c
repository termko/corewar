/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <vellery-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:49:38 by vellery-          #+#    #+#             */
/*   Updated: 2020/02/20 16:57:38 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_op	*t_op_tab(void)
{
	static t_op		op_tab[17] = {
	{1, 1, {T_DIR}, 1, 10, 0, 0},
	{2, 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{2, 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
	{3, 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{3, 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 0},
	{3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 0},
	{3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 0},
	{1, 1, {T_DIR}, 9, 20, 0, 1},
	{3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},
	{3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},
	{1, 1, {T_DIR}, 12, 800, 0, 1},
	{2, 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
	{3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1},
	{1, 1, {T_DIR}, 15, 1000, 0, 1},
	{1, 1, {T_REG}, 16, 2, 1, 0},
	{0, 0, 0, 0, 0, 0, 0}
	};

	return (op_tab);
}
