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

TA_LIB_API int TA_CDLDOJISTAR_Lookback( void )
{
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;
   return (fmax(BodyDoji_avgPeriod,BodyLong_avgPeriod)+1);
}

TA_LIB_API TA_RetCode TA_CDLDOJISTAR( int    startIdx,
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
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;

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

   lookbackTotal = TA_CDLDOJISTAR_Lookback();
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
   BodyLongTrailingIdx = ((startIdx-1)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      if( (((fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_2)&&(fabs((inClose[i]-inOpen[i]))<=_candleaverage_3))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLDOJISTAR_Logic( int    startIdx,
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
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;

   lookbackTotal = TA_CDLDOJISTAR_Lookback();
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
   BodyLongTrailingIdx = ((startIdx-1)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      if( (((fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_2)&&(fabs((inClose[i]-inOpen[i]))<=_candleaverage_3))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLDOJISTAR TA_CDLDOJISTAR_Logic

TA_RetCode TA_S_CDLDOJISTAR( int    startIdx,
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
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;

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

   lookbackTotal = TA_CDLDOJISTAR_Lookback();
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
   BodyLongTrailingIdx = ((startIdx-1)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      if( (((fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_2)&&(fabs((inClose[i]-inOpen[i]))<=_candleaverage_3))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLDOJISTAR_Logic( int    startIdx,
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
   double BodyLongPeriodTotal;
   int i;
   int outIdx;
   int BodyDojiTrailingIdx;
   int BodyLongTrailingIdx;
   int lookbackTotal;
   int BodyDoji_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].rangeType;
   int BodyDoji_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].avgPeriod;
   double BodyDoji_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyDoji].factor;
   int BodyLong_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].rangeType;
   int BodyLong_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].avgPeriod;
   double BodyLong_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_BodyLong].factor;

   lookbackTotal = TA_CDLDOJISTAR_Lookback();
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
   BodyLongTrailingIdx = ((startIdx-1)-BodyLong_avgPeriod);
   BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
   i = BodyLongTrailingIdx;
   while( (i<(startIdx-1)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((BodyLong_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyLong_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyLong_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyLongPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = BodyDojiTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      BodyDojiPeriodTotal += _candlerange_1;
      i += 1;
   }
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_5;
      _candlerange_5 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (_candlerange_5));
      double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
      if( (((fabs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_2)&&(fabs((inClose[i]-inOpen[i]))<=_candleaverage_3))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-1)],inClose[(i-1)]))) ? (1) : (0))))) )
      {
         outInteger[outIdx++] = ((0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_6;
      _candlerange_6 = ((BodyLong_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((BodyLong_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((BodyLong_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_7;
      _candlerange_7 = ((BodyLong_rangeType==0) ? (fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]))) : (((BodyLong_rangeType==1) ? ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])) : (((BodyLong_rangeType==2) ? (((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-fabs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])))) : (0.0))))));
      BodyLongPeriodTotal += (_candlerange_6-_candlerange_7);
      double _candlerange_8;
      _candlerange_8 = ((BodyDoji_rangeType==0) ? (fabs((inClose[i]-inOpen[i]))) : (((BodyDoji_rangeType==1) ? ((inHigh[i]-inLow[i])) : (((BodyDoji_rangeType==2) ? (((inHigh[i]-inLow[i])-fabs((inClose[i]-inOpen[i])))) : (0.0))))));
      double _candlerange_9;
      _candlerange_9 = ((BodyDoji_rangeType==0) ? (fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]))) : (((BodyDoji_rangeType==1) ? ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])) : (((BodyDoji_rangeType==2) ? (((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-fabs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])))) : (0.0))))));
      BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
      i += 1;
      BodyLongTrailingIdx += 1;
      BodyDojiTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

