/* Generated */
   public int cdlladderbottomLookback( )
   {
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (ShadowVeryShort_avgPeriod+4) ;

   }
   public RetCode cdlladderbottom( int startIdx,
                                   int endIdx,
                                   double inOpen[],
                                   double inHigh[],
                                   double inLow[],
                                   double inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlladderbottomLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((ShadowVeryShort_factor*avg_1)/divisor_1);
         if( (((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[(i-4)]>inOpen[(i-3)]))&&(inOpen[(i-3)]>inOpen[(i-2)]))&&(inClose[(i-4)]>inClose[(i-3)]))&&(inClose[(i-3)]>inClose[(i-2)]))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]>inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlladderbottomLogic( int startIdx,
                                        int endIdx,
                                        double inOpen[],
                                        double inHigh[],
                                        double inLow[],
                                        double inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlladderbottomLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((ShadowVeryShort_factor*avg_1)/divisor_1);
         if( (((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[(i-4)]>inOpen[(i-3)]))&&(inOpen[(i-3)]>inOpen[(i-2)]))&&(inClose[(i-4)]>inClose[(i-3)]))&&(inClose[(i-3)]>inClose[(i-2)]))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]>inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlladderbottom( int startIdx,
                                   int endIdx,
                                   float inOpen[],
                                   float inHigh[],
                                   float inLow[],
                                   float inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlladderbottomLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((ShadowVeryShort_factor*avg_1)/divisor_1);
         if( (((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[(i-4)]>inOpen[(i-3)]))&&(inOpen[(i-3)]>inOpen[(i-2)]))&&(inClose[(i-4)]>inClose[(i-3)]))&&(inClose[(i-3)]>inClose[(i-2)]))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]>inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlladderbottomLogic( int startIdx,
                                        int endIdx,
                                        float inOpen[],
                                        float inHigh[],
                                        float inLow[],
                                        float inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlladderbottomLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((ShadowVeryShort_factor*avg_1)/divisor_1);
         if( (((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[(i-4)]>inOpen[(i-3)]))&&(inOpen[(i-3)]>inOpen[(i-2)]))&&(inClose[(i-4)]>inClose[(i-3)]))&&(inClose[(i-3)]>inClose[(i-2)]))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>_candleaverage_1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]>inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
