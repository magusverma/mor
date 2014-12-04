#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <fstream>

#define input_img_count_const 5
int input_img_count =5;

using namespace std;
using namespace cv;

void median(Mat* src_imgs, Mat& dst);
void selective_median(Mat* src_imgs, Mat &mask, Mat& dst, int p, int q);
int find_median_of_vector(vector<int> vals);
int find_mode_of_vector(vector<int> vals);

int main(int argc, char const *argv[])
{
    system("./files.sh > file.txt");
    std::ifstream in("file.txt");
    std::vector<string> contents;
    string line;
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        cout << line << endl;
        contents.push_back(line);
    }
    input_img_count = contents.size();
    Mat src_imgs[input_img_count_const];
    for(int i=0;i<input_img_count;i++){
        src_imgs[i] = imread(contents[i]);
    }

    // // ========================================================
    // cout << num_moving_objects << " moving objects found" << endl;
    // cout << "enter how many objects you want to remove: ";
    // int num_objects_to_remove;
    // cin >> num_objects_to_remove;
    // if (num_objects_to_remove > num_moving_objects)
    // {
    //     cout << "incorrect input" << endl;
    //     return -1;
    // }
    // cout << "select regions to be removed: ";
    // vector<int> regions;
    // for (int i = 0; i < num_objects_to_remove; ++i)
    // {
    //     int tmp;
    //     cin >> tmp;
    //     regions.push_back(tmp);
    // }
    // Mat dst = Mat(src_imgs[0].size(), src_imgs[0].type());
    // for (int i = 0; i < dst.rows; ++i)
    // {
    //     for (int j = 0; j < dst.cols; ++j)
    //     {
    //         /* code */
    //     }
    // }
    // // ========================================================
    // Mat dst = Mat(src_imgs[0].size(), src_imgs[0].type());
    // Mat color_channels[3];
    // split(src_imgs[0], color_channels);
    // for (int i = 0; i < src_imgs[0].rows; ++i)
    // {
    //     for (int j = 0; j < src_imgs[0].cols; ++j)
    //     {
    //         for (int k = 0; k < 3; ++k)
    //         {
    //             color_channels[k].at<uchar>(i, j) = 255;
    //         }
    //     }
    // }
    // Mat to_merge[] = {color_channels[0], color_channels[1], color_channels[2]};
    // merge(to_merge, 3, dst);
    // imshow("test", dst);
    // waitKey(0);
    // src_imgs[0] = imread("../input/vlcsnap-2014-11-20-14h22m55s6.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[1] = imread("../input/vlcsnap-2014-11-20-14h22m55s8.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[2] = imread("../input/vlcsnap-2014-11-20-14h22m55s10.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[3] = imread("../input/vlcsnap-2014-11-20-14h22m55s12.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[4] = imread("../input/vlcsnap-2014-11-20-14h22m55s14.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[5] = imread("../input/vlcsnap-2014-11-20-14h22m56s16.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[6] = imread("../input/vlcsnap-2014-11-20-14h22m56s18.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[7] = imread("../input/vlcsnap-2014-11-20-14h22m56s20.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[8] = imread("../input/vlcsnap-2014-11-20-14h22m56s22.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[9] = imread("../input/vlcsnap-2014-11-20-14h22m56s24.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[10] = imread("../input/vlcsnap-2014-11-20-14h22m57s26.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[11] = imread("../input/vlcsnap-2014-11-20-14h22m57s28.tiff", CV_LOAD_IMAGE_COLOR);
    // src_imgs[12] = imread("../input/vlcsnap-2014-11-20-14h22m57s30.tiff", CV_LOAD_IMAGE_COLOR);

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
    Mat color_channels[input_img_count_const][3];

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
            // cout << color_channels[0][0].type() << endl;
            // if (i == 110 && j == 300)
            // {
            //     for (int m = 0; m < pixels[1].size(); ++m)
            //     {
            //         cout << pixels[1][i] << endl;
            //     }
            // }
            int mid_val = find_median_of_vector(pixels[1]);
            int mid_val_index = -1;
            for (int i = 0; i < pixels[1].size(); ++i)
            {
                if (pixels[1][i] == mid_val)
                {
                    mid_val_index = i;
                    break;
                }
            }
            if (mid_val_index == -1)
            {
                cout << "mid_val_index not found" << endl;
            } else {
                channel_b.at<uchar>(i, j) = pixels[0][mid_val_index];
                channel_g.at<uchar>(i, j) = pixels[1][mid_val_index];
                channel_r.at<uchar>(i, j) = pixels[2][mid_val_index];
            }

        }   
    }

    Mat to_merge[] = {channel_b, channel_g, channel_r};
    merge(to_merge, 3, dst);
}

void selective_median(Mat* src_imgs, Mat& mask, Mat& dst, int p, int q) {
    Mat color_channels[input_img_count_const][3];

    for (int n = 0; n < input_img_count; ++n) {
        split(src_imgs[n], color_channels[n]);
    }

    Mat channel_b = Mat(color_channels[0][0].size(), color_channels[0][0].type());
    Mat channel_g = Mat(color_channels[0][1].size(), color_channels[0][1].type());
    Mat channel_r = Mat(color_channels[0][2].size(), color_channels[0][2].type());

    for (int i = 0; i < src_imgs[0].rows; ++i) {
        for (int j = 0; j < src_imgs[0].cols; ++j) {
            if (mask.at<uchar>(i, j) != p)
            {
                channel_b.at<uchar>(i, j) = color_channels[q][0].at<uchar>(i, j);
                channel_g.at<uchar>(i, j) = color_channels[q][1].at<uchar>(i, j);
                channel_r.at<uchar>(i, j) = color_channels[q][2].at<uchar>(i, j);
                continue;
            }
            vector<int> pixels[3];
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < input_img_count; ++l) {
                    pixels[k].push_back(color_channels[l][k].at<uchar>(i, j));
                }
            }
            int mid_val = find_median_of_vector(pixels[1]);
            int mid_val_index = -1;
            for (int i = 0; i < pixels[1].size(); ++i)
            {
                if (pixels[1][i] == mid_val)
                {
                    mid_val_index = i;
                    break;
                }
            }
            if (mid_val_index == -1)
            {
                cout << "mid_val_index not found" << endl;
            } else {
                channel_b.at<uchar>(i, j) = pixels[0][mid_val_index];
                channel_g.at<uchar>(i, j) = pixels[1][mid_val_index];
                channel_r.at<uchar>(i, j) = pixels[2][mid_val_index];
            }

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












