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
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int BodyShortTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
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
         double _candleaverage_5;
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
         double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
         double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_13;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double _candlerange_14;
         switch( BodyLong_rangeType )
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
         double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
         double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
         if( ((((((((((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&(Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_9)) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_15;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_15 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_17;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            double _candlerange_18;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_19 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         double _candlerange_20;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_20 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_20 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_20 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_20 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
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
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int BodyShortTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
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
         double _candleaverage_5;
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
         double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
         double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_13;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double _candlerange_14;
         switch( BodyLong_rangeType )
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
         double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
         double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
         if( ((((((((((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&(Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_9)) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_15;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_15 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_17;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            double _candlerange_18;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_19 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         double _candlerange_20;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_20 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_20 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_20 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_20 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
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
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int BodyShortTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
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
         double _candleaverage_5;
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
         double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
         double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_13;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double _candlerange_14;
         switch( BodyLong_rangeType )
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
         double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
         double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
         if( ((((((((((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&(Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_9)) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_15;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_15 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_17;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            double _candlerange_18;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_19 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         double _candlerange_20;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_20 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_20 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_20 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_20 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
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
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int BodyShortTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
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
         double _candleaverage_5;
         double _candlerange_10;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_5 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[4]/BodyLong_avgPeriod)) : (_candlerange_10));
         double divisor_5 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((BodyLong_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_11;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-3)]-inOpen[(i-3)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-3)]-inLow[(i-3)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-3)]-inLow[(i-3)])-Math.abs((inClose[(i-3)]-inOpen[(i-3)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double avg_6 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[3]/BodyShort_avgPeriod)) : (_candlerange_11));
         double divisor_6 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((BodyShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double _candlerange_12;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         double avg_7 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[2]/BodyShort_avgPeriod)) : (_candlerange_12));
         double divisor_7 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyShort_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_13;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_13 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_13 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_13 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_13 = 0.0;
            break;
         }
         double avg_8 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal[1]/BodyShort_avgPeriod)) : (_candlerange_13));
         double divisor_8 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((BodyShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double _candlerange_14;
         switch( BodyLong_rangeType )
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
         double avg_9 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_14));
         double divisor_9 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((BodyLong_factor*avg_9)/divisor_9);
         if( ((((((((((((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&(Math.min(inOpen[(i-3)], inClose[(i-3)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-2)], inClose[(i-2)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-2)], inClose[(i-2)])>inLow[(i-4)]))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])<inHigh[(i-4)]))&&(Math.max(inOpen[(i-1)], inClose[(i-1)])>inLow[(i-4)]))&&((inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-3)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))<(inClose[(i-2)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inOpen[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-1)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&((inClose[i]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))>(inClose[(i-4)]*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))))))&&(Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_5))&&(Math.abs((inClose[(i-3)]-inOpen[(i-3)]))<_candleaverage_6))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<_candleaverage_7))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<_candleaverage_8))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_9)) ) {
            outInteger[outIdx++] = (100*(((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1))));
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_15;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_15 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_15 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_15 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_15 = 0.0;
            break;
         }
         double _candlerange_16;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_16 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_16 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_16 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
            break;
         default:
            _candlerange_16 = 0.0;
            break;
         }
         BodyPeriodTotal[4] = (BodyPeriodTotal[4]+(_candlerange_15-_candlerange_16));
         for( totIdx = 3; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_17;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            double _candlerange_18;
            switch( BodyShort_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(BodyShortTrailingIdx-totIdx)]-inLow[(BodyShortTrailingIdx-totIdx)])-Math.abs((inClose[(BodyShortTrailingIdx-totIdx)]-inOpen[(BodyShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            BodyPeriodTotal[totIdx] = (BodyPeriodTotal[totIdx]+(_candlerange_17-_candlerange_18));
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_19 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         double _candlerange_20;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_20 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_20 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_20 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_20 = 0.0;
            break;
         }
         BodyPeriodTotal[0] = (BodyPeriodTotal[0]+(_candlerange_19-_candlerange_20));
         i += 1;
         BodyShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
