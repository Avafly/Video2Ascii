#include "Video2Ascii.hpp"
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

void Video2Ascii::clear_console() {
    // clear console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int Video2Ascii::measure_latency(int desired_fps) {
    int test_sec = 3;
    int frame_size = test_sec * desired_fps;
    std::string test_frame;
    for(int i = 0; i < this->height; ++i) {
        test_frame += std::string(this->width, ' ');
        test_frame += '\n';
    }
    std::vector<std::string> test_frames(frame_size, test_frame);

    // start time
    auto start = std::chrono::high_resolution_clock::now();

    auto frame_duration_msec = std::chrono::microseconds(static_cast<int>((1.0 / desired_fps) * this->SEC_2_MSEC));
    for(const auto &frame : test_frames) {
        std::cout << "\033[H";
        // std::cout << "\033[2J\033[H";
        std::cout << frame << std::flush;
        std::this_thread::sleep_for(frame_duration_msec);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return static_cast<int>((duration.count() - test_sec * 1000000) / static_cast<double>(frame_size));
}

int Video2Ascii::nearest_divisor(int N, int input) {
    if (input <= 0) { return -1; }
    int lower = input, upper = input;
    while(N % lower) { --lower; }
    while(N % upper) { ++upper; }
    return (input - lower >= upper - input) ? upper : lower;
}

void Video2Ascii::set_width_and_height(const cv::VideoCapture &video) {
    // get video size
    int video_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int video_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);

    // get terminal size
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    int tmnl_width = ws.ws_col;
    int tmnl_height = ws.ws_row;

    // compute playback height and width
    double aspect_ratio = static_cast<double>(video_width) / static_cast<double>(video_height) / 0.5;
    this->width = std::min(video_width, tmnl_width);
    this->height = static_cast<int>(this->width / aspect_ratio);
    if(this->height > tmnl_height) {
        this->height = tmnl_height;
        this->width = static_cast<int>(this->height * aspect_ratio);
    }
}


std::string Video2Ascii::frame_to_ascii(cv::Mat frame) {
    std::string ascii_chars = "@%#*+=-:. ";
    std::string ascii_frame;

    // resize frame
    cv::resize(frame, frame, cv::Size(this->width, this->height));

    for(int y = 0; y < this->height; ++y) {
        for(int x = 0; x < this->width; ++x) {
            // map pixel values to ascii chars
            ascii_frame += ascii_chars[frame.at<uchar>(y, x) / 32];
        }
        ascii_frame += "\n";
    }

    return ascii_frame;
}


void Video2Ascii::video_to_ascii(const std::string &video_path, int desired_fps) {
    cv::VideoCapture video(video_path);
    if(!video.isOpened()) {
        std::cerr << "Error opening video file " << video_path << std::endl;
        video.release();
        return;
    }

    // determine playback height and width
    this->set_width_and_height(video);

    // get frame rate
    int original_fps = static_cast<int>(video.get(cv::CAP_PROP_FPS));
    desired_fps = std::min(desired_fps, original_fps);
    desired_fps = nearest_divisor(original_fps, desired_fps);
    int frame_skip = std::max(1, original_fps / desired_fps);
    // show frame info
    std::cout << "original fps: " << original_fps
              << ", desired fps: " << desired_fps
              << std::endl;

    int frame_count = 0;
    std::vector<std::string> ascii_frames;
    std::cout << "Coverting ..." << std::endl;
    // convert frame to ascii
    while(1) {
        // read next frame
        cv::Mat frame;
        video >> frame;
        ++frame_count;
        if(frame.empty()) {
            break;
        }
        if(frame_count % frame_skip != 0) {
            continue;
        }

        // convert frame to grayscale
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        // convert gray frame to ascii
        ascii_frames.push_back(this->frame_to_ascii(frame));
    }

    clear_console();

    // compensate for latency
    std::ios::sync_with_stdio(false);
    int latency = measure_latency(desired_fps);
    double frame_duration = 1.0 / desired_fps;
    auto frame_duration_msec = std::chrono::microseconds(static_cast<int>(frame_duration * this->SEC_2_MSEC) - latency);

    // print frames
    for(const auto &ascii_frame : ascii_frames) {
        // move cursor to the top-left corner
        std::cout << "\033[H";

        // print ascii frame to console
        std::cout << ascii_frame << std::flush;

        // wait for the duration of the frame
        std::this_thread::sleep_for(frame_duration_msec);
    }

    clear_console();

    video.release();
}
