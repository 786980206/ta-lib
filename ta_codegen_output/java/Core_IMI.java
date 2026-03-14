/* Generated */
   public int imiLookback( int optInTimePeriod )
   {
      return ((optInTimePeriod+this.unstablePeriod[FuncUnstId.Imi.ordinal()])-1) ;

   }
   public RetCode imi( int startIdx,
                       int endIdx,
                       double inOpen[],
                       double inClose[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int lookback;
      int outIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outIdx = 0;
      lookback = imiLookback(optInTimePeriod);
      if( (startIdx<lookback) ) {
         startIdx = lookback;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outBegIdx.value = startIdx;
      while( (startIdx<=endIdx) ) {
         for( i = (startIdx-lookback); (i<=startIdx); i += 1 ) {
            if( (close>open) ) {
               upsum += (close-open);
            } else {
               downsum += (open-close);
            }
            outReal[outIdx] = (100.0*(upsum/(upsum+downsum)));
         }
         startIdx += 1;
         outIdx += 1;
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode imiLogic( int startIdx,
                            int endIdx,
                            double inOpen[],
                            double inClose[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int lookback;
      int outIdx;
      outIdx = 0;
      lookback = imiLookback(optInTimePeriod);
      if( (startIdx<lookback) ) {
         startIdx = lookback;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outBegIdx.value = startIdx;
      while( (startIdx<=endIdx) ) {
         for( i = (startIdx-lookback); (i<=startIdx); i += 1 ) {
            if( (close>open) ) {
               upsum += (close-open);
            } else {
               downsum += (open-close);
            }
            outReal[outIdx] = (100.0*(upsum/(upsum+downsum)));
         }
         startIdx += 1;
         outIdx += 1;
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode imi( int startIdx,
                       int endIdx,
                       float inOpen[],
                       float inClose[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int lookback;
      int outIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outIdx = 0;
      lookback = imiLookback(optInTimePeriod);
      if( (startIdx<lookback) ) {
         startIdx = lookback;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outBegIdx.value = startIdx;
      while( (startIdx<=endIdx) ) {
         for( i = (startIdx-lookback); (i<=startIdx); i += 1 ) {
            if( (close>open) ) {
               upsum += (close-open);
            } else {
               downsum += (open-close);
            }
            outReal[outIdx] = (100.0*(upsum/(upsum+downsum)));
         }
         startIdx += 1;
         outIdx += 1;
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode imiLogic( int startIdx,
                            int endIdx,
                            float inOpen[],
                            float inClose[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int lookback;
      int outIdx;
      outIdx = 0;
      lookback = imiLookback(optInTimePeriod);
      if( (startIdx<lookback) ) {
         startIdx = lookback;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outBegIdx.value = startIdx;
      while( (startIdx<=endIdx) ) {
         for( i = (startIdx-lookback); (i<=startIdx); i += 1 ) {
            if( (close>open) ) {
               upsum += (close-open);
            } else {
               downsum += (open-close);
            }
            outReal[outIdx] = (100.0*(upsum/(upsum+downsum)));
         }
         startIdx += 1;
         outIdx += 1;
      }
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
