
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <Image_Params.h>
#include <Utility.h>
#include <ImageAlgo_Adaptive.h>


int FDAlgoUpdateBackground(unsigned char* backgroundRawData,
                           unsigned char* runtimeRawData,
                           int            img_w,
                           int            img_h)
{

    int   exitCode = dFALSE,
          i = 0,
          j = 0;

    double adaptive_th = 0.9;

    for(j = 0; j < img_h; j++)
    {
        for(i = 0; i < img_w; i++)
        {
            backgroundRawData[j * img_w + i] = (int)(adaptive_th * backgroundRawData[j * img_w + i]
                + (1 - adaptive_th) * runtimeRawData[j * img_w + i]);
        }
    }

    return exitCode;
}
