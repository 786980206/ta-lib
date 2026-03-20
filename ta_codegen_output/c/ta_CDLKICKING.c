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

TA_LIB_API int TA_CDLKICKING_Lookback( void )
{
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (fmax(ShadowVeryShort_avgPeriod,BodyLong_avgPeriod)+1);
}

TA_LIB_API TA_RetCode TA_CDLKICKING( int    startIdx,
                                     int    endIdx,
                                     const double inOpen[],
                                     const double inHigh[],
                                     const double inLow[],
                                     const double inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[2];
   double BodyLongPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
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

   lookbackTotal = TA_CDLKICKING_Lookback();
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
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_1 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_13 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( ShadowVeryShort_rangeType )
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
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
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
      if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_17 = fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_17 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         double _candlerange_18;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_18 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_19 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLKICKING_Logic( int    startIdx,
                                           int    endIdx,
                                           const double inOpen[],
                                           const double inHigh[],
                                           const double inLow[],
                                           const double inClose[],
                                           int          *outBegIdx,
                                           int          *outNBElement,
                                           int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[2];
   double BodyLongPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLKICKING_Lookback();
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
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_1 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_13 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( ShadowVeryShort_rangeType )
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
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
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
      if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_17 = fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_17 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         double _candlerange_18;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_18 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_19 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLKICKING TA_CDLKICKING_Logic

TA_RetCode TA_S_CDLKICKING( int    startIdx,
                            int    endIdx,
                            const float inOpen[],
                            const float inHigh[],
                            const float inLow[],
                            const float inClose[],
                            int          *outBegIdx,
                            int          *outNBElement,
                            int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[2];
   double BodyLongPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
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

   lookbackTotal = TA_CDLKICKING_Lookback();
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
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_1 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_13 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( ShadowVeryShort_rangeType )
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
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
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
      if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_17 = fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_17 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         double _candlerange_18;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_18 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_19 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLKICKING_Logic( int    startIdx,
                                  int    endIdx,
                                  const float inOpen[],
                                  const float inHigh[],
                                  const float inLow[],
                                  const float inClose[],
                                  int          *outBegIdx,
                                  int          *outNBElement,
                                  int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[2];
   double BodyLongPeriodTotal[2];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLKICKING_Lookback();
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
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortPeriodTotal[0] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   BodyLongPeriodTotal[1] = 0;
   BodyLongPeriodTotal[0] = 0;
   BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_1 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_1 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_1 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_1 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
      i += 1;
   }
   i = BodyLongTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
      double _candlerange_3;
      switch( BodyLong_rangeType )
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
      BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_4;
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_10));
      double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_12;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
      double _candlerange_13;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_13 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_13 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_13 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_13 = 0.0;
         break;
      }
      double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_13));
      double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_14;
      switch( ShadowVeryShort_rangeType )
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
      double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (_candlerange_14));
      double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
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
      if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 1; (totIdx>=0); totIdx -= 1 )
      {
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_17 = fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_17 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-fabs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         double _candlerange_18;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_18 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_19 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
      BodyLongTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

