/* Generated */
   public int maLookback( int optInTimePeriod, MAType optInMAType )
   {
      int retValue;
      if( (optInTimePeriod<=1) ) {
         return 0 ;
      }
      switch( optInMAType )
      {
      case TA_MAType_SMA:
         retValue = smaLookback(optInTimePeriod);
         break;
      case TA_MAType_EMA:
         retValue = emaLookback(optInTimePeriod);
         break;
      case TA_MAType_WMA:
         retValue = wmaLookback(optInTimePeriod);
         break;
      case TA_MAType_DEMA:
         retValue = demaLookback(optInTimePeriod);
         break;
      case TA_MAType_TEMA:
         retValue = temaLookback(optInTimePeriod);
         break;
      case TA_MAType_TRIMA:
         retValue = trimaLookback(optInTimePeriod);
         break;
      case TA_MAType_KAMA:
         retValue = kamaLookback(optInTimePeriod);
         break;
      case TA_MAType_MAMA:
         retValue = mamaLookback(0.5, 0.05);
         break;
      case TA_MAType_T3:
         retValue = t3Lookback(optInTimePeriod, 0.7);
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
                      MAType optInMAType,
                      MInteger outBegIdx,
                      MInteger outNBElement,
                      double outReal[] )
   {
      double[] dummyBuffer;
      RetCode retCode;
      int nbElement;
      int outIdx;
      int todayIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         for( todayIdx = startIdx, outIdx = 0; (outIdx<nbElement); outIdx += 1, todayIdx += 1 ) {
            outReal[outIdx] = inReal[todayIdx];
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case TA_MAType_SMA:
         retCode = smaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_EMA:
         retCode = emaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_WMA:
         retCode = wmaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_DEMA:
         retCode = demaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TEMA:
         retCode = temaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TRIMA:
         retCode = trimaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_KAMA:
         retCode = kamaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_MAMA:
         dummyBuffer = new double[(int)((((endIdx-startIdx)+1)*1))];
         retCode = mamaLogic(startIdx, endIdx, inReal, 0.5, 0.05, outBegIdx, outNBElement, outReal, dummyBuffer);
         break;
      case TA_MAType_T3:
         retCode = t3Logic(startIdx, endIdx, inReal, optInTimePeriod, 0.7, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
   }
   public RetCode maLogic( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInTimePeriod,
                           MAType optInMAType,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
   {
      double[] dummyBuffer;
      RetCode retCode;
      int nbElement;
      int outIdx;
      int todayIdx;
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         for( todayIdx = startIdx, outIdx = 0; (outIdx<nbElement); outIdx += 1, todayIdx += 1 ) {
            outReal[outIdx] = inReal[todayIdx];
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case TA_MAType_SMA:
         retCode = smaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_EMA:
         retCode = emaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_WMA:
         retCode = wmaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_DEMA:
         retCode = demaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TEMA:
         retCode = temaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TRIMA:
         retCode = trimaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_KAMA:
         retCode = kamaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_MAMA:
         dummyBuffer = new double[(int)((((endIdx-startIdx)+1)*1))];
         retCode = mamaLogic(startIdx, endIdx, inReal, 0.5, 0.05, outBegIdx, outNBElement, outReal, dummyBuffer);
         break;
      case TA_MAType_T3:
         retCode = t3Logic(startIdx, endIdx, inReal, optInTimePeriod, 0.7, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
   }
   public RetCode ma( int startIdx,
                      int endIdx,
                      float inReal[],
                      int optInTimePeriod,
                      MAType optInMAType,
                      MInteger outBegIdx,
                      MInteger outNBElement,
                      double outReal[] )
   {
      double[] dummyBuffer;
      RetCode retCode;
      int nbElement;
      int outIdx;
      int todayIdx;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         for( todayIdx = startIdx, outIdx = 0; (outIdx<nbElement); outIdx += 1, todayIdx += 1 ) {
            outReal[outIdx] = inReal[todayIdx];
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case TA_MAType_SMA:
         retCode = smaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_EMA:
         retCode = emaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_WMA:
         retCode = wmaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_DEMA:
         retCode = demaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TEMA:
         retCode = temaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TRIMA:
         retCode = trimaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_KAMA:
         retCode = kamaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_MAMA:
         dummyBuffer = new double[(int)((((endIdx-startIdx)+1)*1))];
         retCode = mamaLogic(startIdx, endIdx, inReal, 0.5, 0.05, outBegIdx, outNBElement, outReal, dummyBuffer);
         break;
      case TA_MAType_T3:
         retCode = t3Logic(startIdx, endIdx, inReal, optInTimePeriod, 0.7, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
   }
   public RetCode maLogic( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInTimePeriod,
                           MAType optInMAType,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
   {
      double[] dummyBuffer;
      RetCode retCode;
      int nbElement;
      int outIdx;
      int todayIdx;
      if( (optInTimePeriod==1) ) {
         nbElement = ((endIdx-startIdx)+1);
         outNBElement.value = nbElement;
         for( todayIdx = startIdx, outIdx = 0; (outIdx<nbElement); outIdx += 1, todayIdx += 1 ) {
            outReal[outIdx] = inReal[todayIdx];
         }
         outBegIdx.value = startIdx;
         return RetCode.Success ;
      }
      switch( optInMAType )
      {
      case TA_MAType_SMA:
         retCode = smaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_EMA:
         retCode = emaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_WMA:
         retCode = wmaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_DEMA:
         retCode = demaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TEMA:
         retCode = temaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_TRIMA:
         retCode = trimaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_KAMA:
         retCode = kamaLogic(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
         break;
      case TA_MAType_MAMA:
         dummyBuffer = new double[(int)((((endIdx-startIdx)+1)*1))];
         retCode = mamaLogic(startIdx, endIdx, inReal, 0.5, 0.05, outBegIdx, outNBElement, outReal, dummyBuffer);
         break;
      case TA_MAType_T3:
         retCode = t3Logic(startIdx, endIdx, inReal, optInTimePeriod, 0.7, outBegIdx, outNBElement, outReal);
         break;
      default:
         retCode = RetCode.BadParam;
         break;
      }
      return retCode ;
   }
