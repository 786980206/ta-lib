/* Generated */
   public int cdltakuriLookback( )
   {
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return Math.max(Math.max(BodyDoji_avgPeriod, ShadowVeryShort_avgPeriod), ShadowVeryLong_avgPeriod) ;

   }
   public RetCode cdltakuri( int startIdx,
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
      double ShadowVeryShortPeriodTotal;
      double ShadowVeryLongPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int ShadowVeryLongTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdltakuriLookback();
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
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      ShadowVeryLongPeriodTotal = 0;
      ShadowVeryLongTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryLong_rangeType )
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
         ShadowVeryLongPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowVeryLongPeriodTotal/ShadowVeryLong_avgPeriod)) : (ta_candlerange(ShadowVeryLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryLong_factor*avg_5)/divisor_5);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_8 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_10 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx])-Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryLongPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         ShadowVeryLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltakuriLogic( int startIdx,
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
      double ShadowVeryShortPeriodTotal;
      double ShadowVeryLongPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int ShadowVeryLongTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdltakuriLookback();
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
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      ShadowVeryLongPeriodTotal = 0;
      ShadowVeryLongTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryLong_rangeType )
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
         ShadowVeryLongPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowVeryLongPeriodTotal/ShadowVeryLong_avgPeriod)) : (ta_candlerange(ShadowVeryLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryLong_factor*avg_5)/divisor_5);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_8 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_10 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx])-Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryLongPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         ShadowVeryLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltakuri( int startIdx,
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
      double ShadowVeryShortPeriodTotal;
      double ShadowVeryLongPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int ShadowVeryLongTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdltakuriLookback();
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
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      ShadowVeryLongPeriodTotal = 0;
      ShadowVeryLongTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryLong_rangeType )
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
         ShadowVeryLongPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowVeryLongPeriodTotal/ShadowVeryLong_avgPeriod)) : (ta_candlerange(ShadowVeryLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryLong_factor*avg_5)/divisor_5);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_8 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_10 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx])-Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryLongPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         ShadowVeryLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltakuriLogic( int startIdx,
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
      double ShadowVeryShortPeriodTotal;
      double ShadowVeryLongPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int ShadowVeryLongTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryLong_rangeType = this.candleSettings.shadowVeryLong.rangeType;
      int ShadowVeryLong_avgPeriod = this.candleSettings.shadowVeryLong.avgPeriod;
      double ShadowVeryLong_factor = this.candleSettings.shadowVeryLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdltakuriLookback();
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
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      ShadowVeryLongPeriodTotal = 0;
      ShadowVeryLongTrailingIdx = (startIdx-ShadowVeryLong_avgPeriod);
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryLong_rangeType )
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
         ShadowVeryLongPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryLong_avgPeriod!=0)) ? ((ShadowVeryLongPeriodTotal/ShadowVeryLong_avgPeriod)) : (ta_candlerange(ShadowVeryLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryLong_factor*avg_5)/divisor_5);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_8 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         double _candlerange_9;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_10 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double _candlerange_11;
         switch( ShadowVeryLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryLongTrailingIdx]-inLow[ShadowVeryLongTrailingIdx])-Math.abs((inClose[ShadowVeryLongTrailingIdx]-inOpen[ShadowVeryLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryLongPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         ShadowVeryLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
