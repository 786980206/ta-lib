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

TA_LIB_API int TA_CDLMORNINGDOJISTAR_Lookback( double optInPenetration )
{
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   return (fmax(fmax(BodyDoji_avgPeriod,BodyLong_avgPeriod),BodyShort_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDLMORNINGDOJISTAR( int    startIdx,
                                             int    endIdx,
                                             const double inOpen[],
                                             const double inHigh[],
                                             const double inLow[],
                                             const double inClose[],
                                             double optInPenetration,
                                             int          *outBegIdx,
                                             int          *outNBElement,
                                             int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
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

   if( !inOpen )
      return TA_BAD_PARAM;
   if( !inHigh )
      return TA_BAD_PARAM;
   if( !inLow )
      return TA_BAD_PARAM;
   if( !inClose )
      return TA_BAD_PARAM;
   if( optInPenetration == -4e37 )
      optInPenetration = 0.3;
   else if( optInPenetration < 0.0 || optInPenetration > 2147483647.0 )
      return TA_BAD_PARAM;
   if( !outInteger )
      return TA_BAD_PARAM;

   lookbackTotal = TA_CDLMORNINGDOJISTAR_Lookback(optInPenetration);
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
   BodyDojiPeriodTotal = 0;
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = ((startIdx-1)-BodyDoji_avgPeriod);
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = BodyDojiTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
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
      double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyDoji_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_8 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_5 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyShort_factor*avg_5)/divisor_5);
      if( (((((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_3)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_4))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>(inClose[(i-2)]+(fabs((inClose[(i-2)]-inOpen[(i-2)]))*optInPenetration)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_9-_candlerange_10);
      double _candlerange_11;
      switch( BodyDoji_rangeType )
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
      double _candlerange_12;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_12 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_11-_candlerange_12);
      double _candlerange_13;
      switch( BodyShort_rangeType )
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
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_14 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_13-_candlerange_14);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLMORNINGDOJISTAR_Logic( int    startIdx,
                                                   int    endIdx,
                                                   const double inOpen[],
                                                   const double inHigh[],
                                                   const double inLow[],
                                                   const double inClose[],
                                                   double optInPenetration,
                                                   int          *outBegIdx,
                                                   int          *outNBElement,
                                                   int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLMORNINGDOJISTAR_Lookback(optInPenetration);
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
   BodyDojiPeriodTotal = 0;
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = ((startIdx-1)-BodyDoji_avgPeriod);
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = BodyDojiTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
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
      double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyDoji_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_8 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_5 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyShort_factor*avg_5)/divisor_5);
      if( (((((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_3)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_4))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>(inClose[(i-2)]+(fabs((inClose[(i-2)]-inOpen[(i-2)]))*optInPenetration)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_9-_candlerange_10);
      double _candlerange_11;
      switch( BodyDoji_rangeType )
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
      double _candlerange_12;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_12 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_11-_candlerange_12);
      double _candlerange_13;
      switch( BodyShort_rangeType )
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
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_14 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_13-_candlerange_14);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLMORNINGDOJISTAR TA_CDLMORNINGDOJISTAR_Logic

TA_RetCode TA_S_CDLMORNINGDOJISTAR( int    startIdx,
                                    int    endIdx,
                                    const float inOpen[],
                                    const float inHigh[],
                                    const float inLow[],
                                    const float inClose[],
                                    double optInPenetration,
                                    int          *outBegIdx,
                                    int          *outNBElement,
                                    int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
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

   if( !inOpen )
      return TA_BAD_PARAM;
   if( !inHigh )
      return TA_BAD_PARAM;
   if( !inLow )
      return TA_BAD_PARAM;
   if( !inClose )
      return TA_BAD_PARAM;
   if( optInPenetration == -4e37 )
      optInPenetration = 0.3;
   else if( optInPenetration < 0.0 || optInPenetration > 2147483647.0 )
      return TA_BAD_PARAM;
   if( !outInteger )
      return TA_BAD_PARAM;

   lookbackTotal = TA_CDLMORNINGDOJISTAR_Lookback(optInPenetration);
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
   BodyDojiPeriodTotal = 0;
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = ((startIdx-1)-BodyDoji_avgPeriod);
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = BodyDojiTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
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
      double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyDoji_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_8 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_5 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyShort_factor*avg_5)/divisor_5);
      if( (((((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_3)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_4))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>(inClose[(i-2)]+(fabs((inClose[(i-2)]-inOpen[(i-2)]))*optInPenetration)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_9-_candlerange_10);
      double _candlerange_11;
      switch( BodyDoji_rangeType )
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
      double _candlerange_12;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_12 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_11-_candlerange_12);
      double _candlerange_13;
      switch( BodyShort_rangeType )
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
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_14 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_13-_candlerange_14);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLMORNINGDOJISTAR_Logic( int    startIdx,
                                          int    endIdx,
                                          const float inOpen[],
                                          const float inHigh[],
                                          const float inLow[],
                                          const float inClose[],
                                          double optInPenetration,
                                          int          *outBegIdx,
                                          int          *outNBElement,
                                          int        outInteger[] )
{
   double BodyDojiPeriodTotal;
   double BodyLongPeriodTotal;
   double BodyShortPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int BodyShortTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = TA_Globals->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = TA_Globals->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = TA_Globals->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLMORNINGDOJISTAR_Lookback(optInPenetration);
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
   BodyDojiPeriodTotal = 0;
   BodyShortPeriodTotal = 0;
   BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = ((startIdx-1)-BodyDoji_avgPeriod);
   BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
   i = BodyDojiTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_2;
      switch( BodyShort_rangeType )
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
      BodyShortPeriodTotal += _candlerange_2;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
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
      double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((BodyDoji_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_8;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_8 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_5 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
      double divisor_5 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((BodyShort_factor*avg_5)/divisor_5);
      if( (((((((fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_3)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_4))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&(fabs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>(inClose[(i-2)]+(fabs((inClose[(i-2)]-inOpen[(i-2)]))*optInPenetration)))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_10;
      switch( BodyLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
         break;
      case 1:
         _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      BodyLongPeriodTotal += (_candlerange_9-_candlerange_10);
      double _candlerange_11;
      switch( BodyDoji_rangeType )
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
      double _candlerange_12;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_12 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_12 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_12 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_12 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_11-_candlerange_12);
      double _candlerange_13;
      switch( BodyShort_rangeType )
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
      double _candlerange_14;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_14 = fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
         break;
      case 1:
         _candlerange_14 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
         break;
      case 2:
         _candlerange_14 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
         break;
      default:
         _candlerange_14 = 0.0;
         break;
      }
      BodyShortPeriodTotal += (_candlerange_13-_candlerange_14);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
      BodyShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

