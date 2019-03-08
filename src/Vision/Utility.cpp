
#include <Utility.h>
#include <Image_Params.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int FDAlgoCVReadImg(unsigned char*		raw_data,
                    int*              img_w,
                    int*              img_h,
                    char*             img_str)
{
    int             exitCode = dFALSE,
                    i = 0,
                    j = 0;

    const std::string    str(img_str);

    try
    {
        Mat img,
            yuv_img;

        img = imread(str);

        *img_h = img.rows;
        *img_w = img.cols;

        cvtColor(img, yuv_img, COLOR_BGR2YUV);

        unsigned char *pY = raw_data,
                      *pU = raw_data + FD_MAX_WIDTH * FD_MAX_HEIGHT,
                      *pV = raw_data + FD_MAX_WIDTH * FD_MAX_HEIGHT * 2;

        for(j = 0; j < img.rows; j++)
        {
            for(i = 0; i < img.cols; i++)
            {
               *(pY + i) = yuv_img.at<cv::Vec3b>(j,i)[0];
               *(pU + i) = yuv_img.at<cv::Vec3b>(j,i)[1];
               *(pV + i) = yuv_img.at<cv::Vec3b>(j,i)[2];
            }

            pY += img.cols;
            pU += img.cols;
            pV += img.cols;
        }
    }
    catch( cv::Exception& e )
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
        exitCode = dTRUE;
    }

    return exitCode;
}

int FDAlgoCVSaveAsImg(unsigned char*    raw_data,
                      int             	img_w,
                      int             	img_h,
                      char*           	img_str,
                      int               channel)
{
    int             exitCode = dFALSE;

    std::string     strTmp(img_str);

    std::string     strOutput;

    unsigned char* pRawData = 0;

    switch (channel)
    {
      case eIMAGE_Y:
        strOutput = "Y";
        strOutput += strTmp;
        pRawData = raw_data;
        break;
      case eIMAGE_U:
        strOutput = "U";
        strOutput += strTmp;
        pRawData = raw_data + FD_MAX_WIDTH * FD_MAX_HEIGHT;
        break;
      case eIMAGE_V:
        strOutput = "V";
        strOutput += strTmp;
        pRawData = raw_data + FD_MAX_WIDTH * FD_MAX_HEIGHT * 2;
        break;
      default:
        strOutput = "Y";
        strOutput += strTmp;
        break;
    }

    try
    {
        // create Mat
        Mat image(Size(img_w, img_h), CV_8UC1, pRawData, Mat::AUTO_STEP);

        // save as image
        imwrite(strOutput, image);
    }
    catch( cv::Exception& e )
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
        exitCode = dTRUE;
    }

    return exitCode;
}

int FDAlgoOtsu(unsigned char*    raw_data,
               int             	 img_w,
               int             	 img_h,
               int*              otsuTh)
{
    #define GRAYLEVEL 255

    int hist[GRAYLEVEL];
    double prob[GRAYLEVEL], omega[GRAYLEVEL]; /* prob of graylevels */
    double myu[GRAYLEVEL];   /* mean value for separation */
    double max_sigma, sigma[GRAYLEVEL]; /* inter-class variance */
    int i, x, y; /* Loop variable */
    int threshold; /* threshold for binarization */

    /* Histogram generation */
    for (i = 0; i < GRAYLEVEL; i++) hist[i] = 0;
    for (y = 0; y < img_h; y++)
      for (x = 0; x < img_w; x++) {
        hist[raw_data[y*img_w + x]]++;
      }
    /* calculation of probability density */
    for ( i = 0; i < GRAYLEVEL; i ++ ) {
      prob[i] = (double)hist[i] / (img_h * img_w);
    }

    /* omega & myu generation */
    omega[0] = prob[0];
    myu[0] = 0.0;       /* 0.0 times prob[0] equals zero */
    for (i = 1; i < GRAYLEVEL; i++) {
      omega[i] = omega[i-1] + prob[i];
      myu[i] = myu[i-1] + i*prob[i];
    }

    /* sigma maximization
       sigma stands for inter-class variance
       and determines optimal threshold value */
    threshold = 0;
    max_sigma = 0.0;
    for (i = 0; i < GRAYLEVEL-1; i++) {
      if (omega[i] != 0.0 && omega[i] != 1.0)
        sigma[i] = pow(myu[GRAYLEVEL-1]*omega[i] - myu[i], 2) /
    (omega[i]*(1.0 - omega[i]));
      else
        sigma[i] = 0.0;
      if (sigma[i] > max_sigma) {
        max_sigma = sigma[i];
        threshold = i;
      }
    }

    *otsuTh = threshold;

    return 0;
}


