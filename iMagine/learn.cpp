//
//  learn.cpp
//  iMagine
//
//  Created by Corey on 15 07, 2016.
//  Copyright © 2016 Corey. All rights reserved.
//

#include "learn.hpp"
#include "operators.hpp"

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv/ml.h>

#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;



vector<Mat> learn::getData(Mat points){
    namedWindow("TEST", CV_WINDOW_AUTOSIZE);
    Mat image = imread("0.jpg", CV_32FC1);
    threshold(image, image, 100, 255, 0);
    resize(image, image, Size(image.rows, image.rows));
    
    // I don't know why, but I get a segmentation error 11
    //      if I don't open the image immediately.
    imshow("TEST", image);
//    destroyWindow("TEST");
    waitKey(10);
    
    return image;
}

Mat learn::labelData(Mat points){
    Mat labels(points.rows, 1, CV_32FC1);
    for (int i=0; i<2; i++){
        Mat image = learn::getData(points).at(i);
    
    for(int i = 0; i < points.rows; i++) {
        float x = points.at<float>(i,0) * points.rows;
        float y = points.at<float>(i,1) * points.rows;
        
        labels.at<float>(i, 0) = image.at<int>(Point(x,y)) >= 0 ? -1 : 1;
    }
    }
    return labels;
}



CvANN_MLP learn::create_mlp(Mat trainingData, Mat trainingClasses, Mat testData, Mat testClasses) {
    
    Mat layers = cv::Mat(4, 1, CV_32SC1);
    
    layers.row(0) = cv::Scalar(2);
    layers.row(1) = cv::Scalar(10);
    layers.row(2) = cv::Scalar(15);
    layers.row(3) = cv::Scalar(1);
    
    CvANN_MLP mlp;
    CvANN_MLP_TrainParams params;
    CvTermCriteria criteria;
    criteria.max_iter = 100;
    criteria.epsilon = 0.00001f;
    criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
    params.train_method = CvANN_MLP_TrainParams::BACKPROP;
    params.bp_dw_scale = 0.05f;
    params.bp_moment_scale = 0.05f;
    params.term_crit = criteria;
    
    mlp.create(layers);
    
    // train
    mlp.train(trainingData, trainingClasses, Mat(), Mat(), params);
    
    cv::Mat response(1, 1, CV_32FC1);
    cv::Mat predicted(testClasses.rows, 1, CV_32F);
    for(int i = 0; i < testData.rows; i++) {
        cv::Mat response(1, 1, CV_32FC1);
        cv::Mat sample = testData.row(i);
        
        mlp.predict(sample, response);
        predicted.at<float>(i,0) = response.at<float>(0,0);
    }
    operators::plot_binary(testData, predicted, "Predictions");
    return mlp;
}


Mat learn::prepareResponses(int size){
    Mat response = Mat(200, 200, CV_32FC1);
    for (int i=0; i<size; i++)
        response.at<float>(0, i) = (float)i;
    return response;
}




// Turns a single file into a vector of matrices
// This file contains 300 samples of 32x32 binary images of digits
//vector<vector<Mat>> prepareData(){
void learn::prepareData(){
    // Declare datasets
    vector<vector<Mat>>    classEnum;   // 0, 1, 2 ... 9
    vector<Mat>            sampleEnum;  // For each class (digit) we'll have many samples
    Mat sample = Mat(32, 32, CV_8U);    // Matrix used for each sample
    char valIn;
    
    // Read from file
    ifstream readFile ("optdigits-orig.cv");

    if(readFile.is_open())
    {
        while (!readFile.good()){
    for(int row = 0; row < 32; row++){            // Height = 32
        for (int col = 0; col < 32; col++){       // Width  = 32
                readFile >> valIn;
                sample.at<int>(row, col) = (int)valIn*255;
                cout << valIn;
                }
            cout << endl;
            }
        }
    }
    else cout << "test failed" << endl;
    
    namedWindow("TEST", CV_WINDOW_AUTOSIZE);
    imshow("TEST", sample);
    
    
//   return classEnum;
}



