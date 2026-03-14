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

TA_LIB_API int TA_CDLMATCHINGLOW_Lookback( void )
{
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;
   return (Equal_avgPeriod+1);
}

TA_LIB_API TA_RetCode TA_CDLMATCHINGLOW( int    startIdx,
                                         int    endIdx,
                                         const double inOpen[],
                                         const double inHigh[],
                                         const double inLow[],
                                         const double inClose[],
                                         int          *outBegIdx,
                                         int          *outNBElement,
                                         int        outInteger[] )
{
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDLMATCHINGLOW_Lookback();
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
   EqualPeriodTotal = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Equal_rangeType )
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
      EqualPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      switch( Equal_rangeType )
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
      double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
      if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      switch( Equal_rangeType )
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
      double _candlerange_6;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      EqualPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLMATCHINGLOW_Logic( int    startIdx,
                                               int    endIdx,
                                               const double inOpen[],
                                               const double inHigh[],
                                               const double inLow[],
                                               const double inClose[],
                                               int          *outBegIdx,
                                               int          *outNBElement,
                                               int        outInteger[] )
{
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;

   lookbackTotal = TA_CDLMATCHINGLOW_Lookback();
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
   EqualPeriodTotal = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Equal_rangeType )
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
      EqualPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      switch( Equal_rangeType )
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
      double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
      if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      switch( Equal_rangeType )
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
      double _candlerange_6;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      EqualPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLMATCHINGLOW TA_CDLMATCHINGLOW_Logic

TA_RetCode TA_S_CDLMATCHINGLOW( int    startIdx,
                                int    endIdx,
                                const float inOpen[],
                                const float inHigh[],
                                const float inLow[],
                                const float inClose[],
                                int          *outBegIdx,
                                int          *outNBElement,
                                int        outInteger[] )
{
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDLMATCHINGLOW_Lookback();
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
   EqualPeriodTotal = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Equal_rangeType )
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
      EqualPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      switch( Equal_rangeType )
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
      double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
      if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      switch( Equal_rangeType )
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
      double _candlerange_6;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      EqualPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLMATCHINGLOW_Logic( int    startIdx,
                                      int    endIdx,
                                      const float inOpen[],
                                      const float inHigh[],
                                      const float inLow[],
                                      const float inClose[],
                                      int          *outBegIdx,
                                      int          *outNBElement,
                                      int        outInteger[] )
{
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = TA_Globals->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = TA_Globals->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = TA_Globals->candleSettings[TA_Equal].factor;

   lookbackTotal = TA_CDLMATCHINGLOW_Lookback();
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
   EqualPeriodTotal = 0;
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Equal_rangeType )
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
      EqualPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      switch( Equal_rangeType )
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
      double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[(i-1)]-inOpen[(i-1)]));
         break;
      case 1:
         _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
      if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      switch( Equal_rangeType )
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
      double _candlerange_6;
      switch( Equal_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      EqualPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

