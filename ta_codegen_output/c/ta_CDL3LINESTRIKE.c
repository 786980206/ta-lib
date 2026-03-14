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

TA_LIB_API int TA_CDL3LINESTRIKE_Lookback( void )
{
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;
   return (Near_avgPeriod+3);
}

TA_LIB_API TA_RetCode TA_CDL3LINESTRIKE( int    startIdx,
                                         int    endIdx,
                                         const double inOpen[],
                                         const double inHigh[],
                                         const double inLow[],
                                         const double inClose[],
                                         int          *outBegIdx,
                                         int          *outNBElement,
                                         int        outInteger[] )
{
   double NearPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDL3LINESTRIKE_Lookback();
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
   NearPeriodTotal[3] = 0;
   NearPeriodTotal[2] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Near_rangeType )
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
      NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( Near_rangeType )
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
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_4 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Near_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      switch( Near_rangeType )
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
      double avg_5 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Near_factor*avg_5)/divisor_5);
      if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(fmin(inOpen[(i-3)],inClose[(i-3)])-_candleaverage_2)))&&(inOpen[(i-2)]<=(fmax(inOpen[(i-3)],inClose[(i-3)])+_candleaverage_3)))&&(inOpen[(i-1)]>=(fmin(inOpen[(i-2)],inClose[(i-2)])-_candleaverage_4)))&&(inOpen[(i-1)]<=(fmax(inOpen[(i-2)],inClose[(i-2)])+_candleaverage_5)))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=2); totIdx -= 1 )
      {
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
      }
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_CDL3LINESTRIKE_Logic( int    startIdx,
                                               int    endIdx,
                                               const double inOpen[],
                                               const double inHigh[],
                                               const double inLow[],
                                               const double inClose[],
                                               int          *outBegIdx,
                                               int          *outNBElement,
                                               int        outInteger[] )
{
   double NearPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDL3LINESTRIKE_Lookback();
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
   NearPeriodTotal[3] = 0;
   NearPeriodTotal[2] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Near_rangeType )
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
      NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( Near_rangeType )
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
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_4 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Near_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      switch( Near_rangeType )
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
      double avg_5 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Near_factor*avg_5)/divisor_5);
      if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(fmin(inOpen[(i-3)],inClose[(i-3)])-_candleaverage_2)))&&(inOpen[(i-2)]<=(fmax(inOpen[(i-3)],inClose[(i-3)])+_candleaverage_3)))&&(inOpen[(i-1)]>=(fmin(inOpen[(i-2)],inClose[(i-2)])-_candleaverage_4)))&&(inOpen[(i-1)]<=(fmax(inOpen[(i-2)],inClose[(i-2)])+_candleaverage_5)))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=2); totIdx -= 1 )
      {
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
      }
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_CDL3LINESTRIKE TA_CDL3LINESTRIKE_Logic

