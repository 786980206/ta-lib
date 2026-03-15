/* Generated */
   public int cdlhangingmanLookback( )
   {
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(Math.max(BodyShort_avgPeriod, ShadowLong_avgPeriod), ShadowVeryShort_avgPeriod), Near_avgPeriod)+1) ;

   }
   public RetCode cdlhangingman( int startIdx,
                                 int endIdx,
                                 double inOpen[],
                                 double inHigh[],
                                 double inLow[],
                                 double inClose[],
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double BodyPeriodTotal = 0;
      double ShadowLongPeriodTotal = 0;
      double ShadowVeryShortPeriodTotal = 0;
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int BodyTrailingIdx = 0;
      int ShadowLongTrailingIdx = 0;
      int ShadowVeryShortTrailingIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhangingmanLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal += _candlerange_0;
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_3 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyShort_rangeType )
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
         double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_9 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(Math.min(inClose[i], inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_12-_candlerange_13);
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_14 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         double _candlerange_15;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_15 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
         double _candlerange_16;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_16 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_17 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
         double _candlerange_18;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_19 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhangingmanLogic( int startIdx,
                                      int endIdx,
                                      double inOpen[],
                                      double inHigh[],
                                      double inLow[],
                                      double inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double BodyPeriodTotal = 0;
      double ShadowLongPeriodTotal = 0;
      double ShadowVeryShortPeriodTotal = 0;
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int BodyTrailingIdx = 0;
      int ShadowLongTrailingIdx = 0;
      int ShadowVeryShortTrailingIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlhangingmanLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal += _candlerange_0;
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_3 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyShort_rangeType )
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
         double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_9 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(Math.min(inClose[i], inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_12-_candlerange_13);
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_14 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         double _candlerange_15;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_15 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
         double _candlerange_16;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_16 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_17 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
         double _candlerange_18;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_19 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhangingman( int startIdx,
                                 int endIdx,
                                 float inOpen[],
                                 float inHigh[],
                                 float inLow[],
                                 float inClose[],
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double BodyPeriodTotal = 0;
      double ShadowLongPeriodTotal = 0;
      double ShadowVeryShortPeriodTotal = 0;
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int BodyTrailingIdx = 0;
      int ShadowLongTrailingIdx = 0;
      int ShadowVeryShortTrailingIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhangingmanLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal += _candlerange_0;
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_3 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyShort_rangeType )
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
         double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_9 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(Math.min(inClose[i], inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_12-_candlerange_13);
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_14 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         double _candlerange_15;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_15 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
         double _candlerange_16;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_16 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_17 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
         double _candlerange_18;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_19 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhangingmanLogic( int startIdx,
                                      int endIdx,
                                      float inOpen[],
                                      float inHigh[],
                                      float inLow[],
                                      float inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double BodyPeriodTotal = 0;
      double ShadowLongPeriodTotal = 0;
      double ShadowVeryShortPeriodTotal = 0;
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int BodyTrailingIdx = 0;
      int ShadowLongTrailingIdx = 0;
      int ShadowVeryShortTrailingIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlhangingmanLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-1)-Near_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal += _candlerange_0;
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
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_3 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyShort_rangeType )
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
         double avg_4 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_9 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_11));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_4)&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])>_candleaverage_5))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_6))&&(Math.min(inClose[i], inOpen[i])>=(inHigh[(i-1)]-_candleaverage_7))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_13 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_12-_candlerange_13);
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_14 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         double _candlerange_15;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_15 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_14-_candlerange_15);
         double _candlerange_16;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_16 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         double _candlerange_17;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_17 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_16-_candlerange_17);
         double _candlerange_18;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx]));
            break;
         case 1:
            _candlerange_19 = (inHigh[NearTrailingIdx]-inLow[NearTrailingIdx]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[NearTrailingIdx]-inLow[NearTrailingIdx])-Math.abs((inClose[NearTrailingIdx]-inOpen[NearTrailingIdx])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
