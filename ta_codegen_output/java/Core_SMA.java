/* Generated */
   public int smaLookback( )
   {
      return optInTimePeriod - 1;
   }
   public RetCode sma( int startIdx,
                       int endIdx,
                       double inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double periodTotal;
      double tempReal;
      int i;
      int outIdx;
      int trailingIdx;
      int lookbackTotal;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      periodTotal = 0;
      lookbackTotal = ((int)(optInTimePeriod-1)));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      periodTotal = 0;
      trailingIdx = (startIdx-lookbackTotal);
      i = trailingIdx;
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            periodTotal += ((double)inReal[i]));
            i = (i+1);
         }
      }
      outIdx = 0;
      while( (i<=endIdx) ) {
         periodTotal += ((double)inReal[i]));
         i = (i+1);
         tempReal = periodTotal;
         periodTotal -= ((double)inReal[trailingIdx]));
         trailingIdx = (trailingIdx+1);
         outReal[outIdx] = (tempReal/((double)optInTimePeriod)));
         outIdx = (outIdx+1);
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode sma( int startIdx,
                       int endIdx,
                       float inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double periodTotal;
      double tempReal;
      int i;
      int outIdx;
      int trailingIdx;
      int lookbackTotal;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      periodTotal = 0;
      lookbackTotal = ((int)(optInTimePeriod-1)));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      periodTotal = 0;
      trailingIdx = (startIdx-lookbackTotal);
      i = trailingIdx;
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            periodTotal += ((double)inReal[i]));
            i = (i+1);
         }
      }
      outIdx = 0;
      while( (i<=endIdx) ) {
         periodTotal += ((double)inReal[i]));
         i = (i+1);
         tempReal = periodTotal;
         periodTotal -= ((double)inReal[trailingIdx]));
         trailingIdx = (trailingIdx+1);
         outReal[outIdx] = (tempReal/((double)optInTimePeriod)));
         outIdx = (outIdx+1);
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
