/* Generated */
   public int cdlcounterattackLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      return (Math.max(Equal_avgPeriod, BodyLong_avgPeriod)+1) ;

   }
   public RetCode cdlcounterattack( int startIdx,
                                    int endIdx,
                                    double inOpen[],
                                    double inHigh[],
                                    double inLow[],
                                    double inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double EqualPeriodTotal = 0;
      double[] BodyLongPeriodTotal = new double[2];
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int EqualTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlcounterattackLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
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
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double _candlerange_7;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_7));
         double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyLong_rangeType )
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
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_6 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Equal_factor*avg_6)/divisor_6);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_3))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_4))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_5)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_6))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Equal_rangeType )
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
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_11-_candlerange_12);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_13;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            double _candlerange_14;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
         }
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlcounterattackLogic( int startIdx,
                                         int endIdx,
                                         double inOpen[],
                                         double inHigh[],
                                         double inLow[],
                                         double inClose[],
                                         MInteger outBegIdx,
                                         MInteger outNBElement,
                                         int outInteger[] )
   {
      double EqualPeriodTotal = 0;
      double[] BodyLongPeriodTotal = new double[2];
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int EqualTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlcounterattackLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
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
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double _candlerange_7;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_7));
         double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyLong_rangeType )
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
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_6 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Equal_factor*avg_6)/divisor_6);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_3))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_4))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_5)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_6))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Equal_rangeType )
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
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_11-_candlerange_12);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_13;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            double _candlerange_14;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
         }
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlcounterattack( int startIdx,
                                    int endIdx,
                                    float inOpen[],
                                    float inHigh[],
                                    float inLow[],
                                    float inClose[],
                                    MInteger outBegIdx,
                                    MInteger outNBElement,
                                    int outInteger[] )
   {
      double EqualPeriodTotal = 0;
      double[] BodyLongPeriodTotal = new double[2];
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int EqualTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlcounterattackLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
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
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double _candlerange_7;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_7));
         double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyLong_rangeType )
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
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_6 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Equal_factor*avg_6)/divisor_6);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_3))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_4))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_5)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_6))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Equal_rangeType )
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
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_11-_candlerange_12);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_13;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            double _candlerange_14;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
         }
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlcounterattackLogic( int startIdx,
                                         int endIdx,
                                         float inOpen[],
                                         float inHigh[],
                                         float inLow[],
                                         float inClose[],
                                         MInteger outBegIdx,
                                         MInteger outNBElement,
                                         int outInteger[] )
   {
      double EqualPeriodTotal = 0;
      double[] BodyLongPeriodTotal = new double[2];
      int i = 0;
      int outIdx = 0;
      int totIdx = 0;
      int EqualTrailingIdx = 0;
      int BodyLongTrailingIdx = 0;
      int lookbackTotal = 0;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Equal_rangeType = this.candleSettings.equal.rangeType;
      int Equal_avgPeriod = this.candleSettings.equal.avgPeriod;
      double Equal_factor = this.candleSettings.equal.factor;
      lookbackTotal = cdlcounterattackLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      EqualPeriodTotal = 0;
      EqualTrailingIdx = (startIdx-Equal_avgPeriod);
      BodyLongPeriodTotal[1] = 0;
      BodyLongPeriodTotal[0] = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = EqualTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Equal_rangeType )
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
         EqualPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
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
         double _candlerange_2;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal[0] = (BodyLongPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_3;
         double _candlerange_7;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_7 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         double avg_3 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[1]/BodyLong_avgPeriod)) : (_candlerange_7));
         double divisor_3 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyLong_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double _candlerange_8;
         switch( BodyLong_rangeType )
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
         double avg_4 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal[0]/BodyLong_avgPeriod)) : (_candlerange_8));
         double divisor_4 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((BodyLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double _candlerange_9;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         double avg_5 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_9));
         double divisor_5 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((Equal_factor*avg_5)/divisor_5);
         double _candleaverage_6;
         double _candlerange_10;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_6 = (((Equal_avgPeriod!=0)) ? ((EqualPeriodTotal/Equal_avgPeriod)) : (_candlerange_10));
         double divisor_6 = (((Equal_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_6 = ((Equal_factor*avg_6)/divisor_6);
         if( ((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>_candleaverage_3))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_4))&&(inClose[i]<=(inClose[(i-1)]+_candleaverage_5)))&&(inClose[i]>=(inClose[(i-1)]-_candleaverage_6))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Equal_rangeType )
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
         double _candlerange_12;
         switch( Equal_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(EqualTrailingIdx-1)]-inLow[(EqualTrailingIdx-1)])-Math.abs((inClose[(EqualTrailingIdx-1)]-inOpen[(EqualTrailingIdx-1)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         EqualPeriodTotal += (_candlerange_11-_candlerange_12);
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_13;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            double _candlerange_14;
            switch( BodyLong_rangeType )
            {
            case 0:
               _candlerange_14 = Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_14 = (inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_14 = ((inHigh[(BodyLongTrailingIdx-totIdx)]-inLow[(BodyLongTrailingIdx-totIdx)])-Math.abs((inClose[(BodyLongTrailingIdx-totIdx)]-inOpen[(BodyLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_14 = 0.0;
               break;
            }
            BodyLongPeriodTotal[totIdx] = (BodyLongPeriodTotal[totIdx]+(_candlerange_13-_candlerange_14));
         }
         i += 1;
         EqualTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
