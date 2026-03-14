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
         double _candleaverage_2;
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_8-_candlerange_9);
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
         double _candleaverage_2;
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_8-_candlerange_9);
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
         double _candleaverage_2;
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_8-_candlerange_9);
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
         double _candleaverage_2;
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Near_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         if( (((((((((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))||((((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))&&(((Math.max(inOpen[i], inClose[i])<Math.min(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(Math.abs((inClose[i]-inOpen[i]))>=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_2)))&&(Math.abs((inClose[i]-inOpen[i]))<=(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_5))) ) {
            outInteger[outIdx++] = (((((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0))) ? (100) : ((0-100)));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(NearTrailingIdx-1)]-inLow[(NearTrailingIdx-1)])-Math.abs((inClose[(NearTrailingIdx-1)]-inOpen[(NearTrailingIdx-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_8-_candlerange_9);
         i += 1;
         NearTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
