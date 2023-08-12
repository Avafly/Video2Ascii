#ifndef Video2Ascii_hpp
#define Video2Ascii_hpp

#include <opencv2/opencv.hpp>

class Video2Ascii {
public:
    void clear_console();

    /**
     * Description:
     * nearest_divisor() finds the nearest divisor of N to a given input value.
     *
     * Arguments:
     * @param N: The integer for which the nearest divisor is to be found.
     * @param input: The reference value to which the nearest divisor of N should be close.
     *
     * Returns:
     * An integer representing the nearest divisor of N to the input value.
     */
    int nearest_divisor(int N, int input);


    /**
     * Description:
     * set_width_and_height() determines playback height and width.
     *
     * Arguments:
     * @param video: A reference to VideoCapture object
     */
    void set_width_and_height(const cv::VideoCapture &video);

    /**
     * Description:
     * frame_to_ascii() converts a image to ascii code.
     *
     * Arguments:
     * @param frame: Image to be converted
     *
     * Return value:
     * The converted ascii code.
     */
    std::string frame_to_ascii(cv::Mat frame);

    /**
     * Description:
     * video_to_ascii() converts the video to ascii code using frame_to_ascii() and prints ascii code at the same frame rate as the video.
     *
     * Arguments:
     * @param video_path: Pathname of the video file
     * @param desired_fps: Display fps
     */
    void video_to_ascii(const std::string &video_path, int desired_fps=12);

private:
    // slightly reduce the value of SEC_2_MSEC to compensate for the print latency effect
    static constexpr int SEC_2_MSEC = 996000;
    // playback  width and height
    int width;
    int height;
};

#endif /* Video2Ascii_hpp */
