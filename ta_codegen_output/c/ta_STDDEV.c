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

TA_LIB_API int TA_STDDEV_Lookback( int optInTimePeriod, double optInNbDev )
{
   return TA_VAR_Lookback(optInTimePeriod,optInNbDev);
}

TA_LIB_API TA_RetCode TA_STDDEV( int    startIdx,
                                 int    endIdx,
                                 const double inReal[],
                                 int optInTimePeriod,
                                 double optInNbDev,
                                 int          *outBegIdx,
                                 int          *outNBElement,
                                 double        outReal[] )
{
   int i;
   TA_RetCode retCode;
   double tempReal;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   retCode = TA_INT_VAR(startIdx,endIdx,inReal,optInTimePeriod,1.0,outBegIdx,outNBElement,outReal);
   if( (retCode!=TA_SUCCESS) )
   {
      return retCode;
   }
   if( (optInNbDev!=1.0) )
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = (sqrt(tempReal)*optInNbDev);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   } else 
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = sqrt(tempReal);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   }
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_LIB_API TA_RetCode TA_STDDEV_Logic( int    startIdx,
                                       int    endIdx,
                                       const double inReal[],
                                       int optInTimePeriod,
                                       double optInNbDev,
                                       int          *outBegIdx,
                                       int          *outNBElement,
                                       double        outReal[] )
{
   int i;
   TA_RetCode retCode;
   double tempReal;

   retCode = TA_INT_VAR(startIdx,endIdx,inReal,optInTimePeriod,1.0,outBegIdx,outNBElement,outReal);
   if( (retCode!=TA_SUCCESS) )
   {
      return retCode;
   }
   if( (optInNbDev!=1.0) )
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = (sqrt(tempReal)*optInNbDev);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   } else 
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = sqrt(tempReal);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   }
   return TA_SUCCESS;

   return TA_SUCCESS;
}

#define TA_INT_STDDEV TA_STDDEV_Logic

TA_RetCode TA_S_STDDEV( int    startIdx,
                        int    endIdx,
                        const float inReal[],
                        int optInTimePeriod,
                        double optInNbDev,
                        int          *outBegIdx,
                        int          *outNBElement,
                        double        outReal[] )
{
   int i;
   TA_RetCode retCode;
   double tempReal;

   if( startIdx < 0 )
      return TA_OUT_OF_RANGE_START_INDEX;
   if( (endIdx < 0) || (endIdx < startIdx) )
      return TA_OUT_OF_RANGE_END_INDEX;

   retCode = TA_INT_VAR(startIdx,endIdx,inReal,optInTimePeriod,1.0,outBegIdx,outNBElement,outReal);
   if( (retCode!=TA_SUCCESS) )
   {
      return retCode;
   }
   if( (optInNbDev!=1.0) )
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = (sqrt(tempReal)*optInNbDev);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   } else 
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = sqrt(tempReal);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   }
   return TA_SUCCESS;

   return TA_SUCCESS;
}

TA_RetCode TA_S_STDDEV_Logic( int    startIdx,
                              int    endIdx,
                              const float inReal[],
                              int optInTimePeriod,
                              double optInNbDev,
                              int          *outBegIdx,
                              int          *outNBElement,
                              double        outReal[] )
{
   int i;
   TA_RetCode retCode;
   double tempReal;

   retCode = TA_INT_VAR(startIdx,endIdx,inReal,optInTimePeriod,1.0,outBegIdx,outNBElement,outReal);
   if( (retCode!=TA_SUCCESS) )
   {
      return retCode;
   }
   if( (optInNbDev!=1.0) )
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = (sqrt(tempReal)*optInNbDev);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   } else 
   {
      for( i = 0; (i<((int)*outNBElement)); i += 1 )
      {
         tempReal = outReal[i];
         if( !((tempReal<0.00000001)) )
         {
            outReal[i] = sqrt(tempReal);
         } else 
         {
            outReal[i] = ((double)0.0);
         }
      }
   }
   return TA_SUCCESS;

   return TA_SUCCESS;
}

