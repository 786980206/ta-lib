/* Generated */
   public int linearregLookback( int optInTimePeriod )
   {
      return (optInTimePeriod-1) ;

   }
   public RetCode linearreg( int startIdx,
                             int endIdx,
                             double inReal[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      int outIdx;
      int today;
      int lookbackTotal;
      double SumX;
      double SumXY;
      double SumY;
      double SumXSqr;
      double Divisor;
      double m;
      double b;
      int i;
      double tempValue1;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = linearregLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      SumX = ((optInTimePeriod*(optInTimePeriod-1))*0.5);
      SumXSqr = (((optInTimePeriod*(optInTimePeriod-1))*((2*optInTimePeriod)-1))/6);
      Divisor = ((SumX*SumX)-(optInTimePeriod*SumXSqr));
      while( (today<=endIdx) ) {
         SumXY = 0;
         SumY = 0;
         for( i = optInTimePeriod; (i--!=0);  ) {
            tempValue1 = inReal[(today-i)];
            SumY += tempValue1;
            SumXY += (((double)i)*tempValue1);
         }
         m = (((optInTimePeriod*SumXY)-(SumX*SumY))/Divisor);
         b = ((SumY-(m*SumX))/((double)optInTimePeriod));
         outReal[outIdx++] = (b+(m*((double)(optInTimePeriod-1))));
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode linearregLogic( int startIdx,
                                  int endIdx,
                                  double inReal[],
                                  int optInTimePeriod,
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  double outReal[] )
   {
      int outIdx;
      int today;
      int lookbackTotal;
      double SumX;
      double SumXY;
      double SumY;
      double SumXSqr;
      double Divisor;
      double m;
      double b;
      int i;
      double tempValue1;
      lookbackTotal = linearregLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      SumX = ((optInTimePeriod*(optInTimePeriod-1))*0.5);
      SumXSqr = (((optInTimePeriod*(optInTimePeriod-1))*((2*optInTimePeriod)-1))/6);
      Divisor = ((SumX*SumX)-(optInTimePeriod*SumXSqr));
      while( (today<=endIdx) ) {
         SumXY = 0;
         SumY = 0;
         for( i = optInTimePeriod; (i--!=0);  ) {
            tempValue1 = inReal[(today-i)];
            SumY += tempValue1;
            SumXY += (((double)i)*tempValue1);
         }
         m = (((optInTimePeriod*SumXY)-(SumX*SumY))/Divisor);
         b = ((SumY-(m*SumX))/((double)optInTimePeriod));
         outReal[outIdx++] = (b+(m*((double)(optInTimePeriod-1))));
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode linearreg( int startIdx,
                             int endIdx,
                             float inReal[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      int outIdx;
      int today;
      int lookbackTotal;
      double SumX;
      double SumXY;
      double SumY;
      double SumXSqr;
      double Divisor;
      double m;
      double b;
      int i;
      double tempValue1;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = linearregLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      SumX = ((optInTimePeriod*(optInTimePeriod-1))*0.5);
      SumXSqr = (((optInTimePeriod*(optInTimePeriod-1))*((2*optInTimePeriod)-1))/6);
      Divisor = ((SumX*SumX)-(optInTimePeriod*SumXSqr));
      while( (today<=endIdx) ) {
         SumXY = 0;
         SumY = 0;
         for( i = optInTimePeriod; (i--!=0);  ) {
            tempValue1 = inReal[(today-i)];
            SumY += tempValue1;
            SumXY += (((double)i)*tempValue1);
         }
         m = (((optInTimePeriod*SumXY)-(SumX*SumY))/Divisor);
         b = ((SumY-(m*SumX))/((double)optInTimePeriod));
         outReal[outIdx++] = (b+(m*((double)(optInTimePeriod-1))));
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
   public RetCode linearregLogic( int startIdx,
                                  int endIdx,
                                  float inReal[],
                                  int optInTimePeriod,
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  double outReal[] )
   {
      int outIdx;
      int today;
      int lookbackTotal;
      double SumX;
      double SumXY;
      double SumY;
      double SumXSqr;
      double Divisor;
      double m;
      double b;
      int i;
      double tempValue1;
      lookbackTotal = linearregLookback(optInTimePeriod);
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      outIdx = 0;
      today = startIdx;
      SumX = ((optInTimePeriod*(optInTimePeriod-1))*0.5);
      SumXSqr = (((optInTimePeriod*(optInTimePeriod-1))*((2*optInTimePeriod)-1))/6);
      Divisor = ((SumX*SumX)-(optInTimePeriod*SumXSqr));
      while( (today<=endIdx) ) {
         SumXY = 0;
         SumY = 0;
         for( i = optInTimePeriod; (i--!=0);  ) {
            tempValue1 = inReal[(today-i)];
            SumY += tempValue1;
            SumXY += (((double)i)*tempValue1);
         }
         m = (((optInTimePeriod*SumXY)-(SumX*SumY))/Divisor);
         b = ((SumY-(m*SumX))/((double)optInTimePeriod));
         outReal[outIdx++] = (b+(m*((double)(optInTimePeriod-1))));
         today += 1;
      }
      outBegIdx.value = startIdx;
      outNBElement.value = outIdx;
      return RetCode.Success ;
   }
