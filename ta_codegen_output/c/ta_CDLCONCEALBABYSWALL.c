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

TA_LIB_API int TA_CDLCONCEALBABYSWALL_Lookback( void )
{
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;
   return (ShadowVeryShort_avgPeriod+3);
}

TA_LIB_API TA_RetCode TA_CDLCONCEALBABYSWALL( int    startIdx,
                                              int    endIdx,
                                              const double inOpen[],
                                              const double inHigh[],
                                              const double inLow[],
                                              const double inClose[],
                                              int          *outBegIdx,
                                              int          *outNBElement,
                                              int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
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

   lookbackTotal = TA_CDLCONCEALBABYSWALL_Lookback();
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
   ShadowVeryShortPeriodTotal[3] = 0;
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[3] = (ShadowVeryShortPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
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
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_1);
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
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
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
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
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
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      if( ((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-3)]>=inOpen[(i-3)])) ? (inOpen[(i-3)]) : (inClose[(i-3)]))-inLow[(i-3)])<_candleaverage_3))&&((inHigh[(i-3)]-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (inClose[(i-3)]) : (inOpen[(i-3)])))<_candleaverage_4))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_6))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_7))&&(inHigh[(i-1)]>inClose[(i-2)]))&&(inHigh[i]>inHigh[(i-1)]))&&(inLow[i]<inLow[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_13;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_14 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLCONCEALBABYSWALL_Logic( int    startIdx,
                                                    int    endIdx,
                                                    const double inOpen[],
                                                    const double inHigh[],
                                                    const double inLow[],
                                                    const double inClose[],
                                                    int          *outBegIdx,
                                                    int          *outNBElement,
                                                    int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLCONCEALBABYSWALL_Lookback();
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
   ShadowVeryShortPeriodTotal[3] = 0;
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[3] = (ShadowVeryShortPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
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
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_1);
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
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
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
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
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
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      if( ((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-3)]>=inOpen[(i-3)])) ? (inOpen[(i-3)]) : (inClose[(i-3)]))-inLow[(i-3)])<_candleaverage_3))&&((inHigh[(i-3)]-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (inClose[(i-3)]) : (inOpen[(i-3)])))<_candleaverage_4))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_6))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_7))&&(inHigh[(i-1)]>inClose[(i-2)]))&&(inHigh[i]>inHigh[(i-1)]))&&(inLow[i]<inLow[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_13;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_14 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLCONCEALBABYSWALL TA_CDLCONCEALBABYSWALL_Logic

TA_RetCode TA_S_CDLCONCEALBABYSWALL( int    startIdx,
                                     int    endIdx,
                                     const float inOpen[],
                                     const float inHigh[],
                                     const float inLow[],
                                     const float inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
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

   lookbackTotal = TA_CDLCONCEALBABYSWALL_Lookback();
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
   ShadowVeryShortPeriodTotal[3] = 0;
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[3] = (ShadowVeryShortPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
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
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_1);
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
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
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
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
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
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      if( ((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-3)]>=inOpen[(i-3)])) ? (inOpen[(i-3)]) : (inClose[(i-3)]))-inLow[(i-3)])<_candleaverage_3))&&((inHigh[(i-3)]-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (inClose[(i-3)]) : (inOpen[(i-3)])))<_candleaverage_4))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_6))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_7))&&(inHigh[(i-1)]>inClose[(i-2)]))&&(inHigh[i]>inHigh[(i-1)]))&&(inLow[i]<inLow[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_13;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_14 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLCONCEALBABYSWALL_Logic( int    startIdx,
                                           int    endIdx,
                                           const float inOpen[],
                                           const float inHigh[],
                                           const float inLow[],
                                           const float inClose[],
                                           int          *outBegIdx,
                                           int          *outNBElement,
                                           int        outInteger[] )
{
   double ShadowVeryShortPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int ShadowVeryShortTrailingIdx;
   int lookbackTotal;
   int ShadowVeryShort_rangeType = TA_Globals->candleSettings[TA_ShadowVeryShort].rangeType;
   int ShadowVeryShort_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryShort].avgPeriod;
   double ShadowVeryShort_factor = TA_Globals->candleSettings[TA_ShadowVeryShort].factor;

   lookbackTotal = TA_CDLCONCEALBABYSWALL_Lookback();
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
   ShadowVeryShortPeriodTotal[3] = 0;
   ShadowVeryShortPeriodTotal[2] = 0;
   ShadowVeryShortPeriodTotal[1] = 0;
   ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
   i = ShadowVeryShortTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_0 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_0 = 0.0;
         break;
      }
      ShadowVeryShortPeriodTotal[3] = (ShadowVeryShortPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( ShadowVeryShort_rangeType )
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
      ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_1);
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
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_3;
      double _candlerange_8;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_8));
      double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_9;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_9 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[3]/ShadowVeryShort_avgPeriod)) : (_candlerange_9));
      double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_10;
      switch( ShadowVeryShort_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
      double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
      double _candleaverage_6;
      double _candlerange_11;
      switch( ShadowVeryShort_rangeType )
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
      double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (_candlerange_11));
      double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
      double _candleaverage_7;
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
      double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (_candlerange_12));
      double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
      if( ((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-3)]>=inOpen[(i-3)])) ? (inOpen[(i-3)]) : (inClose[(i-3)]))-inLow[(i-3)])<_candleaverage_3))&&((inHigh[(i-3)]-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (inClose[(i-3)]) : (inOpen[(i-3)])))<_candleaverage_4))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_6))&&(((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_7))&&(inHigh[(i-1)]>inClose[(i-2)]))&&(inHigh[i]>inHigh[(i-1)]))&&(inLow[i]<inLow[(i-1)])) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=1); totIdx -= 1 )
      {
         double _candlerange_13;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_14 = fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-fabs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
      }
      i += 1;
      ShadowVeryShortTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

