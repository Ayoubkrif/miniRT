/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:10:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/11 11:33:40 by aykrifa          ###   ########.fr       */
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
# define VECT_NULL "Director vector norm is 0 :"
# define COLOR "Wrong range for color :"
# define FOV "Wrong range for fov :"
# define BRIGHTNESS "Wrong range for brightness :"

# define KA 0.2
# define KD 0.5
# define KS 0.9
# define ALPHA_S 200

#endif
