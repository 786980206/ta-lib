/* Generated */
   public int cdlhighwaveLookback( )
   {
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      return Math.max(BodyShort_avgPeriod, ShadowVeryLong_avgPeriod) ;

   }
   public RetCode cdlhighwave( int startIdx,
                               int endIdx,
                               double inOpen[],
                               double inHigh[],
                               double inLow[],
                               double inClose[],
                               MInteger outBegIdx,
                               MInteger outNBElement,
                               int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhighwaveLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_1 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         if( (((Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_2 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhighwaveLogic( int startIdx,
                                    int endIdx,
                                    double inOpen[],
                                    double inHigh[],
                                    double inLow[],
                                    double inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      lookbackTotal = cdlhighwaveLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_1 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         if( (((Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_2 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhighwave( int startIdx,
                               int endIdx,
                               float inOpen[],
                               float inHigh[],
                               float inLow[],
                               float inClose[],
                               MInteger outBegIdx,
                               MInteger outNBElement,
                               int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhighwaveLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_1 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         if( (((Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_2 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhighwaveLogic( int startIdx,
                                    int endIdx,
                                    float inOpen[],
                                    float inHigh[],
                                    float inLow[],
                                    float inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      lookbackTotal = cdlhighwaveLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_1 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         if( (((Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>ta_candleaverage(ShadowVeryLong_rangeType, ShadowVeryLong_avgPeriod, ShadowVeryLong_factor, ShadowPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i]))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_2 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
