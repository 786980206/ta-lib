/* Generated */
   public int cdl3blackcrowsLookback( )
   {
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (ShadowVeryShort_avgPeriod+3) ;

   }
   public RetCode cdl3blackcrows( int startIdx,
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
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl3blackcrowsLookback();
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_6;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3blackcrowsLogic( int startIdx,
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
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3blackcrowsLookback();
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_6;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3blackcrows( int startIdx,
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
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl3blackcrowsLookback();
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_6;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3blackcrowsLogic( int startIdx,
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
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3blackcrowsLookback();
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowVeryShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_4 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowVeryShort_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( (((((((((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-2)]>=inOpen[(i-2)])) ? (inOpen[(i-2)]) : (inClose[(i-2)]))-inLow[(i-2)])<_candleaverage_3))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[(i-1)]>=inOpen[(i-1)])) ? (inOpen[(i-1)]) : (inClose[(i-1)]))-inLow[(i-1)])<_candleaverage_4))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(inOpen[(i-1)]<inOpen[(i-2)]))&&(inOpen[(i-1)]>inClose[(i-2)]))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inHigh[(i-3)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[i])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_6;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_7 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_7 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_7 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_7 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_6-_candlerange_7));
         }
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
