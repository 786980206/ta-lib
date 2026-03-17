/* ta_func.h — Generated header for standalone compilation.
 * Types come from ta_lib_types.h (hand-written).
 * Forward declarations are auto-generated per indicator.
 */
#ifndef TA_FUNC_H
#define TA_FUNC_H

#include "ta_lib_types.h"

/* Forward declarations for all indicators */
extern int TA_ACCBANDS_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ACCBANDS(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern TA_RetCode TA_ACCBANDS_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
#define TA_INT_ACCBANDS TA_ACCBANDS_Logic
extern TA_RetCode TA_S_ACCBANDS(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern TA_RetCode TA_S_ACCBANDS_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern int TA_ACOS_Lookback(void);
extern TA_RetCode TA_ACOS(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ACOS_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ACOS TA_ACOS_Logic
extern TA_RetCode TA_S_ACOS(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ACOS_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_AD_Lookback(void);
extern TA_RetCode TA_AD(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_AD_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_AD TA_AD_Logic
extern TA_RetCode TA_S_AD(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_AD_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ADD_Lookback(void);
extern TA_RetCode TA_ADD(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ADD_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ADD TA_ADD_Logic
extern TA_RetCode TA_S_ADD(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ADD_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ADOSC_Lookback(int optInFastPeriod, int optInSlowPeriod);
extern TA_RetCode TA_ADOSC(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int optInFastPeriod, int optInSlowPeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ADOSC_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int optInFastPeriod, int optInSlowPeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ADOSC TA_ADOSC_Logic
extern TA_RetCode TA_S_ADOSC(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int optInFastPeriod, int optInSlowPeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ADOSC_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int optInFastPeriod, int optInSlowPeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ADX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ADX(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ADX_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ADX TA_ADX_Logic
extern TA_RetCode TA_S_ADX(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ADX_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ADXR_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ADXR(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ADXR_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ADXR TA_ADXR_Logic
extern TA_RetCode TA_S_ADXR(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ADXR_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_APO_Lookback(int optInFastPeriod, int optInSlowPeriod, int optInMAType);
extern TA_RetCode TA_APO(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_APO_Logic(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_APO TA_APO_Logic
extern TA_RetCode TA_S_APO(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_APO_Logic(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_AROON_Lookback(int optInTimePeriod);
extern TA_RetCode TA_AROON(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outAroonDown[], double outAroonUp[]);
extern TA_RetCode TA_AROON_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outAroonDown[], double outAroonUp[]);
#define TA_INT_AROON TA_AROON_Logic
extern TA_RetCode TA_S_AROON(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outAroonDown[], double outAroonUp[]);
extern TA_RetCode TA_S_AROON_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outAroonDown[], double outAroonUp[]);
extern int TA_AROONOSC_Lookback(int optInTimePeriod);
extern TA_RetCode TA_AROONOSC(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_AROONOSC_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_AROONOSC TA_AROONOSC_Logic
extern TA_RetCode TA_S_AROONOSC(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_AROONOSC_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ASIN_Lookback(void);
extern TA_RetCode TA_ASIN(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ASIN_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ASIN TA_ASIN_Logic
extern TA_RetCode TA_S_ASIN(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ASIN_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ATAN_Lookback(void);
extern TA_RetCode TA_ATAN(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ATAN_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ATAN TA_ATAN_Logic
extern TA_RetCode TA_S_ATAN(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ATAN_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ATR_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ATR(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ATR_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ATR TA_ATR_Logic
extern TA_RetCode TA_S_ATR(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ATR_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_AVGDEV_Lookback(int optInTimePeriod);
extern TA_RetCode TA_AVGDEV(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_AVGDEV_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_AVGDEV TA_AVGDEV_Logic
extern TA_RetCode TA_S_AVGDEV(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_AVGDEV_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_AVGPRICE_Lookback(void);
extern TA_RetCode TA_AVGPRICE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_AVGPRICE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_AVGPRICE TA_AVGPRICE_Logic
extern TA_RetCode TA_S_AVGPRICE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_AVGPRICE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_BBANDS_Lookback(int optInTimePeriod, double optInNbDevUp, double optInNbDevDn, int optInMAType);
extern TA_RetCode TA_BBANDS(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDevUp, double optInNbDevDn, int optInMAType, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern TA_RetCode TA_BBANDS_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDevUp, double optInNbDevDn, int optInMAType, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
#define TA_INT_BBANDS TA_BBANDS_Logic
extern TA_RetCode TA_S_BBANDS(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDevUp, double optInNbDevDn, int optInMAType, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern TA_RetCode TA_S_BBANDS_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDevUp, double optInNbDevDn, int optInMAType, int *outBegIdx, int *outNBElement, double outRealUpperBand[], double outRealMiddleBand[], double outRealLowerBand[]);
extern int TA_BETA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_BETA(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_BETA_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_BETA TA_BETA_Logic
extern TA_RetCode TA_S_BETA(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_BETA_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_BOP_Lookback(void);
extern TA_RetCode TA_BOP(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_BOP_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_BOP TA_BOP_Logic
extern TA_RetCode TA_S_BOP(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_BOP_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_CCI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_CCI(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_CCI_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_CCI TA_CCI_Logic
extern TA_RetCode TA_S_CCI(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_CCI_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_CDL2CROWS_Lookback(void);
extern TA_RetCode TA_CDL2CROWS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL2CROWS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL2CROWS TA_CDL2CROWS_Logic
extern TA_RetCode TA_S_CDL2CROWS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL2CROWS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3BLACKCROWS_Lookback(void);
extern TA_RetCode TA_CDL3BLACKCROWS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3BLACKCROWS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3BLACKCROWS TA_CDL3BLACKCROWS_Logic
extern TA_RetCode TA_S_CDL3BLACKCROWS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3BLACKCROWS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3INSIDE_Lookback(void);
extern TA_RetCode TA_CDL3INSIDE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3INSIDE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3INSIDE TA_CDL3INSIDE_Logic
extern TA_RetCode TA_S_CDL3INSIDE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3INSIDE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3LINESTRIKE_Lookback(void);
extern TA_RetCode TA_CDL3LINESTRIKE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3LINESTRIKE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3LINESTRIKE TA_CDL3LINESTRIKE_Logic
extern TA_RetCode TA_S_CDL3LINESTRIKE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3LINESTRIKE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3OUTSIDE_Lookback(void);
extern TA_RetCode TA_CDL3OUTSIDE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3OUTSIDE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3OUTSIDE TA_CDL3OUTSIDE_Logic
extern TA_RetCode TA_S_CDL3OUTSIDE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3OUTSIDE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3STARSINSOUTH_Lookback(void);
extern TA_RetCode TA_CDL3STARSINSOUTH(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3STARSINSOUTH_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3STARSINSOUTH TA_CDL3STARSINSOUTH_Logic
extern TA_RetCode TA_S_CDL3STARSINSOUTH(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3STARSINSOUTH_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDL3WHITESOLDIERS_Lookback(void);
extern TA_RetCode TA_CDL3WHITESOLDIERS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDL3WHITESOLDIERS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDL3WHITESOLDIERS TA_CDL3WHITESOLDIERS_Logic
extern TA_RetCode TA_S_CDL3WHITESOLDIERS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDL3WHITESOLDIERS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLABANDONEDBABY_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLABANDONEDBABY(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLABANDONEDBABY_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLABANDONEDBABY TA_CDLABANDONEDBABY_Logic
extern TA_RetCode TA_S_CDLABANDONEDBABY(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLABANDONEDBABY_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLADVANCEBLOCK_Lookback(void);
extern TA_RetCode TA_CDLADVANCEBLOCK(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLADVANCEBLOCK_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLADVANCEBLOCK TA_CDLADVANCEBLOCK_Logic
extern TA_RetCode TA_S_CDLADVANCEBLOCK(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLADVANCEBLOCK_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLBELTHOLD_Lookback(void);
extern TA_RetCode TA_CDLBELTHOLD(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLBELTHOLD_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLBELTHOLD TA_CDLBELTHOLD_Logic
extern TA_RetCode TA_S_CDLBELTHOLD(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLBELTHOLD_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLBREAKAWAY_Lookback(void);
extern TA_RetCode TA_CDLBREAKAWAY(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLBREAKAWAY_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLBREAKAWAY TA_CDLBREAKAWAY_Logic
extern TA_RetCode TA_S_CDLBREAKAWAY(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLBREAKAWAY_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLCLOSINGMARUBOZU_Lookback(void);
extern TA_RetCode TA_CDLCLOSINGMARUBOZU(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLCLOSINGMARUBOZU_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLCLOSINGMARUBOZU TA_CDLCLOSINGMARUBOZU_Logic
extern TA_RetCode TA_S_CDLCLOSINGMARUBOZU(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLCLOSINGMARUBOZU_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLCONCEALBABYSWALL_Lookback(void);
extern TA_RetCode TA_CDLCONCEALBABYSWALL(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLCONCEALBABYSWALL_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLCONCEALBABYSWALL TA_CDLCONCEALBABYSWALL_Logic
extern TA_RetCode TA_S_CDLCONCEALBABYSWALL(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLCONCEALBABYSWALL_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLCOUNTERATTACK_Lookback(void);
extern TA_RetCode TA_CDLCOUNTERATTACK(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLCOUNTERATTACK_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLCOUNTERATTACK TA_CDLCOUNTERATTACK_Logic
extern TA_RetCode TA_S_CDLCOUNTERATTACK(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLCOUNTERATTACK_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLDARKCLOUDCOVER_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLDARKCLOUDCOVER(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLDARKCLOUDCOVER_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLDARKCLOUDCOVER TA_CDLDARKCLOUDCOVER_Logic
extern TA_RetCode TA_S_CDLDARKCLOUDCOVER(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLDARKCLOUDCOVER_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLDOJI_Lookback(void);
extern TA_RetCode TA_CDLDOJI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLDOJI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLDOJI TA_CDLDOJI_Logic
extern TA_RetCode TA_S_CDLDOJI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLDOJI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLDOJISTAR_Lookback(void);
extern TA_RetCode TA_CDLDOJISTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLDOJISTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLDOJISTAR TA_CDLDOJISTAR_Logic
extern TA_RetCode TA_S_CDLDOJISTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLDOJISTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLDRAGONFLYDOJI_Lookback(void);
extern TA_RetCode TA_CDLDRAGONFLYDOJI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLDRAGONFLYDOJI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLDRAGONFLYDOJI TA_CDLDRAGONFLYDOJI_Logic
extern TA_RetCode TA_S_CDLDRAGONFLYDOJI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLDRAGONFLYDOJI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLENGULFING_Lookback(void);
extern TA_RetCode TA_CDLENGULFING(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLENGULFING_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLENGULFING TA_CDLENGULFING_Logic
extern TA_RetCode TA_S_CDLENGULFING(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLENGULFING_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLEVENINGDOJISTAR_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLEVENINGDOJISTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLEVENINGDOJISTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLEVENINGDOJISTAR TA_CDLEVENINGDOJISTAR_Logic
extern TA_RetCode TA_S_CDLEVENINGDOJISTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLEVENINGDOJISTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLEVENINGSTAR_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLEVENINGSTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLEVENINGSTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLEVENINGSTAR TA_CDLEVENINGSTAR_Logic
extern TA_RetCode TA_S_CDLEVENINGSTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLEVENINGSTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLGAPSIDESIDEWHITE_Lookback(void);
extern TA_RetCode TA_CDLGAPSIDESIDEWHITE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLGAPSIDESIDEWHITE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLGAPSIDESIDEWHITE TA_CDLGAPSIDESIDEWHITE_Logic
extern TA_RetCode TA_S_CDLGAPSIDESIDEWHITE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLGAPSIDESIDEWHITE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLGRAVESTONEDOJI_Lookback(void);
extern TA_RetCode TA_CDLGRAVESTONEDOJI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLGRAVESTONEDOJI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLGRAVESTONEDOJI TA_CDLGRAVESTONEDOJI_Logic
extern TA_RetCode TA_S_CDLGRAVESTONEDOJI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLGRAVESTONEDOJI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHAMMER_Lookback(void);
extern TA_RetCode TA_CDLHAMMER(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHAMMER_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHAMMER TA_CDLHAMMER_Logic
extern TA_RetCode TA_S_CDLHAMMER(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHAMMER_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHANGINGMAN_Lookback(void);
extern TA_RetCode TA_CDLHANGINGMAN(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHANGINGMAN_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHANGINGMAN TA_CDLHANGINGMAN_Logic
extern TA_RetCode TA_S_CDLHANGINGMAN(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHANGINGMAN_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHARAMI_Lookback(void);
extern TA_RetCode TA_CDLHARAMI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHARAMI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHARAMI TA_CDLHARAMI_Logic
extern TA_RetCode TA_S_CDLHARAMI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHARAMI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHARAMICROSS_Lookback(void);
extern TA_RetCode TA_CDLHARAMICROSS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHARAMICROSS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHARAMICROSS TA_CDLHARAMICROSS_Logic
extern TA_RetCode TA_S_CDLHARAMICROSS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHARAMICROSS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHIGHWAVE_Lookback(void);
extern TA_RetCode TA_CDLHIGHWAVE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHIGHWAVE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHIGHWAVE TA_CDLHIGHWAVE_Logic
extern TA_RetCode TA_S_CDLHIGHWAVE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHIGHWAVE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHIKKAKE_Lookback(void);
extern TA_RetCode TA_CDLHIKKAKE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHIKKAKE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHIKKAKE TA_CDLHIKKAKE_Logic
extern TA_RetCode TA_S_CDLHIKKAKE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHIKKAKE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHIKKAKEMOD_Lookback(void);
extern TA_RetCode TA_CDLHIKKAKEMOD(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHIKKAKEMOD_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHIKKAKEMOD TA_CDLHIKKAKEMOD_Logic
extern TA_RetCode TA_S_CDLHIKKAKEMOD(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHIKKAKEMOD_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLHOMINGPIGEON_Lookback(void);
extern TA_RetCode TA_CDLHOMINGPIGEON(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLHOMINGPIGEON_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLHOMINGPIGEON TA_CDLHOMINGPIGEON_Logic
extern TA_RetCode TA_S_CDLHOMINGPIGEON(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLHOMINGPIGEON_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLIDENTICAL3CROWS_Lookback(void);
extern TA_RetCode TA_CDLIDENTICAL3CROWS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLIDENTICAL3CROWS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLIDENTICAL3CROWS TA_CDLIDENTICAL3CROWS_Logic
extern TA_RetCode TA_S_CDLIDENTICAL3CROWS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLIDENTICAL3CROWS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLINNECK_Lookback(void);
extern TA_RetCode TA_CDLINNECK(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLINNECK_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLINNECK TA_CDLINNECK_Logic
extern TA_RetCode TA_S_CDLINNECK(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLINNECK_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLINVERTEDHAMMER_Lookback(void);
extern TA_RetCode TA_CDLINVERTEDHAMMER(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLINVERTEDHAMMER_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLINVERTEDHAMMER TA_CDLINVERTEDHAMMER_Logic
extern TA_RetCode TA_S_CDLINVERTEDHAMMER(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLINVERTEDHAMMER_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLKICKING_Lookback(void);
extern TA_RetCode TA_CDLKICKING(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLKICKING_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLKICKING TA_CDLKICKING_Logic
extern TA_RetCode TA_S_CDLKICKING(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLKICKING_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLKICKINGBYLENGTH_Lookback(void);
extern TA_RetCode TA_CDLKICKINGBYLENGTH(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLKICKINGBYLENGTH_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLKICKINGBYLENGTH TA_CDLKICKINGBYLENGTH_Logic
extern TA_RetCode TA_S_CDLKICKINGBYLENGTH(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLKICKINGBYLENGTH_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLLADDERBOTTOM_Lookback(void);
extern TA_RetCode TA_CDLLADDERBOTTOM(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLLADDERBOTTOM_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLLADDERBOTTOM TA_CDLLADDERBOTTOM_Logic
extern TA_RetCode TA_S_CDLLADDERBOTTOM(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLLADDERBOTTOM_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLLONGLEGGEDDOJI_Lookback(void);
extern TA_RetCode TA_CDLLONGLEGGEDDOJI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLLONGLEGGEDDOJI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLLONGLEGGEDDOJI TA_CDLLONGLEGGEDDOJI_Logic
extern TA_RetCode TA_S_CDLLONGLEGGEDDOJI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLLONGLEGGEDDOJI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLLONGLINE_Lookback(void);
extern TA_RetCode TA_CDLLONGLINE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLLONGLINE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLLONGLINE TA_CDLLONGLINE_Logic
extern TA_RetCode TA_S_CDLLONGLINE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLLONGLINE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLMARUBOZU_Lookback(void);
extern TA_RetCode TA_CDLMARUBOZU(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLMARUBOZU_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLMARUBOZU TA_CDLMARUBOZU_Logic
extern TA_RetCode TA_S_CDLMARUBOZU(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLMARUBOZU_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLMATCHINGLOW_Lookback(void);
extern TA_RetCode TA_CDLMATCHINGLOW(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLMATCHINGLOW_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLMATCHINGLOW TA_CDLMATCHINGLOW_Logic
extern TA_RetCode TA_S_CDLMATCHINGLOW(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLMATCHINGLOW_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLMATHOLD_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLMATHOLD(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLMATHOLD_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLMATHOLD TA_CDLMATHOLD_Logic
extern TA_RetCode TA_S_CDLMATHOLD(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLMATHOLD_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLMORNINGDOJISTAR_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLMORNINGDOJISTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLMORNINGDOJISTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLMORNINGDOJISTAR TA_CDLMORNINGDOJISTAR_Logic
extern TA_RetCode TA_S_CDLMORNINGDOJISTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLMORNINGDOJISTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLMORNINGSTAR_Lookback(double optInPenetration);
extern TA_RetCode TA_CDLMORNINGSTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLMORNINGSTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLMORNINGSTAR TA_CDLMORNINGSTAR_Logic
extern TA_RetCode TA_S_CDLMORNINGSTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLMORNINGSTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLONNECK_Lookback(void);
extern TA_RetCode TA_CDLONNECK(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLONNECK_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLONNECK TA_CDLONNECK_Logic
extern TA_RetCode TA_S_CDLONNECK(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLONNECK_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLPIERCING_Lookback(void);
extern TA_RetCode TA_CDLPIERCING(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLPIERCING_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLPIERCING TA_CDLPIERCING_Logic
extern TA_RetCode TA_S_CDLPIERCING(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLPIERCING_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLRICKSHAWMAN_Lookback(void);
extern TA_RetCode TA_CDLRICKSHAWMAN(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLRICKSHAWMAN_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLRICKSHAWMAN TA_CDLRICKSHAWMAN_Logic
extern TA_RetCode TA_S_CDLRICKSHAWMAN(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLRICKSHAWMAN_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLRISEFALL3METHODS_Lookback(void);
extern TA_RetCode TA_CDLRISEFALL3METHODS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLRISEFALL3METHODS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLRISEFALL3METHODS TA_CDLRISEFALL3METHODS_Logic
extern TA_RetCode TA_S_CDLRISEFALL3METHODS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLRISEFALL3METHODS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSEPARATINGLINES_Lookback(void);
extern TA_RetCode TA_CDLSEPARATINGLINES(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSEPARATINGLINES_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSEPARATINGLINES TA_CDLSEPARATINGLINES_Logic
extern TA_RetCode TA_S_CDLSEPARATINGLINES(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSEPARATINGLINES_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSHOOTINGSTAR_Lookback(void);
extern TA_RetCode TA_CDLSHOOTINGSTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSHOOTINGSTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSHOOTINGSTAR TA_CDLSHOOTINGSTAR_Logic
extern TA_RetCode TA_S_CDLSHOOTINGSTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSHOOTINGSTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSHORTLINE_Lookback(void);
extern TA_RetCode TA_CDLSHORTLINE(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSHORTLINE_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSHORTLINE TA_CDLSHORTLINE_Logic
extern TA_RetCode TA_S_CDLSHORTLINE(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSHORTLINE_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSPINNINGTOP_Lookback(void);
extern TA_RetCode TA_CDLSPINNINGTOP(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSPINNINGTOP_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSPINNINGTOP TA_CDLSPINNINGTOP_Logic
extern TA_RetCode TA_S_CDLSPINNINGTOP(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSPINNINGTOP_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSTALLEDPATTERN_Lookback(void);
extern TA_RetCode TA_CDLSTALLEDPATTERN(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSTALLEDPATTERN_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSTALLEDPATTERN TA_CDLSTALLEDPATTERN_Logic
extern TA_RetCode TA_S_CDLSTALLEDPATTERN(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSTALLEDPATTERN_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLSTICKSANDWICH_Lookback(void);
extern TA_RetCode TA_CDLSTICKSANDWICH(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLSTICKSANDWICH_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLSTICKSANDWICH TA_CDLSTICKSANDWICH_Logic
extern TA_RetCode TA_S_CDLSTICKSANDWICH(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLSTICKSANDWICH_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLTAKURI_Lookback(void);
extern TA_RetCode TA_CDLTAKURI(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLTAKURI_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLTAKURI TA_CDLTAKURI_Logic
extern TA_RetCode TA_S_CDLTAKURI(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLTAKURI_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLTASUKIGAP_Lookback(void);
extern TA_RetCode TA_CDLTASUKIGAP(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLTASUKIGAP_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLTASUKIGAP TA_CDLTASUKIGAP_Logic
extern TA_RetCode TA_S_CDLTASUKIGAP(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLTASUKIGAP_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLTHRUSTING_Lookback(void);
extern TA_RetCode TA_CDLTHRUSTING(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLTHRUSTING_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLTHRUSTING TA_CDLTHRUSTING_Logic
extern TA_RetCode TA_S_CDLTHRUSTING(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLTHRUSTING_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLTRISTAR_Lookback(void);
extern TA_RetCode TA_CDLTRISTAR(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLTRISTAR_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLTRISTAR TA_CDLTRISTAR_Logic
extern TA_RetCode TA_S_CDLTRISTAR(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLTRISTAR_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLUNIQUE3RIVER_Lookback(void);
extern TA_RetCode TA_CDLUNIQUE3RIVER(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLUNIQUE3RIVER_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLUNIQUE3RIVER TA_CDLUNIQUE3RIVER_Logic
extern TA_RetCode TA_S_CDLUNIQUE3RIVER(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLUNIQUE3RIVER_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLUPSIDEGAP2CROWS_Lookback(void);
extern TA_RetCode TA_CDLUPSIDEGAP2CROWS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLUPSIDEGAP2CROWS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLUPSIDEGAP2CROWS TA_CDLUPSIDEGAP2CROWS_Logic
extern TA_RetCode TA_S_CDLUPSIDEGAP2CROWS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLUPSIDEGAP2CROWS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CDLXSIDEGAP3METHODS_Lookback(void);
extern TA_RetCode TA_CDLXSIDEGAP3METHODS(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_CDLXSIDEGAP3METHODS_Logic(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_CDLXSIDEGAP3METHODS TA_CDLXSIDEGAP3METHODS_Logic
extern TA_RetCode TA_S_CDLXSIDEGAP3METHODS(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_CDLXSIDEGAP3METHODS_Logic(int startIdx, int endIdx, const float inOpen[], const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_CEIL_Lookback(void);
extern TA_RetCode TA_CEIL(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_CEIL_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_CEIL TA_CEIL_Logic
extern TA_RetCode TA_S_CEIL(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_CEIL_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_CMO_Lookback(int optInTimePeriod);
extern TA_RetCode TA_CMO(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_CMO_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_CMO TA_CMO_Logic
extern TA_RetCode TA_S_CMO(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_CMO_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_CORREL_Lookback(int optInTimePeriod);
extern TA_RetCode TA_CORREL(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_CORREL_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_CORREL TA_CORREL_Logic
extern TA_RetCode TA_S_CORREL(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_CORREL_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_COS_Lookback(void);
extern TA_RetCode TA_COS(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_COS_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_COS TA_COS_Logic
extern TA_RetCode TA_S_COS(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_COS_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_COSH_Lookback(void);
extern TA_RetCode TA_COSH(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_COSH_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_COSH TA_COSH_Logic
extern TA_RetCode TA_S_COSH(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_COSH_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_DEMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_DEMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_DEMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_DEMA TA_DEMA_Logic
extern TA_RetCode TA_S_DEMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_DEMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_DIV_Lookback(void);
extern TA_RetCode TA_DIV(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_DIV_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_DIV TA_DIV_Logic
extern TA_RetCode TA_S_DIV(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_DIV_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_DX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_DX(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_DX_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_DX TA_DX_Logic
extern TA_RetCode TA_S_DX(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_DX_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_EMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_EMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_EMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInK_1, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_EMA TA_EMA_Logic
extern TA_RetCode TA_S_EMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_EMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInK_1, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_EXP_Lookback(void);
extern TA_RetCode TA_EXP(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_EXP_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_EXP TA_EXP_Logic
extern TA_RetCode TA_S_EXP(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_EXP_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_FLOOR_Lookback(void);
extern TA_RetCode TA_FLOOR(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_FLOOR_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_FLOOR TA_FLOOR_Logic
extern TA_RetCode TA_S_FLOOR(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_FLOOR_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_HT_DCPERIOD_Lookback(void);
extern TA_RetCode TA_HT_DCPERIOD(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_HT_DCPERIOD_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_HT_DCPERIOD TA_HT_DCPERIOD_Logic
extern TA_RetCode TA_S_HT_DCPERIOD(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_HT_DCPERIOD_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_HT_DCPHASE_Lookback(void);
extern TA_RetCode TA_HT_DCPHASE(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_HT_DCPHASE_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_HT_DCPHASE TA_HT_DCPHASE_Logic
extern TA_RetCode TA_S_HT_DCPHASE(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_HT_DCPHASE_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_HT_PHASOR_Lookback(void);
extern TA_RetCode TA_HT_PHASOR(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outInPhase[], double outQuadrature[]);
extern TA_RetCode TA_HT_PHASOR_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outInPhase[], double outQuadrature[]);
#define TA_INT_HT_PHASOR TA_HT_PHASOR_Logic
extern TA_RetCode TA_S_HT_PHASOR(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outInPhase[], double outQuadrature[]);
extern TA_RetCode TA_S_HT_PHASOR_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outInPhase[], double outQuadrature[]);
extern int TA_HT_SINE_Lookback(void);
extern TA_RetCode TA_HT_SINE(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outSine[], double outLeadSine[]);
extern TA_RetCode TA_HT_SINE_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outSine[], double outLeadSine[]);
#define TA_INT_HT_SINE TA_HT_SINE_Logic
extern TA_RetCode TA_S_HT_SINE(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outSine[], double outLeadSine[]);
extern TA_RetCode TA_S_HT_SINE_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outSine[], double outLeadSine[]);
extern int TA_HT_TRENDLINE_Lookback(void);
extern TA_RetCode TA_HT_TRENDLINE(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_HT_TRENDLINE_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_HT_TRENDLINE TA_HT_TRENDLINE_Logic
extern TA_RetCode TA_S_HT_TRENDLINE(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_HT_TRENDLINE_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_HT_TRENDMODE_Lookback(void);
extern TA_RetCode TA_HT_TRENDMODE(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_HT_TRENDMODE_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_HT_TRENDMODE TA_HT_TRENDMODE_Logic
extern TA_RetCode TA_S_HT_TRENDMODE(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_HT_TRENDMODE_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_IMI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_IMI(int startIdx, int endIdx, const double inOpen[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_IMI_Logic(int startIdx, int endIdx, const double inOpen[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_IMI TA_IMI_Logic
extern TA_RetCode TA_S_IMI(int startIdx, int endIdx, const float inOpen[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_IMI_Logic(int startIdx, int endIdx, const float inOpen[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_KAMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_KAMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_KAMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_KAMA TA_KAMA_Logic
extern TA_RetCode TA_S_KAMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_KAMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LINEARREG_Lookback(int optInTimePeriod);
extern TA_RetCode TA_LINEARREG(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LINEARREG_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LINEARREG TA_LINEARREG_Logic
extern TA_RetCode TA_S_LINEARREG(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LINEARREG_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LINEARREG_ANGLE_Lookback(int optInTimePeriod);
extern TA_RetCode TA_LINEARREG_ANGLE(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LINEARREG_ANGLE_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LINEARREG_ANGLE TA_LINEARREG_ANGLE_Logic
extern TA_RetCode TA_S_LINEARREG_ANGLE(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LINEARREG_ANGLE_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LINEARREG_INTERCEPT_Lookback(int optInTimePeriod);
extern TA_RetCode TA_LINEARREG_INTERCEPT(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LINEARREG_INTERCEPT_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LINEARREG_INTERCEPT TA_LINEARREG_INTERCEPT_Logic
extern TA_RetCode TA_S_LINEARREG_INTERCEPT(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LINEARREG_INTERCEPT_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LINEARREG_SLOPE_Lookback(int optInTimePeriod);
extern TA_RetCode TA_LINEARREG_SLOPE(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LINEARREG_SLOPE_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LINEARREG_SLOPE TA_LINEARREG_SLOPE_Logic
extern TA_RetCode TA_S_LINEARREG_SLOPE(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LINEARREG_SLOPE_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LN_Lookback(void);
extern TA_RetCode TA_LN(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LN_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LN TA_LN_Logic
extern TA_RetCode TA_S_LN(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LN_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_LOG10_Lookback(void);
extern TA_RetCode TA_LOG10(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_LOG10_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_LOG10 TA_LOG10_Logic
extern TA_RetCode TA_S_LOG10(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_LOG10_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MA_Lookback(int optInTimePeriod, int optInMAType);
extern TA_RetCode TA_MA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MA TA_MA_Logic
extern TA_RetCode TA_S_MA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MACD_Lookback(int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod);
extern TA_RetCode TA_MACD(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_MACD_Logic(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
#define TA_INT_MACD TA_MACD_Logic
extern TA_RetCode TA_S_MACD(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_S_MACD_Logic(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern int TA_MACDEXT_Lookback(int optInFastPeriod, int optInFastMAType, int optInSlowPeriod, int optInSlowMAType, int optInSignalPeriod, int optInSignalMAType);
extern TA_RetCode TA_MACDEXT(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInFastMAType, int optInSlowPeriod, int optInSlowMAType, int optInSignalPeriod, int optInSignalMAType, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_MACDEXT_Logic(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInFastMAType, int optInSlowPeriod, int optInSlowMAType, int optInSignalPeriod, int optInSignalMAType, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
#define TA_INT_MACDEXT TA_MACDEXT_Logic
extern TA_RetCode TA_S_MACDEXT(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInFastMAType, int optInSlowPeriod, int optInSlowMAType, int optInSignalPeriod, int optInSignalMAType, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_S_MACDEXT_Logic(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInFastMAType, int optInSlowPeriod, int optInSlowMAType, int optInSignalPeriod, int optInSignalMAType, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern int TA_MACDFIX_Lookback(int optInSignalPeriod);
extern TA_RetCode TA_MACDFIX(int startIdx, int endIdx, const double inReal[], int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_MACDFIX_Logic(int startIdx, int endIdx, const double inReal[], int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
#define TA_INT_MACDFIX TA_MACDFIX_Logic
extern TA_RetCode TA_S_MACDFIX(int startIdx, int endIdx, const float inReal[], int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern TA_RetCode TA_S_MACDFIX_Logic(int startIdx, int endIdx, const float inReal[], int optInSignalPeriod, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[]);
extern int TA_MAMA_Lookback(double optInFastLimit, double optInSlowLimit);
extern TA_RetCode TA_MAMA(int startIdx, int endIdx, const double inReal[], double optInFastLimit, double optInSlowLimit, int *outBegIdx, int *outNBElement, double outMAMA[], double outFAMA[]);
extern TA_RetCode TA_MAMA_Logic(int startIdx, int endIdx, const double inReal[], double optInFastLimit, double optInSlowLimit, int *outBegIdx, int *outNBElement, double outMAMA[], double outFAMA[]);
#define TA_INT_MAMA TA_MAMA_Logic
extern TA_RetCode TA_S_MAMA(int startIdx, int endIdx, const float inReal[], double optInFastLimit, double optInSlowLimit, int *outBegIdx, int *outNBElement, double outMAMA[], double outFAMA[]);
extern TA_RetCode TA_S_MAMA_Logic(int startIdx, int endIdx, const float inReal[], double optInFastLimit, double optInSlowLimit, int *outBegIdx, int *outNBElement, double outMAMA[], double outFAMA[]);
extern int TA_MAVP_Lookback(int optInMinPeriod, int optInMaxPeriod, int optInMAType);
extern TA_RetCode TA_MAVP(int startIdx, int endIdx, const double inReal[], const double inPeriods[], int optInMinPeriod, int optInMaxPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MAVP_Logic(int startIdx, int endIdx, const double inReal[], const double inPeriods[], int optInMinPeriod, int optInMaxPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MAVP TA_MAVP_Logic
extern TA_RetCode TA_S_MAVP(int startIdx, int endIdx, const float inReal[], const float inPeriods[], int optInMinPeriod, int optInMaxPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MAVP_Logic(int startIdx, int endIdx, const float inReal[], const float inPeriods[], int optInMinPeriod, int optInMaxPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MAX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MAX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MAX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MAX TA_MAX_Logic
extern TA_RetCode TA_S_MAX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MAX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MAXINDEX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MAXINDEX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_MAXINDEX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_MAXINDEX TA_MAXINDEX_Logic
extern TA_RetCode TA_S_MAXINDEX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_MAXINDEX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_MEDPRICE_Lookback(void);
extern TA_RetCode TA_MEDPRICE(int startIdx, int endIdx, const double inHigh[], const double inLow[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MEDPRICE_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MEDPRICE TA_MEDPRICE_Logic
extern TA_RetCode TA_S_MEDPRICE(int startIdx, int endIdx, const float inHigh[], const float inLow[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MEDPRICE_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MFI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MFI(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MFI_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MFI TA_MFI_Logic
extern TA_RetCode TA_S_MFI(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MFI_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], const float inVolume[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MIDPOINT_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MIDPOINT(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MIDPOINT_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MIDPOINT TA_MIDPOINT_Logic
extern TA_RetCode TA_S_MIDPOINT(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MIDPOINT_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MIDPRICE_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MIDPRICE(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MIDPRICE_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MIDPRICE TA_MIDPRICE_Logic
extern TA_RetCode TA_S_MIDPRICE(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MIDPRICE_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MIN_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MIN(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MIN_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MIN TA_MIN_Logic
extern TA_RetCode TA_S_MIN(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MIN_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MININDEX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MININDEX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_MININDEX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
#define TA_INT_MININDEX TA_MININDEX_Logic
extern TA_RetCode TA_S_MININDEX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern TA_RetCode TA_S_MININDEX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outInteger[]);
extern int TA_MINMAX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MINMAX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outMin[], double outMax[]);
extern TA_RetCode TA_MINMAX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outMin[], double outMax[]);
#define TA_INT_MINMAX TA_MINMAX_Logic
extern TA_RetCode TA_S_MINMAX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outMin[], double outMax[]);
extern TA_RetCode TA_S_MINMAX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outMin[], double outMax[]);
extern int TA_MINMAXINDEX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MINMAXINDEX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outMinIdx[], int outMaxIdx[]);
extern TA_RetCode TA_MINMAXINDEX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outMinIdx[], int outMaxIdx[]);
#define TA_INT_MINMAXINDEX TA_MINMAXINDEX_Logic
extern TA_RetCode TA_S_MINMAXINDEX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outMinIdx[], int outMaxIdx[]);
extern TA_RetCode TA_S_MINMAXINDEX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, int outMinIdx[], int outMaxIdx[]);
extern int TA_MINUS_DI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MINUS_DI(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MINUS_DI_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MINUS_DI TA_MINUS_DI_Logic
extern TA_RetCode TA_S_MINUS_DI(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MINUS_DI_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MINUS_DM_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MINUS_DM(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MINUS_DM_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MINUS_DM TA_MINUS_DM_Logic
extern TA_RetCode TA_S_MINUS_DM(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MINUS_DM_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MOM_Lookback(int optInTimePeriod);
extern TA_RetCode TA_MOM(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MOM_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MOM TA_MOM_Logic
extern TA_RetCode TA_S_MOM(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MOM_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_MULT_Lookback(void);
extern TA_RetCode TA_MULT(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_MULT_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_MULT TA_MULT_Logic
extern TA_RetCode TA_S_MULT(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_MULT_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_NATR_Lookback(int optInTimePeriod);
extern TA_RetCode TA_NATR(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_NATR_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_NATR TA_NATR_Logic
extern TA_RetCode TA_S_NATR(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_NATR_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_NVI_Lookback(void);
extern TA_RetCode TA_NVI(int startIdx, int endIdx, const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_NVI_Logic(int startIdx, int endIdx, const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_NVI TA_NVI_Logic
extern TA_RetCode TA_S_NVI(int startIdx, int endIdx, const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_NVI_Logic(int startIdx, int endIdx, const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_OBV_Lookback(void);
extern TA_RetCode TA_OBV(int startIdx, int endIdx, const double inReal[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_OBV_Logic(int startIdx, int endIdx, const double inReal[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_OBV TA_OBV_Logic
extern TA_RetCode TA_S_OBV(int startIdx, int endIdx, const float inReal[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_OBV_Logic(int startIdx, int endIdx, const float inReal[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_PLUS_DI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_PLUS_DI(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_PLUS_DI_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_PLUS_DI TA_PLUS_DI_Logic
extern TA_RetCode TA_S_PLUS_DI(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_PLUS_DI_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_PLUS_DM_Lookback(int optInTimePeriod);
extern TA_RetCode TA_PLUS_DM(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_PLUS_DM_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_PLUS_DM TA_PLUS_DM_Logic
extern TA_RetCode TA_S_PLUS_DM(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_PLUS_DM_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_PPO_Lookback(int optInFastPeriod, int optInSlowPeriod, int optInMAType);
extern TA_RetCode TA_PPO(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_PPO_Logic(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_PPO TA_PPO_Logic
extern TA_RetCode TA_S_PPO(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_PPO_Logic(int startIdx, int endIdx, const float inReal[], int optInFastPeriod, int optInSlowPeriod, int optInMAType, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_PVI_Lookback(void);
extern TA_RetCode TA_PVI(int startIdx, int endIdx, const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_PVI_Logic(int startIdx, int endIdx, const double inClose[], const double inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_PVI TA_PVI_Logic
extern TA_RetCode TA_S_PVI(int startIdx, int endIdx, const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_PVI_Logic(int startIdx, int endIdx, const float inClose[], const float inVolume[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ROC_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ROC(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ROC_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ROC TA_ROC_Logic
extern TA_RetCode TA_S_ROC(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ROC_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ROCP_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ROCP(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ROCP_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ROCP TA_ROCP_Logic
extern TA_RetCode TA_S_ROCP(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ROCP_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ROCR_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ROCR(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ROCR_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ROCR TA_ROCR_Logic
extern TA_RetCode TA_S_ROCR(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ROCR_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ROCR100_Lookback(int optInTimePeriod);
extern TA_RetCode TA_ROCR100(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ROCR100_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ROCR100 TA_ROCR100_Logic
extern TA_RetCode TA_S_ROCR100(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ROCR100_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_RSI_Lookback(int optInTimePeriod);
extern TA_RetCode TA_RSI(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_RSI_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_RSI TA_RSI_Logic
extern TA_RetCode TA_S_RSI(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_RSI_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SAR_Lookback(double optInAcceleration, double optInMaximum);
extern TA_RetCode TA_SAR(int startIdx, int endIdx, const double inHigh[], const double inLow[], double optInAcceleration, double optInMaximum, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SAR_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], double optInAcceleration, double optInMaximum, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SAR TA_SAR_Logic
extern TA_RetCode TA_S_SAR(int startIdx, int endIdx, const float inHigh[], const float inLow[], double optInAcceleration, double optInMaximum, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SAR_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], double optInAcceleration, double optInMaximum, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SAREXT_Lookback(double optInStartValue, double optInOffsetOnReverse, double optInAccelerationInitLong, double optInAccelerationLong, double optInAccelerationMaxLong, double optInAccelerationInitShort, double optInAccelerationShort, double optInAccelerationMaxShort);
extern TA_RetCode TA_SAREXT(int startIdx, int endIdx, const double inHigh[], const double inLow[], double optInStartValue, double optInOffsetOnReverse, double optInAccelerationInitLong, double optInAccelerationLong, double optInAccelerationMaxLong, double optInAccelerationInitShort, double optInAccelerationShort, double optInAccelerationMaxShort, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SAREXT_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], double optInStartValue, double optInOffsetOnReverse, double optInAccelerationInitLong, double optInAccelerationLong, double optInAccelerationMaxLong, double optInAccelerationInitShort, double optInAccelerationShort, double optInAccelerationMaxShort, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SAREXT TA_SAREXT_Logic
extern TA_RetCode TA_S_SAREXT(int startIdx, int endIdx, const float inHigh[], const float inLow[], double optInStartValue, double optInOffsetOnReverse, double optInAccelerationInitLong, double optInAccelerationLong, double optInAccelerationMaxLong, double optInAccelerationInitShort, double optInAccelerationShort, double optInAccelerationMaxShort, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SAREXT_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], double optInStartValue, double optInOffsetOnReverse, double optInAccelerationInitLong, double optInAccelerationLong, double optInAccelerationMaxLong, double optInAccelerationInitShort, double optInAccelerationShort, double optInAccelerationMaxShort, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SIN_Lookback(void);
extern TA_RetCode TA_SIN(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SIN_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SIN TA_SIN_Logic
extern TA_RetCode TA_S_SIN(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SIN_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SINH_Lookback(void);
extern TA_RetCode TA_SINH(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SINH_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SINH TA_SINH_Logic
extern TA_RetCode TA_S_SINH(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SINH_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_SMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SMA TA_SMA_Logic
extern TA_RetCode TA_S_SMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SQRT_Lookback(void);
extern TA_RetCode TA_SQRT(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SQRT_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SQRT TA_SQRT_Logic
extern TA_RetCode TA_S_SQRT(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SQRT_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_STDDEV_Lookback(int optInTimePeriod, double optInNbDev);
extern TA_RetCode TA_STDDEV(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_STDDEV_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_STDDEV TA_STDDEV_Logic
extern TA_RetCode TA_S_STDDEV(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_STDDEV_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_STOCH_Lookback(int optInFastK_Period, int optInSlowK_Period, int optInSlowK_MAType, int optInSlowD_Period, int optInSlowD_MAType);
extern TA_RetCode TA_STOCH(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInFastK_Period, int optInSlowK_Period, int optInSlowK_MAType, int optInSlowD_Period, int optInSlowD_MAType, int *outBegIdx, int *outNBElement, double outSlowK[], double outSlowD[]);
extern TA_RetCode TA_STOCH_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInFastK_Period, int optInSlowK_Period, int optInSlowK_MAType, int optInSlowD_Period, int optInSlowD_MAType, int *outBegIdx, int *outNBElement, double outSlowK[], double outSlowD[]);
#define TA_INT_STOCH TA_STOCH_Logic
extern TA_RetCode TA_S_STOCH(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInFastK_Period, int optInSlowK_Period, int optInSlowK_MAType, int optInSlowD_Period, int optInSlowD_MAType, int *outBegIdx, int *outNBElement, double outSlowK[], double outSlowD[]);
extern TA_RetCode TA_S_STOCH_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInFastK_Period, int optInSlowK_Period, int optInSlowK_MAType, int optInSlowD_Period, int optInSlowD_MAType, int *outBegIdx, int *outNBElement, double outSlowK[], double outSlowD[]);
extern int TA_STOCHF_Lookback(int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType);
extern TA_RetCode TA_STOCHF(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern TA_RetCode TA_STOCHF_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
#define TA_INT_STOCHF TA_STOCHF_Logic
extern TA_RetCode TA_S_STOCHF(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern TA_RetCode TA_S_STOCHF_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern int TA_STOCHRSI_Lookback(int optInTimePeriod, int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType);
extern TA_RetCode TA_STOCHRSI(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern TA_RetCode TA_STOCHRSI_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
#define TA_INT_STOCHRSI TA_STOCHRSI_Logic
extern TA_RetCode TA_S_STOCHRSI(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern TA_RetCode TA_S_STOCHRSI_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int optInFastK_Period, int optInFastD_Period, int optInFastD_MAType, int *outBegIdx, int *outNBElement, double outFastK[], double outFastD[]);
extern int TA_SUB_Lookback(void);
extern TA_RetCode TA_SUB(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SUB_Logic(int startIdx, int endIdx, const double inReal0[], const double inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SUB TA_SUB_Logic
extern TA_RetCode TA_S_SUB(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SUB_Logic(int startIdx, int endIdx, const float inReal0[], const float inReal1[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_SUM_Lookback(int optInTimePeriod);
extern TA_RetCode TA_SUM(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_SUM_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_SUM TA_SUM_Logic
extern TA_RetCode TA_S_SUM(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_SUM_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_T3_Lookback(int optInTimePeriod, double optInVFactor);
extern TA_RetCode TA_T3(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInVFactor, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_T3_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInVFactor, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_T3 TA_T3_Logic
extern TA_RetCode TA_S_T3(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInVFactor, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_T3_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInVFactor, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TAN_Lookback(void);
extern TA_RetCode TA_TAN(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TAN_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TAN TA_TAN_Logic
extern TA_RetCode TA_S_TAN(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TAN_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TANH_Lookback(void);
extern TA_RetCode TA_TANH(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TANH_Logic(int startIdx, int endIdx, const double inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TANH TA_TANH_Logic
extern TA_RetCode TA_S_TANH(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TANH_Logic(int startIdx, int endIdx, const float inReal[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TEMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_TEMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TEMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TEMA TA_TEMA_Logic
extern TA_RetCode TA_S_TEMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TEMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TRANGE_Lookback(void);
extern TA_RetCode TA_TRANGE(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TRANGE_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TRANGE TA_TRANGE_Logic
extern TA_RetCode TA_S_TRANGE(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TRANGE_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TRIMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_TRIMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TRIMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TRIMA TA_TRIMA_Logic
extern TA_RetCode TA_S_TRIMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TRIMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TRIX_Lookback(int optInTimePeriod);
extern TA_RetCode TA_TRIX(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TRIX_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TRIX TA_TRIX_Logic
extern TA_RetCode TA_S_TRIX(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TRIX_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TSF_Lookback(int optInTimePeriod);
extern TA_RetCode TA_TSF(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TSF_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TSF TA_TSF_Logic
extern TA_RetCode TA_S_TSF(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TSF_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_TYPPRICE_Lookback(void);
extern TA_RetCode TA_TYPPRICE(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_TYPPRICE_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_TYPPRICE TA_TYPPRICE_Logic
extern TA_RetCode TA_S_TYPPRICE(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_TYPPRICE_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_ULTOSC_Lookback(int optInTimePeriod1, int optInTimePeriod2, int optInTimePeriod3);
extern TA_RetCode TA_ULTOSC(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod1, int optInTimePeriod2, int optInTimePeriod3, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_ULTOSC_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod1, int optInTimePeriod2, int optInTimePeriod3, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_ULTOSC TA_ULTOSC_Logic
extern TA_RetCode TA_S_ULTOSC(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod1, int optInTimePeriod2, int optInTimePeriod3, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_ULTOSC_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod1, int optInTimePeriod2, int optInTimePeriod3, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_VAR_Lookback(int optInTimePeriod, double optInNbDev);
extern TA_RetCode TA_VAR(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_VAR_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_VAR TA_VAR_Logic
extern TA_RetCode TA_S_VAR(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_VAR_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_WCLPRICE_Lookback(void);
extern TA_RetCode TA_WCLPRICE(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_WCLPRICE_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_WCLPRICE TA_WCLPRICE_Logic
extern TA_RetCode TA_S_WCLPRICE(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_WCLPRICE_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_WILLR_Lookback(int optInTimePeriod);
extern TA_RetCode TA_WILLR(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_WILLR_Logic(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_WILLR TA_WILLR_Logic
extern TA_RetCode TA_S_WILLR(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_WILLR_Logic(int startIdx, int endIdx, const float inHigh[], const float inLow[], const float inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern int TA_WMA_Lookback(int optInTimePeriod);
extern TA_RetCode TA_WMA(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_WMA_Logic(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
#define TA_INT_WMA TA_WMA_Logic
extern TA_RetCode TA_S_WMA(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);
extern TA_RetCode TA_S_WMA_Logic(int startIdx, int endIdx, const float inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[]);

/* Internal helper forward declarations */
extern void stddev_using_precalc_ma(const double inReal[], const double inMovAvg[], int inMovAvgBegIdx, int inMovAvgNbElement, int timePeriod, double output[]);

#endif /* TA_FUNC_H */
