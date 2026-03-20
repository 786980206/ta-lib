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

TA_LIB_API int TA_CDLRICKSHAWMAN_Lookback( void )
{
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;
   return fmax(fmax(BodyDoji_avgPeriod,ShadowLong_avgPeriod),Near_avgPeriod);
}

TA_LIB_API TA_RetCode TA_CDLRICKSHAWMAN( int    startIdx,
                                         int    endIdx,
                                         const double inOpen[],
                                         const double inHigh[],
                                         const double inLow[],
                                         const double inClose[],
                                         int          *outBegIdx,
                                         int          *outNBElement,
                                         int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double ShadowLongPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;

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

   lookbackTotal = TA_CDLRICKSHAWMAN_Lookback();
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
   BodyDojiPeriodTotal = 0;
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_0;
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_2;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((fmin(inOpen[i],inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(fmax(inOpen[i],inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_13;
      _candlerange_13 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_14;
      _candlerange_14 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_13-_candlerange_14);
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_15-_candlerange_16);
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_17-_candlerange_18);
      i += 1;
      BodyDojiTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLRICKSHAWMAN_Logic( int    startIdx,
                                               int    endIdx,
                                               const double inOpen[],
                                               const double inHigh[],
                                               const double inLow[],
                                               const double inClose[],
                                               int          *outBegIdx,
                                               int          *outNBElement,
                                               int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double ShadowLongPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;

   lookbackTotal = TA_CDLRICKSHAWMAN_Lookback();
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
   BodyDojiPeriodTotal = 0;
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_0;
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_2;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((fmin(inOpen[i],inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(fmax(inOpen[i],inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_13;
      _candlerange_13 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_14;
      _candlerange_14 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_13-_candlerange_14);
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_15-_candlerange_16);
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_17-_candlerange_18);
      i += 1;
      BodyDojiTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLRICKSHAWMAN TA_CDLRICKSHAWMAN_Logic

TA_RetCode TA_S_CDLRICKSHAWMAN( int    startIdx,
                                int    endIdx,
                                const float inOpen[],
                                const float inHigh[],
                                const float inLow[],
                                const float inClose[],
                                int          *outBegIdx,
                                int          *outNBElement,
                                int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double ShadowLongPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;

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

   lookbackTotal = TA_CDLRICKSHAWMAN_Lookback();
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
   BodyDojiPeriodTotal = 0;
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_0;
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_2;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((fmin(inOpen[i],inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(fmax(inOpen[i],inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_13;
      _candlerange_13 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_14;
      _candlerange_14 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_13-_candlerange_14);
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_15-_candlerange_16);
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_17-_candlerange_18);
      i += 1;
      BodyDojiTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLRICKSHAWMAN_Logic( int    startIdx,
                                      int    endIdx,
                                      const float inOpen[],
                                      const float inHigh[],
                                      const float inLow[],
                                      const float inClose[],
                                      int          *outBegIdx,
                                      int          *outNBElement,
                                      int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double ShadowLongPeriodTotal;
   double NearPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int ShadowLongTrailingIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_ShadowLong].factor;

   lookbackTotal = TA_CDLRICKSHAWMAN_Lookback();
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
   BodyDojiPeriodTotal = 0;
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   NearPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_0;
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
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      _candlerange_2 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      NearPeriodTotal += _candlerange_2;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      _candlerange_9 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      _candlerange_10 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      if( ((((fabs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((fmin(inOpen[i],inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(fmax(inOpen[i],inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_13;
      _candlerange_13 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_14;
      _candlerange_14 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_13-_candlerange_14);
      double _candlerange_15;
      _candlerange_15 = ((ShadowLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((ShadowLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((ShadowLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_16;
      _candlerange_16 = ((ShadowLong_rangeType==0) ? (fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]))) : (((ShadowLong_rangeType==1) ? ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])) : (((ShadowLong_rangeType==2) ? (((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-fabs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])))) : (0.0))))));
      ShadowLongPeriodTotal += (_candlerange_15-_candlerange_16);
      double _candlerange_17;
      _candlerange_17 = ((Near_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((Near_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((Near_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_18;
      _candlerange_18 = ((Near_rangeType==0) ? (fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]))) : (((Near_rangeType==1) ? ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])) : (((Near_rangeType==2) ? (((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-fabs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_17-_candlerange_18);
      i += 1;
      BodyDojiTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

