/* Generated */
   public int cdlgapsidesidewhiteLookback( )
   {
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      return (Math.max(Near_avgPeriod, Equal_avgPeriod)+2) ;

   }
   public RetCode cdlgapsidesidewhite( int startIdx,
                                       int endIdx,
                                       double inOpen[],
                                       double inHigh[],
                                       double inLow[],
                                       double inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double NearPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlgapsidesidewhiteLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      EqualPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]>=(inOpen[(i-1)]-ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]<=(inOpen[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Near_rangeType )
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
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         NearTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgapsidesidewhiteLogic( int startIdx,
                                            int endIdx,
                                            double inOpen[],
                                            double inHigh[],
                                            double inLow[],
                                            double inClose[],
                                            MInteger outBegIdx,
                                            MInteger outNBElement,
                                            int outInteger[] )
   {
      double NearPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdlgapsidesidewhiteLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      EqualPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]>=(inOpen[(i-1)]-ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]<=(inOpen[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Near_rangeType )
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
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         NearTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgapsidesidewhite( int startIdx,
                                       int endIdx,
                                       float inOpen[],
                                       float inHigh[],
                                       float inLow[],
                                       float inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double NearPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlgapsidesidewhiteLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      EqualPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]>=(inOpen[(i-1)]-ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]<=(inOpen[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Near_rangeType )
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
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         NearTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgapsidesidewhiteLogic( int startIdx,
                                            int endIdx,
                                            float inOpen[],
                                            float inHigh[],
                                            float inLow[],
                                            float inClose[],
                                            MInteger outBegIdx,
                                            MInteger outNBElement,
                                            int outInteger[] )
   {
      double NearPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdlgapsidesidewhiteLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      EqualPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]>=(inOpen[(i-1)]-ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(inOpen[i]<=(inOpen[(i-1)]+ta_candleaverage(Equal_rangeType, Equal_avgPeriod, Equal_factor, EqualPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( Near_rangeType )
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
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_2-_candlerange_3);
         double _candlerange_4;
         switch( Equal_rangeType )
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
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         NearTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
