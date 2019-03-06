/*
 * Author: Yu-Shiang Yan
 *
 * Note: Image processing interface
 */
 
#ifndef IMAGE_PROCESSING_H_INCLUDED
#define IMAGE_PROCESSING_H_INCLUDED

#include <ImageAlgo_Traditional.h>
#include <ImageAlgo_Adaptive.h>
#include <ImageAlgo_GMM.h>
#include <Utility.h>

#ifdef __cplusplus
extern "C" {
#endif

/* image */
typedef struct struct_FD_Image
{
    unsigned char	    *raw_data;
    unsigned char           *mask_data;
    int             	    width;
    int             	    height;
    int			    pitch;
    int                     roi_shape;

} FD_Image;

/**
 * @brief   read image
 * @param	image       [in]    image structure(raw data, width, etc.)
 * @param	img_str     [in]    image file name
 * @return	error code  [out]
 */
int FD_ReadImg(FD_Image*   srcImg,
               char*       str);

/**
 * @brief   save as image
 * @param	image       [in]    image structure(raw data, width, etc.)
 * @param	img_str     [in]    image file name
 * @return	error code  [out]
 */			
int FD_SaveAsImg(FD_Image*  image,
                 char*      img_str);

					  
/**
 * @brief   initialize image resoure(image's memory)
 * @param	image       [in]    image structure(raw data, width, etc.)
 * @return	error code  [out]
 */
int FD_Image_Resource_Init(FD_Image** image);

/**
 * @brief   release image resoure
 * @param	image   [in]    image structure(raw data, width, etc.)
 */
void FD_Image_Resource_Release(FD_Image* image);



int FD_Tranditional_Detection(FD_Image* runtimeImg,
                              FD_Image* backgroundImg,
                              FD_Image* resultImg);


int FD_Update_Background(FD_Image* runtimeImg,
                         FD_Image* backgroundImg);

#ifdef __cplusplus
}
#endif

#endif //