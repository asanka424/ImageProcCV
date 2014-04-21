#ifndef ERRORNUMBERS_H
#define ERRORNUMBERS_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  0 - No errors                                                       //
//  Positive - Warnings. Program could go further But it can fail       //
//  Negative - Errors. Program cannot proceed                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#define NO_ERRORS 0 //no errors occures. This is used in every module
#define EXCEPTION_OCCURED -1 //exception. used in every module

// -99 to 99 values dedicated for ImageProcCV

//Errors
#define EMPTY_IMAGE_MTRX -2 //empty image in matrix
#define INV_IMG_TYPE -3 //invalid type of image
#define NO_ENTRY_PNT_FOUND -4 //no entry point found for countour
#define NEXT_PNT_NOT_FOUND -5 //couldn't find next point
#define NOT_CONVERGING -6 //looping forward but doesnt end the loop
#define LUT_IS_INVALID -7 //lookup table is invalid
#define OUTPUT_IMG_EMPTY -8 //output image is empty
#define INPUT_IMG_EMPTY -9 //input image is empty
#define NO_INPUT_POINTS -10 //input vector doesn't have any points

//Warnings
#define BW_IMG_NO_INTROR_PIXELS 26 //no interior pixels present in bw image
#define NO_LABELS_SELECTED 27  //no label could be selected for the given point
#define EQUAL_INTENSITY_PIXELS 28 //all the pixels in the image has same intensity level
#define BW_IMG_NO_FGRND_PIXELS 25 //binary image does not have any foreground pixels



//-199 to -100 and 100 to 199  used by GVF_Snake

//Errors
#define MODULE_NOT_READY -100
#define ERROR_IN_MATRIX_INVERSION -101
#define INPUT_PNTS_EXCEEDS_MAX -102
//Warnings



//-299 to -200 and 200 to 299  used by DCE_Centreline

//Errors
#define PARAMETERS_NOT_READY -200
#define START_POINT_NOT_FOUND -201
#define NEXT_POINT_NOT_FOUND  -202
#define NEGETIVE_VALUE_IN_RELEVANCES -203
#define NO_SKEL_POINTS_FOUND -204
#define NO_BRANCHES_FOUND -205
#define INVALID_NUMBER_OF_BRANCHES -206
#define CONTOUR_NOT_AVAILABLE -207
#define ENDPOINTS_NOT_AVAILABLE -208

//-399 to -300 and 300 to 399 used by CurveInterpolation

//Errors
#define NOT_ENOUGH_INPUT_POINTS -300
#define NOT_ENOUGH_SAMPLE_POINTS -301

//Warnings
#define INPUT_POINTS_RETURNED_AS_INTERPOLATED_POINTS 300;

//-499 to -400 and 400 to 499 used by Ranker

//Errors
#define DIR_NOT_EXISTS -400
#define EMPTY_TRAINED_SET -401
#define RANKING_NOT_FINISHED -402

//-599 to -500 and 500 to 599 used by SisterChromatidSeparation

#define NO_CONTOUR_POINTS -500
#define NO_TELOMERE_POINTS -501
#define INV_NUMBEROF_CANDIDATE_POINTS -502
#define INV_INDICES_FOR_TELOMERES -503
#define ERROR_IN_TELOMERE_POINTS -504


#endif // ERRORNUMBERS_H
