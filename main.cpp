#include "opencv2/ximgproc/segmentation.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <ctime>
 
using namespace cv;
using namespace cv::ximgproc::segmentation;
 


int main(int argc, char** argv) {
    std::string picName;
    std::cout << "Enter your picture name:" << std::endl;
    std::cin >> picName;

    // read image
    Mat im = imread(picName);
    if(!im.data){
        return -1;
    }
    
    cv::setUseOptimized(true);
    cv::setNumThreads(4);
 
    
    // resize image
    int newHeight = 200;
    int newWidth = im.cols*newHeight/im.rows;
    resize(im, im, Size(newWidth, newHeight));
 
    // create Selective Search Segmentation Object using default parameters
    Ptr<SelectiveSearchSegmentation> ss = createSelectiveSearchSegmentation();
    // set input image on which we will run segmentation
    ss->setBaseImage(im);
 
    //ss->switchToSelectiveSearchFast();

    ss->switchToSelectiveSearchQuality();

 
    // run selective search segmentation on input image
    std::vector<Rect> rects;
    ss->process(rects);
    std::cout << "Total Number of Region Proposals: " << rects.size() << std::endl;
 
    // number of region proposals to show
    int numShowRects = 100;
    // increment to increase/decrease total number
    // of reason proposals to be shown
    int increment = 50;
 
    while(1) {
        // create a copy of original image
        Mat imOut = im.clone();
 
        // itereate over all the region proposals
        for(int i = 0; i < rects.size(); i++) {
            if (i < numShowRects) {
                rectangle(imOut, rects[i], Scalar(0, 255, 0));
            }
            else {
                break;
            }
        }
 
        // show output
        imshow("Output", imOut);
 
        // record key press
        int k = waitKey();
 
        // m is pressed
        if (k == 109) {
            // increase total number of rectangles to show by increment
            numShowRects += increment;
        }
        // l is pressed
        else if (k == 108 && numShowRects > increment) {
            // decrease total number of rectangles to show by increment
            numShowRects -= increment;
        }
        // q is pressed
        else if (k == 113) {
            break;
        }
    }
    return 0;
}