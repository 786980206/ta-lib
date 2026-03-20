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

TA_LIB_API int TA_CDLRISEFALL3METHODS_Lookback( void )
{
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   return (fmax(BodyShort_avgPeriod,BodyLong_avgPeriod)+4);
}

TA_LIB_API TA_RetCode TA_CDLRISEFALL3METHODS( int    startIdx,
                                              int    endIdx,
                                              const double inOpen[],
                                              const double inHigh[],
                                              const double inLow[],
                                              const double inClose[],
                                              int          *outBegIdx,
                                              int          *outNBElement,
                                              int        outInteger[] )
{
   double BodyPeriodTotal[5];
   int i;
   int outIdx;
   int totIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

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

   lookbackTotal = TA_CDLRISEFALL3METHODS_Lookback();
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
   BodyPeriodTotal[4] = 0;
   BodyPeriodTotal[3] = 0;
   BodyPeriodTotal[2] = 0;
   BodyPeriodTotal[1] = 0;
   BodyPeriodTotal[0] = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_14;
      _candlerange_14 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
      double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
      if( (((((((((((((((((((fabs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5)&&(fabs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_9))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(fmin(inOpen[(i-3)],inClose[(i-3)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-3)],inClose[(i-3)])>inLow[(i-4)]))&&(fmin(inOpen[(i-2)],inClose[(i-2)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-2)],inClose[(i-2)])>inLow[(i-4)]))&&(fmin(inOpen[(i-1)],inClose[(i-1)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-1)],inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) )
      {
         outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_15;
      _candlerange_15 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_17;
         _candlerange_17 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_18;
         _candlerange_18 = ((BodyShort_rangeType==0) ? (fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])))) : (0.0))))));
         BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
      }
      double _candlerange_19;
      _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_20;
      _candlerange_20 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
      i += 1;
      BodyShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLRISEFALL3METHODS_Logic( int    startIdx,
                                                    int    endIdx,
                                                    const double inOpen[],
                                                    const double inHigh[],
                                                    const double inLow[],
                                                    const double inClose[],
                                                    int          *outBegIdx,
                                                    int          *outNBElement,
                                                    int        outInteger[] )
{
   double BodyPeriodTotal[5];
   int i;
   int outIdx;
   int totIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLRISEFALL3METHODS_Lookback();
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
   BodyPeriodTotal[4] = 0;
   BodyPeriodTotal[3] = 0;
   BodyPeriodTotal[2] = 0;
   BodyPeriodTotal[1] = 0;
   BodyPeriodTotal[0] = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_14;
      _candlerange_14 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
      double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
      if( (((((((((((((((((((fabs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5)&&(fabs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_9))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(fmin(inOpen[(i-3)],inClose[(i-3)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-3)],inClose[(i-3)])>inLow[(i-4)]))&&(fmin(inOpen[(i-2)],inClose[(i-2)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-2)],inClose[(i-2)])>inLow[(i-4)]))&&(fmin(inOpen[(i-1)],inClose[(i-1)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-1)],inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) )
      {
         outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_15;
      _candlerange_15 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_17;
         _candlerange_17 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_18;
         _candlerange_18 = ((BodyShort_rangeType==0) ? (fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])))) : (0.0))))));
         BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
      }
      double _candlerange_19;
      _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_20;
      _candlerange_20 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
      i += 1;
      BodyShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLRISEFALL3METHODS TA_CDLRISEFALL3METHODS_Logic

TA_RetCode TA_S_CDLRISEFALL3METHODS( int    startIdx,
                                     int    endIdx,
                                     const float inOpen[],
                                     const float inHigh[],
                                     const float inLow[],
                                     const float inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double BodyPeriodTotal[5];
   int i;
   int outIdx;
   int totIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

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

   lookbackTotal = TA_CDLRISEFALL3METHODS_Lookback();
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
   BodyPeriodTotal[4] = 0;
   BodyPeriodTotal[3] = 0;
   BodyPeriodTotal[2] = 0;
   BodyPeriodTotal[1] = 0;
   BodyPeriodTotal[0] = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_14;
      _candlerange_14 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
      double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
      if( (((((((((((((((((((fabs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5)&&(fabs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_9))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(fmin(inOpen[(i-3)],inClose[(i-3)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-3)],inClose[(i-3)])>inLow[(i-4)]))&&(fmin(inOpen[(i-2)],inClose[(i-2)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-2)],inClose[(i-2)])>inLow[(i-4)]))&&(fmin(inOpen[(i-1)],inClose[(i-1)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-1)],inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) )
      {
         outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_15;
      _candlerange_15 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_17;
         _candlerange_17 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_18;
         _candlerange_18 = ((BodyShort_rangeType==0) ? (fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])))) : (0.0))))));
         BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
      }
      double _candlerange_19;
      _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_20;
      _candlerange_20 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
      i += 1;
      BodyShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLRISEFALL3METHODS_Logic( int    startIdx,
                                           int    endIdx,
                                           const float inOpen[],
                                           const float inHigh[],
                                           const float inLow[],
                                           const float inClose[],
                                           int          *outBegIdx,
                                           int          *outNBElement,
                                           int        outInteger[] )
{
   double BodyPeriodTotal[5];
   int i;
   int outIdx;
   int totIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLRISEFALL3METHODS_Lookback();
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
   BodyPeriodTotal[4] = 0;
   BodyPeriodTotal[3] = 0;
   BodyPeriodTotal[2] = 0;
   BodyPeriodTotal[1] = 0;
   BodyPeriodTotal[0] = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-3)]-inOpen[(i-3)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-3)]-inLow[(i-3)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])))) : (0.0))))));
      double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_14;
      _candlerange_14 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
      double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
      if( (((((((((((((((((((fabs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5)&&(fabs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_9))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(fmin(inOpen[(i-3)],inClose[(i-3)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-3)],inClose[(i-3)])>inLow[(i-4)]))&&(fmin(inOpen[(i-2)],inClose[(i-2)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-2)],inClose[(i-2)])>inLow[(i-4)]))&&(fmin(inOpen[(i-1)],inClose[(i-1)])<inHigh[(i-4)]))&&(fmax(inOpen[(i-1)],inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) )
      {
         outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_15;
      _candlerange_15 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-4)]-inOpen[(i-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-4)]-inLow[(i-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-4)]-inLow[(i-4)])-fabs((inClose[(i-4)]-inOpen[(i-4)])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-fabs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])))) : (0.0))))));
      BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_17;
         _candlerange_17 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_18;
         _candlerange_18 = ((BodyShort_rangeType==0) ? (fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])) : (((BodyShort_rangeType==2) ? (((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-fabs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])))) : (0.0))))));
         BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
      }
      double _candlerange_19;
      _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_20;
      _candlerange_20 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
      i += 1;
      BodyShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

