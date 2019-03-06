/*
 * Author: Yu-Shiang Yan
 *
 * Note: Image processing's parameter(Ex. version, camera parameters, error code)
 */
 
#ifndef IMAGE_PARAMS_H_INCLUDED
#define IMAGE_PARAMS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define PRINT_ERROR_CODE(e)\
                if(e)\
                {\
                    printf("error code:%X\n",e);\
                    return;\
                }

#define ERROR_CODE_LOG(e)\
                if(e)\
                {\
                    return e;\
                }


//#define DMVT_EXAMPLE_DEBUG

#ifdef DMVT_EXAMPLE_DEBUG
#define		CALL(func)	\
            {\
                DmvtErr	e;\
                e	= func;\
                if (e != LIBDMVT_NO_ERROR)\
                {\
                    printf("%s\n", dmvtGetErrInfo(e));\
                }\
            }\

#else
#define		CALL(func)	func;
#endif

#define dTRUE   1
#define dFALSE  0

#define CR_MAX_WIDTH 3072
#define CR_MAX_HEIGHT 2048
#define CR_MAX_PITCH_SIZE 3

/* vision error code */
typedef enum _eVisionError
{
    eIMAGE_PROCESS_IMG_INIT = 0x1001,
    eIMAGE_PROCESS_SAVE_IMG_SRC_INPUT,
    eIMAGE_PROCESS_SAVE_IMG,
    eIMAGE_PROCESS_READ_IMG_SRC_INPUT,
    eIMAGE_PROCESS_READ_IMG,
    eIMAGE_PROCESS_TRANDITIONAL_DETECTION_IMG_SRC_INPUT = 0x2001,
    eIMAGE_PROCESS_TRANDITIONAL_DETECTION,
    eIMAGE_PROCESS_ADAPTIVE_DETECTION_IMG_SRC_INPUT = 0x3001,
    eIMAGE_PROCESS_ADAPTIVE_DETECTION

} eVisionError_T;


#ifdef __cplusplus
}
#endif

#endif //
