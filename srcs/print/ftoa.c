/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:11:22 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/17 08:27:33 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program for implementation of ftoa() 
#include <math.h> 
#include <stdio.h> 

// Reverses a string 'str' of length 'len' 
void	reverse(char *str, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning. 
int	int_to_str(int x, char str[])
{
	int	i;

	i = 0;
	if (x == 0)
		str[i++] = '0';
	else
	{
		while (x)
		{
			str[i++] = (x % 10) + '0';
			x = x / 10;
		}
	}
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

// Converts a floating-point/double number to a string. 
void	ftoa(float n, char *res, int afterpoint)
{
	int		i;
	int		ipart;
	float	fpart;

	i = 0;
	if (n < 0)
	{
		res[i] = '-';
		n = -n;
		i++;
	}
	ipart = (int)n;
	fpart = n - (float)ipart;
	i += int_to_str(ipart, &res[i]);
	if (afterpoint != 0)
	{
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		int_to_str((int)fpart, res + i + 1);
	}
}
