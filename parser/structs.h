#ifndef _STRUCTS_H_
# define _STRUCTS_H_

# include <stdio.h>
# include <stdlib.h>

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
typedef struct		t_textures
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_textures;
	char	*sprite_texture;
} 					s_textures;

#endif