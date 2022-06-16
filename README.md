[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

# pong-clone
this project is a clone of the original pong game written in C programing language for a university project

# showcase

[![menu](https://i.imgur.com/MioH0Tn.png)](https://i.imgur.com/MioH0Tn.png)

[![settings](https://i.imgur.com/kDxCdzF.png)](https://i.imgur.com/kDxCdzF.png)

[![game](https://i.imgur.com/DXOE6P1.png)](https://i.imgur.com/DXOE6P1.png)
# dependencies

> [glfw](https://github.com/glfw/glfw)
>
> [glad](https://github.com/Dav1dde/glad)
>
>[freetype](https://github.com/freetype/freetype)
> 
> [stb](https://github.com/nothings/stb)

# building

```
    git clone https://github.com/Mat1337/pong-clone.git --recurse-submodules
```

```
    cd pong-clone
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
```