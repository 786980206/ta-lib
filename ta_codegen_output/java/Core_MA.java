/* Generated */
   public int maLookback( int optInTimePeriod, int optInMAType )
   {
      int retValue;
      if( (optInTimePeriod<=1) ) {
         return 0 ;
      }
      switch( optInMAType )
      {
      case MAType.Sma:
         retValue = smaLookback(optInTimePeriod);
         break;
      case MAType.Ema:
         retValue = emaLookback(optInTimePeriod);
         break;
      default:
         retValue = 0;
         break;
      }
      return retValue ;

   }
   public RetCode ma( int startIdx,
                      int endIdx,
                      double inReal[],
                      int optInTimePeriod,
                      int optInMAType,
                      MInteger outBegIdx,
                      MInteger outNBElement,
                      double outReal[] )
   {
      int nbElement;
      int outIdx;
      int todayIdx;
      RetCode retCode;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         todayIdx = startIdx;
         outIdx = 0;
         while( (outIdx<nbElement) ) {
            outReal[outIdx] = ((double)inReal[todayIdx]);
            outIdx = (outIdx+1);
            todayIdx = (todayIdx+1);
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case MAType.Sma:
         retCode = sma(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case MAType.Ema:
         retCode = ema(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
      return RetCode.Success ;
   }
   public RetCode ma( int startIdx,
                      int endIdx,
                      float inReal[],
                      int optInTimePeriod,
                      int optInMAType,
                      MInteger outBegIdx,
                      MInteger outNBElement,
                      double outReal[] )
   {
      int nbElement;
      int outIdx;
      int todayIdx;
      RetCode retCode;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         todayIdx = startIdx;
         outIdx = 0;
         while( (outIdx<nbElement) ) {
            outReal[outIdx] = ((double)inReal[todayIdx]);
            outIdx = (outIdx+1);
            todayIdx = (todayIdx+1);
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case MAType.Sma:
         retCode = sma(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case MAType.Ema:
         retCode = ema(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
      return RetCode.Success ;
   }
