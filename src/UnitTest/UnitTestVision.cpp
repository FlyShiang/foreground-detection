/*
 * Vision Module Unit Testing
 * 
 * Author: Yu-Shiang Yan
 * Overview: First we will get calibration information(Ex. hand coordinates, chessboard pattern). Last we will caculate camera
 * calibration and hnad-eye calibration.
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <Image_Processing.h>
#include <Image_Params.h>

#define dFOREGROUND_DETECTION_IMG_PATH "../../../testImg/test1/"

#define dTRADITIONAL_RESULT_IMG_NAME "resultTRA.png"
#define dTRADITIONAL_BACKGROUND_IMG_NAME "Fountain1150.bmp"
#define dTRADITIONAL_RUNTIME_IMG_NAME "Fountain1165.bmp"


#define dADAPTIVE_RESULT_IMG_NAME "resultADAP.png"
#define dADAPTIVE_FIRST_BACKGROUND_IMG_NAME "Fountain1150.bmp"
#define dADAPTIVE_RUNTIME_IMG_PREFIX "Fountain"
#define dADAPTIVE_FIRST_IMG_ID 1150
#define dADAPTIVE_NUM 15


static void adaptive_test(int argc, char* argv[])
{
    int     ret       = 0,
            testID    = 0,
            i         = 0;

    FD_Image    *runtime_img    = 0,
                *background_img = 0,
                *result_img     = 0;

    std::string testStr,
                saveImgStr;

    /* initialize image resource using Heap memory */
    ret = FD_Image_Resource_Init(&runtime_img);
    PRINT_ERROR_CODE(ret)

    ret = FD_Image_Resource_Init(&background_img);
    PRINT_ERROR_CODE(ret)

    ret = FD_Image_Resource_Init(&result_img);
    PRINT_ERROR_CODE(ret)

    /* read image */
    testStr = dFOREGROUND_DETECTION_IMG_PATH;

    testStr += dADAPTIVE_FIRST_BACKGROUND_IMG_NAME;

    ret = FD_ReadImg(background_img,
                     (char*)testStr.c_str());
    PRINT_ERROR_CODE(ret)

    for(i = 0; i < dADAPTIVE_NUM; i++)
    {
        testStr = dFOREGROUND_DETECTION_IMG_PATH;

        testStr += dADAPTIVE_RUNTIME_IMG_PREFIX;

        testID = dADAPTIVE_FIRST_IMG_ID + i;

        testStr += std::to_string(testID);

        testStr += ".bmp";

        ret = FD_ReadImg(runtime_img,
                       (char*)testStr.c_str());
        PRINT_ERROR_CODE(ret)

        ret = FD_Update_Background(runtime_img,
                                   background_img);
        PRINT_ERROR_CODE(ret)
    }

    testStr = dFOREGROUND_DETECTION_IMG_PATH;

    testStr += dADAPTIVE_RUNTIME_IMG_PREFIX;

    testID = dADAPTIVE_FIRST_IMG_ID + i;

    testStr += std::to_string(testID);

    testStr += ".bmp";

    ret = FD_ReadImg(runtime_img,
                   (char*)testStr.c_str());
    PRINT_ERROR_CODE(ret)

    ret = FD_Tranditional_Detection(runtime_img,
                                    background_img,
                                    result_img);
    PRINT_ERROR_CODE(ret)

    saveImgStr = dADAPTIVE_RESULT_IMG_NAME;

    ret = FD_SaveAsImg(result_img,
                       (char*)saveImgStr.c_str());
    PRINT_ERROR_CODE(ret)

    // release resource
    FD_Image_Resource_Release(runtime_img);

    FD_Image_Resource_Release(background_img);

    FD_Image_Resource_Release(result_img);

    return;
}

static void traditional_test(int argc, char* argv[])
{
    int     ret       = 0;

    FD_Image    *runtime_img    = 0,
                *background_img = 0,
                *result_img     = 0;

    std::string testStr,
                saveImgStr;

    /* initialize image resource using Heap memory */
    ret = FD_Image_Resource_Init(&runtime_img);
    PRINT_ERROR_CODE(ret)

    ret = FD_Image_Resource_Init(&background_img);
    PRINT_ERROR_CODE(ret)

    ret = FD_Image_Resource_Init(&result_img);
    PRINT_ERROR_CODE(ret)

    /* read image */
    testStr = dFOREGROUND_DETECTION_IMG_PATH;

    testStr += dTRADITIONAL_BACKGROUND_IMG_NAME;

    ret = FD_ReadImg(background_img,
                     (char*)testStr.c_str());
    PRINT_ERROR_CODE(ret)

    testStr = dFOREGROUND_DETECTION_IMG_PATH;

    testStr += dTRADITIONAL_RUNTIME_IMG_NAME;

    ret = FD_ReadImg(runtime_img,
                     (char*)testStr.c_str());
    PRINT_ERROR_CODE(ret)

    ret = FD_Tranditional_Detection(runtime_img,
                                    background_img,
                                    result_img);

    saveImgStr = dTRADITIONAL_RESULT_IMG_NAME;

    ret = FD_SaveAsImg(result_img,
                       (char*)saveImgStr.c_str());
    PRINT_ERROR_CODE(ret)

    // release resource
    FD_Image_Resource_Release(runtime_img);

    FD_Image_Resource_Release(background_img);

    FD_Image_Resource_Release(result_img);

    return;
}

int main(int argc, char* argv[])
{
    printf("My pid is: %d\n", getpid());

    traditional_test(argc,argv);

    adaptive_test(argc,argv);

    return 0;
}

