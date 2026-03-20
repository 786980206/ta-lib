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

TA_LIB_API int TA_CDLADVANCEBLOCK_Lookback( void )
{
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].factor;
   return (fmax(fmax(fmax(ShadowLong_avgPeriod,ShadowShort_avgPeriod),fmax(Far_avgPeriod,Near_avgPeriod)),BodyLong_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDLADVANCEBLOCK( int    startIdx,
                                          int    endIdx,
                                          const double inOpen[],
                                          const double inHigh[],
                                          const double inLow[],
                                          const double inClose[],
                                          int          *outBegIdx,
                                          int          *outNBElement,
                                          int        outInteger[] )
{
   double ShadowShortPeriodTotal[3];
   double ShadowLongPeriodTotal[2];
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int ShadowShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].factor;

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

   lookbackTotal = TA_CDLADVANCEBLOCK_Lookback();
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
   ShadowShortPeriodTotal[2] = 0;
   ShadowShortPeriodTotal[1] = 0;
   ShadowShortPeriodTotal[0] = 0;
   ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
   ShadowLongPeriodTotal[1] = 0;
   ShadowLongPeriodTotal[0] = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      _candlerange_9 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      _candlerange_22 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      _candlerange_23 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      _candlerange_24 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      _candlerange_25 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      _candlerange_27 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      _candlerange_28 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      _candlerange_29 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_19 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal[0]/ShadowLong_avgPeriod)) : (_candlerange_29));
      double divisor_19 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_19 = ((ShadowLong_factor*avg_19)/divisor_19);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_10)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_11)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_12))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_13))&&(((((fabs((inClose[(i-1)]-inOpen[(i-1)]))<(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_14))&&(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_15)))||(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_16)))||(((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_17)||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_18))))||((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_19)))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_30;
         _candlerange_30 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_31;
         _candlerange_31 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         _candlerange_32 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_33;
         _candlerange_33 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         _candlerange_34 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_35;
         _candlerange_35 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         _candlerange_36 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_37;
         _candlerange_37 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      _candlerange_38 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_39;
      _candlerange_39 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_38-_candlerange_39);
      i += 1;
      ShadowShortTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLADVANCEBLOCK_Logic( int    startIdx,
                                                int    endIdx,
                                                const double inOpen[],
                                                const double inHigh[],
                                                const double inLow[],
                                                const double inClose[],
                                                int          *outBegIdx,
                                                int          *outNBElement,
                                                int        outInteger[] )
{
   double ShadowShortPeriodTotal[3];
   double ShadowLongPeriodTotal[2];
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int ShadowShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].factor;

   lookbackTotal = TA_CDLADVANCEBLOCK_Lookback();
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
   ShadowShortPeriodTotal[2] = 0;
   ShadowShortPeriodTotal[1] = 0;
   ShadowShortPeriodTotal[0] = 0;
   ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
   ShadowLongPeriodTotal[1] = 0;
   ShadowLongPeriodTotal[0] = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      _candlerange_9 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      _candlerange_22 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      _candlerange_23 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      _candlerange_24 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      _candlerange_25 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      _candlerange_27 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      _candlerange_28 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      _candlerange_29 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_19 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal[0]/ShadowLong_avgPeriod)) : (_candlerange_29));
      double divisor_19 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_19 = ((ShadowLong_factor*avg_19)/divisor_19);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_10)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_11)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_12))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_13))&&(((((fabs((inClose[(i-1)]-inOpen[(i-1)]))<(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_14))&&(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_15)))||(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_16)))||(((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_17)||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_18))))||((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_19)))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_30;
         _candlerange_30 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_31;
         _candlerange_31 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         _candlerange_32 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_33;
         _candlerange_33 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         _candlerange_34 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_35;
         _candlerange_35 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         _candlerange_36 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_37;
         _candlerange_37 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      _candlerange_38 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_39;
      _candlerange_39 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_38-_candlerange_39);
      i += 1;
      ShadowShortTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLADVANCEBLOCK TA_CDLADVANCEBLOCK_Logic

