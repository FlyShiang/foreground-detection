/*
 * Author: Yu-Shiang Yan
 *
 * Note: GMM foreground detection interface
 */

#ifndef IMAGEALGO_GMM_H
#define IMAGEALGO_GMM_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct struct_FD_GMM_RAW_DATA
{
    unsigned char	    RawDataY;
    unsigned char	    RawDataU;
    unsigned char	    RawDataV;

} FD_GMM_RAW_DATA;


typedef struct struct_FD_GMM_PARAM
{
    FD_GMM_RAW_DATA	    **histRawData;

} FD_GMM_PARAM;

int FDAlgoHistogramBackground(unsigned char*  backgroundRawData,
                              FD_GMM_RAW_DATA** histRawData,
                              int             img_w,
                              int             img_h,
                              int             frameID);


#ifdef __cplusplus
}
#endif

#endif
