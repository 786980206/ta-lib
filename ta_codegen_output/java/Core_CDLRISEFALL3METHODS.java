/* Generated */
   public int cdlrisefall3methodsLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      return (Math.max(BodyShort_avgPeriod, BodyLong_avgPeriod)+4) ;

   }
   public RetCode cdlrisefall3methods( int startIdx,
                                       int endIdx,
                                       double inOpen[],
                                       double inHigh[],
                                       double inLow[],
                                       double inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double[] BodyPeriodTotal = new double[5];
      int i;
      int outIdx;
      int totIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlrisefall3methodsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal[4] = 0;
      BodyPeriodTotal[3] = 0;
      BodyPeriodTotal[2] = 0;
      BodyPeriodTotal[1] = 0;
      BodyPeriodTotal[0] = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[4], inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)]))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)])))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_5-_candlerange_6));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_7;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            double _candlerange_8;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_7-_candlerange_8));
         }
         double _candlerange_9;
         switch( BodyLong_rangeType )
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
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_9-_candlerange_10));
         i += 1;
         BodyShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrisefall3methodsLogic( int startIdx,
                                            int endIdx,
                                            double inOpen[],
                                            double inHigh[],
                                            double inLow[],
                                            double inClose[],
                                            MInteger outBegIdx,
                                            MInteger outNBElement,
                                            int outInteger[] )
   {
      double[] BodyPeriodTotal = new double[5];
      int i;
      int outIdx;
      int totIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      lookbackTotal = cdlrisefall3methodsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal[4] = 0;
      BodyPeriodTotal[3] = 0;
      BodyPeriodTotal[2] = 0;
      BodyPeriodTotal[1] = 0;
      BodyPeriodTotal[0] = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[4], inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)]))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)])))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_5-_candlerange_6));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_7;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            double _candlerange_8;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_7-_candlerange_8));
         }
         double _candlerange_9;
         switch( BodyLong_rangeType )
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
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_9-_candlerange_10));
         i += 1;
         BodyShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrisefall3methods( int startIdx,
                                       int endIdx,
                                       float inOpen[],
                                       float inHigh[],
                                       float inLow[],
                                       float inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double[] BodyPeriodTotal = new double[5];
      int i;
      int outIdx;
      int totIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlrisefall3methodsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal[4] = 0;
      BodyPeriodTotal[3] = 0;
      BodyPeriodTotal[2] = 0;
      BodyPeriodTotal[1] = 0;
      BodyPeriodTotal[0] = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[4], inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)]))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)])))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_5-_candlerange_6));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_7;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            double _candlerange_8;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_7-_candlerange_8));
         }
         double _candlerange_9;
         switch( BodyLong_rangeType )
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
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_9-_candlerange_10));
         i += 1;
         BodyShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlrisefall3methodsLogic( int startIdx,
                                            int endIdx,
                                            float inOpen[],
                                            float inHigh[],
                                            float inLow[],
                                            float inClose[],
                                            MInteger outBegIdx,
                                            MInteger outNBElement,
                                            int outInteger[] )
   {
      double[] BodyPeriodTotal = new double[5];
      int i;
      int outIdx;
      int totIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      lookbackTotal = cdlrisefall3methodsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal[4] = 0;
      BodyPeriodTotal[3] = 0;
      BodyPeriodTotal[2] = 0;
      BodyPeriodTotal[1] = 0;
      BodyPeriodTotal[0] = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal[3] = (BodyPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[2] = (BodyPeriodTotal[2]+_candlerange_1);
         double _candlerange_2;
         switch( BodyShort_rangeType )
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
         BodyPeriodTotal[1] = (BodyPeriodTotal[1]+_candlerange_2);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+_candlerange_3);
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[4], inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)]))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)])))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<ta_candleaverage(BodyShort_rangeType, BodyShort_avgPeriod, BodyShort_factor, BodyPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))&&(Math.abs((inClose[i]-inOpen[i]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i])))&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1))))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))))) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_5 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_5-_candlerange_6));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_7;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            double _candlerange_8;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_8 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_8 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_8 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_8 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_7-_candlerange_8));
         }
         double _candlerange_9;
         switch( BodyLong_rangeType )
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
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_10 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_9-_candlerange_10));
         i += 1;
         BodyShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
