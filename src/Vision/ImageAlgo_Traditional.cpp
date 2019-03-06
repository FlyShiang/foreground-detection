
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <Image_Params.h>
#include <Utility.h>
#include <ImageAlgo_Traditional.h>


int FDAlgoTranditionalDetection(unsigned char* backgroundRawData,
                                unsigned char* runtimeRawData,
                                unsigned char* resultRawData,
                                int            img_w,
                                int            img_h,
                                int*           resultImg_w,
                                int*           resultImg_h)
{

    int   exitCode = dFALSE,
          i = 0,
          j = 0,
          otsuTh = 0;

    for(j = 0; j < img_h; j++)
    {
        for(i = 0; i < img_w; i++)
        {
            resultRawData[j * img_w + i] = abs(backgroundRawData[j * img_w + i] - runtimeRawData[j * img_w + i]);
        }
    }

    exitCode = FDAlgoOtsu(resultRawData,
                          img_w,
                          img_h,
                          &otsuTh);

    for(j = 0; j < img_h; j++)
    {
        for(i = 0; i < img_w; i++)
        {
            if(resultRawData[j * img_w + i] > otsuTh)
            {
                resultRawData[j * img_w + i] = 255;
            }
            else
            {
                resultRawData[j * img_w + i] = 0;
            }
        }
    }

    *resultImg_w = img_w;
    *resultImg_h = img_h;

    return exitCode;
}
