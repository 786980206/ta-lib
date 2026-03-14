/* Generated */
   public int cdlinneckLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      return (Math.max(Equal_avgPeriod, BodyLong_avgPeriod)+1) ;

   }
   public RetCode cdlinneck( int startIdx,
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
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlinneckLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
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
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inLow[(i-1)]))&&(inClose[i]<=(inClose[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inClose[i]>=inClose[(i-1)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)])-Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlinneckLogic( int startIdx,
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
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlinneckLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
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
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inLow[(i-1)]))&&(inClose[i]<=(inClose[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inClose[i]>=inClose[(i-1)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)])-Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlinneck( int startIdx,
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
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlinneckLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
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
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inLow[(i-1)]))&&(inClose[i]<=(inClose[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inClose[i]>=inClose[(i-1)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)])-Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlinneckLogic( int startIdx,
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
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int EqualTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlinneckLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
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
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_1 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inOpen[i]<inLow[(i-1)]))&&(inClose[i]<=(inClose[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inClose[i]>=inClose[(i-1)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(BodyLongTrailingIdx-1)]-inLow[(BodyLongTrailingIdx-1)])-Math.abs((inClose[(BodyLongTrailingIdx-1)]-inOpen[(BodyLongTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
