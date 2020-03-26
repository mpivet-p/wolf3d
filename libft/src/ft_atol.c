//HEADER

#include "libft.h"

int8_t	ft_atol(const char *s, int64_t *result)
{
	size_t	i;
	int64_t	save;
	int8_t	sign;

	i = 0;
	*result = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] != '-' && s[i] != '+' && !(s[i] >= '0' && s[i] <= '9'))
		return (-1);
	if (s[i] == '+' || s[i] == '-')
		sign *= (s[i++] == '-') ? -1 : 1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		save = *result;
		*result = (*result * 10) + ((s[i++] - '0') * sign);
		if ((sign == -1 && save < *result) || (sign == 1 && save > *result))
			return (-1);
	}
	while (s[i] == ' ')
		i++;
	return ((s[i] != 0) ? -1 : 0);
}