TA_RetCode TA_S_CDL3LINESTRIKE( int    startIdx,
                                int    endIdx,
                                const float inOpen[],
                                const float inHigh[],
                                const float inLow[],
                                const float inClose[],
                                int          *outBegIdx,
                                int          *outNBElement,
                                int        outInteger[] )
{
   double NearPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   lookbackTotal = TA_CDL3LINESTRIKE_Lookback();
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
   NearPeriodTotal[3] = 0;
   NearPeriodTotal[2] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Near_rangeType )
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
      NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( Near_rangeType )
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
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_4 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Near_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      switch( Near_rangeType )
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
      double avg_5 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Near_factor*avg_5)/divisor_5);
      if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(fmin(inOpen[(i-3)],inClose[(i-3)])-_candleaverage_2)))&&(inOpen[(i-2)]<=(fmax(inOpen[(i-3)],inClose[(i-3)])+_candleaverage_3)))&&(inOpen[(i-1)]>=(fmin(inOpen[(i-2)],inClose[(i-2)])-_candleaverage_4)))&&(inOpen[(i-1)]<=(fmax(inOpen[(i-2)],inClose[(i-2)])+_candleaverage_5)))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=2); totIdx -= 1 )
      {
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
      }
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_CDL3LINESTRIKE_Logic( int    startIdx,
                                      int    endIdx,
                                      const float inOpen[],
                                      const float inHigh[],
                                      const float inLow[],
                                      const float inClose[],
                                      int          *outBegIdx,
                                      int          *outNBElement,
                                      int        outInteger[] )
{
   double NearPeriodTotal[4];
   int i;
   int outIdx;
   int totIdx;
   int NearTrailingIdx;
   int lookbackTotal;
   int Near_rangeType = TA_Globals->candleSettings[TA_Near].rangeType;
   int Near_avgPeriod = TA_Globals->candleSettings[TA_Near].avgPeriod;
   double Near_factor = TA_Globals->candleSettings[TA_Near].factor;

   lookbackTotal = TA_CDL3LINESTRIKE_Lookback();
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
   NearPeriodTotal[3] = 0;
   NearPeriodTotal[2] = 0;
   NearTrailingIdx = (startIdx-Near_avgPeriod);
   i = NearTrailingIdx;
   while( (i<startIdx) )
   {
      double _candlerange_0;
      switch( Near_rangeType )
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
      NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
      double _candlerange_1;
      switch( Near_rangeType )
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
      NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
      i += 1;
   }
   i = startIdx;
   outIdx = 0;
   do
   {
      double _candleaverage_2;
      double _candlerange_6;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_6 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_6 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_6 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_6 = 0.0;
         break;
      }
      double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_6));
      double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
      double _candleaverage_3;
      double _candlerange_7;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_7 = fabs((inClose[(i-3)]-inOpen[(i-3)]));
         break;
      case 1:
         _candlerange_7 = (inHigh[(i-3)]-inLow[(i-3)]);
         break;
      case 2:
         _candlerange_7 = ((inHigh[(i-3)]-inLow[(i-3)])-fabs((inClose[(i-3)]-inOpen[(i-3)])));
         break;
      default:
         _candlerange_7 = 0.0;
         break;
      }
      double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[3]/Near_avgPeriod)) : (_candlerange_7));
      double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
      double _candleaverage_4;
      double _candlerange_8;
      switch( Near_rangeType )
      {
      case 0:
         _candlerange_8 = fabs((inClose[(i-2)]-inOpen[(i-2)]));
         break;
      case 1:
         _candlerange_8 = (inHigh[(i-2)]-inLow[(i-2)]);
         break;
      case 2:
         _candlerange_8 = ((inHigh[(i-2)]-inLow[(i-2)])-fabs((inClose[(i-2)]-inOpen[(i-2)])));
         break;
      default:
         _candlerange_8 = 0.0;
         break;
      }
      double avg_4 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_8));
      double divisor_4 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_4 = ((Near_factor*avg_4)/divisor_4);
      double _candleaverage_5;
      double _candlerange_9;
      switch( Near_rangeType )
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
      double avg_5 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (_candlerange_9));
      double divisor_5 = (((Near_rangeType==2)) ? (2.0) : (1.0));
      _candleaverage_5 = ((Near_factor*avg_5)/divisor_5);
      if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(fmin(inOpen[(i-3)],inClose[(i-3)])-_candleaverage_2)))&&(inOpen[(i-2)]<=(fmax(inOpen[(i-3)],inClose[(i-3)])+_candleaverage_3)))&&(inOpen[(i-1)]>=(fmin(inOpen[(i-2)],inClose[(i-2)])-_candleaverage_4)))&&(inOpen[(i-1)]<=(fmax(inOpen[(i-2)],inClose[(i-2)])+_candleaverage_5)))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) )
      {
         outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
      } else 
      {
         outInteger[outIdx++] = 0;
      }
      for( totIdx = 3; (totIdx>=2); totIdx -= 1 )
      {
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-fabs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-fabs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
      }
      i += 1;
      NearTrailingIdx += 1;
   } while( (i<=endIdx) );
   *outNBElement= outIdx;
   *outBegIdx= startIdx;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

