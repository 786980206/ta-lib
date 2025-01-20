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

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *  BT       Barry Tsung
 *
 * Change history:
 *
 *  MMDDYY BY      Description
 *  -------------------------------------------------------------------
 *  112605 MF      Initial version.
 *  021806 MF,BT   Fix #1434450 reported by BT.
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #include "TA-Lib-Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode::InternalError)
/* Generated */    namespace TicTacTec { namespace TA { namespace Library {
/* Generated */ #elif defined( _JAVA )
/* Generated */    #include "ta_defs.h"
/* Generated */    #include "ta_java_defs.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode.InternalError)
/* Generated */ #elif defined( _RUST )
/* Generated */    #include "ta_defs.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode.InternalError)
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::CmoLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public int cmoLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API int TA_CMO_Lookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */
   int retValue;

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 14;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return -1;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/

   /* insert lookback code here. */

   retValue = optInTimePeriod + TA_GLOBALS_UNSTABLE_PERIOD(TA_FUNC_UNST_CMO,Cmo);
   if( TA_GLOBALS_COMPATIBILITY == ENUM_VALUE(Compatibility,TA_COMPATIBILITY_METASTOCK,Metastock) )
      retValue--;

   return retValue;
}

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/*
 * TA_CMO - Chande Momentum Oscillator
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Cmo( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     SubArray<double>^ inReal,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Cmo( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     cli::array<double>^ inReal,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cmo( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     double       inReal[],
/* Generated */                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                     MInteger     outBegIdx,
/* Generated */                     MInteger     outNBElement,
/* Generated */                     double        outReal[] )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CMO( int    startIdx,
/* Generated */                               int    endIdx,
/* Generated */                                          const double inReal[],
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          int          *outBegIdx,
/* Generated */                                          int          *outNBElement,
/* Generated */                                          double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
{
	/* insert local variable here */
   int outIdx;

   int today, lookbackTotal, unstablePeriod, i;
   double prevGain, prevLoss, prevValue, savePrevValue;
   double tempValue1, tempValue2, tempValue3, tempValue4;

   #if defined( USE_SINGLE_PRECISION_INPUT )
      ARRAY_MEMMOVEMIX_VAR;
   #endif

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 14;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outReal )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* CMO calculation is mostly identical to RSI.
    *
    * The only difference is in the last step of calculation:
    *
    *   RSI = gain / (gain+loss)
    *   CMO = (gain-loss) / (gain+loss)
    *
    * See the RSI function for potentially some more info
    * on this algo.
    */

   VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
   VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);

   /* Adjust startIdx to account for the lookback period. */
   lookbackTotal = LOOKBACK_CALL(CMO)( optInTimePeriod );

   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
      return ENUM_VALUE(RetCode,TA_SUCCESS,Success);

   outIdx = 0; /* Index into the output. */

   /* Trap special case where the period is '1'.
    * In that case, just copy the input into the
    * output for the requested range (as-is !)
    */
   if( optInTimePeriod == 1 )
   {
      VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
      i = (endIdx-startIdx)+1;
      VALUE_HANDLE_DEREF(outNBElement) = i;
      #if defined( USE_SINGLE_PRECISION_INPUT )
        ARRAY_MEMMOVEMIX( outReal, 0, inReal, startIdx, i );
      #else
        ARRAY_MEMMOVE( outReal, 0, inReal, startIdx, i );
      #endif
      return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
   }

   /* Accumulate Wilder's "Average Gain" and "Average Loss"
    * among the initial period.
    */
   today = startIdx-lookbackTotal;
   prevValue = inReal[today];

   unstablePeriod = TA_GLOBALS_UNSTABLE_PERIOD(TA_FUNC_UNST_CMO,Cmo);

   /* If there is no unstable period,
    * calculate the 'additional' initial
    * price bar who is particuliar to
    * metastock.
    * If there is an unstable period,
    * no need to calculate since this
    * first value will be surely skip.
    */
   if( (unstablePeriod == 0) &&
       (TA_GLOBALS_COMPATIBILITY == ENUM_VALUE(Compatibility,TA_COMPATIBILITY_METASTOCK,Metastock)))
   {
      /* Preserve prevValue because it may get
       * overwritten by the output.
       *(because output ptr could be the same as input ptr).
       */
      savePrevValue = prevValue;

      /* No unstable period, so must calculate first output
       * particular to Metastock.
       * (Metastock re-use the first price bar, so there
       *  is no loss/gain at first. Beats me why they
       *  are doing all this).
       */
      prevGain = 0.0;
      prevLoss = 0.0;
      for( i=optInTimePeriod; i > 0; i-- )
      {
         tempValue1 = inReal[today++];
         tempValue2 = tempValue1 - prevValue;
         prevValue  = tempValue1;
         if( tempValue2 < 0 )
            prevLoss -= tempValue2;
         else
            prevGain += tempValue2;
      }


      tempValue1 = prevLoss/optInTimePeriod;
      tempValue2 = prevGain/optInTimePeriod;
      tempValue3 = tempValue2-tempValue1;
      tempValue4 = tempValue1+tempValue2;

      /* Write the output. */
      if( !TA_IS_ZERO(tempValue4) )
         outReal[outIdx++] = 100*(tempValue3/tempValue4);
      else
         outReal[outIdx++] = 0.0;

      /* Are we done? */
      if( today > endIdx )
      {
         VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
         VALUE_HANDLE_DEREF(outNBElement) = outIdx;
         return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
      }

      /* Start over for the next price bar. */
      today -= optInTimePeriod;
      prevValue = savePrevValue;
   }


   /* Remaining of the processing is identical
    * for both Classic calculation and Metastock.
    */
   prevGain = 0.0;
   prevLoss = 0.0;
   today++;
   for( i=optInTimePeriod; i > 0; i-- )
   {
      tempValue1 = inReal[today++];
      tempValue2 = tempValue1 - prevValue;
      prevValue  = tempValue1;
      if( tempValue2 < 0 )
         prevLoss -= tempValue2;
      else
         prevGain += tempValue2;
   }


   /* Subsequent prevLoss and prevGain are smoothed
    * using the previous values (Wilder's approach).
    *  1) Multiply the previous by 'period-1'.
    *  2) Add today value.
    *  3) Divide by 'period'.
    */
   prevLoss /= optInTimePeriod;
   prevGain /= optInTimePeriod;

   /* Often documentation present the RSI calculation as follow:
    *    RSI = 100 - (100 / 1 + (prevGain/prevLoss))
    *
    * The following is equivalent:
    *    RSI = 100 * (prevGain/(prevGain+prevLoss))
    *
    * The second equation is used here for speed optimization.
    */
   if( today > startIdx )
   {
      tempValue1 = prevGain+prevLoss;
      if( !TA_IS_ZERO(tempValue1) )
         outReal[outIdx++] = 100.0*((prevGain-prevLoss)/tempValue1);
      else
         outReal[outIdx++] = 0.0;
   }
   else
   {
      /* Skip the unstable period. Do the processing
       * but do not write it in the output.
       */
      while( today < startIdx )
      {
         tempValue1 = inReal[today];
         tempValue2 = tempValue1 - prevValue;
         prevValue  = tempValue1;

         prevLoss *= (optInTimePeriod-1);
         prevGain *= (optInTimePeriod-1);
         if( tempValue2 < 0 )
            prevLoss -= tempValue2;
         else
            prevGain += tempValue2;

         prevLoss /= optInTimePeriod;
         prevGain /= optInTimePeriod;

         today++;
      }
   }

   /* Unstable period skipped... now continue
    * processing if needed.
    */
   while( today <= endIdx )
   {
      tempValue1 = inReal[today++];
      tempValue2 = tempValue1 - prevValue;
      prevValue  = tempValue1;

      prevLoss *= (optInTimePeriod-1);
      prevGain *= (optInTimePeriod-1);
      if( tempValue2 < 0 )
         prevLoss -= tempValue2;
      else
         prevGain += tempValue2;

      prevLoss /= optInTimePeriod;
      prevGain /= optInTimePeriod;
      tempValue1 = prevGain+prevLoss;
      if( !TA_IS_ZERO(tempValue1) )
         outReal[outIdx++] = 100.0*((prevGain-prevLoss)/tempValue1);
      else
         outReal[outIdx++] = 0.0;
   }

   VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
   VALUE_HANDLE_DEREF(outNBElement) = outIdx;

   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED ) && !defined( _JAVA )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Cmo( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     SubArray<float>^ inReal,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Cmo( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     cli::array<float>^ inReal,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cmo( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     float        inReal[],
/* Generated */                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                     MInteger     outBegIdx,
/* Generated */                     MInteger     outNBElement,
/* Generated */                     double        outReal[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_CMO( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      const float  inReal[],
/* Generated */                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                      int          *outBegIdx,
/* Generated */                      int          *outNBElement,
/* Generated */                      double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    int outIdx;
/* Generated */    int today, lookbackTotal, unstablePeriod, i;
/* Generated */    double prevGain, prevLoss, prevValue, savePrevValue;
/* Generated */    double tempValue1, tempValue2, tempValue3, tempValue4;
/* Generated */    #if defined( USE_SINGLE_PRECISION_INPUT )
/* Generated */       ARRAY_MEMMOVEMIX_VAR;
/* Generated */    #endif
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */     if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod = 14;
/* Generated */     else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !outReal )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */  #endif 
/* Generated */    VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */    VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
/* Generated */    lookbackTotal = LOOKBACK_CALL(CMO)( optInTimePeriod );
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    outIdx = 0; 
/* Generated */    if( optInTimePeriod == 1 )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
/* Generated */       i = (endIdx-startIdx)+1;
/* Generated */       VALUE_HANDLE_DEREF(outNBElement) = i;
/* Generated */       #if defined( USE_SINGLE_PRECISION_INPUT )
/* Generated */         ARRAY_MEMMOVEMIX( outReal, 0, inReal, startIdx, i );
/* Generated */       #else
/* Generated */         ARRAY_MEMMOVE( outReal, 0, inReal, startIdx, i );
/* Generated */       #endif
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    }
/* Generated */    today = startIdx-lookbackTotal;
/* Generated */    prevValue = inReal[today];
/* Generated */    unstablePeriod = TA_GLOBALS_UNSTABLE_PERIOD(TA_FUNC_UNST_CMO,Cmo);
/* Generated */    if( (unstablePeriod == 0) &&
/* Generated */        (TA_GLOBALS_COMPATIBILITY == ENUM_VALUE(Compatibility,TA_COMPATIBILITY_METASTOCK,Metastock)))
/* Generated */    {
/* Generated */       savePrevValue = prevValue;
/* Generated */       prevGain = 0.0;
/* Generated */       prevLoss = 0.0;
/* Generated */       for( i=optInTimePeriod; i > 0; i-- )
/* Generated */       {
/* Generated */          tempValue1 = inReal[today++];
/* Generated */          tempValue2 = tempValue1 - prevValue;
/* Generated */          prevValue  = tempValue1;
/* Generated */          if( tempValue2 < 0 )
/* Generated */             prevLoss -= tempValue2;
/* Generated */          else
/* Generated */             prevGain += tempValue2;
/* Generated */       }
/* Generated */       tempValue1 = prevLoss/optInTimePeriod;
/* Generated */       tempValue2 = prevGain/optInTimePeriod;
/* Generated */       tempValue3 = tempValue2-tempValue1;
/* Generated */       tempValue4 = tempValue1+tempValue2;
/* Generated */       if( !TA_IS_ZERO(tempValue4) )
/* Generated */          outReal[outIdx++] = 100*(tempValue3/tempValue4);
/* Generated */       else
/* Generated */          outReal[outIdx++] = 0.0;
/* Generated */       if( today > endIdx )
/* Generated */       {
/* Generated */          VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
/* Generated */          VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */          return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */       }
/* Generated */       today -= optInTimePeriod;
/* Generated */       prevValue = savePrevValue;
/* Generated */    }
/* Generated */    prevGain = 0.0;
/* Generated */    prevLoss = 0.0;
/* Generated */    today++;
/* Generated */    for( i=optInTimePeriod; i > 0; i-- )
/* Generated */    {
/* Generated */       tempValue1 = inReal[today++];
/* Generated */       tempValue2 = tempValue1 - prevValue;
/* Generated */       prevValue  = tempValue1;
/* Generated */       if( tempValue2 < 0 )
/* Generated */          prevLoss -= tempValue2;
/* Generated */       else
/* Generated */          prevGain += tempValue2;
/* Generated */    }
/* Generated */    prevLoss /= optInTimePeriod;
/* Generated */    prevGain /= optInTimePeriod;
/* Generated */    if( today > startIdx )
/* Generated */    {
/* Generated */       tempValue1 = prevGain+prevLoss;
/* Generated */       if( !TA_IS_ZERO(tempValue1) )
/* Generated */          outReal[outIdx++] = 100.0*((prevGain-prevLoss)/tempValue1);
/* Generated */       else
/* Generated */          outReal[outIdx++] = 0.0;
/* Generated */    }
/* Generated */    else
/* Generated */    {
/* Generated */       while( today < startIdx )
/* Generated */       {
/* Generated */          tempValue1 = inReal[today];
/* Generated */          tempValue2 = tempValue1 - prevValue;
/* Generated */          prevValue  = tempValue1;
/* Generated */          prevLoss *= (optInTimePeriod-1);
/* Generated */          prevGain *= (optInTimePeriod-1);
/* Generated */          if( tempValue2 < 0 )
/* Generated */             prevLoss -= tempValue2;
/* Generated */          else
/* Generated */             prevGain += tempValue2;
/* Generated */          prevLoss /= optInTimePeriod;
/* Generated */          prevGain /= optInTimePeriod;
/* Generated */          today++;
/* Generated */       }
/* Generated */    }
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */       tempValue1 = inReal[today++];
/* Generated */       tempValue2 = tempValue1 - prevValue;
/* Generated */       prevValue  = tempValue1;
/* Generated */       prevLoss *= (optInTimePeriod-1);
/* Generated */       prevGain *= (optInTimePeriod-1);
/* Generated */       if( tempValue2 < 0 )
/* Generated */          prevLoss -= tempValue2;
/* Generated */       else
/* Generated */          prevGain += tempValue2;
/* Generated */       prevLoss /= optInTimePeriod;
/* Generated */       prevGain /= optInTimePeriod;
/* Generated */       tempValue1 = prevGain+prevLoss;
/* Generated */       if( !TA_IS_ZERO(tempValue1) )
/* Generated */          outReal[outIdx++] = 100.0*((prevGain-prevLoss)/tempValue1);
/* Generated */       else
/* Generated */          outReal[outIdx++] = 0.0;
/* Generated */    }
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
/* Generated */    VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */    return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }}} // Close namespace TicTacTec.TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/

