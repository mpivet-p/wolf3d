#include "wolf.h"
#include <math.h>

t_vector	rotate_vector(t_vector *vector, double angle)
{
	t_vector	new_vec;

	new_vec.x = (vector->x * cos(angle)) - (sin(angle) * vector->y);
	new_vec.y = (vector->x * sin(angle)) + (cos(angle) * vector->y);
	return (new_vec);
}
