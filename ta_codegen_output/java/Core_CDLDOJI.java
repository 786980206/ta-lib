/* Generated */
   public int cdldojiLookback( )
   {
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      return BodyDoji_avgPeriod ;

   }
   public RetCode cdldoji( int startIdx,
                           int endIdx,
                           double inOpen[],
                           double inHigh[],
                           double inLow[],
                           double inClose[],
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           int outInteger[] )
   {
      double BodyDojiPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdldojiLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyDojiPeriodTotal = 0;
      BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
      i = BodyDojiTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
         BodyDojiPeriodTotal += _candlerange_0;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         if( (Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_1) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyDojiTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdldojiLogic( int startIdx,
                                int endIdx,
                                double inOpen[],
                                double inHigh[],
                                double inLow[],
                                double inClose[],
                                MInteger outBegIdx,
                                MInteger outNBElement,
                                int outInteger[] )
   {
      double BodyDojiPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      lookbackTotal = cdldojiLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyDojiPeriodTotal = 0;
      BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
      i = BodyDojiTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
         BodyDojiPeriodTotal += _candlerange_0;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         if( (Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_1) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyDojiTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdldoji( int startIdx,
                           int endIdx,
                           float inOpen[],
                           float inHigh[],
                           float inLow[],
                           float inClose[],
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           int outInteger[] )
   {
      double BodyDojiPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdldojiLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyDojiPeriodTotal = 0;
      BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
      i = BodyDojiTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
         BodyDojiPeriodTotal += _candlerange_0;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         if( (Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_1) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyDojiTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdldojiLogic( int startIdx,
                                int endIdx,
                                float inOpen[],
                                float inHigh[],
                                float inLow[],
                                float inClose[],
                                MInteger outBegIdx,
                                MInteger outNBElement,
                                int outInteger[] )
   {
      double BodyDojiPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      lookbackTotal = cdldojiLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyDojiPeriodTotal = 0;
      BodyDojiTrailingIdx = (startIdx-BodyDoji_avgPeriod);
      i = BodyDojiTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
         BodyDojiPeriodTotal += _candlerange_0;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         if( (Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_1) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyDojiTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
