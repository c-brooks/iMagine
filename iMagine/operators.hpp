//
//  operators.hpp
//  iMagine
//
//  Created by Corey on 2016-06-29.
//  Copyright © 2016 Corey. All rights reserved.
//

#ifndef operators_hpp
#define operators_hpp

#include <stdio.h>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

class operators {
private:
    static Mat grey, sobelIm;
    
public:
    static Mat edgeDetect(Mat src);
    static Mat gblur(Mat src, int kernLength);
    static void help();
};
#endif // End operators.h