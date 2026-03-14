/* Generated */
   public int cdlidentical3crowsLookback( )
   {
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(ShadowVeryShort_avgPeriod, Equal_avgPeriod)+2) ;

   }
   public RetCode cdlidentical3crows( int startIdx,
                                      int endIdx,
                                      double inOpen[],
                                      double inHigh[],
                                      double inLow[],
                                      double inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[3];
      double[] EqualPeriodTotal = new double[3];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
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
      lookbackTotal = cdlidentical3crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[2] = 0;
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      EqualPeriodTotal[2] = 0;
      EqualPeriodTotal[1] = 0;
      EqualPeriodTotal[0] = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
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
         EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_12 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_12 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_12 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_12 = 0.0;
               break;
            }
            double _candlerange_13;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            double _candlerange_15;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlidentical3crowsLogic( int startIdx,
                                           int endIdx,
                                           double inOpen[],
                                           double inHigh[],
                                           double inLow[],
                                           double inClose[],
                                           MInteger outBegIdx,
                                           MInteger outNBElement,
                                           int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[3];
      double[] EqualPeriodTotal = new double[3];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlidentical3crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[2] = 0;
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      EqualPeriodTotal[2] = 0;
      EqualPeriodTotal[1] = 0;
      EqualPeriodTotal[0] = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
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
         EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_12 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_12 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_12 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_12 = 0.0;
               break;
            }
            double _candlerange_13;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            double _candlerange_15;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlidentical3crows( int startIdx,
                                      int endIdx,
                                      float inOpen[],
                                      float inHigh[],
                                      float inLow[],
                                      float inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[3];
      double[] EqualPeriodTotal = new double[3];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
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
      lookbackTotal = cdlidentical3crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[2] = 0;
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      EqualPeriodTotal[2] = 0;
      EqualPeriodTotal[1] = 0;
      EqualPeriodTotal[0] = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
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
         EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_12 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_12 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_12 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_12 = 0.0;
               break;
            }
            double _candlerange_13;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            double _candlerange_15;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlidentical3crowsLogic( int startIdx,
                                           int endIdx,
                                           float inOpen[],
                                           float inHigh[],
                                           float inLow[],
                                           float inClose[],
                                           MInteger outBegIdx,
                                           MInteger outNBElement,
                                           int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[3];
      double[] EqualPeriodTotal = new double[3];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int EqualTrailingIdx;
      int lookbackTotal;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlidentical3crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[2] = 0;
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      EqualPeriodTotal[2] = 0;
      EqualPeriodTotal[1] = 0;
      EqualPeriodTotal[0] = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[2] = (ShadowVeryShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_1);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         EqualPeriodTotal[2] = (EqualPeriodTotal[2]+_candlerange_3);
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
         EqualPeriodTotal[1] = (EqualPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Equal_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[2]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_9 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((Equal_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_10 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((Equal_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal[1]/Equal_avgPeriod)) : (ta_candlerange(Equal_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_11 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Equal_factor*avg_11)/divisor_11);
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_5))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_7))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_8)))&&(inOpen[(i-1)]>=(inClose[(i-2)]-_candleaverage_9)))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_10)))&&(inOpen[i]>=(inClose[(i-1)]-_candleaverage_11))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_12 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_12 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_12 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_12 = 0.0;
               break;
            }
            double _candlerange_13;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            double _candlerange_15;
            switch( Equal_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(EqualTrailingIdx-totIdx)]-inLow[(EqualTrailingIdx-totIdx)])-Math.abs((inClose[(EqualTrailingIdx-totIdx)]-inOpen[(EqualTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            EqualPeriodTotal[totIdx] = (EqualPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         EqualTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
