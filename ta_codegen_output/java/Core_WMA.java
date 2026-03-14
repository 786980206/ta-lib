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
      int inIdx;
      int outIdx;
      int i;
      int trailingIdx;
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int lookbackTotal;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outBegIdx.value = startIdx;
         outNBElement.value = ((endIdx-startIdx)+1);
         System.arraycopy(inReal, startIdx, outReal, 0, (((int)outNBElement.value)*1));
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))>>1);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      periodSub = ((double)0.0);
      periodSum = periodSub;
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSum += (tempReal*i);
         i += 1;
      }
      trailingValue = 0.0;
      while( (inIdx<=endIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*optInTimePeriod);
         trailingValue = inReal[trailingIdx++];
         outReal[outIdx++] = (periodSum/divider);
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode wmaLogic( int startIdx,
                            int endIdx,
                            double inReal[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int inIdx;
      int outIdx;
      int i;
      int trailingIdx;
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int lookbackTotal;
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outBegIdx.value = startIdx;
         outNBElement.value = ((endIdx-startIdx)+1);
         System.arraycopy(inReal, startIdx, outReal, 0, (((int)outNBElement.value)*1));
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))>>1);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      periodSub = ((double)0.0);
      periodSum = periodSub;
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSum += (tempReal*i);
         i += 1;
      }
      trailingValue = 0.0;
      while( (inIdx<=endIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*optInTimePeriod);
         trailingValue = inReal[trailingIdx++];
         outReal[outIdx++] = (periodSum/divider);
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
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
      int inIdx;
      int outIdx;
      int i;
      int trailingIdx;
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int lookbackTotal;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outBegIdx.value = startIdx;
         outNBElement.value = ((endIdx-startIdx)+1);
         System.arraycopy(inReal, startIdx, outReal, 0, (((int)outNBElement.value)*1));
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))>>1);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      periodSub = ((double)0.0);
      periodSum = periodSub;
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSum += (tempReal*i);
         i += 1;
      }
      trailingValue = 0.0;
      while( (inIdx<=endIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*optInTimePeriod);
         trailingValue = inReal[trailingIdx++];
         outReal[outIdx++] = (periodSum/divider);
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode wmaLogic( int startIdx,
                            int endIdx,
                            float inReal[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int inIdx;
      int outIdx;
      int i;
      int trailingIdx;
      int divider;
      double periodSum;
      double periodSub;
      double tempReal;
      double trailingValue;
      int lookbackTotal;
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( (optInTimePeriod==1) ) {
         outBegIdx.value = startIdx;
         outNBElement.value = ((endIdx-startIdx)+1);
         System.arraycopy(inReal, startIdx, outReal, 0, (((int)outNBElement.value)*1));
         return RetCode.Success ;
      }
      divider = ((optInTimePeriod*(optInTimePeriod+1))>>1);
      outIdx = 0;
      trailingIdx = (startIdx-lookbackTotal);
      periodSub = ((double)0.0);
      periodSum = periodSub;
      inIdx = trailingIdx;
      i = 1;
      while( (inIdx<startIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSum += (tempReal*i);
         i += 1;
      }
      trailingValue = 0.0;
      while( (inIdx<=endIdx) ) {
         tempReal = inReal[inIdx++];
         periodSub += tempReal;
         periodSub -= trailingValue;
         periodSum += (tempReal*optInTimePeriod);
         trailingValue = inReal[trailingIdx++];
         outReal[outIdx++] = (periodSum/divider);
         periodSum -= periodSub;
      }
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
