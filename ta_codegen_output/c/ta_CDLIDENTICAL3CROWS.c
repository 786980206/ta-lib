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

TA_LIB_API int TA_CDLIDENTICAL3CROWS_Lookback( void )
{
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(ShadowVeryShort_avgPeriod,Equal_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDLIDENTICAL3CROWS( int    startIdx,
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
   double EqualPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
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

   lookbackTotal = TA_CDLIDENTICAL3CROWS_Lookback();
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
   EqualPeriodTotal[2] = 0;
   EqualPeriodTotal[1] = 0;
   EqualPeriodTotal[0] = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
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
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_12;
      _candlerange_12 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_13;
      _candlerange_13 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_15;
      _candlerange_15 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_15));
      double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_16;
      _candlerange_16 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_16));
      double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_17;
      _candlerange_17 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_17));
      double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_18;
      _candlerange_18 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_18));
      double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_19;
         _candlerange_19 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_20;
         _candlerange_20 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_19-_candlerange_20));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_21;
         _candlerange_21 = ((Equal_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_22;
         _candlerange_22 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])))) : (0.0))))));
         EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLIDENTICAL3CROWS_Logic( int    startIdx,
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
   double EqualPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLIDENTICAL3CROWS_Lookback();
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
   EqualPeriodTotal[2] = 0;
   EqualPeriodTotal[1] = 0;
   EqualPeriodTotal[0] = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
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
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_12;
      _candlerange_12 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_13;
      _candlerange_13 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_15;
      _candlerange_15 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_15));
      double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_16;
      _candlerange_16 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_16));
      double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_17;
      _candlerange_17 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_17));
      double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_18;
      _candlerange_18 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_18));
      double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_19;
         _candlerange_19 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_20;
         _candlerange_20 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_19-_candlerange_20));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_21;
         _candlerange_21 = ((Equal_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_22;
         _candlerange_22 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])))) : (0.0))))));
         EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLIDENTICAL3CROWS TA_CDLIDENTICAL3CROWS_Logic

TA_RetCode TA_S_CDLIDENTICAL3CROWS( int    startIdx,
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
   double EqualPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
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

   lookbackTotal = TA_CDLIDENTICAL3CROWS_Lookback();
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
   EqualPeriodTotal[2] = 0;
   EqualPeriodTotal[1] = 0;
   EqualPeriodTotal[0] = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
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
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_12;
      _candlerange_12 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_13;
      _candlerange_13 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_15;
      _candlerange_15 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_15));
      double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_16;
      _candlerange_16 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_16));
      double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_17;
      _candlerange_17 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_17));
      double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_18;
      _candlerange_18 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_18));
      double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_19;
         _candlerange_19 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_20;
         _candlerange_20 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_19-_candlerange_20));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_21;
         _candlerange_21 = ((Equal_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_22;
         _candlerange_22 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])))) : (0.0))))));
         EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLIDENTICAL3CROWS_Logic( int    startIdx,
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
   double EqualPeriodTotal[3];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLIDENTICAL3CROWS_Lookback();
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
   EqualPeriodTotal[2] = 0;
   EqualPeriodTotal[1] = 0;
   EqualPeriodTotal[0] = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
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
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_12;
      _candlerange_12 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_13;
      _candlerange_13 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_15;
      _candlerange_15 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_15));
      double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_16;
      _candlerange_16 = ((Equal_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Equal_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (_candlerange_16));
      double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_17;
      _candlerange_17 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_17));
      double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_18;
      _candlerange_18 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (_candlerange_18));
      double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_19;
         _candlerange_19 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_20;
         _candlerange_20 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_19-_candlerange_20));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_21;
         _candlerange_21 = ((Equal_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_22;
         _candlerange_22 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-fabs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])))) : (0.0))))));
         EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

