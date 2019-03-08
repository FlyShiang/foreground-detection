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

#include <Image_Processing.h>
#include <Image_Params.h>
#include <Utility.h>


int FD_Histogram_Background(FD_Image*     backgroundImg,
                            FD_GMM_PARAM* gmmParam,
                            int           frameID)
{
    int exitCode  = dFALSE;

    if(backgroundImg == 0 || gmmParam == 0)
    {
        return eIMAGE_PROCESS_GMM_HIST_BACKGROUND_IMG_SRC_INPUT;
    }

    exitCode = FDAlgoHistogramBackground(backgroundImg->rawData,
                                        gmmParam->histRawData,
                                        backgroundImg->width,
                                        backgroundImg->height,
                                        frameID);

    if(exitCode)
    {
        return eIMAGE_PROCESS_GMM_HIST_BACKGROUND;
    }

    return exitCode;
}


int FD_Update_Background(FD_Image* runtimeImg,
                         FD_Image* backgroundImg)
{
    int exitCode = dFALSE;

    if(runtimeImg == 0 || backgroundImg == 0)
    {
        return eIMAGE_PROCESS_ADAPTIVE_DETECTION_IMG_SRC_INPUT;
    }


    exitCode = FDAlgoUpdateBackground(backgroundImg->rawData,
                                      runtimeImg->rawData,
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


    exitCode = FDAlgoTranditionalDetection(backgroundImg->rawData,
                                           runtimeImg->rawData,
                                           resultImg->rawData,
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

    exitCode = FDAlgoCVReadImg(srcImg->rawData,
                               &srcImg->width,
                               &srcImg->height,
                               str);

    if(exitCode)
    {
        return eIMAGE_PROCESS_READ_IMG;
    }

    return exitCode;
}

int FD_SaveAsImg(FD_Image*      image,
                 char*          img_str,
                 int            channel)
{
    int exitCode = dFALSE;

    if((image == 0) || (img_str == 0))
    {
        return eIMAGE_PROCESS_SAVE_IMG_SRC_INPUT;
    }

    exitCode = FDAlgoCVSaveAsImg(image->rawData,
                                 image->width,
                                 image->height,
                                 img_str,
                                 channel);

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

        (*image)->rawData = (unsigned char*)malloc((FD_MAX_WIDTH * FD_MAX_HEIGHT * FD_MAX_PITCH_SIZE));

        if((*image)->rawData == NULL)
        {
            return eIMAGE_PROCESS_IMG_INIT;
        }

        memset((*image)->rawData, 0, (FD_MAX_WIDTH * FD_MAX_HEIGHT * FD_MAX_PITCH_SIZE));

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
        if(image->rawData)
        {
            free(image->rawData);
        }

        free(image);
    }
}

int FD_GMM_Param_Init(FD_GMM_PARAM** gmmParam)
{
    int	exitCode = dFALSE,
        i        = 0;

    (*gmmParam)  = (FD_GMM_PARAM*)malloc(sizeof(FD_GMM_PARAM));

    if((*gmmParam))
    {
        memset((*gmmParam), 0, sizeof(FD_GMM_PARAM));

        (*gmmParam)->histRawData = (FD_GMM_RAW_DATA**)malloc((FD_MAX_WIDTH * FD_MAX_HEIGHT * FD_MAX_PITCH_SIZE) * sizeof(FD_GMM_RAW_DATA*));

        for(i = 0; i < FD_MAX_WIDTH * FD_MAX_HEIGHT * FD_MAX_PITCH_SIZE; i++)
        {
             (*gmmParam)->histRawData[i] = (FD_GMM_RAW_DATA*)malloc(FD_MAX_GMM_HIST_SIZE * sizeof(FD_GMM_RAW_DATA));

              memset(((*gmmParam)->histRawData[i]), FD_MAX_GMM_HIST_SIZE, sizeof(FD_GMM_RAW_DATA));
        }
    }
    else
    {
        return eIMAGE_PROCESS_GMM_PARAM_INIT;
    }

    return exitCode;
}

void FD_GMM_Param_Release(FD_GMM_PARAM* gmmParam)
{
    int i = 0;

    if(gmmParam)
    {
        if(gmmParam->histRawData)
        {
            for(i = 0; i < FD_MAX_WIDTH * FD_MAX_HEIGHT * FD_MAX_PITCH_SIZE; i++)
            {
                free(gmmParam->histRawData[i]);
            }

            free(gmmParam->histRawData);
        }

        free(gmmParam);
    }
}
