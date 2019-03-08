#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <Image_Params.h>
#include <Utility.h>
#include <ImageAlgo_GMM.h>


int FDAlgoHistogramBackground(unsigned char*    backgroundRawData,
                              FD_GMM_RAW_DATA** histRawData,
                              int               img_w,
                              int               img_h,
                              int               frameID)
{
    int exitCode = dFALSE,
        i        = 0,
        j        = 0;

    unsigned char *pY = backgroundRawData,
                  *pU = backgroundRawData + FD_MAX_WIDTH * FD_MAX_HEIGHT,
                  *pV = backgroundRawData + FD_MAX_WIDTH * FD_MAX_HEIGHT * 2;



    for(j = 0; j < img_h; j++)
    {
        for(i = 0; i < img_w; i++)
        {
           histRawData[j * img_w + i][frameID].RawDataY = *(pY + i);
           histRawData[j * img_w + i][frameID].RawDataU = *(pU + i);
           histRawData[j * img_w + i][frameID].RawDataV = *(pV + i);
        }

         pY += img_w;
         pU += img_w;
         pV += img_w;
    }

    return exitCode;
}
