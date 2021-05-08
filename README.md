-freeglut.dll must be in the same folder as the Windows .exe  
-To pipe an .obj into the .exe, use Ubuntu on Windows Subsystem for Linux (WSL) ( not sure why a Windows exe can run on Ubuntu :confused: )

# How to use WSL to run this:
1) Install and Run XServer (XMing, X410 etc)
2) In WSL, run `export DISPLAY=:0` (you would have to run this for each shell session, or put it in your `~/.bash_profile` or `~/.bashrc` so you don't have to)
3) Test if OpenGL works `glxgears`
4) Install vecmath library https://github.com/ydm/mit-vecmath. `make` then `make install`.
- (NOTE: the source code in that repo is outdated. `make` the provided code in the assignment)
6) `make` the assignment. Pipe an .obj if you need to:
```
./a0
./a0 < garg.obj
```
