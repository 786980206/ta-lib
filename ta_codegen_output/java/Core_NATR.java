/* Generated */
   public int natrLookback( int optInTimePeriod )
   {
      return (optInTimePeriod+this.unstablePeriod[FuncUnstId.Natr.ordinal()]) ;

   }
   public RetCode natr( int startIdx,
                        int endIdx,
                        double inHigh[],
                        double inLow[],
                        double inClose[],
                        int optInTimePeriod,
                        MInteger outBegIdx,
                        MInteger outNBElement,
                        double outReal[] )
   {
      RetCode retCode;
      int outIdx;
      int today;
      int lookbackTotal;
      int nbATR;
      MInteger outBegIdx1 = new MInteger();
      MInteger outNbElement1 = new MInteger();
      double prevATR;
      double tempValue;
      double[] tempBuffer;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outBegIdx.value = 0;
      outNBElement.value = 0;
      lookbackTotal = natrLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         return RetCode.Success ;
      }
      if( (optInTimePeriod<=1) ) {
         return trangeLogic(startIdx, endIdx, inHigh, inLow, inClose, outBegIdx, outNBElement, outReal) ;
      }
      tempBuffer = new double[(int)((((lookbackTotal+(endIdx-startIdx))+1)*1))];
      retCode = trangeLogic(((startIdx-lookbackTotal)+1), endIdx, inHigh, inLow, inClose, outBegIdx1, outNbElement1, tempBuffer);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      retCode = smaLogic((optInTimePeriod-1), (optInTimePeriod-1), tempBuffer, optInTimePeriod, outBegIdx1, outNbElement1, prevATR);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      today = optInTimePeriod;
      outIdx = this.unstablePeriod[FuncUnstId.Natr.ordinal()];
      while( (outIdx!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         outIdx -= 1;
      }
      outIdx = 1;
      tempValue = inClose[today];
      if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
         outReal[0] = ((prevATR.value/tempValue)*100.0);
      } else {
         outReal[0] = 0.0;
      }
      nbATR = ((endIdx-startIdx)+1);
      while( (--nbATR!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         tempValue = inClose[today];
         if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
            outReal[outIdx] = ((prevATR.value/tempValue)*100.0);
         } else {
            outReal[0] = 0.0;
         }
         outIdx += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return retCode ;
   }
   public RetCode natrLogic( int startIdx,
                             int endIdx,
                             double inHigh[],
                             double inLow[],
                             double inClose[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      RetCode retCode;
      int outIdx;
      int today;
      int lookbackTotal;
      int nbATR;
      MInteger outBegIdx1 = new MInteger();
      MInteger outNbElement1 = new MInteger();
      double prevATR;
      double tempValue;
      double[] tempBuffer;
      outBegIdx.value = 0;
      outNBElement.value = 0;
      lookbackTotal = natrLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         return RetCode.Success ;
      }
      if( (optInTimePeriod<=1) ) {
         return trangeLogic(startIdx, endIdx, inHigh, inLow, inClose, outBegIdx, outNBElement, outReal) ;
      }
      tempBuffer = new double[(int)((((lookbackTotal+(endIdx-startIdx))+1)*1))];
      retCode = trangeLogic(((startIdx-lookbackTotal)+1), endIdx, inHigh, inLow, inClose, outBegIdx1, outNbElement1, tempBuffer);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      retCode = smaLogic((optInTimePeriod-1), (optInTimePeriod-1), tempBuffer, optInTimePeriod, outBegIdx1, outNbElement1, prevATR);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      today = optInTimePeriod;
      outIdx = this.unstablePeriod[FuncUnstId.Natr.ordinal()];
      while( (outIdx!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         outIdx -= 1;
      }
      outIdx = 1;
      tempValue = inClose[today];
      if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
         outReal[0] = ((prevATR.value/tempValue)*100.0);
      } else {
         outReal[0] = 0.0;
      }
      nbATR = ((endIdx-startIdx)+1);
      while( (--nbATR!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         tempValue = inClose[today];
         if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
            outReal[outIdx] = ((prevATR.value/tempValue)*100.0);
         } else {
            outReal[0] = 0.0;
         }
         outIdx += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return retCode ;
   }
   public RetCode natr( int startIdx,
                        int endIdx,
                        float inHigh[],
                        float inLow[],
                        float inClose[],
                        int optInTimePeriod,
                        MInteger outBegIdx,
                        MInteger outNBElement,
                        double outReal[] )
   {
      RetCode retCode;
      int outIdx;
      int today;
      int lookbackTotal;
      int nbATR;
      MInteger outBegIdx1 = new MInteger();
      MInteger outNbElement1 = new MInteger();
      double prevATR;
      double tempValue;
      double[] tempBuffer;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      outBegIdx.value = 0;
      outNBElement.value = 0;
      lookbackTotal = natrLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         return RetCode.Success ;
      }
      if( (optInTimePeriod<=1) ) {
         return trangeLogic(startIdx, endIdx, inHigh, inLow, inClose, outBegIdx, outNBElement, outReal) ;
      }
      tempBuffer = new double[(int)((((lookbackTotal+(endIdx-startIdx))+1)*1))];
      retCode = trangeLogic(((startIdx-lookbackTotal)+1), endIdx, inHigh, inLow, inClose, outBegIdx1, outNbElement1, tempBuffer);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      retCode = smaLogic((optInTimePeriod-1), (optInTimePeriod-1), tempBuffer, optInTimePeriod, outBegIdx1, outNbElement1, prevATR);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      today = optInTimePeriod;
      outIdx = this.unstablePeriod[FuncUnstId.Natr.ordinal()];
      while( (outIdx!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         outIdx -= 1;
      }
      outIdx = 1;
      tempValue = inClose[today];
      if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
         outReal[0] = ((prevATR.value/tempValue)*100.0);
      } else {
         outReal[0] = 0.0;
      }
      nbATR = ((endIdx-startIdx)+1);
      while( (--nbATR!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         tempValue = inClose[today];
         if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
            outReal[outIdx] = ((prevATR.value/tempValue)*100.0);
         } else {
            outReal[0] = 0.0;
         }
         outIdx += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return retCode ;
   }
   public RetCode natrLogic( int startIdx,
                             int endIdx,
                             float inHigh[],
                             float inLow[],
                             float inClose[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      RetCode retCode;
      int outIdx;
      int today;
      int lookbackTotal;
      int nbATR;
      MInteger outBegIdx1 = new MInteger();
      MInteger outNbElement1 = new MInteger();
      double prevATR;
      double tempValue;
      double[] tempBuffer;
      outBegIdx.value = 0;
      outNBElement.value = 0;
      lookbackTotal = natrLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         return RetCode.Success ;
      }
      if( (optInTimePeriod<=1) ) {
         return trangeLogic(startIdx, endIdx, inHigh, inLow, inClose, outBegIdx, outNBElement, outReal) ;
      }
      tempBuffer = new double[(int)((((lookbackTotal+(endIdx-startIdx))+1)*1))];
      retCode = trangeLogic(((startIdx-lookbackTotal)+1), endIdx, inHigh, inLow, inClose, outBegIdx1, outNbElement1, tempBuffer);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      retCode = smaLogic((optInTimePeriod-1), (optInTimePeriod-1), tempBuffer, optInTimePeriod, outBegIdx1, outNbElement1, prevATR);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      today = optInTimePeriod;
      outIdx = this.unstablePeriod[FuncUnstId.Natr.ordinal()];
      while( (outIdx!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         outIdx -= 1;
      }
      outIdx = 1;
      tempValue = inClose[today];
      if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
         outReal[0] = ((prevATR.value/tempValue)*100.0);
      } else {
         outReal[0] = 0.0;
      }
      nbATR = ((endIdx-startIdx)+1);
      while( (--nbATR!=0) ) {
         prevATR.value *= (optInTimePeriod-1);
         prevATR.value += tempBuffer[today++];
         prevATR.value /= optInTimePeriod;
         tempValue = inClose[today];
         if( !((((0-0.00000001)<tempValue)&&(tempValue<0.00000001))) ) {
            outReal[outIdx] = ((prevATR.value/tempValue)*100.0);
         } else {
            outReal[0] = 0.0;
         }
         outIdx += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return retCode ;
   }
