#include "utils.h"

/**
 * @param str: ip address string
 * @return IP value in network byte order
 */
__be32 in_aton(const char *str)
{
	unsigned int l;
	unsigned int val;
	int i;

	l = 0;
	for (i = 0; i < 4; i++)	{
		l <<= 8;
		if (*str != '\0') {
			val = 0;
			while (*str != '\0' && *str != '.' && *str != '\n') {
				val *= 10;
				val += *str - '0';
				str++;
			}
			l |= val;
			if (*str != '\0')
				str++;
		}
	}
	return htonl(l);
}