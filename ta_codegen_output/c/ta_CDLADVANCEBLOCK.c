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
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = TA_Globals->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = TA_Globals->candleSettings[TA_Far].avgPeriod;
   double Far_factor = TA_Globals->candleSettings[TA_Far].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = TA_Globals->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = TA_Globals->candleSettings[TA_ShadowShort].factor;
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
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = TA_Globals->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = TA_Globals->candleSettings[TA_Far].avgPeriod;
   double Far_factor = TA_Globals->candleSettings[TA_Far].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = TA_Globals->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = TA_Globals->candleSettings[TA_ShadowShort].factor;

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
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_2 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_4 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_21 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_21 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_21 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_21 = 0.0;
         break;
      }
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_22 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_22 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_22 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_22 = 0.0;
         break;
      }
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_23 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_24 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_25 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_25 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_25 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_25 = 0.0;
         break;
      }
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_26 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_26 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_26 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_26 = 0.0;
         break;
      }
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_27 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_27 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_27 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_27 = 0.0;
         break;
      }
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_28 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_28 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_28 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_28 = 0.0;
         break;
      }
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_29 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_29 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_29 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_29 = 0.0;
         break;
      }
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
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_30 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_30 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_30 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_30 = 0.0;
            break;
         }
         double _candlerange_31;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_31 = fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_31 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_31 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_31 = 0.0;
            break;
         }
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_32 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_32 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_32 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_32 = 0.0;
            break;
         }
         double _candlerange_33;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_33 = fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_33 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_33 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_33 = 0.0;
            break;
         }
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_34 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_34 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_34 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_34 = 0.0;
            break;
         }
         double _candlerange_35;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_35 = fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_35 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_35 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_35 = 0.0;
            break;
         }
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_36 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_36 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_36 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_36 = 0.0;
            break;
         }
         double _candlerange_37;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_37 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_37 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_37 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_37 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_38 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_38 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_38 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_38 = 0.0;
         break;
      }
      double _candlerange_39;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_39 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_39 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_39 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_39 = 0.0;
         break;
      }
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
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = TA_Globals->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = TA_Globals->candleSettings[TA_Far].avgPeriod;
   double Far_factor = TA_Globals->candleSettings[TA_Far].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = TA_Globals->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = TA_Globals->candleSettings[TA_ShadowShort].factor;

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
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_2 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_4 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_21 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_21 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_21 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_21 = 0.0;
         break;
      }
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_22 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_22 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_22 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_22 = 0.0;
         break;
      }
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_23 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_24 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_25 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_25 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_25 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_25 = 0.0;
         break;
      }
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_26 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_26 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_26 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_26 = 0.0;
         break;
      }
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_27 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_27 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_27 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_27 = 0.0;
         break;
      }
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_28 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_28 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_28 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_28 = 0.0;
         break;
      }
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_29 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_29 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_29 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_29 = 0.0;
         break;
      }
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
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_30 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_30 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_30 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_30 = 0.0;
            break;
         }
         double _candlerange_31;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_31 = fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_31 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_31 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_31 = 0.0;
            break;
         }
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_32 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_32 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_32 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_32 = 0.0;
            break;
         }
         double _candlerange_33;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_33 = fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_33 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_33 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_33 = 0.0;
            break;
         }
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_34 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_34 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_34 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_34 = 0.0;
            break;
         }
         double _candlerange_35;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_35 = fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_35 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_35 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_35 = 0.0;
            break;
         }
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_36 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_36 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_36 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_36 = 0.0;
            break;
         }
         double _candlerange_37;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_37 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_37 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_37 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_37 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_38 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_38 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_38 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_38 = 0.0;
         break;
      }
      double _candlerange_39;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_39 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_39 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_39 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_39 = 0.0;
         break;
      }
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
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = TA_Globals->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = TA_Globals->candleSettings[TA_Far].avgPeriod;
   double Far_factor = TA_Globals->candleSettings[TA_Far].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = TA_Globals->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = TA_Globals->candleSettings[TA_ShadowShort].factor;

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
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_2 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_4 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_21 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_21 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_21 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_21 = 0.0;
         break;
      }
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_22 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_22 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_22 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_22 = 0.0;
         break;
      }
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_23 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_24 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_25 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_25 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_25 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_25 = 0.0;
         break;
      }
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_26 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_26 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_26 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_26 = 0.0;
         break;
      }
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_27 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_27 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_27 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_27 = 0.0;
         break;
      }
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_28 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_28 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_28 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_28 = 0.0;
         break;
      }
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_29 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_29 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_29 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_29 = 0.0;
         break;
      }
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
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_30 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_30 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_30 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_30 = 0.0;
            break;
         }
         double _candlerange_31;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_31 = fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_31 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_31 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_31 = 0.0;
            break;
         }
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_32 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_32 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_32 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_32 = 0.0;
            break;
         }
         double _candlerange_33;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_33 = fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_33 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_33 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_33 = 0.0;
            break;
         }
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_34 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_34 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_34 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_34 = 0.0;
            break;
         }
         double _candlerange_35;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_35 = fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_35 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_35 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_35 = 0.0;
            break;
         }
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_36 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_36 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_36 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_36 = 0.0;
            break;
         }
         double _candlerange_37;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_37 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_37 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_37 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_37 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_38 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_38 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_38 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_38 = 0.0;
         break;
      }
      double _candlerange_39;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_39 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_39 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_39 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_39 = 0.0;
         break;
      }
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
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int Far_rangeType = TA_Globals->candleSettings[TA_Far].rangeType;
   int Far_avgPeriod = TA_Globals->candleSettings[TA_Far].avgPeriod;
   double Far_factor = TA_Globals->candleSettings[TA_Far].factor;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowShort_rangeType = TA_Globals->candleSettings[TA_ShadowShort].rangeType;
   int ShadowShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowShort].avgPeriod;
   double ShadowShort_factor = TA_Globals->candleSettings[TA_ShadowShort].factor;

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
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
      double _candlerange_2;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_2 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_3;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
      double _candlerange_4;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_4 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
      i += 1;
   }
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_5;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
      i += 1;
   }
   i = FarTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_7;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
      double _candlerange_8;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_9;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_9;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_10;
      double _candlerange_20;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      double avg_10 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_20));
      double divisor_10 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((Near_factor*avg_10)/divisor_10);
      double _candleaverage_11;
      double _candlerange_21;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_21 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_21 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_21 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_21 = 0.0;
         break;
      }
      double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_21));
      double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
      double _candleaverage_12;
      double _candlerange_22;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_22 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_22 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_22 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_22 = 0.0;
         break;
      }
      double avg_12 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_22));
      double divisor_12 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_12 = ((BodyLong_factor*avg_12)/divisor_12);
      double _candleaverage_13;
      double _candlerange_23;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_23 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double avg_13 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[2]/ShadowShort_avgPeriod)) : (_candlerange_23));
      double divisor_13 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_13 = ((ShadowShort_factor*avg_13)/divisor_13);
      double _candleaverage_14;
      double _candlerange_24;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_24 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (_candlerange_24));
      double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
      double _candleaverage_15;
      double _candlerange_25;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_25 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_25 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_25 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_25 = 0.0;
         break;
      }
      double avg_15 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (_candlerange_25));
      double divisor_15 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_15 = ((Near_factor*avg_15)/divisor_15);
      double _candleaverage_16;
      double _candlerange_26;
      switch( Far_rangeType )
      {
      case 0:
         _candlerange_26 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_26 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_26 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_26 = 0.0;
         break;
      }
      double avg_16 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (_candlerange_26));
      double divisor_16 = (((Far_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_16 = ((Far_factor*avg_16)/divisor_16);
      double _candleaverage_17;
      double _candlerange_27;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_27 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_27 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_27 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_27 = 0.0;
         break;
      }
      double avg_17 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[0]/ShadowShort_avgPeriod)) : (_candlerange_27));
      double divisor_17 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_17 = ((ShadowShort_factor*avg_17)/divisor_17);
      double _candleaverage_18;
      double _candlerange_28;
      switch( ShadowShort_rangeType )
      {
      case 0:
         _candlerange_28 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_28 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_28 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_28 = 0.0;
         break;
      }
      double avg_18 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowShortPeriodTotal[1]/ShadowShort_avgPeriod)) : (_candlerange_28));
      double divisor_18 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_18 = ((ShadowShort_factor*avg_18)/divisor_18);
      double _candleaverage_19;
      double _candlerange_29;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_29 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_29 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_29 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_29 = 0.0;
         break;
      }
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
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_30 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_30 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_30 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_30 = 0.0;
            break;
         }
         double _candlerange_31;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_31 = fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_31 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_31 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_31 = 0.0;
            break;
         }
         ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_30-_candlerange_31));
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_32;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_32 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_32 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_32 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_32 = 0.0;
            break;
         }
         double _candlerange_33;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_33 = fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_33 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_33 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-fabs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_33 = 0.0;
            break;
         }
         ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_32-_candlerange_33));
      }
      for( totIdx = 2; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_34;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_34 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_34 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_34 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_34 = 0.0;
            break;
         }
         double _candlerange_35;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_35 = fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_35 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_35 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-fabs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_35 = 0.0;
            break;
         }
         FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_34-_candlerange_35));
         double _candlerange_36;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_36 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_36 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_36 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_36 = 0.0;
            break;
         }
         double _candlerange_37;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_37 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_37 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_37 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_37 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_36-_candlerange_37));
      }
      double _candlerange_38;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_38 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_38 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_38 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_38 = 0.0;
         break;
      }
      double _candlerange_39;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_39 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_39 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_39 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_39 = 0.0;
         break;
      }
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

