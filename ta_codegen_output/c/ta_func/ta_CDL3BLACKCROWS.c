/* TA-LIB Copyright (c) 1999-2025, Mario Fortier
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following
* conditions are met:
*
* - Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* - Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in
*   the documentation and/or other materials provided with the
*   distribution.
*
* - Neither name of author nor the names of its contributors
*   may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string.h>
#include <math.h>
#include "ta_func.h"

TA_LIB_API int TA_CDL3BLACKCROWS_Lookback( void )
{
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (ShadowVeryShort_avgPeriod+3);
}

TA_LIB_API TA_RetCode TA_CDL3BLACKCROWS( int    startIdx,
                                         int    endIdx,
                                         const double inOpen[],
                                         const double inHigh[],
                                         const double inLow[],
                                         const double inClose[],
                                         int          *outBegIdx,
                                         int          *outNBElement,
                                         int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( !inOpen )
      return TA_BAD_PARAM;
   if( !inHigh )
      return TA_BAD_PARAM;
   if( !inLow )
      return TA_BAD_PARAM;
   if( !inClose )
      return TA_BAD_PARAM;
   if( !outInteger )
      return TA_BAD_PARAM;

   lookbackTotal = TA_CDL3BLACKCROWS_Lookback();
   if( (startIdx<lookbackTotal) )
   {
      startIdx = lookbackTotal;
   }
   if( (startIdx>endIdx) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_SUCCESS;
   }
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_6;
      _candlerange_6 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      _candlerange_7 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      _candlerange_8 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_9;
         _candlerange_9 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_10;
         _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDL3BLACKCROWS_Logic( int    startIdx,
                                               int    endIdx,
                                               const double inOpen[],
                                               const double inHigh[],
                                               const double inLow[],
                                               const double inClose[],
                                               int          *outBegIdx,
                                               int          *outNBElement,
                                               int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3BLACKCROWS_Lookback();
   if( (startIdx<lookbackTotal) )
   {
      startIdx = lookbackTotal;
   }
   if( (startIdx>endIdx) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_SUCCESS;
   }
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_6;
      _candlerange_6 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      _candlerange_7 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      _candlerange_8 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_9;
         _candlerange_9 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_10;
         _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDL3BLACKCROWS TA_CDL3BLACKCROWS_Logic

TA_RetCode TA_S_CDL3BLACKCROWS( int    startIdx,
                                int    endIdx,
                                const float inOpen[],
                                const float inHigh[],
                                const float inLow[],
                                const float inClose[],
                                int          *outBegIdx,
                                int          *outNBElement,
                                int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( !inOpen )
      return TA_BAD_PARAM;
   if( !inHigh )
      return TA_BAD_PARAM;
   if( !inLow )
      return TA_BAD_PARAM;
   if( !inClose )
      return TA_BAD_PARAM;
   if( !outInteger )
      return TA_BAD_PARAM;

   lookbackTotal = TA_CDL3BLACKCROWS_Lookback();
   if( (startIdx<lookbackTotal) )
   {
      startIdx = lookbackTotal;
   }
   if( (startIdx>endIdx) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_SUCCESS;
   }
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_6;
      _candlerange_6 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      _candlerange_7 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      _candlerange_8 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_9;
         _candlerange_9 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_10;
         _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDL3BLACKCROWS_Logic( int    startIdx,
                                      int    endIdx,
                                      const float inOpen[],
                                      const float inHigh[],
                                      const float inLow[],
                                      const float inClose[],
                                      int          *outBegIdx,
                                      int          *outNBElement,
                                      int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3BLACKCROWS_Lookback();
   if( (startIdx<lookbackTotal) )
   {
      startIdx = lookbackTotal;
   }
   if( (startIdx>endIdx) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_SUCCESS;
   }
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_6;
      _candlerange_6 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      _candlerange_7 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      _candlerange_8 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_9;
         _candlerange_9 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_10;
         _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

