/* Generated */
   public int cdlstalledpatternLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(BodyLong_avgPeriod, BodyShort_avgPeriod), Math.max(ShadowVeryShort_avgPeriod, Near_avgPeriod))+2) ;

   }
   public RetCode cdlstalledpattern( int startIdx,
                                     int endIdx,
                                     double inOpen[],
                                     double inHigh[],
                                     double inLow[],
                                     double inClose[],
                                     MInteger outBegIdx,
                                     MInteger outNBElement,
                                     int outInteger[] )
   {
      double[] BodyLongPeriodTotal = new double[3];
      double[] NearPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlstalledpatternLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal[2] = 0;
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
         BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
         double _candlerange_5;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inOpen[i]>=((inClose[(i-1)]-Math.abs((inClose[i]-inOpen[i])))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_6;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_6 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_6 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_6 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_6 = 0.0;
               break;
            }
            double _candlerange_7;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
            double _candlerange_8;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            double _candlerange_9;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_8-_candlerange_9));
         }
         double _candlerange_10;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlstalledpatternLogic( int startIdx,
                                          int endIdx,
                                          double inOpen[],
                                          double inHigh[],
                                          double inLow[],
                                          double inClose[],
                                          MInteger outBegIdx,
                                          MInteger outNBElement,
                                          int outInteger[] )
   {
      double[] BodyLongPeriodTotal = new double[3];
      double[] NearPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlstalledpatternLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal[2] = 0;
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
         BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
         double _candlerange_5;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inOpen[i]>=((inClose[(i-1)]-Math.abs((inClose[i]-inOpen[i])))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_6;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_6 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_6 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_6 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_6 = 0.0;
               break;
            }
            double _candlerange_7;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
            double _candlerange_8;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            double _candlerange_9;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_8-_candlerange_9));
         }
         double _candlerange_10;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlstalledpattern( int startIdx,
                                     int endIdx,
                                     float inOpen[],
                                     float inHigh[],
                                     float inLow[],
                                     float inClose[],
                                     MInteger outBegIdx,
                                     MInteger outNBElement,
                                     int outInteger[] )
   {
      double[] BodyLongPeriodTotal = new double[3];
      double[] NearPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlstalledpatternLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal[2] = 0;
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
         BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
         double _candlerange_5;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inOpen[i]>=((inClose[(i-1)]-Math.abs((inClose[i]-inOpen[i])))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_6;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_6 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_6 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_6 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_6 = 0.0;
               break;
            }
            double _candlerange_7;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
            double _candlerange_8;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            double _candlerange_9;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_8-_candlerange_9));
         }
         double _candlerange_10;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlstalledpatternLogic( int startIdx,
                                          int endIdx,
                                          float inOpen[],
                                          float inHigh[],
                                          float inLow[],
                                          float inClose[],
                                          MInteger outBegIdx,
                                          MInteger outNBElement,
                                          int outInteger[] )
   {
      double[] BodyLongPeriodTotal = new double[3];
      double[] NearPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int BodyShortTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlstalledpatternLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal[2] = 0;
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
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
         BodyLongPeriodTotal[2] = (BodyLongPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_1);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += _candlerange_3;
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_4);
         double _candlerange_5;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_5);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<ta_candleaverage(ShadowVeryShort_rangeType, ShadowVeryShort_avgPeriod, ShadowVeryShort_factor, ShadowVeryShortPeriodTotal, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(Math.abs((inClose[i]-inOpen[i]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyShortPeriodTotal, inOpen[i], inHigh[i], inLow[i], inClose[i])))&&(inOpen[i]>=((inClose[(i-1)]-Math.abs((inClose[i]-inOpen[i])))-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_6;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_6 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_6 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_6 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_6 = 0.0;
               break;
            }
            double _candlerange_7;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
            double _candlerange_8;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            double _candlerange_9;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_9 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_9 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_9 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_9 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_8-_candlerange_9));
         }
         double _candlerange_10;
         switch( BodyShort_rangeType )
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
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_10-_candlerange_11);
         double _candlerange_12;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(ShadowVeryShortTrailingIdx-1)]-inLow[(ShadowVeryShortTrailingIdx-1)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-1)]-inOpen[(ShadowVeryShortTrailingIdx-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_12-_candlerange_13);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
