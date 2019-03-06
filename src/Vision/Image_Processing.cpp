/*
 * Author: Yu-Shiang Yan
 *
 * Note: Image processing interface
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <ImageAlgo_Traditional.h>
#include <Image_Processing.h>
#include <Image_Params.h>
#include <Utility.h>

int FD_Update_Background(FD_Image* runtimeImg,
                         FD_Image* backgroundImg)
{
    int exitCode = dFALSE;

    if(runtimeImg == 0 || backgroundImg == 0)
    {
        return eIMAGE_PROCESS_ADAPTIVE_DETECTION_IMG_SRC_INPUT;
    }


    exitCode = FDAlgoUpdateBackground(backgroundImg->raw_data,
                                      runtimeImg->raw_data,
                                      runtimeImg->width,
                                      runtimeImg->height);

    if(exitCode)
    {
        return eIMAGE_PROCESS_ADAPTIVE_DETECTION;
    }

    return exitCode;
}


int FD_Tranditional_Detection(FD_Image* runtimeImg,
                              FD_Image* backgroundImg,
                              FD_Image* resultImg)
{
    int exitCode = dFALSE;

    if(runtimeImg == 0 || backgroundImg == 0 || resultImg == 0)
    {
        return eIMAGE_PROCESS_TRANDITIONAL_DETECTION_IMG_SRC_INPUT;
    }


    exitCode = FDAlgoTranditionalDetection(backgroundImg->raw_data,
                                           runtimeImg->raw_data,
                                           resultImg->raw_data,
                                           runtimeImg->width,
                                           runtimeImg->height,
                                           &resultImg->width,
                                           &resultImg->height);

    if(exitCode)
    {
        return eIMAGE_PROCESS_TRANDITIONAL_DETECTION;
    }

    return exitCode;
}


int FD_ReadImg(FD_Image*   srcImg,
               char*       str)
{
    int exitCode = dFALSE;

    if(srcImg == 0)
    {
        return eIMAGE_PROCESS_READ_IMG_SRC_INPUT;
    }

    exitCode = FDAlgoCVReadImg(srcImg->raw_data,
                               &srcImg->width,
                               &srcImg->height,
                               &srcImg->pitch,
                               str);

    if(exitCode)
    {
        return eIMAGE_PROCESS_READ_IMG;
    }

    return exitCode;
}

int FD_SaveAsImg(FD_Image* image,
                 char*	   img_str)
{
    int exitCode = dFALSE;

    if((image == 0) || (img_str == 0))
    {
        return eIMAGE_PROCESS_SAVE_IMG_SRC_INPUT;
    }

    exitCode = FDAlgoCVSaveAsImg(image->raw_data,
                                 image->width,
                                 image->height,
                                 image->pitch,
                                 img_str);

    if(exitCode)
    {
        return eIMAGE_PROCESS_SAVE_IMG;
    }
	
    return exitCode;
}

int FD_Image_Resource_Init(FD_Image** image)
{
    int	exitCode = dFALSE;

    (*image)  = (FD_Image*)malloc(sizeof(FD_Image));

    if((*image))
    {
        memset((*image), 0, sizeof(FD_Image));

        (*image)->raw_data = (unsigned char*)malloc((CR_MAX_WIDTH * CR_MAX_HEIGHT * CR_MAX_PITCH_SIZE));

        if((*image)->raw_data == NULL)
        {
            return eIMAGE_PROCESS_IMG_INIT;
        }

        memset((*image)->raw_data, 0, (CR_MAX_WIDTH * CR_MAX_HEIGHT * CR_MAX_PITCH_SIZE) );

        (*image)->mask_data = (unsigned char*)malloc(CR_MAX_WIDTH * CR_MAX_HEIGHT);

        if((*image)->mask_data == NULL)
        {
            return eIMAGE_PROCESS_IMG_INIT;
        }

        memset((*image)->mask_data, 255, CR_MAX_WIDTH * CR_MAX_HEIGHT);
    }
    else
    {
        return eIMAGE_PROCESS_IMG_INIT;
    }

    return exitCode;
}

void FD_Image_Resource_Release(FD_Image* image)
{
    if(image)
    {
        if(image->raw_data)
        {
            free(image->raw_data);
        }

        if(image->mask_data)
        {
            free(image->mask_data);
        }

        free(image);
    }
}
