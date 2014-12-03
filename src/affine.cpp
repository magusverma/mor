#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void get_src_points(Mat &img, int src_points[][2]);

int main(int argc, char const *argv[])
{
    Mat img = imread("../affine_input/one.jpg");
    if (!img.data)
    {
        cout << "img not read correctly" << endl;
    } else {
        cout << img.size() << endl;
    }

    int src_points[16][2];
    get_src_points(img, src_points);
    for (int i = 0; i < 16; ++i) {
        cout << src_points[i][0] << " ";
        cout << src_points[i][1] << endl;
    }
    cout << endl;

    

    // waitKey(0);
    // destroyAllWindows();
    return 0;
}

void get_src_points(Mat &img, int src_points[][2]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            src_points[i*4+j][0] = (img.cols*(i+1))/5;
            src_points[i*4+j][1] =  (img.rows*(j+1))/5;
        }
    }
}