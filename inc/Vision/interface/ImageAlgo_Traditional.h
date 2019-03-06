/*
 * Author: Yu-Shiang Yan
 *
 * Note: Traditional foreground detection interface
 */

#ifndef IMAGEALGO_TRADITIONAL_H
#define IMAGEALGO_TRADITIONAL_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

int FDAlgoTranditionalDetection(unsigned char* backgroundRawData,
                                unsigned char* runtimeRawData,
                                unsigned char* resultRawData,
                                int            img_w,
                                int            img_h,
                                int*           resultImg_w,
                                int*           resultImg_h);


#ifdef __cplusplus
}
#endif

#endif

