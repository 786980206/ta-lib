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

TA_LIB_API int TA_CDL3WHITESOLDIERS_Lookback( void )
{
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(fmax(ShadowVeryShort_avgPeriod,BodyShort_avgPeriod),fmax(Far_avgPeriod,Near_avgPeriod))+2);
}

TA_LIB_API TA_RetCode TA_CDL3WHITESOLDIERS( int    startIdx,
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
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].factor;

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

   lookbackTotal = TA_CDL3WHITESOLDIERS_Lookback();
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
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_7;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_8;
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_17));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_18;
      _candlerange_18 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_18));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_19));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_21;
      _candlerange_21 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_21));
      double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_22;
      _candlerange_22 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_22));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_23));
      double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
      if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(fabs((inClose[i]-inOpen[i]))>(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_15)) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_24;
         _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_25;
         _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_24-_candlerange_25));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_26;
         _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_27;
         _candlerange_27 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_26-_candlerange_27));
         double _candlerange_28;
         _candlerange_28 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_29;
         _candlerange_29 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_28-_candlerange_29));
      }
      double _candlerange_30;
      _candlerange_30 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_31;
      _candlerange_31 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_30-_candlerange_31);
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDL3WHITESOLDIERS_Logic( int    startIdx,
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
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3WHITESOLDIERS_Lookback();
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
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_7;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_8;
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_17));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_18;
      _candlerange_18 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_18));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_19));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_21;
      _candlerange_21 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_21));
      double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_22;
      _candlerange_22 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_22));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_23));
      double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
      if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(fabs((inClose[i]-inOpen[i]))>(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_15)) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_24;
         _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_25;
         _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_24-_candlerange_25));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_26;
         _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_27;
         _candlerange_27 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_26-_candlerange_27));
         double _candlerange_28;
         _candlerange_28 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_29;
         _candlerange_29 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_28-_candlerange_29));
      }
      double _candlerange_30;
      _candlerange_30 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_31;
      _candlerange_31 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_30-_candlerange_31);
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDL3WHITESOLDIERS TA_CDL3WHITESOLDIERS_Logic

TA_RetCode TA_S_CDL3WHITESOLDIERS( int    startIdx,
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
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].factor;

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

   lookbackTotal = TA_CDL3WHITESOLDIERS_Lookback();
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
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_7;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_8;
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_17));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_18;
      _candlerange_18 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_18));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_19));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_21;
      _candlerange_21 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_21));
      double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_22;
      _candlerange_22 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_22));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_23));
      double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
      if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(fabs((inClose[i]-inOpen[i]))>(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_15)) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_24;
         _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_25;
         _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_24-_candlerange_25));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_26;
         _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_27;
         _candlerange_27 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_26-_candlerange_27));
         double _candlerange_28;
         _candlerange_28 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_29;
         _candlerange_29 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_28-_candlerange_29));
      }
      double _candlerange_30;
      _candlerange_30 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_31;
      _candlerange_31 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_30-_candlerange_31);
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDL3WHITESOLDIERS_Logic( int    startIdx,
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
   double NearPeriodTotal[3];
   double FarPeriodTotal[3];
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int FarTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   int Far_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].avgPeriod;
   double Far_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Far].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3WHITESOLDIERS_Lookback();
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
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   FarPeriodTotal[2] = 0;
   FarPeriodTotal[1] = 0;
   FarPeriodTotal[0] = 0;
   FarTrailingIdx = (startIdx-Far_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      _candlerange_5 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      _candlerange_6 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      _candlerange_7 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_7;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_8;
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_17));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_18;
      _candlerange_18 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_18));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_19));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_20;
      _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_21;
      _candlerange_21 = ((Far_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Far_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Far_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_21));
      double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_22;
      _candlerange_22 = ((Far_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Far_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Far_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_22));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_23));
      double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
      if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>(fabs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(fabs((inClose[i]-inOpen[i]))>(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_15)) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_24;
         _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_25;
         _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])))) : (0.0))))));
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_24-_candlerange_25));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_26;
         _candlerange_26 = ((Far_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_27;
         _candlerange_27 = ((Far_rangeType==0) ? (fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]))) : (((Far_rangeType==1) ? ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])) : (((Far_rangeType==2) ? (((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])))) : (0.0))))));
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_26-_candlerange_27));
         double _candlerange_28;
         _candlerange_28 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_29;
         _candlerange_29 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_28-_candlerange_29));
      }
      double _candlerange_30;
      _candlerange_30 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_31;
      _candlerange_31 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_30-_candlerange_31);
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
      FarTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

