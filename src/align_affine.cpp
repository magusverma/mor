#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    Mat one = imread("../align_input/one.jpg");
    if (!one.data)
    {
        cout << "one not read correctly" << endl;
    }

    Mat two = imread("../align_input/two.jpg/");
    if (!two.data)
    {
        cout << "two not read correctly" << endl; 
    }

    imshow("one", one);
    imshow("two", two);

    waitKey(0);
    destroyAllWindows();
    return 0;
}