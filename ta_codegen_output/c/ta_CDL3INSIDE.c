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

TA_LIB_API int TA_CDL3INSIDE_Lookback( void )
{
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   return (fmax(BodyShort_avgPeriod,BodyLong_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDL3INSIDE( int    startIdx,
                                     int    endIdx,
                                     const double inOpen[],
                                     const double inHigh[],
                                     const double inLow[],
                                     const double inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double BodyShortPeriodTotal;
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDL3INSIDE_Lookback();
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
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-2)) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_0 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( (((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2)&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(fmax(inClose[(i-1)],inOpen[(i-1)])<fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fmin(inClose[(i-1)],inOpen[(i-1)])>fmin(inClose[(i-2)],inOpen[(i-2)])))&&(((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<inOpen[(i-2)]))||((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inOpen[(i-2)])))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double _candlerange_7;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_7 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      switch( BodyShort_rangeType )
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDL3INSIDE_Logic( int    startIdx,
                                           int    endIdx,
                                           const double inOpen[],
                                           const double inHigh[],
                                           const double inLow[],
                                           const double inClose[],
                                           int          *outBegIdx,
                                           int          *outNBElement,
                                           int        outInteger[] )
{
   double BodyShortPeriodTotal;
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDL3INSIDE_Lookback();
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
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-2)) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_0 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( (((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2)&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(fmax(inClose[(i-1)],inOpen[(i-1)])<fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fmin(inClose[(i-1)],inOpen[(i-1)])>fmin(inClose[(i-2)],inOpen[(i-2)])))&&(((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<inOpen[(i-2)]))||((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inOpen[(i-2)])))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double _candlerange_7;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_7 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      switch( BodyShort_rangeType )
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDL3INSIDE TA_CDL3INSIDE_Logic

TA_RetCode TA_S_CDL3INSIDE( int    startIdx,
                            int    endIdx,
                            const float inOpen[],
                            const float inHigh[],
                            const float inLow[],
                            const float inClose[],
                            int          *outBegIdx,
                            int          *outNBElement,
                            int        outInteger[] )
{
   double BodyShortPeriodTotal;
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDL3INSIDE_Lookback();
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
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-2)) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_0 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( (((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2)&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(fmax(inClose[(i-1)],inOpen[(i-1)])<fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fmin(inClose[(i-1)],inOpen[(i-1)])>fmin(inClose[(i-2)],inOpen[(i-2)])))&&(((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<inOpen[(i-2)]))||((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inOpen[(i-2)])))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double _candlerange_7;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_7 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      switch( BodyShort_rangeType )
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDL3INSIDE_Logic( int    startIdx,
                                  int    endIdx,
                                  const float inOpen[],
                                  const float inHigh[],
                                  const float inLow[],
                                  const float inClose[],
                                  int          *outBegIdx,
                                  int          *outNBElement,
                                  int        outInteger[] )
{
   double BodyShortPeriodTotal;
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyShortTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDL3INSIDE_Lookback();
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
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-2)) )
   {
      double _candlerange_0;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_0 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( (((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2)&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(fmax(inClose[(i-1)],inOpen[(i-1)])<fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fmin(inClose[(i-1)],inOpen[(i-1)])>fmin(inClose[(i-2)],inOpen[(i-2)])))&&(((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<inOpen[(i-2)]))||((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inOpen[(i-2)])))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double _candlerange_7;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_7 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      switch( BodyShort_rangeType )
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

