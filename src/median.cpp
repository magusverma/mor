#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

#define input_img_count 5
// #define input_img_count 13

using namespace std;
using namespace cv;

void median(Mat* src_imgs, Mat& dst);
int find_median_of_vector(vector<int> vals);
int find_mode_of_vector(vector<int> vals);

int main(int argc, char const *argv[])
{
    Mat src_imgs[input_img_count];
    // src_imgs[0] = imread("../input/vlcsnap-2014-11-20-14h22m55s6.tiff", IMREAD_COLOR);
    // src_imgs[1] = imread("../input/vlcsnap-2014-11-20-14h22m55s8.tiff", IMREAD_COLOR);
    // src_imgs[2] = imread("../input/vlcsnap-2014-11-20-14h22m55s10.tiff", IMREAD_COLOR);
    // src_imgs[3] = imread("../input/vlcsnap-2014-11-20-14h22m55s12.tiff", IMREAD_COLOR);
    // src_imgs[4] = imread("../input/vlcsnap-2014-11-20-14h22m55s14.tiff", IMREAD_COLOR);
    // src_imgs[5] = imread("../input/vlcsnap-2014-11-20-14h22m56s16.tiff", IMREAD_COLOR);
    // src_imgs[6] = imread("../input/vlcsnap-2014-11-20-14h22m56s18.tiff", IMREAD_COLOR);
    // src_imgs[7] = imread("../input/vlcsnap-2014-11-20-14h22m56s20.tiff", IMREAD_COLOR);
    // src_imgs[8] = imread("../input/vlcsnap-2014-11-20-14h22m56s22.tiff", IMREAD_COLOR);
    // src_imgs[9] = imread("../input/vlcsnap-2014-11-20-14h22m56s24.tiff", IMREAD_COLOR);
    // src_imgs[10] = imread("../input/vlcsnap-2014-11-20-14h22m57s26.tiff", IMREAD_COLOR);
    // src_imgs[11] = imread("../input/vlcsnap-2014-11-20-14h22m57s28.tiff", IMREAD_COLOR);
    // src_imgs[12] = imread("../input/vlcsnap-2014-11-20-14h22m57s30.tiff", IMREAD_COLOR);

    src_imgs[0] = imread("../input_color_1.jpg", IMREAD_COLOR);
    src_imgs[1] = imread("../input_color_2.jpg", IMREAD_COLOR);
    src_imgs[2] = imread("../input_color_3.jpg", IMREAD_COLOR);
    src_imgs[3] = imread("../input_color_4.jpg", IMREAD_COLOR);
    src_imgs[4] = imread("../input_color_5.jpg", IMREAD_COLOR);

    Mat median_img = Mat(src_imgs[0].size(), src_imgs[0].type());
    median(src_imgs, median_img);

    if (!src_imgs[0].data) {
        cout << src_imgs[0].size() << "no data in median_img" << endl;
    } else {
        // imshow("median", median_img);
        imwrite("../output/output_median.tiff", median_img);
    }

    // waitKey(0);
    return 0;
}

void median(Mat* src_imgs, Mat& dst) {
    Mat color_channels[input_img_count][3];

    for (int n = 0; n < input_img_count; ++n) {
        split(src_imgs[n], color_channels[n]);
    }

    Mat channel_b = Mat(color_channels[0][0].size(), color_channels[0][0].type());
    Mat channel_g = Mat(color_channels[0][1].size(), color_channels[0][1].type());
    Mat channel_r = Mat(color_channels[0][2].size(), color_channels[0][2].type());

    for (int i = 0; i < src_imgs[0].rows; ++i) {
        for (int j = 0; j < src_imgs[0].cols; ++j) {
            vector<int> pixels[3];
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < input_img_count; ++l) {
                    pixels[k].push_back(color_channels[l][k].at<uchar>(i, j));
                }
            }

            channel_b.at<uchar>(i, j) = find_median_of_vector(pixels[0]);
            channel_g.at<uchar>(i, j) = find_median_of_vector(pixels[1]);
            channel_r.at<uchar>(i, j) = find_median_of_vector(pixels[2]);

        }   
    }

    Mat to_merge[] = {channel_b, channel_g, channel_r};
    merge(to_merge, 3, dst);
}

int find_median_of_vector(vector<int> vals) {
    nth_element(vals.begin(), vals.begin()+vals.size()/2, vals.end());
    return vals[vals.size()/2];
}

int find_mode_of_vector(vector<int> vals) {
    vector<int> freq_table(256,0);
    for( int i=0; i<vals.size(); ++i ) {
      freq_table[vals[i]]++;
    }
    return max_element( freq_table.begin(), freq_table.end() ) - freq_table.begin();
}












