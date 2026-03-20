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

TA_LIB_API int TA_CDLSTALLEDPATTERN_Lookback( void )
{
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(fmax(BodyLong_avgPeriod,BodyShort_avgPeriod),fmax(ShadowVeryShort_avgPeriod,Near_avgPeriod))+2);
}

TA_LIB_API TA_RetCode TA_CDLSTALLEDPATTERN( int    startIdx,
                                            int    endIdx,
                                            const double inOpen[],
                                            const double inHigh[],
                                            const double inLow[],
                                            const double inClose[],
                                            int          *outBegIdx,
                                            int          *outNBElement,
                                            int        outInteger[] )
{
   double BodyLongPeriodTotal[3];
   double NearPeriodTotal[3];
   double BodyShortPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
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

   lookbackTotal = TA_CDLSTALLEDPATTERN_Lookback();
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
   BodyLongPeriodTotal[2] = 0;
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_6;
      double _candlerange_12;
      _candlerange_12 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_6 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[2]/BodyLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      _candlerange_13 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      _candlerange_15 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Near_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      _candlerange_16 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((BodyShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_17));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_7))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_8))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_9)))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_10))&&(inOpen[i]>=((inClose[(i-1)]-fabs((inClose[i]-inOpen[i])))-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_18;
         _candlerange_18 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_19;
         _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])))) : (0.0))))));
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
         double _candlerange_20;
         _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_21;
         _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
      }
      double _candlerange_22;
      _candlerange_22 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
      double _candlerange_24;
      _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_25;
      _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_24-_candlerange_25);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLSTALLEDPATTERN_Logic( int    startIdx,
                                                  int    endIdx,
                                                  const double inOpen[],
                                                  const double inHigh[],
                                                  const double inLow[],
                                                  const double inClose[],
                                                  int          *outBegIdx,
                                                  int          *outNBElement,
                                                  int        outInteger[] )
{
   double BodyLongPeriodTotal[3];
   double NearPeriodTotal[3];
   double BodyShortPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLSTALLEDPATTERN_Lookback();
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
   BodyLongPeriodTotal[2] = 0;
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_6;
      double _candlerange_12;
      _candlerange_12 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_6 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[2]/BodyLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      _candlerange_13 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      _candlerange_15 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Near_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      _candlerange_16 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((BodyShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_17));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_7))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_8))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_9)))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_10))&&(inOpen[i]>=((inClose[(i-1)]-fabs((inClose[i]-inOpen[i])))-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_18;
         _candlerange_18 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_19;
         _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])))) : (0.0))))));
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
         double _candlerange_20;
         _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_21;
         _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
      }
      double _candlerange_22;
      _candlerange_22 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
      double _candlerange_24;
      _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_25;
      _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_24-_candlerange_25);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLSTALLEDPATTERN TA_CDLSTALLEDPATTERN_Logic

TA_RetCode TA_S_CDLSTALLEDPATTERN( int    startIdx,
                                   int    endIdx,
                                   const float inOpen[],
                                   const float inHigh[],
                                   const float inLow[],
                                   const float inClose[],
                                   int          *outBegIdx,
                                   int          *outNBElement,
                                   int        outInteger[] )
{
   double BodyLongPeriodTotal[3];
   double NearPeriodTotal[3];
   double BodyShortPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
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

   lookbackTotal = TA_CDLSTALLEDPATTERN_Lookback();
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
   BodyLongPeriodTotal[2] = 0;
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_6;
      double _candlerange_12;
      _candlerange_12 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_6 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[2]/BodyLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      _candlerange_13 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      _candlerange_15 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Near_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      _candlerange_16 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((BodyShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_17));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_7))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_8))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_9)))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_10))&&(inOpen[i]>=((inClose[(i-1)]-fabs((inClose[i]-inOpen[i])))-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_18;
         _candlerange_18 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_19;
         _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])))) : (0.0))))));
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
         double _candlerange_20;
         _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_21;
         _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
      }
      double _candlerange_22;
      _candlerange_22 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
      double _candlerange_24;
      _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_25;
      _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_24-_candlerange_25);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLSTALLEDPATTERN_Logic( int    startIdx,
                                         int    endIdx,
                                         const float inOpen[],
                                         const float inHigh[],
                                         const float inLow[],
                                         const float inClose[],
                                         int          *outBegIdx,
                                         int          *outNBElement,
                                         int        outInteger[] )
{
   double BodyLongPeriodTotal[3];
   double NearPeriodTotal[3];
   double BodyShortPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLSTALLEDPATTERN_Lookback();
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
   BodyLongPeriodTotal[2] = 0;
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal[2] = 0;
   NearPeriodTotal[1] = 0;
   NearPeriodTotal[0] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      _candlerange_1 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      _candlerange_3 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_6;
      double _candlerange_12;
      _candlerange_12 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_6 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[2]/BodyLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((BodyLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      _candlerange_13 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      _candlerange_14 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      _candlerange_15 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_9 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((Near_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      _candlerange_16 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_10 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((BodyShort_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_17));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_7))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_8))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_9)))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_10))&&(inOpen[i]>=((inClose[(i-1)]-fabs((inClose[i]-inOpen[i])))-_candleaverage_11))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_18;
         _candlerange_18 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_19;
         _candlerange_19 = ((BodyLong_rangeType==0) ? (fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])) : (((BodyLong_rangeType==2) ? (((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])))) : (0.0))))));
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
         double _candlerange_20;
         _candlerange_20 = ((Near_rangeType==0) ? (fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])))) : (0.0))))));
         double _candlerange_21;
         _candlerange_21 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])))) : (0.0))))));
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
      }
      double _candlerange_22;
      _candlerange_22 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_23;
      _candlerange_23 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
      BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
      double _candlerange_24;
      _candlerange_24 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_25;
      _candlerange_25 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-fabs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_24-_candlerange_25);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

