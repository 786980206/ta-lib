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

TA_LIB_API int TA_CDL3STARSINSOUTH_Lookback( void )
{
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(fmax(ShadowVeryShort_avgPeriod,ShadowLong_avgPeriod),fmax(BodyLong_avgPeriod,BodyShort_avgPeriod))+2);
}

TA_LIB_API TA_RetCode TA_CDL3STARSINSOUTH( int    startIdx,
                                           int    endIdx,
                                           const double inOpen[],
                                           const double inHigh[],
                                           const double inLow[],
                                           const double inClose[],
                                           int          *outBegIdx,
                                           int          *outNBElement,
                                           int        outInteger[] )
{
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
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

   lookbackTotal = TA_CDL3STARSINSOUTH_Lookback();
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
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_3 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_4;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_11;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_14 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_15 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_15 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_15 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_15 = 0.0;
         break;
      }
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_16 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_16 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_16 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_16 = 0.0;
         break;
      }
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_17;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_17 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_17 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_17 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_17 = 0.0;
         break;
      }
      double _candlerange_18;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_18 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_18 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_18 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_18 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_17-_candlerange_18);
      double _candlerange_19;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_19 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_19 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_19 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_19 = 0.0;
         break;
      }
      double _candlerange_20;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += (_candlerange_19-_candlerange_20);
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_21;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_21 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_21 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_21 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_21 = 0.0;
            break;
         }
         double _candlerange_22;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_22 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_22 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      double _candlerange_23;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_23 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double _candlerange_24;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_24 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_23-_candlerange_24);
      i += 1;
      BodyLongTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDL3STARSINSOUTH_Logic( int    startIdx,
                                                 int    endIdx,
                                                 const double inOpen[],
                                                 const double inHigh[],
                                                 const double inLow[],
                                                 const double inClose[],
                                                 int          *outBegIdx,
                                                 int          *outNBElement,
                                                 int        outInteger[] )
{
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3STARSINSOUTH_Lookback();
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
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_3 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_4;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_11;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_14 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_15 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_15 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_15 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_15 = 0.0;
         break;
      }
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_16 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_16 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_16 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_16 = 0.0;
         break;
      }
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_17;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_17 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_17 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_17 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_17 = 0.0;
         break;
      }
      double _candlerange_18;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_18 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_18 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_18 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_18 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_17-_candlerange_18);
      double _candlerange_19;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_19 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_19 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_19 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_19 = 0.0;
         break;
      }
      double _candlerange_20;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += (_candlerange_19-_candlerange_20);
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_21;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_21 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_21 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_21 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_21 = 0.0;
            break;
         }
         double _candlerange_22;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_22 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_22 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      double _candlerange_23;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_23 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double _candlerange_24;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_24 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_23-_candlerange_24);
      i += 1;
      BodyLongTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDL3STARSINSOUTH TA_CDL3STARSINSOUTH_Logic

TA_RetCode TA_S_CDL3STARSINSOUTH( int    startIdx,
                                  int    endIdx,
                                  const float inOpen[],
                                  const float inHigh[],
                                  const float inLow[],
                                  const float inClose[],
                                  int          *outBegIdx,
                                  int          *outNBElement,
                                  int        outInteger[] )
{
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
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

   lookbackTotal = TA_CDL3STARSINSOUTH_Lookback();
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
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_3 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_4;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_11;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_14 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_15 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_15 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_15 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_15 = 0.0;
         break;
      }
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_16 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_16 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_16 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_16 = 0.0;
         break;
      }
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_17;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_17 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_17 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_17 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_17 = 0.0;
         break;
      }
      double _candlerange_18;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_18 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_18 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_18 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_18 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_17-_candlerange_18);
      double _candlerange_19;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_19 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_19 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_19 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_19 = 0.0;
         break;
      }
      double _candlerange_20;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += (_candlerange_19-_candlerange_20);
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_21;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_21 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_21 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_21 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_21 = 0.0;
            break;
         }
         double _candlerange_22;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_22 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_22 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      double _candlerange_23;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_23 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double _candlerange_24;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_24 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_23-_candlerange_24);
      i += 1;
      BodyLongTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDL3STARSINSOUTH_Logic( int    startIdx,
                                        int    endIdx,
                                        const float inOpen[],
                                        const float inHigh[],
                                        const float inLow[],
                                        const float inClose[],
                                        int          *outBegIdx,
                                        int          *outNBElement,
                                        int        outInteger[] )
{
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   double ShadowLongPeriodTotal;
   double ShadowVeryShortPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int ShadowLongTrailingIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowLong_rangeType = TA_Globals->candleSettings[TA_ShadowLong].rangeType;
   int ShadowLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowLong].avgPeriod;
   double ShadowLong_factor = TA_Globals->candleSettings[TA_ShadowLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDL3STARSINSOUTH_Lookback();
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
   BodyLongPeriodTotal = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   ShadowLongPeriodTotal = 0;
   ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyShortPeriodTotal = 0;
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_2 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_2 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_3 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_3 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_3 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_3 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_4;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_4;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_5;
      double _candlerange_11;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_14 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
      double _candleaverage_9;
      double _candlerange_15;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_15 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_15 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_15 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_15 = 0.0;
         break;
      }
      double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_15));
      double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
      double _candleaverage_10;
      double _candlerange_16;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_16 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_16 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_16 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_16 = 0.0;
         break;
      }
      double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_16));
      double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
      if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<fabs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(fabs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_17;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_17 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_17 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_17 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_17 = 0.0;
         break;
      }
      double _candlerange_18;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_18 = fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_18 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_18 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-fabs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_18 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_17-_candlerange_18);
      double _candlerange_19;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_19 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_19 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_19 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_19 = 0.0;
         break;
      }
      double _candlerange_20;
      switch( ShadowLong_rangeType )
      {
      case 0:
         _candlerange_20 = fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
         break;
      case 1:
         _candlerange_20 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
         break;
      case 2:
         _candlerange_20 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-fabs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
         break;
      default:
         _candlerange_20 = 0.0;
         break;
      }
      ShadowLongPeriodTotal += (_candlerange_19-_candlerange_20);
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_21;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_21 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_21 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_21 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_21 = 0.0;
            break;
         }
         double _candlerange_22;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_22 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_22 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_21-_candlerange_22));
      }
      double _candlerange_23;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_23 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_23 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_23 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_23 = 0.0;
         break;
      }
      double _candlerange_24;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_24 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_24 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_24 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_24 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_23-_candlerange_24);
      i += 1;
      BodyLongTrailingIdx += 1;
      ShadowLongTrailingIdx += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

