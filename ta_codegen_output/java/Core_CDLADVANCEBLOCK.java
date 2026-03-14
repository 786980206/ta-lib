/* Generated */
   public int cdladvanceblockLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      return (Math.max(Math.max(Math.max(ShadowLong_avgPeriod, ShadowShort_avgPeriod), Math.max(Far_avgPeriod, Near_avgPeriod)), BodyLong_avgPeriod)+2) ;

   }
   public RetCode cdladvanceblock( int startIdx,
                                   int endIdx,
                                   double inOpen[],
                                   double inHigh[],
                                   double inLow[],
                                   double inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double[] ShadowShortPeriodTotal = new double[3];
      double[] ShadowLongPeriodTotal = new double[2];
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int ShadowShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdladvanceblockLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowShortPeriodTotal[2] = 0;
      ShadowShortPeriodTotal[1] = 0;
      ShadowShortPeriodTotal[0] = 0;
      ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      ShadowLongPeriodTotal[1] = 0;
      ShadowLongPeriodTotal[0] = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
         double _candlerange_2;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
         double _candlerange_4;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
         double _candlerange_8;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_9;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_9;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))))||((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( ShadowShort_rangeType )
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
            switch( ShadowShort_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowLong_rangeType )
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
            switch( ShadowLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Far_rangeType )
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
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
            double _candlerange_16;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            double _candlerange_17;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         double _candlerange_18;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         ShadowShortTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdladvanceblockLogic( int startIdx,
                                        int endIdx,
                                        double inOpen[],
                                        double inHigh[],
                                        double inLow[],
                                        double inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double[] ShadowShortPeriodTotal = new double[3];
      double[] ShadowLongPeriodTotal = new double[2];
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int ShadowShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      lookbackTotal = cdladvanceblockLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowShortPeriodTotal[2] = 0;
      ShadowShortPeriodTotal[1] = 0;
      ShadowShortPeriodTotal[0] = 0;
      ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      ShadowLongPeriodTotal[1] = 0;
      ShadowLongPeriodTotal[0] = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
         double _candlerange_2;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
         double _candlerange_4;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
         double _candlerange_8;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_9;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_9;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))))||((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( ShadowShort_rangeType )
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
            switch( ShadowShort_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowLong_rangeType )
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
            switch( ShadowLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Far_rangeType )
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
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
            double _candlerange_16;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            double _candlerange_17;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         double _candlerange_18;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         ShadowShortTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdladvanceblock( int startIdx,
                                   int endIdx,
                                   float inOpen[],
                                   float inHigh[],
                                   float inLow[],
                                   float inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double[] ShadowShortPeriodTotal = new double[3];
      double[] ShadowLongPeriodTotal = new double[2];
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int ShadowShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdladvanceblockLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowShortPeriodTotal[2] = 0;
      ShadowShortPeriodTotal[1] = 0;
      ShadowShortPeriodTotal[0] = 0;
      ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      ShadowLongPeriodTotal[1] = 0;
      ShadowLongPeriodTotal[0] = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
         double _candlerange_2;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
         double _candlerange_4;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
         double _candlerange_8;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_9;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_9;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))))||((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( ShadowShort_rangeType )
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
            switch( ShadowShort_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowLong_rangeType )
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
            switch( ShadowLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Far_rangeType )
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
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
            double _candlerange_16;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            double _candlerange_17;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         double _candlerange_18;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         ShadowShortTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdladvanceblockLogic( int startIdx,
                                        int endIdx,
                                        float inOpen[],
                                        float inHigh[],
                                        float inLow[],
                                        float inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double[] ShadowShortPeriodTotal = new double[3];
      double[] ShadowLongPeriodTotal = new double[2];
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int BodyLongTrailingIdx;
      int ShadowShortTrailingIdx;
      int ShadowLongTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      lookbackTotal = cdladvanceblockLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      ShadowShortPeriodTotal[2] = 0;
      ShadowShortPeriodTotal[1] = 0;
      ShadowShortPeriodTotal[0] = 0;
      ShadowShortTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      ShadowLongPeriodTotal[1] = 0;
      ShadowLongPeriodTotal[0] = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = ShadowShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[2] = (ShadowShortPeriodTotal[2]+_candlerange_0);
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[1] = (ShadowShortPeriodTotal[1]+_candlerange_1);
         double _candlerange_2;
         switch( ShadowShort_rangeType )
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
         ShadowShortPeriodTotal[0] = (ShadowShortPeriodTotal[0]+_candlerange_2);
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[1] = (ShadowLongPeriodTotal[1]+_candlerange_3);
         double _candlerange_4;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal[0] = (ShadowLongPeriodTotal[0]+_candlerange_4);
         i += 1;
      }
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_7);
         double _candlerange_8;
         switch( Far_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_8 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_8);
         i += 1;
      }
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_9;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_9 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         BodyLongPeriodTotal += _candlerange_9;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>ta_candleaverage(BodyLong_rangeType, BodyLong_avgPeriod, BodyLong_factor, BodyLongPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(((((Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))&&(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(Math.abs((inClose[i]-inOpen[i]))<(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-ta_candleaverage(Far_rangeType, Far_avgPeriod, Far_factor, FarPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)]))))||(((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<Math.abs((inClose[(i-2)]-inOpen[(i-2)]))))&&(((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))||((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))>ta_candleaverage(ShadowShort_rangeType, ShadowShort_avgPeriod, ShadowShort_factor, ShadowShortPeriodTotal[1], inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])))))||((Math.abs((inClose[i]-inOpen[i]))<Math.abs((inClose[(i-1)]-inOpen[(i-1)])))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>ta_candleaverage(ShadowLong_rangeType, ShadowLong_avgPeriod, ShadowLong_factor, ShadowLongPeriodTotal[0], inOpen[i], inHigh[i], inLow[i], inClose[i]))))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_10;
            switch( ShadowShort_rangeType )
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
            switch( ShadowShort_rangeType )
            {
            case 0:
               _candlerange_11 = Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_11 = (inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_11 = ((inHigh[(ShadowShortTrailingIdx-totIdx)]-inLow[(ShadowShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowShortTrailingIdx-totIdx)]-inOpen[(ShadowShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_11 = 0.0;
               break;
            }
            ShadowShortPeriodTotal[totIdx] = (ShadowShortPeriodTotal[totIdx]+(_candlerange_10-_candlerange_11));
         }
         for( totIdx = 1; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_12;
            switch( ShadowLong_rangeType )
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
            switch( ShadowLong_rangeType )
            {
            case 0:
               _candlerange_13 = Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_13 = (inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_13 = ((inHigh[(ShadowLongTrailingIdx-totIdx)]-inLow[(ShadowLongTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowLongTrailingIdx-totIdx)]-inOpen[(ShadowLongTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_13 = 0.0;
               break;
            }
            ShadowLongPeriodTotal[totIdx] = (ShadowLongPeriodTotal[totIdx]+(_candlerange_12-_candlerange_13));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_14;
            switch( Far_rangeType )
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
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_15 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_15 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_15 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_15 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_14-_candlerange_15));
            double _candlerange_16;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_16 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_16 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_16 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_16 = 0.0;
               break;
            }
            double _candlerange_17;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         double _candlerange_18;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_18 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_18 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_18 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_18 = 0.0;
            break;
         }
         double _candlerange_19;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_19 = Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_19 = (inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_19 = ((inHigh[(BodyLongTrailingIdx-2)]-inLow[(BodyLongTrailingIdx-2)])-Math.abs((inClose[(BodyLongTrailingIdx-2)]-inOpen[(BodyLongTrailingIdx-2)])));
            break;
         default:
            _candlerange_19 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_18-_candlerange_19);
         i += 1;
         ShadowShortTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
