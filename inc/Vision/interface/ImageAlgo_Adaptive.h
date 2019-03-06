/*
 * Author: Yu-Shiang Yan
 *
 * Note: Adaptive foreground detection interface
 */

#ifndef IMAGEALGO_ADAPTIVE_H
#define IMAGEALGO_ADAPTIVE_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

int FDAlgoUpdateBackground(unsigned char* backgroundRawData,
                           unsigned char* runtimeRawData,
                           int            img_w,
                           int            img_h);


#ifdef __cplusplus
}
#endif

#endif
