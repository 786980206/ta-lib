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

TA_LIB_API int TA_CDLGAPSIDESIDEWHITE_Lookback( void )
{
   int Equal_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;
   return (fmax(Near_avgPeriod,Equal_avgPeriod)+2);
}

TA_LIB_API TA_RetCode TA_CDLGAPSIDESIDEWHITE( int    startIdx,
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
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].factor;
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

   lookbackTotal = TA_CDLGAPSIDESIDEWHITE_Lookback();
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
   EqualPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      _candlerange_7 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))||((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(fabs((inClose[i]-inOpen[i]))>=(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(fabs((inClose[i]-inOpen[i]))<=(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) )
      {
         outInteger[outIdx++] = (((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_10-_candlerange_11);
      double _candlerange_12;
      _candlerange_12 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])))) : (0.0))))));
      EqualPeriodTotal += (_candlerange_12-_candlerange_13);
      i += 1;
      NearTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDLGAPSIDESIDEWHITE_Logic( int    startIdx,
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
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLGAPSIDESIDEWHITE_Lookback();
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
   EqualPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      _candlerange_7 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))||((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(fabs((inClose[i]-inOpen[i]))>=(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(fabs((inClose[i]-inOpen[i]))<=(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) )
      {
         outInteger[outIdx++] = (((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_10-_candlerange_11);
      double _candlerange_12;
      _candlerange_12 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])))) : (0.0))))));
      EqualPeriodTotal += (_candlerange_12-_candlerange_13);
      i += 1;
      NearTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDLGAPSIDESIDEWHITE TA_CDLGAPSIDESIDEWHITE_Logic

TA_RetCode TA_S_CDLGAPSIDESIDEWHITE( int    startIdx,
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
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].factor;
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

   lookbackTotal = TA_CDLGAPSIDESIDEWHITE_Lookback();
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
   EqualPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      _candlerange_7 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))||((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(fabs((inClose[i]-inOpen[i]))>=(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(fabs((inClose[i]-inOpen[i]))<=(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) )
      {
         outInteger[outIdx++] = (((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_10-_candlerange_11);
      double _candlerange_12;
      _candlerange_12 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])))) : (0.0))))));
      EqualPeriodTotal += (_candlerange_12-_candlerange_13);
      i += 1;
      NearTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDLGAPSIDESIDEWHITE_Logic( int    startIdx,
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
   double EqualPeriodTotal;
   int i;
   int outIdx;
   int NearTrailingIdx;
   int EqualTrailingIdx;
   int lookbackTotal;
   int Equal_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].rangeType;
   int Equal_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].avgPeriod;
   double Equal_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Equal].factor;
   int Near_rangeType = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].avgPeriod;
   double Near_factor = ((volatile TA_GlobalsType *)TA_Globals)->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDLGAPSIDESIDEWHITE_Lookback();
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
   EqualPeriodTotal = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   EqualTrailingIdx = (startIdx-Equal_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      _candlerange_0 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      NearPeriodTotal += _candlerange_0;
      i += 1;
   }
   i = EqualTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_1;
      _candlerange_1 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      EqualPeriodTotal += _candlerange_1;
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      _candlerange_6 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      _candlerange_7 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      _candlerange_8 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      _candlerange_9 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
      if( (((((((((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmin(inOpen[i],inClose[i])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0)))||((((fmax(inOpen[(i-1)],inClose[(i-1)])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))&&(((fmax(inOpen[i],inClose[i])<fmin(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(fabs((inClose[i]-inOpen[i]))>=(fabs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(fabs((inClose[i]-inOpen[i]))<=(fabs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) )
      {
         outInteger[outIdx++] = (((((fmin(inOpen[(i-1)],inClose[(i-1)])>fmax(inOpen[(i-2)],inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      double _candlerange_10;
      _candlerange_10 = ((Near_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Near_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Near_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_11;
      _candlerange_11 = ((Near_rangeType==0) ? (fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]))) : (((Near_rangeType==1) ? ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])) : (((Near_rangeType==2) ? (((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-fabs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])))) : (0.0))))));
      NearPeriodTotal += (_candlerange_10-_candlerange_11);
      double _candlerange_12;
      _candlerange_12 = ((Equal_rangeType==0) ? (fabs((inClose[(i-1)]-inOpen[(i-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(i-1)]-inLow[(i-1)])) : (((Equal_rangeType==2) ? (((inHigh[(i-1)]-inLow[(i-1)])-fabs((inClose[(i-1)]-inOpen[(i-1)])))) : (0.0))))));
      double _candlerange_13;
      _candlerange_13 = ((Equal_rangeType==0) ? (fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]))) : (((Equal_rangeType==1) ? ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])) : (((Equal_rangeType==2) ? (((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-fabs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])))) : (0.0))))));
      EqualPeriodTotal += (_candlerange_12-_candlerange_13);
      i += 1;
      NearTrailingIdx += 1;
      EqualTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

