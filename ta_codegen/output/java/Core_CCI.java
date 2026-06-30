/* Generated */
   public int cciLookback( int optInTimePeriod )
   {
      return (optInTimePeriod-1) ;

   }
   public RetCode cci( int startIdx,
                       int endIdx,
                       double inHigh[],
                       double inLow[],
                       double inClose[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double tempReal = 0;
      double tempReal2 = 0;
      double theAverage = 0;
      double lastValue = 0;
      int i = 0;
      int j = 0;
      int outIdx = 0;
      int lookbackTotal = 0;
      double[] circBuffer;
      int circBuffer_Idx = 0;
      int maxIdx_circBuffer = (30)-1;
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
      if( optInTimePeriod < 1 ) return RetCode.AllocErr;
      circBuffer = new double[optInTimePeriod];
      maxIdx_circBuffer = (optInTimePeriod)-1;
      circBuffer_Idx = 0;
      i = (startIdx-lookbackTotal);
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            circBuffer[circBuffer_Idx] = (((inHigh[i]+inLow[i])+inClose[i])/3);
            i += 1;
            circBuffer_Idx++;
            if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         }
      }
      outIdx = 0;
      do {
         lastValue = (((inHigh[i]+inLow[i])+inClose[i])/3);
         circBuffer[circBuffer_Idx] = lastValue;
         theAverage = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            theAverage += circBuffer[j];
         }
         theAverage /= optInTimePeriod;
         tempReal2 = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            tempReal2 += Math.abs((circBuffer[j]-theAverage));
         }
         tempReal = (lastValue-theAverage);
         if( ((tempReal!=0.0)&&(tempReal2!=0.0)) ) {
            outReal[outIdx++] = (tempReal/(0.015*(tempReal2/optInTimePeriod)));
         } else {
            outReal[outIdx++] = 0.0;
         }
         circBuffer_Idx++;
         if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cciUnguarded( int startIdx,
                                int endIdx,
                                double inHigh[],
                                double inLow[],
                                double inClose[],
                                int optInTimePeriod,
                                MInteger outBegIdx,
                                MInteger outNBElement,
                                double outReal[] )
   {
      double tempReal = 0;
      double tempReal2 = 0;
      double theAverage = 0;
      double lastValue = 0;
      int i = 0;
      int j = 0;
      int outIdx = 0;
      int lookbackTotal = 0;
      double[] circBuffer;
      int circBuffer_Idx = 0;
      int maxIdx_circBuffer = (30)-1;
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( optInTimePeriod < 1 ) return RetCode.AllocErr;
      circBuffer = new double[optInTimePeriod];
      maxIdx_circBuffer = (optInTimePeriod)-1;
      circBuffer_Idx = 0;
      i = (startIdx-lookbackTotal);
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            circBuffer[circBuffer_Idx] = (((inHigh[i]+inLow[i])+inClose[i])/3);
            i += 1;
            circBuffer_Idx++;
            if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         }
      }
      outIdx = 0;
      do {
         lastValue = (((inHigh[i]+inLow[i])+inClose[i])/3);
         circBuffer[circBuffer_Idx] = lastValue;
         theAverage = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            theAverage += circBuffer[j];
         }
         theAverage /= optInTimePeriod;
         tempReal2 = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            tempReal2 += Math.abs((circBuffer[j]-theAverage));
         }
         tempReal = (lastValue-theAverage);
         if( ((tempReal!=0.0)&&(tempReal2!=0.0)) ) {
            outReal[outIdx++] = (tempReal/(0.015*(tempReal2/optInTimePeriod)));
         } else {
            outReal[outIdx++] = 0.0;
         }
         circBuffer_Idx++;
         if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cci( int startIdx,
                       int endIdx,
                       float inHigh[],
                       float inLow[],
                       float inClose[],
                       int optInTimePeriod,
                       MInteger outBegIdx,
                       MInteger outNBElement,
                       double outReal[] )
   {
      double tempReal = 0;
      double tempReal2 = 0;
      double theAverage = 0;
      double lastValue = 0;
      int i = 0;
      int j = 0;
      int outIdx = 0;
      int lookbackTotal = 0;
      double[] circBuffer;
      int circBuffer_Idx = 0;
      int maxIdx_circBuffer = (30)-1;
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
      if( optInTimePeriod < 1 ) return RetCode.AllocErr;
      circBuffer = new double[optInTimePeriod];
      maxIdx_circBuffer = (optInTimePeriod)-1;
      circBuffer_Idx = 0;
      i = (startIdx-lookbackTotal);
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            circBuffer[circBuffer_Idx] = (((inHigh[i]+inLow[i])+inClose[i])/3);
            i += 1;
            circBuffer_Idx++;
            if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         }
      }
      outIdx = 0;
      do {
         lastValue = (((inHigh[i]+inLow[i])+inClose[i])/3);
         circBuffer[circBuffer_Idx] = lastValue;
         theAverage = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            theAverage += circBuffer[j];
         }
         theAverage /= optInTimePeriod;
         tempReal2 = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            tempReal2 += Math.abs((circBuffer[j]-theAverage));
         }
         tempReal = (lastValue-theAverage);
         if( ((tempReal!=0.0)&&(tempReal2!=0.0)) ) {
            outReal[outIdx++] = (tempReal/(0.015*(tempReal2/optInTimePeriod)));
         } else {
            outReal[outIdx++] = 0.0;
         }
         circBuffer_Idx++;
         if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cciUnguarded( int startIdx,
                                int endIdx,
                                float inHigh[],
                                float inLow[],
                                float inClose[],
                                int optInTimePeriod,
                                MInteger outBegIdx,
                                MInteger outNBElement,
                                double outReal[] )
   {
      double tempReal = 0;
      double tempReal2 = 0;
      double theAverage = 0;
      double lastValue = 0;
      int i = 0;
      int j = 0;
      int outIdx = 0;
      int lookbackTotal = 0;
      double[] circBuffer;
      int circBuffer_Idx = 0;
      int maxIdx_circBuffer = (30)-1;
      lookbackTotal = (optInTimePeriod-1);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      if( optInTimePeriod < 1 ) return RetCode.AllocErr;
      circBuffer = new double[optInTimePeriod];
      maxIdx_circBuffer = (optInTimePeriod)-1;
      circBuffer_Idx = 0;
      i = (startIdx-lookbackTotal);
      if( (optInTimePeriod>1) ) {
         while( (i<startIdx) ) {
            circBuffer[circBuffer_Idx] = (((inHigh[i]+inLow[i])+inClose[i])/3);
            i += 1;
            circBuffer_Idx++;
            if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         }
      }
      outIdx = 0;
      do {
         lastValue = (((inHigh[i]+inLow[i])+inClose[i])/3);
         circBuffer[circBuffer_Idx] = lastValue;
         theAverage = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            theAverage += circBuffer[j];
         }
         theAverage /= optInTimePeriod;
         tempReal2 = 0;
         for( j = 0; (j<optInTimePeriod); j += 1 ) {
            tempReal2 += Math.abs((circBuffer[j]-theAverage));
         }
         tempReal = (lastValue-theAverage);
         if( ((tempReal!=0.0)&&(tempReal2!=0.0)) ) {
            outReal[outIdx++] = (tempReal/(0.015*(tempReal2/optInTimePeriod)));
         } else {
            outReal[outIdx++] = 0.0;
         }
         circBuffer_Idx++;
         if( circBuffer_Idx > maxIdx_circBuffer ) { circBuffer_Idx = 0; }
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
