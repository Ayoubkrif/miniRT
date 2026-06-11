# miniRT

> A ray tracer written from scratch in C — Blinn-Phong shading, UV texture mapping, bump mapping, and interactive real-time controls.

<!-- Replace the lines below with actual screenshots once rendered -->
<!-- Tip: run ./miniRT assets/scene/pretty_sphere.rt and take a screenshot -->

![render preview](docs/renders/preview.png)

---

## Features

| Feature | Detail |
|---|---|
| **Primitives** | Sphere, plane, cylinder, cone |
| **Lighting** | Blinn-Phong (diffuse + specular), multiple light sources, ambient |
| **Textures** | XPM texture mapping with UV projection per primitive |
| **Bump mapping** | Normal perturbation from XPM bump maps |
| **Interactive mode** | Move / rotate camera and objects with keyboard in real time |
| **Fast math** | Double-precision Quake fast inverse square root for vector normalization |
| **Scene format** | Human-readable `.rt` scene files |

---

## Gallery

<!-- Add screenshots here. Suggested scenes to render:
     assets/scene/pretty_sphere.rt
     assets/scene/temple.rt
     assets/scene/atoms.rt
     assets/scene/texture_demo.rt
-->

| | | |
|---|---|---|
| ![](docs/renders/sphere.png) | ![](docs/renders/temple.png) | ![](docs/renders/atoms.png) |
| Sphere + bump | Temple | Atoms |

---

## Installation

### Requirements

- Linux (X11)
- `gcc`, `make`
- `libXext`, `libbsd`

```bash
# Ubuntu / Debian
sudo apt install gcc make libxext-dev libbsd-dev
```

### Build

```bash
git clone https://github.com/Ayoubkrif/miniRT.git
cd miniRT
make
```

### Run

```bash
./miniRT assets/scene/pretty_sphere.rt
```

---

## Docker

minilibx ties the build to Linux/X11, which is not portable by nature. The Dockerfile exists to compile without having to install X11 headers on the host — the binary still needs a running X server to display.

```bash
make docker-build           # build the image once
make docker-make            # compile inside the container
```

The binary is produced in the current directory and can then be run on the host.

---

## Scene file format

```
# Ambient light      ratio  R,G,B
A  0.2               255,255,255

# Camera             position        direction       FOV
C  0,0,-5            0,0,1           70

# Light              position        R,G,B
L  -40,50,0          255,255,255

# Sphere             center          diameter  R,G,B
sp 0,0,3             2               255,0,0

# Plane              point           normal    R,G,B
pl 0,-1,0            0,1,0           100,200,100

# Cylinder           center          axis      diameter  height  R,G,B
cy 0,0,3             0,1,0           1         3         0,0,255

# Cone               apex            axis      half-angle  R,G,B
co 0,3,3             0,-1,0          20         255,165,0
```

See `assets/scene/` for full examples including textures and bump maps.

---

## Controls

| Key | Action |
|---|---|
| `W` / `S` | Move camera forward / backward |
| `A` / `D` | Move camera left / right |
| `↑` / `↓` | Rotate camera up / down |
| `←` / `→` | Rotate camera left / right |
| `Tab` | Cycle through objects |
| `IJKL` | Move selected object |
| Mouse wheel | Move object along its axis |
| `ESC` | Exit |

---

## Architecture

```
srcs/
├── main.c                  entry point, mlx event loop
├── init/                   scene parser, object constructors
├── intersection/           ray–object intersection, Blinn-Phong
├── math/                   vector ops, fast inverse square root
├── bump_texture/           UV mapping, bump normal computation
├── keyhook/                keyboard controls per object type
├── mlx/                    pixel write, window management
├── print/                  real-time HUD (object coordinates)
└── utils/                  color ops, camera basis
```

---

## Authors

- [aykrifa](https://github.com/Ayoubkrif)
- cbordeau
