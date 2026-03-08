/* Generated */
   public int emaLookback( int optInTimePeriod )
   {
      int retValue;
      retValue = ((optInTimePeriod-1)+this.unstablePeriod[FuncUnstId.Ema.ordinal()]);
      return retValue ;

   }
   public RetCode ema( int startIdx,
                       int endIdx,
                       double inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double tempReal;
      double prevMA;
      int i;
      int today;
      int outIdx;
      int lookbackTotal;
      double optInK_1;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = ((int)emaLookback(optInTimePeriod));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      optInK_1 = (2.0 / ((double)(optInTimePeriod) + 1.0));
      outBegIdx.value = startIdx;
      if( (this.compatibility==Compatibility.Default) ) {
         today = (startIdx-lookbackTotal);
         i = optInTimePeriod;
         tempReal = 0;
         for( i = optInTimePeriod; i > 0; i-- ) {
            tempReal += ((double)inReal[today]);
            today = (today+1);
         }
         prevMA = (tempReal/((double)optInTimePeriod));
      } else {
         prevMA = ((double)inReal[0]);
         today = 1;
      }
      while( (today<=startIdx) ) {
         prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
         today = (today+1);
      }
      outReal[0] = prevMA;
      outIdx = 1;
      while( (today<=endIdx) ) {
         prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
         today = (today+1);
         outReal[outIdx] = prevMA;
         outIdx = (outIdx+1);
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode ema( int startIdx,
                       int endIdx,
                       float inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double tempReal;
      double prevMA;
      int i;
      int today;
      int outIdx;
      int lookbackTotal;
      double optInK_1;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = ((int)emaLookback(optInTimePeriod));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      optInK_1 = (2.0 / ((double)(optInTimePeriod) + 1.0));
      outBegIdx.value = startIdx;
      if( (this.compatibility==Compatibility.Default) ) {
         today = (startIdx-lookbackTotal);
         i = optInTimePeriod;
         tempReal = 0;
         for( i = optInTimePeriod; i > 0; i-- ) {
            tempReal += ((double)inReal[today]);
            today = (today+1);
         }
         prevMA = (tempReal/((double)optInTimePeriod));
      } else {
         prevMA = ((double)inReal[0]);
         today = 1;
      }
      while( (today<=startIdx) ) {
         prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
         today = (today+1);
      }
      outReal[0] = prevMA;
      outIdx = 1;
      while( (today<=endIdx) ) {
         prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
         today = (today+1);
         outReal[outIdx] = prevMA;
         outIdx = (outIdx+1);
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
