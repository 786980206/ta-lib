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

TA_LIB_API int TA_CDLUPSIDEGAP2CROWS_Lookback( void )
{
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;
   return (fmax(BodyShort_avgPeriod,BodyLong_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDLUPSIDEGAP2CROWS( int    startIdx,
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
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

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

   lookbackTotal = TA_CDLUPSIDEGAP2CROWS_Lookback();
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
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
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

TA_LIB_API TA_RetCode TA_CDLUPSIDEGAP2CROWS_Logic( int    startIdx,
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
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLUPSIDEGAP2CROWS_Lookback();
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
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
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

#define TA_INT_CDLUPSIDEGAP2CROWS TA_CDLUPSIDEGAP2CROWS_Logic

TA_RetCode TA_S_CDLUPSIDEGAP2CROWS( int    startIdx,
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
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

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

   lookbackTotal = TA_CDLUPSIDEGAP2CROWS_Lookback();
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
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
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

TA_RetCode TA_S_CDLUPSIDEGAP2CROWS_Logic( int    startIdx,
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
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   int BodyShort_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].rangeType;
   int BodyShort_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].avgPeriod;
   double BodyShort_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyShort].factor;

   lookbackTotal = TA_CDLUPSIDEGAP2CROWS_Lookback();
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
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyShortTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyShort_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyShort_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyShort_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyShortPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
      if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(fabs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(fabs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) )
      {
         outInteger[outIdx++] = (0-100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyShort_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyShort_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyShort_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyShort_rangeType==0) ? (fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]))) : (((BodyShort_rangeType==1) ? ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])) : (((BodyShort_rangeType==2) ? (((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-fabs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])))) : (0.0))))));
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

