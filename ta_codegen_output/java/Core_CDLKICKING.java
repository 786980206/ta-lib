/* Generated */
   public int cdlkickingLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(ShadowVeryShort_avgPeriod, BodyLong_avgPeriod)+1) ;

   }
   public RetCode cdlkicking( int startIdx,
                              int endIdx,
                              double inOpen[],
                              double inHigh[],
                              double inLow[],
                              double inClose[],
                              MInteger outBegIdx,
                              MInteger outNBElement,
                              int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[2];
      double[] BodyLongPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlkickingLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            double _candlerange_11;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
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
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlkickingLogic( int startIdx,
                                   int endIdx,
                                   double inOpen[],
                                   double inHigh[],
                                   double inLow[],
                                   double inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[2];
      double[] BodyLongPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlkickingLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            double _candlerange_11;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
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
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlkicking( int startIdx,
                              int endIdx,
                              float inOpen[],
                              float inHigh[],
                              float inLow[],
                              float inClose[],
                              MInteger outBegIdx,
                              MInteger outNBElement,
                              int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[2];
      double[] BodyLongPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlkickingLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            double _candlerange_11;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
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
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlkickingLogic( int startIdx,
                                   int endIdx,
                                   float inOpen[],
                                   float inHigh[],
                                   float inLow[],
                                   float inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double[] ShadowVeryShortPeriodTotal = new double[2];
      double[] BodyLongPeriodTotal = new double[2];
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlkickingLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowVeryShortPeriodTotal[1] = 0;
      ShadowVeryShortPeriodTotal[0] = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal[1] = (ShadowVeryShortPeriodTotal[1]+_candlerange_0);
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
         ShadowVeryShortPeriodTotal[0] = (ShadowVeryShortPeriodTotal[0]+_candlerange_1);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[1] = (BodyLongPeriodTotal[1]+_candlerange_2);
         double _candlerange_3;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_3);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_4;
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double avg_6 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_6 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((ShadowVeryShort_factor*avg_6)/divisor_6);
         double _candleaverage_7;
         double avg_7 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_7 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((BodyLong_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         if( (((((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_4))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_5))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_6))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_7))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_8))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_9))&&((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(((inLow[i]>inHigh[(i-1)])) ? (1) : (0)))||(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(((inHigh[i]<inLow[(i-1)])) ? (1) : (0))))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_10 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_10 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_10 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_10 = 0.0;
               break;
            }
            double _candlerange_11;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
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
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
