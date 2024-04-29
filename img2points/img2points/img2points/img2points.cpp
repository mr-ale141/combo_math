#include "img2points.h"

using namespace std;

int main()
{
    std::string output_file_name = "c:/IPS/combo_math/lw4_delone/lw4_delone/points.txt";
    std::ofstream outFile(output_file_name);

    std::string image_path_points = "c:/IPS/combo_math/lw4_delone/lw4_delone/points.jpg";
    cv::Mat img_points = cv::imread(image_path_points, cv::IMREAD_GRAYSCALE);

    if (img_points.empty())
    {
        std::cout << "Could not read the image: " << image_path_points << std::endl;
        return 1;
    }


    cv::Mat img;
    cv::threshold(img_points, img, 50, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    for (auto cnt : contours)
    {
        double area = cv::contourArea(cnt);
        if (area > 3 && area < 10)
        {
            outFile << cnt[0].x << ' ' << cnt[0].y << std::endl;
        }
    }

    cv::imshow("Display window", img);
    int k = cv::waitKey(0);
    return 0;
}
