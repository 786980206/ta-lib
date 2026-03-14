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

TA_LIB_API int TA_MACD_Lookback( int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod )
{
   int tempInteger;
   if( (optInSlowPeriod<optInFastPeriod) )
   {
      tempInteger = optInSlowPeriod;
      optInSlowPeriod = optInFastPeriod;
      optInFastPeriod = tempInteger;
   }
   return (TA_EMA_Lookback(optInSlowPeriod)+TA_EMA_Lookback(optInSignalPeriod));
}

TA_LIB_API TA_RetCode TA_MACD( int    startIdx,
                               int    endIdx,
                               const double inReal[],
                               int optInFastPeriod,
                               int optInSlowPeriod,
                               int optInSignalPeriod,
                               int          *outBegIdx,
                               int          *outNBElement,
                               double        outMACD[],
                               double        outMACDSignal[],
                               double        outMACDHist[] )
{
   double *slowEMABuffer;
   double *fastEMABuffer;
   TA_RetCode retCode;
   int tempInteger;
   int outBegIdx1;
   int outNbElement1;
   int outBegIdx2;
   int outNbElement2;
   int lookbackTotal;
   int lookbackSignal;
   int i;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( (optInSlowPeriod<optInFastPeriod) )
   {
      tempInteger = optInSlowPeriod;
      optInSlowPeriod = optInFastPeriod;
      optInFastPeriod = tempInteger;
   }
   if( (optInSlowPeriod==0) )
   {
      optInSlowPeriod = 26;
   }
   if( (optInFastPeriod==0) )
   {
      optInFastPeriod = 12;
   }
   lookbackSignal = TA_EMA_Lookback(optInSignalPeriod);
   lookbackTotal = lookbackSignal;
   lookbackTotal += TA_EMA_Lookback(optInSlowPeriod);
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
   tempInteger = (((endIdx-startIdx)+1)+lookbackSignal);
   fastEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(fastEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_ALLOC_ERR;
   }
   slowEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(slowEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      return TA_ALLOC_ERR;
   }
   tempInteger = (startIdx-lookbackSignal);
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInSlowPeriod,&outBegIdx1,&outNbElement1,slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInFastPeriod,&outBegIdx2,&outNbElement2,fastEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   if( ((((outBegIdx1!=tempInteger)||(outBegIdx2!=tempInteger))||(outNbElement1!=outNbElement2))||(outNbElement1!=(((endIdx-startIdx)+1)+lookbackSignal))) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return TA_BAD_PARAM;
   }
   for( i = 0; (i<outNbElement1); i += 1 )
   {
      fastEMABuffer[i] = (fastEMABuffer[i]-slowEMABuffer[i]);
   }
   memcpy(outMACD,&fastEMABuffer[lookbackSignal],(((endIdx-startIdx)+1)*sizeof(double)));
   retCode = TA_INT_EMA(0,(outNbElement1-1),fastEMABuffer,optInSignalPeriod,&outBegIdx2,&outNbElement2,outMACDSignal);
   free(fastEMABuffer);
   free(slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return retCode;
   }
   for( i = 0; (i<outNbElement2); i += 1 )
   {
      outMACDHist[i] = (outMACD[i]-outMACDSignal[i]);
   }
   *outBegIdx= startIdx;
   *outNBElement= outNbElement2;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_MACD_Logic( int    startIdx,
                                     int    endIdx,
                                     const double inReal[],
                                     int optInFastPeriod,
                                     int optInSlowPeriod,
                                     int optInSignalPeriod,
                                     int          *outBegIdx,
                                     int          *outNBElement,
                                     double        outMACD[],
                                     double        outMACDSignal[],
                                     double        outMACDHist[] )
{
   double *slowEMABuffer;
   double *fastEMABuffer;
   TA_RetCode retCode;
   int tempInteger;
   int outBegIdx1;
   int outNbElement1;
   int outBegIdx2;
   int outNbElement2;
   int lookbackTotal;
   int lookbackSignal;
   int i;

   if( (optInSlowPeriod<optInFastPeriod) )
   {
      tempInteger = optInSlowPeriod;
      optInSlowPeriod = optInFastPeriod;
      optInFastPeriod = tempInteger;
   }
   if( (optInSlowPeriod==0) )
   {
      optInSlowPeriod = 26;
   }
   if( (optInFastPeriod==0) )
   {
      optInFastPeriod = 12;
   }
   lookbackSignal = TA_EMA_Lookback(optInSignalPeriod);
   lookbackTotal = lookbackSignal;
   lookbackTotal += TA_EMA_Lookback(optInSlowPeriod);
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
   tempInteger = (((endIdx-startIdx)+1)+lookbackSignal);
   fastEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(fastEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_ALLOC_ERR;
   }
   slowEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(slowEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      return TA_ALLOC_ERR;
   }
   tempInteger = (startIdx-lookbackSignal);
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInSlowPeriod,&outBegIdx1,&outNbElement1,slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInFastPeriod,&outBegIdx2,&outNbElement2,fastEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   if( ((((outBegIdx1!=tempInteger)||(outBegIdx2!=tempInteger))||(outNbElement1!=outNbElement2))||(outNbElement1!=(((endIdx-startIdx)+1)+lookbackSignal))) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return TA_BAD_PARAM;
   }
   for( i = 0; (i<outNbElement1); i += 1 )
   {
      fastEMABuffer[i] = (fastEMABuffer[i]-slowEMABuffer[i]);
   }
   memcpy(outMACD,&fastEMABuffer[lookbackSignal],(((endIdx-startIdx)+1)*sizeof(double)));
   retCode = TA_INT_EMA(0,(outNbElement1-1),fastEMABuffer,optInSignalPeriod,&outBegIdx2,&outNbElement2,outMACDSignal);
   free(fastEMABuffer);
   free(slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return retCode;
   }
   for( i = 0; (i<outNbElement2); i += 1 )
   {
      outMACDHist[i] = (outMACD[i]-outMACDSignal[i]);
   }
   *outBegIdx= startIdx;
   *outNBElement= outNbElement2;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_MACD TA_MACD_Logic

TA_RetCode TA_S_MACD( int    startIdx,
                      int    endIdx,
                      const float inReal[],
                      int optInFastPeriod,
                      int optInSlowPeriod,
                      int optInSignalPeriod,
                      int          *outBegIdx,
                      int          *outNBElement,
                      double        outMACD[],
                      double        outMACDSignal[],
                      double        outMACDHist[] )
{
   double *slowEMABuffer;
   double *fastEMABuffer;
   TA_RetCode retCode;
   int tempInteger;
   int outBegIdx1;
   int outNbElement1;
   int outBegIdx2;
   int outNbElement2;
   int lookbackTotal;
   int lookbackSignal;
   int i;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   if( (optInSlowPeriod<optInFastPeriod) )
   {
      tempInteger = optInSlowPeriod;
      optInSlowPeriod = optInFastPeriod;
      optInFastPeriod = tempInteger;
   }
   if( (optInSlowPeriod==0) )
   {
      optInSlowPeriod = 26;
   }
   if( (optInFastPeriod==0) )
   {
      optInFastPeriod = 12;
   }
   lookbackSignal = TA_EMA_Lookback(optInSignalPeriod);
   lookbackTotal = lookbackSignal;
   lookbackTotal += TA_EMA_Lookback(optInSlowPeriod);
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
   tempInteger = (((endIdx-startIdx)+1)+lookbackSignal);
   fastEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(fastEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_ALLOC_ERR;
   }
   slowEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(slowEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      return TA_ALLOC_ERR;
   }
   tempInteger = (startIdx-lookbackSignal);
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInSlowPeriod,&outBegIdx1,&outNbElement1,slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInFastPeriod,&outBegIdx2,&outNbElement2,fastEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   if( ((((outBegIdx1!=tempInteger)||(outBegIdx2!=tempInteger))||(outNbElement1!=outNbElement2))||(outNbElement1!=(((endIdx-startIdx)+1)+lookbackSignal))) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return TA_BAD_PARAM;
   }
   for( i = 0; (i<outNbElement1); i += 1 )
   {
      fastEMABuffer[i] = (fastEMABuffer[i]-slowEMABuffer[i]);
   }
   memcpy(outMACD,&fastEMABuffer[lookbackSignal],(((endIdx-startIdx)+1)*sizeof(double)));
   retCode = TA_INT_EMA(0,(outNbElement1-1),fastEMABuffer,optInSignalPeriod,&outBegIdx2,&outNbElement2,outMACDSignal);
   free(fastEMABuffer);
   free(slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return retCode;
   }
   for( i = 0; (i<outNbElement2); i += 1 )
   {
      outMACDHist[i] = (outMACD[i]-outMACDSignal[i]);
   }
   *outBegIdx= startIdx;
   *outNBElement= outNbElement2;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_MACD_Logic( int    startIdx,
                            int    endIdx,
                            const float inReal[],
                            int optInFastPeriod,
                            int optInSlowPeriod,
                            int optInSignalPeriod,
                            int          *outBegIdx,
                            int          *outNBElement,
                            double        outMACD[],
                            double        outMACDSignal[],
                            double        outMACDHist[] )
{
   double *slowEMABuffer;
   double *fastEMABuffer;
   TA_RetCode retCode;
   int tempInteger;
   int outBegIdx1;
   int outNbElement1;
   int outBegIdx2;
   int outNbElement2;
   int lookbackTotal;
   int lookbackSignal;
   int i;

   if( (optInSlowPeriod<optInFastPeriod) )
   {
      tempInteger = optInSlowPeriod;
      optInSlowPeriod = optInFastPeriod;
      optInFastPeriod = tempInteger;
   }
   if( (optInSlowPeriod==0) )
   {
      optInSlowPeriod = 26;
   }
   if( (optInFastPeriod==0) )
   {
      optInFastPeriod = 12;
   }
   lookbackSignal = TA_EMA_Lookback(optInSignalPeriod);
   lookbackTotal = lookbackSignal;
   lookbackTotal += TA_EMA_Lookback(optInSlowPeriod);
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
   tempInteger = (((endIdx-startIdx)+1)+lookbackSignal);
   fastEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(fastEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return TA_ALLOC_ERR;
   }
   slowEMABuffer = malloc((tempInteger*sizeof(double)));
   if( !(slowEMABuffer) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      return TA_ALLOC_ERR;
   }
   tempInteger = (startIdx-lookbackSignal);
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInSlowPeriod,&outBegIdx1,&outNbElement1,slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   retCode = TA_INT_EMA(tempInteger,endIdx,inReal,optInFastPeriod,&outBegIdx2,&outNbElement2,fastEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return retCode;
   }
   if( ((((outBegIdx1!=tempInteger)||(outBegIdx2!=tempInteger))||(outNbElement1!=outNbElement2))||(outNbElement1!=(((endIdx-startIdx)+1)+lookbackSignal))) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      free(fastEMABuffer);
      free(slowEMABuffer);
      return TA_BAD_PARAM;
   }
   for( i = 0; (i<outNbElement1); i += 1 )
   {
      fastEMABuffer[i] = (fastEMABuffer[i]-slowEMABuffer[i]);
   }
   memcpy(outMACD,&fastEMABuffer[lookbackSignal],(((endIdx-startIdx)+1)*sizeof(double)));
   retCode = TA_INT_EMA(0,(outNbElement1-1),fastEMABuffer,optInSignalPeriod,&outBegIdx2,&outNbElement2,outMACDSignal);
   free(fastEMABuffer);
   free(slowEMABuffer);
   if( (retCode!=TA_SUCCESS) )
   {
      *outBegIdx= 0;
      *outNBElement= 0;
      return retCode;
   }
   for( i = 0; (i<outNbElement2); i += 1 )
   {
      outMACDHist[i] = (outMACD[i]-outMACDSignal[i]);
   }
   *outBegIdx= startIdx;
   *outNBElement= outNbElement2;
   return TA_SUCCESS;

   return TA_SUCCESS;
}

