#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

#define input_img_count 13

using namespace std;
using namespace cv;

void median(Mat* src_imgs, Mat& dst);

int main(int argc, char const *argv[])
{
    Mat src_imgs[input_img_count];
    src_imgs[0] = imread("../input/vlcsnap-2014-11-20-14h22m55s6.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[1] = imread("../input/vlcsnap-2014-11-20-14h22m55s8.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[2] = imread("../input/vlcsnap-2014-11-20-14h22m55s10.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[3] = imread("../input/vlcsnap-2014-11-20-14h22m55s12.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[4] = imread("../input/vlcsnap-2014-11-20-14h22m55s14.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[5] = imread("../input/vlcsnap-2014-11-20-14h22m56s16.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[6] = imread("../input/vlcsnap-2014-11-20-14h22m56s18.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[7] = imread("../input/vlcsnap-2014-11-20-14h22m56s20.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[8] = imread("../input/vlcsnap-2014-11-20-14h22m56s22.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[9] = imread("../input/vlcsnap-2014-11-20-14h22m56s24.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[10] = imread("../input/vlcsnap-2014-11-20-14h22m57s26.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[11] = imread("../input/vlcsnap-2014-11-20-14h22m57s28.tiff", CV_LOAD_IMAGE_COLOR);
    src_imgs[12] = imread("../input/vlcsnap-2014-11-20-14h22m57s30.tiff", CV_LOAD_IMAGE_COLOR);

    // imshow("first", src_imgs[8]);

    Mat median_img = Mat(src_imgs[0].size(), src_imgs[0].type());
    median(src_imgs, median_img);

    if (!src_imgs[0].data) {
        cout << src_imgs[0].size() << "no data in median_img" << endl;
    } else {
        imshow("median", median_img);
    }

    waitKey(0);
    return 0;
}

void median(Mat* src_imgs, Mat& dst) {
    Mat color_channels[input_img_count][3];

    for (int n = 0; n < input_img_count; ++n)
    {
        split(src_imgs[n], color_channels[n]);
    }
    imshow("0", color_channels[0][0]);
    imshow("1", color_channels[0][0]);
    imshow("2", color_channels[0][0]);

    Mat channel_b = Mat(color_channels[0][0].size(), color_channels[0][0].type());
    Mat channel_g = Mat(color_channels[0][1].size(), color_channels[0][1].type());
    Mat channel_r = Mat(color_channels[0][2].size(), color_channels[0][2].type());

    for (int i = 0; i < src_imgs[0].rows; ++i)
    {
        for (int j = 0; j < src_imgs[0].cols; ++j)
        {
            vector<int> pixels[3];
            for (int k = 0; k < 3; ++k)
            {
                for (int l = 0; l < input_img_count; ++l)
                {
                    pixels[k].push_back(color_channels[l][k].at<uchar>(i, j));
                }
            }

            nth_element(pixels[0].begin(), pixels[0].begin()+pixels[0].size()/2, pixels[0].end());
            channel_b.at<uchar>(i, j) = pixels[0][input_img_count/2];
            nth_element(pixels[1].begin(), pixels[1].begin()+pixels[1].size()/2, pixels[1].end());
            channel_g.at<uchar>(i, j) = pixels[1][input_img_count/2];
            nth_element(pixels[2].begin(), pixels[2].begin()+pixels[2].size()/2, pixels[2].end());
            channel_r.at<uchar>(i, j) = pixels[2][input_img_count/2];
        }   
    }

    Mat to_merge[] = {channel_b, channel_g, channel_r};
    merge(to_merge, 3, dst);
}














