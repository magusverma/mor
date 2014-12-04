#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <queue>         
#include <fstream>

using namespace cv;
using namespace std;

Mat subtract(Mat img1,Mat img2){
    Mat output( img1.size(), img1.type(), CV_8UC3 );
    for(int i = 0;i < img1.rows;i++){
        for(int j = 0;j < img1.cols;j++){
                if(img2.at<uchar>(i,j) > img1.at<uchar>(i,j)){
                    output.at<uchar>(i,j) = img2.at<uchar>(i,j) - img1.at<uchar>(i,j);
                }
                else{
                    output.at<uchar>(i,j) = 0;
                }
            }
      }

    return (output);
}

int objects_found = 0;

Mat continous_areas(Mat img){
    int width = 3;
    Mat output( img.size(), img.type(), CV_8UC3 );
    queue<Point> all_object_points;
    for(int i = 0;i < img.rows  ; i++){
        for(int j = 0;j < img.cols  ; j++){
            if((int)img.at<uchar>(i,j)>0){
                all_object_points.push(Point(i,j));
            }
        }
    }
    objects_found = 0;
    while(!all_object_points.empty()){
        queue<Point> one_object_points;
        Point current = all_object_points.front();

        if((int)img.at<uchar>(current.x,current.y)>0){
            // would be zero if in past iteration came by
            ++objects_found;
            one_object_points.push( current );
            cout<<current.x<<" "<<current.y<<endl;
        }
        all_object_points.pop();        
        while(!one_object_points.empty()){
            Point now_at = one_object_points.front();
            one_object_points.pop();
            output.at<uchar>(now_at.x,now_at.y) = (uchar)(objects_found*100);
            for (int k = now_at.x-(width/2); k < now_at.x+(width/2); ++k)
            {
                for (int l = now_at.y-(width/2); l < now_at.y+width/2; ++l)
                {
                    cout<<"hi"<<(int)img.at<uchar>(k,l)<<" ,";
                    if(k==now_at.x && l==now_at.y) continue;
                    if((int)img.at<uchar>(k,l)>0){
                        cout<<"oh";
                        one_object_points.push(Point(k,l));
                        output.at<uchar>(k,l) = (uchar)(objects_found*100);
                        img.at<uchar>(k,l) = (uchar)0; // so as to not start a que for this point
                        cout<<img.at<uchar>(k,l)<<endl;
                    }
                }
            }
        }
    }
    cout << objects_found << endl;
    imshow("Objects",output);
    return output;
}

int main()
{
    system("./files.sh > file.txt");
    std::ifstream in("file.txt");
    std::vector<string> contents;
    string line;
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        cout << "Found Image "<< line << endl;
        contents.push_back(line);
    }
    if(contents.size()>1){
        cv::Mat objects_with_background = cv::imread(contents[2]);
        cv::Mat background = cv::imread("/home/neerav/iaproject/mor/output/output_median.tiff");
       cv::cvtColor(objects_with_background, objects_with_background, CV_BGR2GRAY);
        cv::cvtColor(background, background, CV_BGR2GRAY);
        cv::Mat objects_mask = subtract(objects_with_background,background);
        // cv::Mat objects_mask = objects_with_background - background;
        // cv::Mat objects_mask;
        // cv::cvtColor(objects, objects_mask, CV_BGR2GRAY);
        cv::threshold(objects_mask, objects_mask, 20, 255, 0);
        // imshow("image_with_objects",objects_with_background);
        // imshow("background",background);
        // imshow("Objects",objects);
        
        for (int i = 1; i < 30; ++i)
        {
            cv::dilate(objects_mask, objects_mask,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(i, i)) );
            cv::erode(objects_mask, objects_mask,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(i, i)) );
        }
        imshow("Objects Mask",objects_mask);
        continous_areas(objects_mask);
        // for (int i = 1; i < 100; ++i)
        // {
        //     cv::dilate(objects_mask, objects_mask,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
        //     cv::erode(objects_mask, objects_mask,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
        // }

        imshow("Objects Mask after closing",objects_mask);        
        // cv::dilate(bw, bw, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 7)));

    }  
    else{
        cout<<"No Input Images";
    }

    // cv::imshow("part3_hls_threshold", hls_img);    
    // imwrite("part3_hls_threshold.jpg",hls_img);
    cv::waitKey(0);
    return 0;
}