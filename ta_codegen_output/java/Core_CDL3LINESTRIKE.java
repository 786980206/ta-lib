/* Generated */
   public int cdl3linestrikeLookback( )
   {
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      return (Near_avgPeriod+3) ;

   }
   public RetCode cdl3linestrike( int startIdx,
                                  int endIdx,
                                  double inOpen[],
                                  double inHigh[],
                                  double inLow[],
                                  double inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double[] NearPeriodTotal = new double[4];
      int i;
      int outIdx;
      int totIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl3linestrikeLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal[3] = 0;
      NearPeriodTotal[2] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(Math.min(inOpen[(i-3)], inClose[(i-3)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-2)]<=(Math.max(inOpen[(i-3)], inClose[(i-3)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-1)]>=(Math.min(inOpen[(i-2)], inClose[(i-2)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[(i-1)]<=(Math.max(inOpen[(i-2)], inClose[(i-2)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) ) {
            outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 3; (totIdx>=2); totIdx -= 1 ) {
            double _candlerange_2;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_2 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_2 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_2 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_2 = 0.0;
               break;
            }
            double _candlerange_3;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_3 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_3 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_3 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_2-_candlerange_3));
         }
         i += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3linestrikeLogic( int startIdx,
                                       int endIdx,
                                       double inOpen[],
                                       double inHigh[],
                                       double inLow[],
                                       double inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double[] NearPeriodTotal = new double[4];
      int i;
      int outIdx;
      int totIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdl3linestrikeLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal[3] = 0;
      NearPeriodTotal[2] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(Math.min(inOpen[(i-3)], inClose[(i-3)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-2)]<=(Math.max(inOpen[(i-3)], inClose[(i-3)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-1)]>=(Math.min(inOpen[(i-2)], inClose[(i-2)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[(i-1)]<=(Math.max(inOpen[(i-2)], inClose[(i-2)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) ) {
            outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 3; (totIdx>=2); totIdx -= 1 ) {
            double _candlerange_2;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_2 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_2 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_2 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_2 = 0.0;
               break;
            }
            double _candlerange_3;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_3 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_3 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_3 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_2-_candlerange_3));
         }
         i += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3linestrike( int startIdx,
                                  int endIdx,
                                  float inOpen[],
                                  float inHigh[],
                                  float inLow[],
                                  float inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double[] NearPeriodTotal = new double[4];
      int i;
      int outIdx;
      int totIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl3linestrikeLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal[3] = 0;
      NearPeriodTotal[2] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(Math.min(inOpen[(i-3)], inClose[(i-3)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-2)]<=(Math.max(inOpen[(i-3)], inClose[(i-3)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-1)]>=(Math.min(inOpen[(i-2)], inClose[(i-2)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[(i-1)]<=(Math.max(inOpen[(i-2)], inClose[(i-2)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) ) {
            outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 3; (totIdx>=2); totIdx -= 1 ) {
            double _candlerange_2;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_2 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_2 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_2 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_2 = 0.0;
               break;
            }
            double _candlerange_3;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_3 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_3 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_3 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_2-_candlerange_3));
         }
         i += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3linestrikeLogic( int startIdx,
                                       int endIdx,
                                       float inOpen[],
                                       float inHigh[],
                                       float inLow[],
                                       float inClose[],
                                       MInteger outBegIdx,
                                       MInteger outNBElement,
                                       int outInteger[] )
   {
      double[] NearPeriodTotal = new double[4];
      int i;
      int outIdx;
      int totIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdl3linestrikeLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal[3] = 0;
      NearPeriodTotal[2] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal[3] = (NearPeriodTotal[3]+_candlerange_0);
         double _candlerange_1;
         switch( Near_rangeType )
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
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_1);
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((((((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1))))&&((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1))))))&&(inOpen[(i-2)]>=(Math.min(inOpen[(i-3)], inClose[(i-3)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-2)]<=(Math.max(inOpen[(i-3)], inClose[(i-3)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[3], inOpen[(i-3)], inHigh[(i-3)], inLow[(i-3)], inClose[(i-3)]))))&&(inOpen[(i-1)]>=(Math.min(inOpen[(i-2)], inClose[(i-2)])-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(inOpen[(i-1)]<=(Math.max(inOpen[(i-2)], inClose[(i-2)])+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal[2], inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))&&(((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1)&&(inClose[(i-1)]>inClose[(i-2)]))&&(inClose[(i-2)]>inClose[(i-3)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]<inOpen[(i-3)]))||((((((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1))&&(inClose[(i-1)]<inClose[(i-2)]))&&(inClose[(i-2)]<inClose[(i-3)]))&&(inOpen[i]<inClose[(i-1)]))&&(inClose[i]>inOpen[(i-3)])))) ) {
            outInteger[outIdx++] = ((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 3; (totIdx>=2); totIdx -= 1 ) {
            double _candlerange_2;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_2 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_2 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_2 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_2 = 0.0;
               break;
            }
            double _candlerange_3;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_3 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_3 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_3 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_3 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_2-_candlerange_3));
         }
         i += 1;
         NearTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
