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
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_7-_candlerange_8);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_9;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            double _candlerange_10;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
         }
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_11 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_12 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_11-_candlerange_12);
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
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_7-_candlerange_8);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_9;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            double _candlerange_10;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
         }
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_11 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_12 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_11-_candlerange_12);
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
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_7-_candlerange_8);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_9;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            double _candlerange_10;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
         }
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_11 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_12 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_11-_candlerange_12);
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
         if( (((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]<=inHigh[(i-2)]))&&(inLow[(i-1)]<inClose[(i-2)]))&&(inLow[(i-1)]>=inLow[(i-2)]))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])>ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inLow[i]>inLow[(i-1)]))&&(inHigh[i]<inHigh[(i-1)])) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double _candlerange_8;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(ShadowLongTrailingIdx-2)]-inLow[(ShadowLongTrailingIdx-2)])-Math.abs((inClose[(ShadowLongTrailingIdx-2)]-inOpen[(ShadowLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_7-_candlerange_8);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_9;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            double _candlerange_10;
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_9-_candlerange_10));
         }
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_11 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_12 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_11-_candlerange_12);
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
