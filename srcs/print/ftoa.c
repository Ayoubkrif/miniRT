/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:11:22 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/11 11:55:25 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program for implementation of ftoa() 
#include <math.h> 
#include <stdio.h> 

// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len) 
{ 
    int		i = 0, j = len - 1;
	char	temp; 
    while (i < j) { 
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
int intToStr(int x, char str[], int d) 
{
	(void)d;
    int i = 0;
	if (x == 0)
		str[i++] = '0';
	else
	{
		while (x) { 
			str[i++] = (x % 10) + '0'; 
			x = x / 10; 
		}
	}

    // If number of digits required is more, then 
    // add 0s at the beginning 
   /*while (i < d) */
   /*    str[i++] = '0'; */

    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 

// Converts a doubleing-point/double number to a string. 
void ftoa(double n, char* res, int afterpoint) 
{
	int	i;

	i = 0;
	if (n < 0)
	{
		res[i] = '-';
		n = -n;
		i++;
	}
    // Extract integer part 
    int ipart = (int)n; 

    // Extract doubleing part 
    double fpart = n - (double)ipart; 

    // convert integer part to string 
    i += intToStr(ipart, &res[i], 20 - i); 

    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 

        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 

        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
} 

// Driver program to test above function 
// int main() 
// { 
//     char res[20]; 
//     double n = 233.007; 
//     ftoa(n, res, 4); 
//     printf("\"%s\"\n", res); 
//     return 0; 
// }