TA_RetCode TA_S_CDLADVANCEBLOCK( int    startIdx,
                                 int    endIdx,
                                 const float inOpen[],
                                 const float inHigh[],
                                 const float inLow[],
                                 const float inClose[],
                                 int          *outBegIdx,
                                 int          *outNBElement,
                                 int        outInteger[] )
{
   double ShadowShortPeriodTotal[3];
   double ShadowLongPeriodTotal[2];
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int ShadowShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].factor;

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

   lookbackTotal = TA_CDLADVANCEBLOCK_Lookback();
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
   ShadowShortPeriodTotal[2] = 0;
   ShadowShortPeriodTotal[1] = 0;
   ShadowShortPeriodTotal[0] = 0;
   ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
   ShadowLongPeriodTotal[1] = 0;
   ShadowLongPeriodTotal[0] = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      _candlerange_9 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      _candlerange_22 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      _candlerange_23 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      _candlerange_24 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      _candlerange_25 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      _candlerange_27 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      _candlerange_28 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      _candlerange_29 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_19 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal[0]/ShadowLong_avgPeriod)) : (_candlerange_29));
      double divisor_19 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_19 = ((ShadowLong_factor*avg_19)/divisor_19);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_10)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_11)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_12))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_13))&&(((((fabs((inClose[(i-1)]-inOpen[(i-1)]))<(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_14))&&(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_15)))||(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_16)))||(((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_17)||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_18))))||((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_19)))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_30;
         _candlerange_30 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_31;
         _candlerange_31 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         _candlerange_32 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_33;
         _candlerange_33 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         _candlerange_34 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_35;
         _candlerange_35 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         _candlerange_36 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_37;
         _candlerange_37 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      _candlerange_38 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_39;
      _candlerange_39 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_38-_candlerange_39);
      i += 1;
      ShadowShortTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLADVANCEBLOCK_Logic( int    startIdx,
                                       int    endIdx,
                                       const float inOpen[],
                                       const float inHigh[],
                                       const float inLow[],
                                       const float inClose[],
                                       int          *outBegIdx,
                                       int          *outNBElement,
                                       int        outInteger[] )
{
   double ShadowShortPeriodTotal[3];
   double ShadowLongPeriodTotal[2];
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int ShadowShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowShort].factor;

   lookbackTotal = TA_CDLADVANCEBLOCK_Lookback();
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
   ShadowShortPeriodTotal[2] = 0;
   ShadowShortPeriodTotal[1] = 0;
   ShadowShortPeriodTotal[0] = 0;
   ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
   ShadowLongPeriodTotal[1] = 0;
   ShadowLongPeriodTotal[0] = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      _candlerange_2 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      _candlerange_9 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      _candlerange_22 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      _candlerange_23 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      _candlerange_24 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      _candlerange_25 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      _candlerange_27 = ((ShadowShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      _candlerange_28 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      _candlerange_29 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_19 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal[0]/ShadowLong_avgPeriod)) : (_candlerange_29));
      double divisor_19 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_19 = ((ShadowLong_factor*avg_19)/divisor_19);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_10)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_11)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_12))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_13))&&(((((fabs((inClose[(i-1)]-inOpen[(i-1)]))<(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_14))&&(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_15)))||(fabs((inClose[i]-inOpen[i]))<(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_16)))||(((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_17)||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_18))))||((fabs((inClose[i]-inOpen[i]))<fabs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_19)))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_30;
         _candlerange_30 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_31;
         _candlerange_31 = ((ShadowShort_rangeType==0) ? (fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]))) : (((ShadowShort_rangeType==1) ? ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])) : (((ShadowShort_rangeType==2) ? (((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         _candlerange_32 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_33;
         _candlerange_33 = ((ShadowLong_rangeType==0) ? (fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]))) : (((ShadowLong_rangeType==1) ? ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])) : (((ShadowLong_rangeType==2) ? (((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         _candlerange_34 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_35;
         _candlerange_35 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         _candlerange_36 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_37;
         _candlerange_37 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      _candlerange_38 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_39;
      _candlerange_39 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_38-_candlerange_39);
      i += 1;
      ShadowShortTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

