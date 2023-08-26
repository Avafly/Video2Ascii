#include <iostream>
#include <string>
#include "Video2Ascii.hpp"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <fps> <video address>" << std::endl;
        return 1;
    }
    int desired_fps = std::stoi(argv[1]);
    if(desired_fps < 1) {
        std::cerr << "Input Error: Frames cannot be less than 1" << std::endl;
        return 1;
    }

    Video2Ascii v2a;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    v2a.video_to_ascii(argv[2], desired_fps);

    return 0;
}
