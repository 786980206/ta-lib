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

TA_LIB_API int TA_CDLHIKKAKEMOD_Lookback( void )
{
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   return (fmax(1,Near_avgPeriod)+5);
}

TA_LIB_API TA_RetCode TA_CDLHIKKAKEMOD( int    startIdx,
                                        int    endIdx,
                                        const double inOpen[],
                                        const double inHigh[],
                                        const double inLow[],
                                        const double inClose[],
                                        int          *outBegIdx,
                                        int          *outNBElement,
                                        int        outInteger[] )
{
   double NearPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int patternIdx;
   int patternResult;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

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

   lookbackTotal = TA_CDLHIKKAKEMOD_Lookback();
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
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<(startIdx-3)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   patternIdx = 0;
   patternResult = 0;
   i = (startIdx-3);
   while( (i<startIdx) )
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         patternIdx = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      NearTrailingIdx += 1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_7;
      double _candlerange_9;
      _candlerange_9 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
      double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
         outInteger[outIdx++] = patternResult;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
         patternIdx = 0;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_11-_candlerange_12);
      NearTrailingIdx += 1;
      i += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLHIKKAKEMOD_Logic( int    startIdx,
                                              int    endIdx,
                                              const double inOpen[],
                                              const double inHigh[],
                                              const double inLow[],
                                              const double inClose[],
                                              int          *outBegIdx,
                                              int          *outNBElement,
                                              int        outInteger[] )
{
   double NearPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int patternIdx;
   int patternResult;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLHIKKAKEMOD_Lookback();
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
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<(startIdx-3)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   patternIdx = 0;
   patternResult = 0;
   i = (startIdx-3);
   while( (i<startIdx) )
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         patternIdx = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      NearTrailingIdx += 1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_7;
      double _candlerange_9;
      _candlerange_9 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
      double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
         outInteger[outIdx++] = patternResult;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
         patternIdx = 0;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_11-_candlerange_12);
      NearTrailingIdx += 1;
      i += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLHIKKAKEMOD TA_CDLHIKKAKEMOD_Logic

TA_RetCode TA_S_CDLHIKKAKEMOD( int    startIdx,
                               int    endIdx,
                               const float inOpen[],
                               const float inHigh[],
                               const float inLow[],
                               const float inClose[],
                               int          *outBegIdx,
                               int          *outNBElement,
                               int        outInteger[] )
{
   double NearPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int patternIdx;
   int patternResult;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

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

   lookbackTotal = TA_CDLHIKKAKEMOD_Lookback();
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
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<(startIdx-3)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   patternIdx = 0;
   patternResult = 0;
   i = (startIdx-3);
   while( (i<startIdx) )
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         patternIdx = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      NearTrailingIdx += 1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_7;
      double _candlerange_9;
      _candlerange_9 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
      double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
         outInteger[outIdx++] = patternResult;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
         patternIdx = 0;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_11-_candlerange_12);
      NearTrailingIdx += 1;
      i += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLHIKKAKEMOD_Logic( int    startIdx,
                                     int    endIdx,
                                     const float inOpen[],
                                     const float inHigh[],
                                     const float inLow[],
                                     const float inClose[],
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     int        outInteger[] )
{
   double NearPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int patternIdx;
   int patternResult;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLHIKKAKEMOD_Lookback();
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
   NearPeriodTotal = 0;
   NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<(startIdx-3)) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   patternIdx = 0;
   patternResult = 0;
   i = (startIdx-3);
   while( (i<startIdx) )
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         patternIdx = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      NearTrailingIdx += 1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_7;
      double _candlerange_9;
      _candlerange_9 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
      double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
      double _candleaverage_8;
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
      double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
      if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) )
      {
         patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
         patternIdx = i;
         outInteger[outIdx++] = patternResult;
      } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) )
      {
         outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
         patternIdx = 0;
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(i-2)]-inOpen[(i-2)]))) : (((Near_rangeType==1) ? ((inHigh[(i-2)]-inLow[(i-2)])) : (((Near_rangeType==2) ? (((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])))) : (0.0))))));
      double _candlerange_12;
      _candlerange_12 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-fabs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_11-_candlerange_12);
      NearTrailingIdx += 1;
      i += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

