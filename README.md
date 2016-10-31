# Terraria-linux

A tribute to the 2011 2D action-adventure sandbox game developed by Re-Logic.

## Run instructions
Run in the root directory:
```
  cmake .
  make
  ./TerrariaLinux
```

## Recording instructions
Run in the root directory
```
  ffmpeg -video_size 800x600 -framerate 30 -f x11grab -i :0.0+100,100 output.mp4
```
