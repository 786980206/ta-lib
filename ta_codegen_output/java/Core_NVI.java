/* Generated */
   public int nviLookback( )
   {
      return 0 ;

   }
   public RetCode nvi( int startIdx,
                       int endIdx,
                       double inClose[],
                       double inVolume[],
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outBegIdx.value = 0;
      outNBElement.value = 0;
      return RetCode.Success ;
   }
   public RetCode nviLogic( int startIdx,
                            int endIdx,
                            double inClose[],
                            double inVolume[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      outBegIdx.value = 0;
      outNBElement.value = 0;
      return RetCode.Success ;
   }
   public RetCode nvi( int startIdx,
                       int endIdx,
                       float inClose[],
                       float inVolume[],
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outBegIdx.value = 0;
      outNBElement.value = 0;
      return RetCode.Success ;
   }
   public RetCode nviLogic( int startIdx,
                            int endIdx,
                            float inClose[],
                            float inVolume[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      outBegIdx.value = 0;
      outNBElement.value = 0;
      return RetCode.Success ;
   }
