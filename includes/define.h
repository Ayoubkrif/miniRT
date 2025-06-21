/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:10:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/21 13:18:59 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
# define K_ESC         65307

# define K_W           119
# define K_A           97
# define K_S           115
# define K_D           100
# define K_Q           113
# define K_E           101
# define K_C           99
# define K_N           110
# define K_UP          65362
# define K_DOWN        65364
# define K_LEFT        65361
# define K_RIGHT       65363
# define K_PLUS        61
# define K_MINUS       45
# define K_1           49
# define K_2           50
# define K_3           51
# define K_4           52
# define K_5           53
# define K_6           54
# define K_7           55
# define K_8           56
# define K_9           57
# define K_0           48
# define K_SPACE       32
# define K_SHIFT       65505
# define K_CTRL        65507
# define K_ALT         65513
# define K_PLUS 61
# define K_MINUS 45
// Molette de la souris
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

// Événements MLX
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_DESTROY 17

# define MALLOC "Malloc failed"
# define ARGS "Missing arg for "
# define LIGHT "Too many lights"
# define AMBIENT "Too many ambient"
# define CAM "Too many cam"
# define VECT_NORM "Wrong range for vector :"
# define COLOR "Wrong range for color :"
# define FOV "Wrong range for fov :"
# define BRIGHTNESS "Wrong range for brightness :"

# define KA 0.2
# define KD 0.9

#endif
