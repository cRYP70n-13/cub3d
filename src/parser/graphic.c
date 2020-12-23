#include "../../includes/header.h"
#include "../../includes/structs.h"
#include "../utils/Errors/errors.h"
#include "../utils/libft/libft.h"

void    ft_3d_walls(float x, float y)
{
  float distance = sqrt(pow((x - g_player.x), 2) + pow((y - g_player.y), 2));
  float correct = distance * cos(player_angle - g_player.rotation_angle);
  float distanceProjectionPlane = (resolution.width / 2) / tan(FOV / 2);

  float stripeHeight = (TAIL_SIZE / correct) * distanceProjectionPlane;

  int c = (resolution.height / 2) - (stripeHeight / 2);
  while (++c <= (resolution.height / 2) + (stripeHeight / 2))
  {
  	ft_put_image(c, g_count, 0x0FF0AB0);
  }
  ft_put_image(1000, 500, 0x0FF0AB0);
}
