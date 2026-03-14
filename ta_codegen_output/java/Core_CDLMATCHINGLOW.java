/* Generated */
   public int cdlmatchinglowLookback( )
   {
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      return (Equal_avgPeriod+1) ;

   }
   public RetCode cdlmatchinglow( int startIdx,
                                  int endIdx,
                                  double inOpen[],
                                  double inHigh[],
                                  double inLow[],
                                  double inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlmatchinglowLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
         if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         double _candlerange_4;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_3-_candlerange_4);
         i += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlmatchinglowLogic( int startIdx,
                                       int endIdx,
                                       double inOpen[],
                                       double inHigh[],
                                       double inLow[],
                                       double inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlmatchinglowLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
         if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         double _candlerange_4;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_3-_candlerange_4);
         i += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlmatchinglow( int startIdx,
                                  int endIdx,
                                  float inOpen[],
                                  float inHigh[],
                                  float inLow[],
                                  float inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlmatchinglowLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
         if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         double _candlerange_4;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_3-_candlerange_4);
         i += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlmatchinglowLogic( int startIdx,
                                       int endIdx,
                                       float inOpen[],
                                       float inHigh[],
                                       float inLow[],
                                       float inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlmatchinglowLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_1 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Equal_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Equal_factor*avg_2)/divisor_2);
         if( (((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_1)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_2))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         double _candlerange_4;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_3-_candlerange_4);
         i += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
