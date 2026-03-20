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

TA_LIB_API int TA_CDLHANGINGMAN_Lookback( void )
{
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(fmax(fmax(BodyShort_avgPeriod,ShadowLong_avgPeriod),ShadowVeryShort_avgPeriod),Near_avgPeriod)+1);
}

TA_LIB_API TA_RetCode TA_CDLHANGINGMAN( int    startIdx,
                                        int    endIdx,
                                        const double inOpen[],
                                        const double inHigh[],
                                        const double inLow[],
                                        const double inClose[],
                                        int          *outBegIdx,
                                        int          *outNBElement,
                                        int        outInteger[] )
{
   double BodyPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
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

   lookbackTotal = TA_CDLHANGINGMAN_Lookback();
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
   BodyPeriodTotal = 0;
   BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_10;
      _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(fmin(inClose[i],inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal += (_candlerange_12-_candlerange_13);
      double _candlerange_14;
      _candlerange_14 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_18-_candlerange_19);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLHANGINGMAN_Logic( int    startIdx,
                                              int    endIdx,
                                              const double inOpen[],
                                              const double inHigh[],
                                              const double inLow[],
                                              const double inClose[],
                                              int          *outBegIdx,
                                              int          *outNBElement,
                                              int        outInteger[] )
{
   double BodyPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLHANGINGMAN_Lookback();
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
   BodyPeriodTotal = 0;
   BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_10;
      _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(fmin(inClose[i],inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal += (_candlerange_12-_candlerange_13);
      double _candlerange_14;
      _candlerange_14 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_18-_candlerange_19);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLHANGINGMAN TA_CDLHANGINGMAN_Logic

TA_RetCode TA_S_CDLHANGINGMAN( int    startIdx,
                               int    endIdx,
                               const float inOpen[],
                               const float inHigh[],
                               const float inLow[],
                               const float inClose[],
                               int          *outBegIdx,
                               int          *outNBElement,
                               int        outInteger[] )
{
   double BodyPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
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

   lookbackTotal = TA_CDLHANGINGMAN_Lookback();
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
   BodyPeriodTotal = 0;
   BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_10;
      _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(fmin(inClose[i],inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal += (_candlerange_12-_candlerange_13);
      double _candlerange_14;
      _candlerange_14 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_18-_candlerange_19);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLHANGINGMAN_Logic( int    startIdx,
                                     int    endIdx,
                                     const float inOpen[],
                                     const float inHigh[],
                                     const float inLow[],
                                     const float inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double BodyPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLHANGINGMAN_Lookback();
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
   BodyPeriodTotal = 0;
   BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_3;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_10;
      _candlerange_10 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(fmin(inClose[i],inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_12;
      _candlerange_12 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])))) : (0.0))))));
      BodyPeriodTotal += (_candlerange_12-_candlerange_13);
      double _candlerange_14;
      _candlerange_14 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
      double _candlerange_16;
      _candlerange_16 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_17;
      _candlerange_17 = ((ShadowVeryShort_rangeType==0) ? (fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]))) : (((ShadowVeryShort_rangeType==1) ? ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])) : (((ShadowVeryShort_rangeType==2) ? (((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-fabs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])))) : (0.0))))));
      ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_19;
      _candlerange_19 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_18-_candlerange_19);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

