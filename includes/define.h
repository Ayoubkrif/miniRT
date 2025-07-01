/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:10:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/01 10:37:27 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
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
# define KD 0.8

#endif
