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

TA_LIB_API int TA_CDLHIGHWAVE_Lookback( void )
{
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowVeryLong_rangeType = TA_Globals->candleSettings[TA_ShadowVeryLong].rangeType;
   int ShadowVeryLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryLong].avgPeriod;
   double ShadowVeryLong_factor = TA_Globals->candleSettings[TA_ShadowVeryLong].factor;
   return fmax(BodyShort_avgPeriod,ShadowVeryLong_avgPeriod);
}

TA_LIB_API TA_RetCode TA_CDLHIGHWAVE( int    startIdx,
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
   double ShadowPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowVeryLong_rangeType = TA_Globals->candleSettings[TA_ShadowVeryLong].rangeType;
   int ShadowVeryLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryLong].avgPeriod;
   double ShadowVeryLong_factor = TA_Globals->candleSettings[TA_ShadowVeryLong].factor;

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

   lookbackTotal = TA_CDLHIGHWAVE_Lookback();
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
   ShadowPeriodTotal = 0;
   ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyShort_rangeType )
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
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowVeryLong_rangeType )
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
      ShadowPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_5 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_2 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_2 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyShort_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_6;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_6 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_7 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryLong_factor*avg_4)/divisor_4);
      if( (((fabs((inClose[i]-inOpen[i]))<_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4)) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyPeriodTotal += (_candlerange_8-_candlerange_9);
      double _candlerange_10;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_10 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double _candlerange_11;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
         break;
      case 1:
         _candlerange_11 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      ShadowPeriodTotal += (_candlerange_10-_candlerange_11);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLHIGHWAVE_Logic( int    startIdx,
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
   double ShadowPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowVeryLong_rangeType = TA_Globals->candleSettings[TA_ShadowVeryLong].rangeType;
   int ShadowVeryLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryLong].avgPeriod;
   double ShadowVeryLong_factor = TA_Globals->candleSettings[TA_ShadowVeryLong].factor;

   lookbackTotal = TA_CDLHIGHWAVE_Lookback();
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
   ShadowPeriodTotal = 0;
   ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyShort_rangeType )
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
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowVeryLong_rangeType )
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
      ShadowPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_5 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_2 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_2 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyShort_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_6;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_6 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_7 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryLong_factor*avg_4)/divisor_4);
      if( (((fabs((inClose[i]-inOpen[i]))<_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4)) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyPeriodTotal += (_candlerange_8-_candlerange_9);
      double _candlerange_10;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_10 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double _candlerange_11;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
         break;
      case 1:
         _candlerange_11 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      ShadowPeriodTotal += (_candlerange_10-_candlerange_11);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLHIGHWAVE TA_CDLHIGHWAVE_Logic

TA_RetCode TA_S_CDLHIGHWAVE( int    startIdx,
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
   double ShadowPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowVeryLong_rangeType = TA_Globals->candleSettings[TA_ShadowVeryLong].rangeType;
   int ShadowVeryLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryLong].avgPeriod;
   double ShadowVeryLong_factor = TA_Globals->candleSettings[TA_ShadowVeryLong].factor;

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

   lookbackTotal = TA_CDLHIGHWAVE_Lookback();
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
   ShadowPeriodTotal = 0;
   ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyShort_rangeType )
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
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowVeryLong_rangeType )
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
      ShadowPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_5 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_2 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_2 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyShort_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_6;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_6 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_7 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryLong_factor*avg_4)/divisor_4);
      if( (((fabs((inClose[i]-inOpen[i]))<_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4)) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyPeriodTotal += (_candlerange_8-_candlerange_9);
      double _candlerange_10;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_10 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double _candlerange_11;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
         break;
      case 1:
         _candlerange_11 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      ShadowPeriodTotal += (_candlerange_10-_candlerange_11);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLHIGHWAVE_Logic( int    startIdx,
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
   double ShadowPeriodTotal;
   int i;
   int outIdx;
   int BodyTrailingIdx;
   int ShadowTrailingIdx;
   int lookbackTotal;
   int BodyShort_rangeType = TA_Globals->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = TA_Globals->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = TA_Globals->candleSettings[TA_BodyShort].factor;
   int ShadowVeryLong_rangeType = TA_Globals->candleSettings[TA_ShadowVeryLong].rangeType;
   int ShadowVeryLong_avgPeriod = TA_Globals->candleSettings[TA_ShadowVeryLong].avgPeriod;
   double ShadowVeryLong_factor = TA_Globals->candleSettings[TA_ShadowVeryLong].factor;

   lookbackTotal = TA_CDLHIGHWAVE_Lookback();
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
   ShadowPeriodTotal = 0;
   ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
   i = BodyTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( BodyShort_rangeType )
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
      BodyPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = ShadowTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      switch( ShadowVeryLong_rangeType )
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
      ShadowPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_5;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_5 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_5 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_5 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_5 = 0.0;
         break;
      }
      double avg_2 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_2 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyShort_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_6;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_6 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_3 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_6));
      double divisor_3 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((ShadowVeryLong_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_7;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_7 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_4 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowVeryLong_avgPeriod)) : (_candlerange_7));
      double divisor_4 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((ShadowVeryLong_factor*avg_4)/divisor_4);
      if( (((fabs((inClose[i]-inOpen[i]))<_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4)) )
      {
         outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
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
      double _candlerange_9;
      switch( BodyShort_rangeType )
      {
      case 0:
         _candlerange_9 = fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
         break;
      case 1:
         _candlerange_9 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
         break;
      case 2:
         _candlerange_9 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-fabs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
         break;
      default:
         _candlerange_9 = 0.0;
         break;
      }
      BodyPeriodTotal += (_candlerange_8-_candlerange_9);
      double _candlerange_10;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_10 = fabs((inClose[i]-inOpen[i]));
         break;
      case 1:
         _candlerange_10 = (inHigh[i]-inLow[i]);
         break;
      case 2:
         _candlerange_10 = ((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])));
         break;
      default:
         _candlerange_10 = 0.0;
         break;
      }
      double _candlerange_11;
      switch( ShadowVeryLong_rangeType )
      {
      case 0:
         _candlerange_11 = fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
         break;
      case 1:
         _candlerange_11 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
         break;
      case 2:
         _candlerange_11 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-fabs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
         break;
      default:
         _candlerange_11 = 0.0;
         break;
      }
      ShadowPeriodTotal += (_candlerange_10-_candlerange_11);
      i += 1;
      BodyTrailingIdx += 1;
      ShadowTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

