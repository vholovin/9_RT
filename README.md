# RT

Features:
C + POSIX Threads + cJSON + SDL2
- Multithread using pthreads
- All scene data serialized of cJSON
- SDL2 used for interactive mode and for out information display

Objects:
- Sphere
- Infinity Plane
- Infinity Cylinder
- Infinity Cone
- Ellipsoid
- Paraboloid
- Torus
- Disc
- Triangle
- Limited Plane

Camera:
- Angle of view
- Rotate direction
- Movement regardless of axes

Ray Tracing:
- Multisampling for antialiasing
- Ambient, point, direct and parralel lights
- Lambert lighting model
- Mirror and gloss reflections (Fong's model)
- Reflection and refraction of rays (with Fresnel's law)
- Index (%) of reflection and transparency
- Refraction with refractive indexes
- Attenuation by transparent objects (with Beer's law)
- Shadows depend from transparency and color of objects
- Cartoon effect, B&W and Sepia

Texture mapping:
- All objects have UV mapping
- Stretch and compress textures
- Shift textures on an objects
- Loading textures from PNG, BMP and JPG

Controls

Key	Action:
ESC - Exit
I - Open/Close gui
p - Print Screen
W,S,A,D - Movement camera
Up,Dwn,Lft,Rgth - Rotate camera
C - Change color
"-","+" - Change number of reflect
"[","]" - Change number of refract
"<",">" - Change number of Antialiasing
" T " - show/hide texture
" ; " - show/hide shadow
" ' " - show/hide glossy