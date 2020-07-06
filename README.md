# Raylib-Super-Mario-Clone
Super mario clone made using raylib 3.0

Assets are from [VideoGameSprites.net](http://www.videogamesprites.net/SuperMarioBros1/)


## Required Libraries :
- Raylib 3.0

All installation and other important details are available from [Raylib's github page.](https://github.com/raysan5/raylib)

## How to run :

It is recommended to install Raylib using Homebrew 

##### With Homebrew

- If you don't want to build it yourself, install Homebrew by executing the following command in Terminal.app:  
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
- Once Homebrew is installed, run the following command in Terminal:
```
brew install raylib
```

### How to compile Raylib using Clang (or on MacOSX)

#### C
 ```
 clang -std=c11 -framework IOKit -framework Cocoa -framework OpenGL /usr/local/Cellar/raylib/3.0.0/lib/libraylib.a  main.c -o my_app && ./my_app
 ```

#### C++
```
clang -std=c++11 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL  /path/to/libraylib.a main.cpp -o my_app
```

#### On Windows : 
```
gcc -o core_basic_window.exe core_basic_window.c -s C:\raylib\raylib\raylib_icon -Iexternal -lraylib -lglfw3 -lopengl32 -lgdi32 -lopenal32 -lwinmm -std=c99 -Wl,-allow-multiple-definition -Wl,--subsystem,windows
```


