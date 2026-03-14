/* Generated */
   public int cdl3starsinsouthLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(ShadowVeryShort_avgPeriod, ShadowLong_avgPeriod), Math.max(BodyLong_avgPeriod, BodyShort_avgPeriod))+2) ;

   }
   public RetCode cdl3starsinsouth( int startIdx,
                                    int endIdx,
                                    double inOpen[],
                                    double inHigh[],
                                    double inLow[],
                                    double inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double BodyLongPeriodTotal;
      double BodyShortPeriodTotal;
      double ShadowLongPeriodTotal;
      double[] ShadowVeryShortPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
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
      lookbackTotal = cdl3starsinsouthLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_4;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(Math.abs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_11-_candlerange_12);
         double _candlerange_13;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_13-_candlerange_14);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_15;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_15-_candlerange_16));
         }
         double _candlerange_17;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_17 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         double _candlerange_18;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_18 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_17-_candlerange_18);
         i += 1;
         BodyLongTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3starsinsouthLogic( int startIdx,
                                         int endIdx,
                                         double inOpen[],
                                         double inHigh[],
                                         double inLow[],
                                         double inClose[],
                                         MInteger outBegIdx,
                                         MInteger outNBElement,
                                         int outInteger[] )
   {
      double BodyLongPeriodTotal;
      double BodyShortPeriodTotal;
      double ShadowLongPeriodTotal;
      double[] ShadowVeryShortPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3starsinsouthLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_4;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(Math.abs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_11-_candlerange_12);
         double _candlerange_13;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_13-_candlerange_14);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_15;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_15-_candlerange_16));
         }
         double _candlerange_17;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_17 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         double _candlerange_18;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_18 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_17-_candlerange_18);
         i += 1;
         BodyLongTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3starsinsouth( int startIdx,
                                    int endIdx,
                                    float inOpen[],
                                    float inHigh[],
                                    float inLow[],
                                    float inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double BodyLongPeriodTotal;
      double BodyShortPeriodTotal;
      double ShadowLongPeriodTotal;
      double[] ShadowVeryShortPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
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
      lookbackTotal = cdl3starsinsouthLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_4;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(Math.abs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_11-_candlerange_12);
         double _candlerange_13;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_13-_candlerange_14);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_15;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_15-_candlerange_16));
         }
         double _candlerange_17;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_17 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         double _candlerange_18;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_18 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_17-_candlerange_18);
         i += 1;
         BodyLongTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3starsinsouthLogic( int startIdx,
                                         int endIdx,
                                         float inOpen[],
                                         float inHigh[],
                                         float inLow[],
                                         float inClose[],
                                         MInteger outBegIdx,
                                         MInteger outNBElement,
                                         int outInteger[] )
   {
      double BodyLongPeriodTotal;
      double BodyShortPeriodTotal;
      double ShadowLongPeriodTotal;
      double[] ShadowVeryShortPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3starsinsouthLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_1 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_1 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_1 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
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
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_4 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_4;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_5;
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_6 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowLong_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_7 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((ShadowVeryShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_5))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>_candleaverage_6))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>_candleaverage_7))&&(Math.abs((inClose[i]-inOpen[i]))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_11-_candlerange_12);
         double _candlerange_13;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double _candlerange_14;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_14 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_14 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_14 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_14 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_13-_candlerange_14);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_15;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_15-_candlerange_16));
         }
         double _candlerange_17;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_17 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_17 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_17 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_17 = 0.0;
            break;
         }
         double _candlerange_18;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_18 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_17-_candlerange_18);
         i += 1;
         BodyLongTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
