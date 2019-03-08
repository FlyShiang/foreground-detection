/*
 * Author: Yu-Shiang Yan
 *
 * Note: Utility Interface(Ex. read CSV file, write CSV file)
 */
 
#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

int FDAlgoCVReadImg(unsigned char*    raw_data,
                    int*              width,
                    int*              height,
                    char*             str);


int FDAlgoCVSaveAsImg(unsigned char*    raw_data,
                      int               width,
                      int               height,
                      char*             str,
                      int               channel);


int FDAlgoOtsu(unsigned char*    raw_data,
               int             	 img_w,
               int             	 img_h,
               int*              otsuTh);

#ifdef __cplusplus
}
#endif

#endif //
