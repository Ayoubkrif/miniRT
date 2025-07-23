/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:10:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/23 11:30:19 by cbordeau         ###   ########.fr       */
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

# define FORMAT "Wrong format for scene file"
# define MALLOC "Malloc failed"
# define ARGS "Missing arg for "
# define LIGHT "Too many lights"
# define AMBIENT "Too many ambient"
# define OBJ "Too many object"
# define CAM "Too many cam"
# define VECT_R "Wrong range for vector :"
# define VECT_NORM "Vector is not normalised :"
# define VECT_NULL "Director vector norm is 0 :"
# define COLOR "Wrong range for color :"
# define FOV "Wrong range for fov :"
# define BRIGHTNESS "Wrong range for brightness :"
# define REFLEXION "No reflexion :"
# define BONUS "Error in bonus parsing :"

# define KA 0.3
# define KD 0.5
# define KS 0.9
# define ALPHA_S 200
# define MAX_OBJ 50
# define MAX_LIGHT 20

#endif
