/* Generated */
   public int wmaLookback( int optInTimePeriod )
   {
      return (optInTimePeriod-1) ;

   }
   public RetCode wma( int startIdx,
                       int endIdx,
                       double inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int inIdx;
      int outIdx;
      int trailingIdx;
      int lookbackTotal;
      int i;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      periodSum = 0;
      periodSub = 0;
      lookbackTotal = ((int)(optInTimePeriod-1));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outNBElement.value = nbElement;
         outBegIdx.value = startIdx;
         System.arraycopy(inReal,startIdx,outReal,0,nbElement);
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))/2);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = ((double)inReal[inIdx]);
         periodSub += tempReal;
         periodSum += (tempReal*((double)i));
         i += 1;
         inIdx += 1;
      }
      trailingValue = 0;
      while( (inIdx<=endIdx) ) {
         tempReal = ((double)inReal[inIdx]);
         inIdx += 1;
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*((double)optInTimePeriod));
         trailingValue = ((double)inReal[trailingIdx]);
         trailingIdx += 1;
         outReal[outIdx] = (periodSum/((double)divider));
         outIdx += 1;
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
      return RetCode.Success ;
   }
   public RetCode wma( int startIdx,
                       int endIdx,
                       float inReal[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int inIdx;
      int outIdx;
      int trailingIdx;
      int lookbackTotal;
      int i;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      periodSum = 0;
      periodSub = 0;
      lookbackTotal = ((int)(optInTimePeriod-1));
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outNBElement.value = nbElement;
         outBegIdx.value = startIdx;
         System.arraycopy(inReal,startIdx,outReal,0,nbElement);
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))/2);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = ((double)inReal[inIdx]);
         periodSub += tempReal;
         periodSum += (tempReal*((double)i));
         i += 1;
         inIdx += 1;
      }
      trailingValue = 0;
      while( (inIdx<=endIdx) ) {
         tempReal = ((double)inReal[inIdx]);
         inIdx += 1;
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*((double)optInTimePeriod));
         trailingValue = ((double)inReal[trailingIdx]);
         trailingIdx += 1;
         outReal[outIdx] = (periodSum/((double)divider));
         outIdx += 1;
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
      return RetCode.Success ;
   }
