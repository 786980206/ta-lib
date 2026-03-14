/* Generated */
   public int cdlrickshawmanLookback( )
   {
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      return Math.max(Math.max(BodyDoji_avgPeriod, ShadowLong_avgPeriod), Near_avgPeriod) ;

   }
   public RetCode cdlrickshawman( int startIdx,
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
      double ShadowLongPeriodTotal;
      double NearPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlrickshawmanLookback();
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
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((Math.min(inOpen[i], inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(Math.max(inOpen[i], inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_8;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowLong_rangeType )
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
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_12 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrickshawmanLogic( int startIdx,
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
      double ShadowLongPeriodTotal;
      double NearPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      lookbackTotal = cdlrickshawmanLookback();
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
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((Math.min(inOpen[i], inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(Math.max(inOpen[i], inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_8;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowLong_rangeType )
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
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_12 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrickshawman( int startIdx,
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
      double ShadowLongPeriodTotal;
      double NearPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlrickshawmanLookback();
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
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((Math.min(inOpen[i], inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(Math.max(inOpen[i], inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_8;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowLong_rangeType )
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
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_12 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrickshawmanLogic( int startIdx,
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
      double ShadowLongPeriodTotal;
      double NearPeriodTotal;
      int i;
      int outIdx;
      int BodyDojiTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      lookbackTotal = cdlrickshawmanLookback();
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
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyDojiPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Near_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_4))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_5))&&((Math.min(inOpen[i], inClose[i])<=((inLow[i]+((inHigh[i]-inLow[i])/2))+_candleaverage_6))&&(Math.max(inOpen[i], inClose[i])>=((inLow[i]+((inHigh[i]-inLow[i])/2))-_candleaverage_7)))) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_8;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[BodyDojiTrailingIdx]-inLow[BodyDojiTrailingIdx])-Math.abs((inClose[BodyDojiTrailingIdx]-inOpen[BodyDojiTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyDojiPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowLong_rangeType )
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
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_12 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyDojiTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
