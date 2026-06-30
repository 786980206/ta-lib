/* Generated */
   public int macdFixLookback( int optInSignalPeriod )
   {
      return (emaLookback(26)+emaLookback(optInSignalPeriod)) ;

   }
   public RetCode macdFix( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInSignalPeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outMACD[],
                           double outMACDSignal[],
                           double outMACDHist[] )
   {
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      return macdUnguarded(startIdx, endIdx, inReal, 0, 0, optInSignalPeriod, outBegIdx, outNBElement, outMACD, outMACDSignal, outMACDHist) ;
   }
   public RetCode macdFixUnguarded( int startIdx,
                                    int endIdx,
                                    double inReal[],
                                    int optInSignalPeriod,
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    double outMACD[],
                                    double outMACDSignal[],
                                    double outMACDHist[] )
   {
      return macdUnguarded(startIdx, endIdx, inReal, 0, 0, optInSignalPeriod, outBegIdx, outNBElement, outMACD, outMACDSignal, outMACDHist) ;
   }
   public RetCode macdFix( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInSignalPeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outMACD[],
                           double outMACDSignal[],
                           double outMACDHist[] )
   {
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      return macdUnguarded(startIdx, endIdx, inReal, 0, 0, optInSignalPeriod, outBegIdx, outNBElement, outMACD, outMACDSignal, outMACDHist) ;
   }
   public RetCode macdFixUnguarded( int startIdx,
                                    int endIdx,
                                    float inReal[],
                                    int optInSignalPeriod,
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    double outMACD[],
                                    double outMACDSignal[],
                                    double outMACDHist[] )
   {
      return macdUnguarded(startIdx, endIdx, inReal, 0, 0, optInSignalPeriod, outBegIdx, outNBElement, outMACD, outMACDSignal, outMACDHist) ;
   }
