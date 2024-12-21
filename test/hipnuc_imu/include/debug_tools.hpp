/**
 * 命名空间包含所有自定义的debug工具
*/
#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

namespace debug_tools{

    // void onMouseHSV(int event, int x, int y, int flags, void* userdata) {
    // /**
    //  * 可以输出鼠标所在区域的HSV/BRG值
    //  * 循环外部定义回调 cv::setMouseCallback("window_name", onMouse, &image)
    // */
    //     if (event == cv::EVENT_MOUSEMOVE) {
    //         cv::Mat* frame = reinterpret_cast<cv::Mat*>(userdata);
    //         if (x >= 0 && x < frame->cols && y >= 0 && y < frame->rows) {
    //             cv::Mat hsv;
    //             cv::cvtColor(*frame, hsv, cv::COLOR_BGR2HSV);
    //             cv::Vec3b pixel = hsv.at<cv::Vec3b>(y, x);
    //             int H = pixel[0];
    //             int S = pixel[1];
    //             int V = pixel[2];
                
    //             cv::Mat display(50, 500, CV_8UC3, cv::Scalar(255, 0, 0));
    //             // cv::Mat display;
    //             // frame->copyTo(display);
    //             std::string text = "H: " + std::to_string(H) + " S: " + std::to_string(S) + " V: " + std::to_string(V);
    //             cv::putText(display, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    //             cv::namedWindow("dialHSV", cv::WINDOW_NORMAL);
    //             // cv::Rect roi(0, 0, 500, 50); // 定义裁剪区域(x, y, width, height)
    //             // cv::Mat cropped = display(roi); // 裁剪图像
    //             cv::imshow("dialHSV", display);
    //         }
    //     }
    // }

    // void onMouseBGR(int event, int x, int y, int flags, void* userdata) {
    // /**
    //  * 可以输出鼠标所在区域的HSV/BRG值
    //  * 循环外部定义回调 cv::setMouseCallback("window_name", onMouse, &image)
    // */
    //     if (event == cv::EVENT_MOUSEMOVE) {
    //         cv::Mat* frame = reinterpret_cast<cv::Mat*>(userdata);
    //         if (x >= 0 && x < frame->cols && y >= 0 && y < frame->rows) {
    //             // 获取 BGR 像素值
    //             cv::Vec3b pixel = frame->at<cv::Vec3b>(y, x);
    //             int B = pixel[0]; // 蓝色通道
    //             int G = pixel[1]; // 绿色通道
    //             int R = pixel[2]; // 红色通道
                
    //             cv::Mat display;
    //             frame->copyTo(display);
    //             std::string text = "B: " + std::to_string(B) + " G: " + std::to_string(G) + " R: " + std::to_string(R);
    //             cv::putText(display, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    //             cv::namedWindow("dial", cv::WINDOW_NORMAL);
    //             cv::Rect roi(0, 0, 500, 50); // 定义裁剪区域(x, y, width, height)
    //             cv::Mat cropped = display(roi); // 裁剪图像
    //             cv::imshow("dial", cropped);
    //         }
    //     }
    // }

    void printError(const std::string& message) {
    /**
     * 在终端打印红色字体
    */
        // ANSI 转义序列设置文本颜色为红色
        std::cout << "\033[31m" << message << "\033[0m" << std::endl; // 31 是红色，0 是重置颜色
    }

    void printWarning(const std::string& message) {
    /**
     * 在终端打印黄色字体
     */
    // ANSI 转义序列设置文本颜色为黄色
    std::cout << "\033[33m" << message << "\033[0m" << std::endl; // 33 是黄色，0 是重置颜色
    }

    class Timer {
    /**
     * 这是一个代码运行计时器
     * 计算 start() ~ end() 之间的代码块用时
    */
    public:
        double duration_seconds;
        double duration_milliseconds;
        double duration_microseconds;

    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        std::string code_block_detail;

        int count = -1; // 运行次数
        double time = 0; // 运行时间
    public:
        
        void start(std::string code_block_detail_) 
        {
            /**
             * 开始计时
             * 传入 string 字符串用来解释代码块信息
             * 会在控制台输出传入的字符串
            */
            start_time = std::chrono::high_resolution_clock::now();
            code_block_detail = code_block_detail_;
        }

        void end()
        {
            /**
             * 结束计时
             * 打印用户定义的代码块注释和用时
             * 单位有 秒/毫秒/微秒
            */
            end_time = std::chrono::high_resolution_clock::now();
            auto duration = end_time - start_time;

            // 以秒为单位
            long long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

            // 转换为毫秒
            long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

            // 转换为微秒
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

            duration_seconds = double(std::chrono::duration_cast<std::chrono::seconds>(duration).count());
            duration_milliseconds = double(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
            duration_microseconds = double(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());

            std::cout << code_block_detail + ": "
                    //   << seconds << " seconds, "
                        // << milliseconds << " milliseconds, "
                        << microseconds << " microseconds\n" 
                        << std::endl;
        }

        void getAverageTime(int warmup_count, int run_count, std::string save_csv_path) {
            // warmup_count 热身次数
            // run_count 运行次数
            if (count > -(warmup_count) && count < 0) { count--; }
            else if (count == -(warmup_count)) {
                count = 0;
            }
            else { 
                count++; 
                time += duration_microseconds;
                std::ofstream file("save_csv_path", std::ios::out | std::ios::app);

                // 检查文件是否成功打开
                if (!file.is_open()) {
                    std::cerr << "Failed to open the file." << std::endl;
                    exit(1);
                }
                file << count << ": " << duration_microseconds << std::endl;
                file.close();
            }
            if (count == run_count) {
                std::cout << "\nwarmup_count: " << warmup_count << std::endl;
                std::cout << "run_count: " << run_count << std::endl;
                std::cout << "average_time: " << time / run_count << "microseconds" << std::endl;
                
                exit(0);
            }
        }

        void getAverageTime(int warmup_count, int run_count) {
            // warmup_count 热身次数
            // run_count 运行次数
            if (count > -(warmup_count) && count < 0) { count--; }
            else if (count == -(warmup_count)) {
                count = 0;
            }
            else { 
                count++; 
                time += duration_microseconds;
            }
            if (count == run_count) {
                std::cout << "\nwarmup_count: " << warmup_count << std::endl;
                std::cout << "run_count: " << run_count << std::endl;
                std::cout << "average_time: " << time / run_count << std::endl;
                exit(0);
            }
        }
        
    };
    
} // namespace debug_tools