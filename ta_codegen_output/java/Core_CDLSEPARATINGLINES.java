/* Generated */
   public int cdlseparatinglinesLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(ShadowVeryShort_avgPeriod, BodyLong_avgPeriod), Equal_avgPeriod)+1) ;

   }
   public RetCode cdlseparatinglines( int startIdx,
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
      double BodyLongPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlseparatinglinesLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
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
         EqualPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Equal_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_6))||(((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_7)))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
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
         switch( BodyLong_rangeType )
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
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlseparatinglinesLogic( int startIdx,
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
      double BodyLongPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlseparatinglinesLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
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
         EqualPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Equal_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_6))||(((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_7)))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
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
         switch( BodyLong_rangeType )
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
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlseparatinglines( int startIdx,
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
      double BodyLongPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlseparatinglinesLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
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
         EqualPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Equal_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_6))||(((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_7)))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
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
         switch( BodyLong_rangeType )
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
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlseparatinglinesLogic( int startIdx,
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
      double BodyLongPeriodTotal;
      double EqualPeriodTotal;
      int i;
      int outIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlseparatinglinesLookback();
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
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
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
         EqualPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((Equal_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((Equal_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(inOpen[i]<=(inOpen[(i-1)]+_candleaverage_3)))&&(inOpen[i]>=(inOpen[(i-1)]-_candleaverage_4)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_5))&&((((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_6))||(((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_7)))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
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
         switch( BodyLong_rangeType )
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
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double _candlerange_13;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
