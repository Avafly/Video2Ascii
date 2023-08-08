# Video2Ascii

A simple C++ program to play videos in the terminal using ASCII characters as pixels.

This program extracts frames of a video by OpenCV and then maps the frame's pixels to corresponding ASCII characters. It subsequently renders these characters at the same frame rate as the original video. The program adaptively adjusts to determine the appropriate frame size and frame rate.

The code is thoroughly commented, making it easy to understand and customize as needed.

## Demo

<p align="center">
  <img src="./images/demo.gif">
</p>

## How to run

1. Build: `make`

2. Run: `./main <fps> <video address>`

   Ex) `./main 15 https://github.com/Avafly/ImageHostingService/raw/master/uPic/badapple.mp4`

*This program needs the OpenCV environment. You can verify if OpenCV is installed by `pkg-config --version opencv`.*

## Final

Each frame's duration is computed theoretically, yet there's a minor delay beyond the duration when actually rendering each frame. The accumulation of these delays can cause the playback to be slightly slower than the actual video, and this delay varies depending on the OS. Therefore, I've slightly reduced the value of `SEC_2_MSEC` in [Video2Ascii.hpp](https://github.com/Avafly/Video2Ascii/blob/main/include/Video2Ascii.hpp). You can adjust this value to compensate for the delay.