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

TA_LIB_API int TA_MA_Lookback( int optInTimePeriod, int optInMAType )
{
   int retValue;
   if( (optInTimePeriod<=1) )
   {
      return 0;
   }
   switch( optInMAType )
   {
   case ENUM_CASE(MAType, TA_MAType_SMA, Sma):
      retValue = TA_SMA_Lookback(optInTimePeriod);
      break;
   case ENUM_CASE(MAType, TA_MAType_EMA, Ema):
      retValue = TA_EMA_Lookback(optInTimePeriod);
      break;
   default:
      retValue = 0;
      break;
   }
   return retValue;
}

TA_LIB_API TA_RetCode TA_MA( int    startIdx,
                             int    endIdx,
                             const double inReal[],
                             int optInTimePeriod,
                             int optInMAType,
                             int          *outBegIdx,
                             int          *outNBElement,
                             double        outReal[] )
{
   int nbElement;
   int outIdx;
   int todayIdx;
   TA_RetCode retCode;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( (optInTimePeriod==1) )
   {
      nbElement = ((endIdx-startIdx)+1);
      *outNBElement = nbElement;
      todayIdx = startIdx;
      outIdx = 0;
      while( (outIdx<nbElement) )
      {
         outReal[outIdx] = ((double)inReal[todayIdx]);
         outIdx = (outIdx+1);
         todayIdx = (todayIdx+1);
      }
      *outBegIdx = startIdx;
      return TA_SUCCESS;
   }
   switch( optInMAType )
   {
   case ENUM_CASE(MAType, TA_MAType_SMA, Sma):
      retCode = TA_SMA(startIdx,endIdx,inReal,optInTimePeriod,outBegIdx,outNBElement,outReal);
      break;
   case ENUM_CASE(MAType, TA_MAType_EMA, Ema):
      retCode = TA_EMA(startIdx,endIdx,inReal,optInTimePeriod,outBegIdx,outNBElement,outReal);
      break;
   default:
      retCode = TA_BAD_PARAM;
      break;
   }
   return retCode;

   return TA_SUCCESS;
}

TA_RetCode TA_S_MA( int    startIdx,
                    int    endIdx,
                    const float inReal[],
                    int optInTimePeriod,
                    int optInMAType,
                    int          *outBegIdx,
                    int          *outNBElement,
                    double        outReal[] )
{
   int nbElement;
   int outIdx;
   int todayIdx;
   TA_RetCode retCode;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( (optInTimePeriod==1) )
   {
      nbElement = ((endIdx-startIdx)+1);
      *outNBElement = nbElement;
      todayIdx = startIdx;
      outIdx = 0;
      while( (outIdx<nbElement) )
      {
         outReal[outIdx] = ((double)inReal[todayIdx]);
         outIdx = (outIdx+1);
         todayIdx = (todayIdx+1);
      }
      *outBegIdx = startIdx;
      return TA_SUCCESS;
   }
   switch( optInMAType )
   {
   case ENUM_CASE(MAType, TA_MAType_SMA, Sma):
      retCode = TA_S_SMA(startIdx,endIdx,inReal,optInTimePeriod,outBegIdx,outNBElement,outReal);
      break;
   case ENUM_CASE(MAType, TA_MAType_EMA, Ema):
      retCode = TA_S_EMA(startIdx,endIdx,inReal,optInTimePeriod,outBegIdx,outNBElement,outReal);
      break;
   default:
      retCode = TA_BAD_PARAM;
      break;
   }
   return retCode;

   return TA_SUCCESS;
}

