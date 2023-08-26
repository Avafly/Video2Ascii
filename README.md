# Video2Ascii

A simple C++ program to play videos in the terminal using ASCII characters as pixels.

This program extracts frames of a video by OpenCV and then maps the frame's pixels to corresponding ASCII characters. It subsequently renders these characters at the same frame rate as the original video. The program adaptively adjusts to determine the appropriate frame size and frame rate.

The code is thoroughly commented, making it easy to understand and customize as needed.

## How to run

1. Build: `make`

2. Run: `./main <fps> <video address>`

   Ex) `./main 15 https://github.com/Avafly/ImageHostingService/raw/master/uPic/badapple.mp4`

*This program needs the OpenCV environment. You can verify if OpenCV is installed by `pkg-config --version opencv`.*

## Demo

Play spinning donut in Terminal

<p align="center">
  <img src="https://github.com/Avafly/ImageHostingService/raw/master/uPic/rot_donutt.gif" width="450">
</p>



Play Bad Apple in Terminus on iPadOS

<p align="center">
  <img src="https://github.com/Avafly/ImageHostingService/raw/master/uPic/bad_apple.gif" width="450">
</p>


Play rotating earth in Visual Studio Console on Windows 10

<p align="center">
  <img src="https://github.com/Avafly/ImageHostingService/raw/master/uPic/earth_vstudio_win10.gif" width="450">
</p>

## Final

While each frame duration is theoretically computed, rendering introduces minor latency, potentially slowing playback. This latency varies across devices.

Therefore, I updated the latency compensation code. The principle behind it is to play 3s of blank frames and compute the latency for each frame to make compensations. It effectively eliminated the latency on a Debian, but somehow, there's still a slight delay when running on my M1 Mac.

~~Therefore, I've slightly reduced the value of `SEC_2_MSEC` in [Video2Ascii.hpp](https://github.com/Avafly/Video2Ascii/blob/main/include/Video2Ascii.hpp). You can adjust this value to compensate for the delay.~~