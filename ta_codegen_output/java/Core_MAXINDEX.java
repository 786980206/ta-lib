/* Generated */
   public int maxindexLookback( int optInTimePeriod )
   {
      return (optInTimePeriod-1) ;

   }
   public RetCode maxindex( int startIdx,
                            int endIdx,
                            double inReal[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            int outInteger[] )
   {
      double highest;
      double tmp;
      int outIdx;
      int nbInitialElementNeeded;
      int trailingIdx;
      int today;
      int i;
      int highestIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      nbInitialElementNeeded = (optInTimePeriod-1);
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      trailingIdx = (startIdx-nbInitialElementNeeded);
      highestIdx = (0-1);
      highest = 0.0;
      while( (today<=endIdx) ) {
         tmp = inReal[today];
         if( (highestIdx<trailingIdx) ) {
            highestIdx = trailingIdx;
            highest = inReal[highestIdx];
            i = highestIdx;
            while( (++i<=today) ) {
               tmp = inReal[i];
               if( (tmp>highest) ) {
                  highestIdx = i;
                  highest = tmp;
               }
            }
         } else if( (tmp>=highest) ) {
            highestIdx = today;
            highest = tmp;
         }
         outInteger[outIdx++] = highestIdx;
         trailingIdx += 1;
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode maxindexLogic( int startIdx,
                                 int endIdx,
                                 double inReal[],
                                 int optInTimePeriod,
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double highest;
      double tmp;
      int outIdx;
      int nbInitialElementNeeded;
      int trailingIdx;
      int today;
      int i;
      int highestIdx;
      nbInitialElementNeeded = (optInTimePeriod-1);
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      trailingIdx = (startIdx-nbInitialElementNeeded);
      highestIdx = (0-1);
      highest = 0.0;
      while( (today<=endIdx) ) {
         tmp = inReal[today];
         if( (highestIdx<trailingIdx) ) {
            highestIdx = trailingIdx;
            highest = inReal[highestIdx];
            i = highestIdx;
            while( (++i<=today) ) {
               tmp = inReal[i];
               if( (tmp>highest) ) {
                  highestIdx = i;
                  highest = tmp;
               }
            }
         } else if( (tmp>=highest) ) {
            highestIdx = today;
            highest = tmp;
         }
         outInteger[outIdx++] = highestIdx;
         trailingIdx += 1;
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode maxindex( int startIdx,
                            int endIdx,
                            float inReal[],
                            int optInTimePeriod,
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            int outInteger[] )
   {
      double highest;
      double tmp;
      int outIdx;
      int nbInitialElementNeeded;
      int trailingIdx;
      int today;
      int i;
      int highestIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      nbInitialElementNeeded = (optInTimePeriod-1);
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      trailingIdx = (startIdx-nbInitialElementNeeded);
      highestIdx = (0-1);
      highest = 0.0;
      while( (today<=endIdx) ) {
         tmp = inReal[today];
         if( (highestIdx<trailingIdx) ) {
            highestIdx = trailingIdx;
            highest = inReal[highestIdx];
            i = highestIdx;
            while( (++i<=today) ) {
               tmp = inReal[i];
               if( (tmp>highest) ) {
                  highestIdx = i;
                  highest = tmp;
               }
            }
         } else if( (tmp>=highest) ) {
            highestIdx = today;
            highest = tmp;
         }
         outInteger[outIdx++] = highestIdx;
         trailingIdx += 1;
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode maxindexLogic( int startIdx,
                                 int endIdx,
                                 float inReal[],
                                 int optInTimePeriod,
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double highest;
      double tmp;
      int outIdx;
      int nbInitialElementNeeded;
      int trailingIdx;
      int today;
      int i;
      int highestIdx;
      nbInitialElementNeeded = (optInTimePeriod-1);
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      trailingIdx = (startIdx-nbInitialElementNeeded);
      highestIdx = (0-1);
      highest = 0.0;
      while( (today<=endIdx) ) {
         tmp = inReal[today];
         if( (highestIdx<trailingIdx) ) {
            highestIdx = trailingIdx;
            highest = inReal[highestIdx];
            i = highestIdx;
            while( (++i<=today) ) {
               tmp = inReal[i];
               if( (tmp>highest) ) {
                  highestIdx = i;
                  highest = tmp;
               }
            }
         } else if( (tmp>=highest) ) {
            highestIdx = today;
            highest = tmp;
         }
         outInteger[outIdx++] = highestIdx;
         trailingIdx += 1;
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
