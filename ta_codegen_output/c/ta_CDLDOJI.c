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

TA_LIB_API int TA_CDLDOJI_Lookback( void )
{
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;
   return BodyDoji_avgPeriod;
}

TA_LIB_API TA_RetCode TA_CDLDOJI( int    startIdx,
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
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDLDOJI_Lookback();
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
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_0;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_2;
      switch( BodyDoji_rangeType )
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
      double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_2));
      double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
      if( (fabs((inClose[i]-inOpen[i]))<=_candleaverage_1) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_3;
      switch( BodyDoji_rangeType )
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
      double _candlerange_4;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_4 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_3-_candlerange_4);
      i += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLDOJI_Logic( int    startIdx,
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
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;

   lookbackTotal = TA_CDLDOJI_Lookback();
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
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_0;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_2;
      switch( BodyDoji_rangeType )
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
      double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_2));
      double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
      if( (fabs((inClose[i]-inOpen[i]))<=_candleaverage_1) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_3;
      switch( BodyDoji_rangeType )
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
      double _candlerange_4;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_4 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_3-_candlerange_4);
      i += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLDOJI TA_CDLDOJI_Logic

TA_RetCode TA_S_CDLDOJI( int    startIdx,
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
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDLDOJI_Lookback();
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
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_0;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_2;
      switch( BodyDoji_rangeType )
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
      double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_2));
      double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
      if( (fabs((inClose[i]-inOpen[i]))<=_candleaverage_1) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_3;
      switch( BodyDoji_rangeType )
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
      double _candlerange_4;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_4 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_3-_candlerange_4);
      i += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLDOJI_Logic( int    startIdx,
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
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = TA_Globals->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = TA_Globals->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = TA_Globals->candleSettings[TA_BodyDoji].factor;

   lookbackTotal = TA_CDLDOJI_Lookback();
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
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyDoji_rangeType )
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
      BodyDojiPeriodTotal += _candlerange_0;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_2;
      switch( BodyDoji_rangeType )
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
      double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_2));
      double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
      if( (fabs((inClose[i]-inOpen[i]))<=_candleaverage_1) )
      {
         outInteger[outIdx++] = 100;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_3;
      switch( BodyDoji_rangeType )
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
      double _candlerange_4;
      switch( BodyDoji_rangeType )
      {
      case 0:
         _candlerange_4 = fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
         break;
      case 1:
         _candlerange_4 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
         break;
      case 2:
         _candlerange_4 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
         break;
      default:
         _candlerange_4 = 0.0;
         break;
      }
      BodyDojiPeriodTotal += (_candlerange_3-_candlerange_4);
      i += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

