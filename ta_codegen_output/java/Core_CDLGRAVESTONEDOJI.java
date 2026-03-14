/* Generated */
   public int cdlgravestonedojiLookback( )
   {
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return Math.max(BodyDoji_avgPeriod, ShadowVeryShort_avgPeriod) ;

   }
   public RetCode cdlgravestonedoji( int startIdx,
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
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlgravestonedojiLookback();
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
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_2)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_3))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgravestonedojiLogic( int startIdx,
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
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlgravestonedojiLookback();
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
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_2)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_3))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgravestonedoji( int startIdx,
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
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlgravestonedojiLookback();
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
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_2)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_3))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlgravestonedojiLogic( int startIdx,
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
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlgravestonedojiLookback();
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
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_2)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_3))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
