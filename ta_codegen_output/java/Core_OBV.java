/* Generated */
   public int obvLookback( )
   {
      return 0 ;

   }
   public RetCode obv( int startIdx,
                       int endIdx,
                       double inReal[],
                       double inVolume[],
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int i;
      int outIdx;
      double prevReal;
      double tempReal;
      double prevOBV;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      prevOBV = inVolume[startIdx];
      prevReal = inReal[startIdx];
      outIdx = 0;
      for( i = startIdx; (i<=endIdx); i += 1 ) {
         tempReal = inReal[i];
         if( (tempReal>prevReal) ) {
            prevOBV += inVolume[i];
         } else if( (tempReal<prevReal) ) {
            prevOBV -= inVolume[i];
         }
         outReal[outIdx++] = prevOBV;
         prevReal = tempReal;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode obvLogic( int startIdx,
                            int endIdx,
                            double inReal[],
                            double inVolume[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int i;
      int outIdx;
      double prevReal;
      double tempReal;
      double prevOBV;
      prevOBV = inVolume[startIdx];
      prevReal = inReal[startIdx];
      outIdx = 0;
      for( i = startIdx; (i<=endIdx); i += 1 ) {
         tempReal = inReal[i];
         if( (tempReal>prevReal) ) {
            prevOBV += inVolume[i];
         } else if( (tempReal<prevReal) ) {
            prevOBV -= inVolume[i];
         }
         outReal[outIdx++] = prevOBV;
         prevReal = tempReal;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode obv( int startIdx,
                       int endIdx,
                       float inReal[],
                       float inVolume[],
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      int i;
      int outIdx;
      double prevReal;
      double tempReal;
      double prevOBV;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      prevOBV = inVolume[startIdx];
      prevReal = inReal[startIdx];
      outIdx = 0;
      for( i = startIdx; (i<=endIdx); i += 1 ) {
         tempReal = inReal[i];
         if( (tempReal>prevReal) ) {
            prevOBV += inVolume[i];
         } else if( (tempReal<prevReal) ) {
            prevOBV -= inVolume[i];
         }
         outReal[outIdx++] = prevOBV;
         prevReal = tempReal;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode obvLogic( int startIdx,
                            int endIdx,
                            float inReal[],
                            float inVolume[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
   {
      int i;
      int outIdx;
      double prevReal;
      double tempReal;
      double prevOBV;
      prevOBV = inVolume[startIdx];
      prevReal = inReal[startIdx];
      outIdx = 0;
      for( i = startIdx; (i<=endIdx); i += 1 ) {
         tempReal = inReal[i];
         if( (tempReal>prevReal) ) {
            prevOBV += inVolume[i];
         } else if( (tempReal<prevReal) ) {
            prevOBV -= inVolume[i];
         }
         outReal[outIdx++] = prevOBV;
         prevReal = tempReal;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
