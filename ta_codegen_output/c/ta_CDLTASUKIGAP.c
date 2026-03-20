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

TA_LIB_API int TA_CDLTASUKIGAP_Lookback( void )
{
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   return (Near_avgPeriod+2);
}

TA_LIB_API TA_RetCode TA_CDLTASUKIGAP( int    startIdx,
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
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

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

   lookbackTotal = TA_CDLTASUKIGAP_Lookback();
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
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inClose[(i-1)]))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inOpen[(i-1)]))&&(inClose[i]>fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_1))||((((((((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-1)]))&&(inClose[i]<fmin(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_2))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLTASUKIGAP_Logic( int    startIdx,
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
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLTASUKIGAP_Lookback();
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
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inClose[(i-1)]))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inOpen[(i-1)]))&&(inClose[i]>fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_1))||((((((((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-1)]))&&(inClose[i]<fmin(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_2))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLTASUKIGAP TA_CDLTASUKIGAP_Logic

TA_RetCode TA_S_CDLTASUKIGAP( int    startIdx,
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
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

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

   lookbackTotal = TA_CDLTASUKIGAP_Lookback();
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
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inClose[(i-1)]))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inOpen[(i-1)]))&&(inClose[i]>fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_1))||((((((((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-1)]))&&(inClose[i]<fmin(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_2))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLTASUKIGAP_Logic( int    startIdx,
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
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLTASUKIGAP_Lookback();
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
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_1;
      double _candlerange_3;
      _candlerange_3 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
      double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
      double _candleaverage_2;
      double _candlerange_4;
      _candlerange_4 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inClose[(i-1)]))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inOpen[(i-1)]))&&(inClose[i]>fmax(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_1))||((((((((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-1)]))&&(inClose[i]<fmin(inClose[(i-2)],inOpen[(i-2)])))&&(fabs((fabs((inClose[(i-1)]-inOpen[(i-1)]))-fabs((inClose[i]-inOpen[i]))))<_candleaverage_2))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_5;
      _candlerange_5 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_5-_candlerange_6);
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

