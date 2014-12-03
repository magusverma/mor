/**
 * @file SURF_FlannMatcher
 * @brief SURF detector + descriptor + FLANN Matcher
 * @author A. Huaman
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

 #define input_img_count_const 5
 int input_img_count = 5;

using namespace cv;
using namespace std;

void readme();
bool compare_Dmatches(DMatch i, DMatch j);

/**
 * @function main
 * @brief Main function
 */
int main( int argc, char** argv )
{
  system("./raw_files.sh > raw_file.txt");
  ifstream in("raw_file.txt");
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
  for(int i=0;i<input_img_count_const;i++){
      src_imgs[i] = imread(contents[i]);
  }
  imwrite("../lotus_input/input1.jpg", src_imgs[0]);

  Mat img_2 = imread( contents[0], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_color_2 = src_imgs[0];
  for (int i = 1; i < input_img_count_const; ++i)
  {

    Mat img_1 = imread( contents[i], CV_LOAD_IMAGE_GRAYSCALE );

    Mat img_color_1 = src_imgs[i];

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector( minHessian );

    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector.detect( img_1, keypoints_1 );
    detector.detect( img_2, keypoints_2 );

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute( img_1, keypoints_1, descriptors_1 );
    extractor.compute( img_2, keypoints_2, descriptors_2 );

    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );

    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_1.rows; i++ )
    { double dist = matches[i].distance;
      if( dist < min_dist ) min_dist = dist;
      if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
    //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
    //-- small)
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;

    for( int i = 0; i < descriptors_1.rows; i++ )
    { if( matches[i].distance <= max(2*min_dist, 0.02) )
      { good_matches.push_back( matches[i]); }
    }

    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    // imshow( "Good Matches", img_matches );

    // int best_i = 0;
    // int best_j = 1;
    // int best_k = 2;
    Mat best_warp;
    double least_shear = 99999999;

      Point2f aff_pts_1[3];
      Point2f aff_pts_2[3];
    for( int i = 0; i < 3; i++ )
    // for( int i = 0; i < (int)good_matches.size(); i++ )
    { 
      // printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d ------ good_matches.distance: %f  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx, good_matches[i].distance ); 
      // cout << keypoints_1[good_matches[i].queryIdx].pt << ",";
      // cout << keypoints_2[good_matches[i].trainIdx].pt << endl;

      aff_pts_1[i] = Point2f((int)keypoints_1[good_matches[i].queryIdx].pt.x,
        (int)keypoints_1[good_matches[i].queryIdx].pt.y);

      aff_pts_2[i] = Point2f((int)keypoints_2[good_matches[i].trainIdx].pt.x,
        (int)keypoints_2[good_matches[i].trainIdx].pt.y);

      best_warp = getAffineTransform(aff_pts_1,aff_pts_2);
    }

    for (int i = 0; i < good_matches.size(); ++i)
    {
      for (int j = i+1; j < good_matches.size(); ++j)
      {
        for (int k = j+1; k < good_matches.size(); ++k)
        {
          Point2f aff_pts_1[3];
          Point2f aff_pts_2[3];
          
          aff_pts_1[0] = Point2f((int)keypoints_1[good_matches[i].queryIdx].pt.x,
            (int)keypoints_1[good_matches[i].queryIdx].pt.y);
          aff_pts_1[1] = Point2f((int)keypoints_1[good_matches[j].queryIdx].pt.x,
            (int)keypoints_1[good_matches[j].queryIdx].pt.y);
          aff_pts_1[2] = Point2f((int)keypoints_1[good_matches[k].queryIdx].pt.x,
            (int)keypoints_1[good_matches[k].queryIdx].pt.y);

          aff_pts_2[0] = Point2f((int)keypoints_2[good_matches[i].trainIdx].pt.x,
            (int)keypoints_2[good_matches[i].trainIdx].pt.y);
          aff_pts_2[1] = Point2f((int)keypoints_2[good_matches[j].trainIdx].pt.x,
            (int)keypoints_2[good_matches[j].trainIdx].pt.y);
          aff_pts_2[2] = Point2f((int)keypoints_2[good_matches[k].trainIdx].pt.x,
            (int)keypoints_2[good_matches[k].trainIdx].pt.y);

          Mat warp_dest(img_color_1.size(),img_color_1.type());
    
          Mat warp_mat = getAffineTransform(aff_pts_1,aff_pts_2);

          double err = (warp_mat.at<double>(0, 1)*warp_mat.at<double>(0, 1)) + \
            (warp_mat.at<double>(1, 0)*warp_mat.at<double>(1, 0));
          if (err < least_shear)
          {
            least_shear = err;
            best_warp = warp_mat;
          }
        }
      }
    }
    if (best_warp.at<double>(0,0) < 0.01)
    {
      // Point2f aff_pts_1[3];
      // Point2f aff_pts_2[3];
      for( int i = 0; i < 3; i++ )
      // for( int i = 0; i < (int)good_matches.size(); i++ )
      { 
        // printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d ------ good_matches.distance: %f  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx, good_matches[i].distance ); 
        // cout << keypoints_1[good_matches[i].queryIdx].pt << ",";
        // cout << keypoints_2[good_matches[i].trainIdx].pt << endl;

        aff_pts_1[i] = Point2f((int)keypoints_1[good_matches[i].queryIdx].pt.x,
          (int)keypoints_1[good_matches[i].queryIdx].pt.y);

        aff_pts_2[i] = Point2f((int)keypoints_2[good_matches[i].trainIdx].pt.x,
          (int)keypoints_2[good_matches[i].trainIdx].pt.y);
      }
      best_warp = getAffineTransform(aff_pts_1,aff_pts_2);
    }

    // std::sort (good_matches.begin(), good_matches.end(), compare_Dmatches);


    // aff_pts_1[0] = Point2f((int)keypoints_1[good_matches[0].queryIdx].pt.x,
    //   (int)keypoints_1[good_matches[0].queryIdx].pt.y);
    // aff_pts_1[1] = Point2f((int)keypoints_1[good_matches[1].queryIdx].pt.x,
    //   (int)keypoints_1[good_matches[1].queryIdx].pt.y);
    // aff_pts_1[2] = Point2f((int)keypoints_1[good_matches[2].queryIdx].pt.x,
    //   (int)keypoints_1[good_matches[2].queryIdx].pt.y);

    // aff_pts_2[0] = Point2f((int)keypoints_2[good_matches[0].trainIdx].pt.x,
    //   (int)keypoints_2[good_matches[0].trainIdx].pt.y);
    // aff_pts_2[0] = Point2f((int)keypoints_2[good_matches[1].trainIdx].pt.x,
    //   (int)keypoints_2[good_matches[1].trainIdx].pt.y);
    // aff_pts_2[0] = Point2f((int)keypoints_2[good_matches[2].trainIdx].pt.x,
    //   (int)keypoints_2[good_matches[2].trainIdx].pt.y);


    // for (int i = 0; i < 3; ++i)
    // {
    //   cout << aff_pts_1[i] << ", ";
    //   cout << aff_pts_2[i] << endl;
    // }

    Mat warp_dest(img_color_1.size(),img_color_1.type());
    
    // Mat warp_mat = getAffineTransform(aff_pts_1,aff_pts_2);

    // cout << warp_mat << endl;
    // // warp_mat.at<double>(0, 0) = 1;
    // // warp_mat.at<double>(0, 1) = 0;
    // // warp_mat.at<double>(1, 0) = 0;
    // // warp_mat.at<double>(1, 1) = 1;
    cout << best_warp << endl;

    warpAffine(img_color_1,warp_dest,best_warp,warp_dest.size());
    // imshow("affined", warp_dest);

    imwrite("../lotus_input/input" + to_string(i+1) + ".jpg", warp_dest);
  }
  // waitKey(0);

  return 0;
}

bool compare_Dmatches(DMatch i, DMatch j) {
  return i.distance > j.distance;
}

/**
 * @function readme
 */
void readme()
{ std::cout << " Usage: ./SURF_FlannMatcher <img1> <img2>" << std::endl; }