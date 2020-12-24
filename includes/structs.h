/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:04:06 by okimdil           #+#    #+#             */
/*   Updated: 2020/12/07 11:04:08 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H_
# define _STRUCTS_H_

# include <stdio.h>
# include <stdlib.h>

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S  4

/**
 * @brief {*} The Resolution structure
 * @param { Resoluition, Height, Width }
 * @return {*} The structure filled by the data
*/
typedef struct t_resolution
{
	char	resolution;
	int 	height;
	int 	width;
} 				s_resolution;

/**
 * @brief The floor Colors
 * @param { RGB } The RGB structure for my code
 * @return	The strucute filled by the colors
*/
typedef struct 		t_floor
{
	char	Floor;
	int		red;
	int		green;
	int		blue;
} 					s_floor;

/**
 * @brief The floor Colors
 * @param { RGB } The RGB structure for my code
 * @return	The strucute filled by the colors
*/
typedef struct 		t_celling
{
	char 	celling;
	int		red;
	int		green;
	int		blue;
} 					s_celling;

/**
 * @brief The Textures and the sprites
 * @param { Path to the textures } The absolute paths to the structures and the sprite
 * @return	The strucute filled by the paths
*/
typedef struct      textures
{
	char **textures;
}                   s_textrs;

/**
 * @brief The MAP datastructure
 * @param {*} IDK
 * @return A 2D map filling by 0s or 1s
*/
typedef struct      t_map
{
	char **virtual_map_before;
	int width;
	int height;
    char *map_in_one_line;
    char **map_2d;
}                   s_map;

#endif