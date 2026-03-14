/* Generated */
   public int cdl3whitesoldiersLookback( )
   {
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(ShadowVeryShort_avgPeriod, BodyShort_avgPeriod), Math.max(Far_avgPeriod, Near_avgPeriod))+2) ;

   }
   public RetCode cdl3whitesoldiers( int startIdx,
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
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int BodyShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
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
      lookbackTotal = cdl3whitesoldiersLookback();
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
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Far_rangeType )
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
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_7;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
         double _candleaverage_12;
         double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
         double _candleaverage_13;
         double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
         double _candleaverage_14;
         double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
         double _candleaverage_15;
         double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
         if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(Math.abs((inClose[i]-inOpen[i]))>(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_15)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_18;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            double _candlerange_19;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_19 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_19 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_19 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_19 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
            double _candlerange_20;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_20 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_20 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_20 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_20 = 0.0;
               break;
            }
            double _candlerange_21;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_21 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_21 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_21 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_21 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
         }
         double _candlerange_22;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_22 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_22 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         double _candlerange_23;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_23 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_23 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_23 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_23 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3whitesoldiersLogic( int startIdx,
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
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int BodyShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3whitesoldiersLookback();
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
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Far_rangeType )
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
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_7;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
         double _candleaverage_12;
         double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
         double _candleaverage_13;
         double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
         double _candleaverage_14;
         double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
         double _candleaverage_15;
         double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
         if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(Math.abs((inClose[i]-inOpen[i]))>(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_15)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_18;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            double _candlerange_19;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_19 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_19 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_19 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_19 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
            double _candlerange_20;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_20 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_20 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_20 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_20 = 0.0;
               break;
            }
            double _candlerange_21;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_21 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_21 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_21 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_21 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
         }
         double _candlerange_22;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_22 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_22 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         double _candlerange_23;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_23 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_23 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_23 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_23 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3whitesoldiers( int startIdx,
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
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int BodyShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
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
      lookbackTotal = cdl3whitesoldiersLookback();
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
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Far_rangeType )
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
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_7;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
         double _candleaverage_12;
         double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
         double _candleaverage_13;
         double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
         double _candleaverage_14;
         double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
         double _candleaverage_15;
         double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
         if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(Math.abs((inClose[i]-inOpen[i]))>(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_15)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_18;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            double _candlerange_19;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_19 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_19 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_19 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_19 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
            double _candlerange_20;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_20 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_20 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_20 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_20 = 0.0;
               break;
            }
            double _candlerange_21;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_21 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_21 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_21 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_21 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
         }
         double _candlerange_22;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_22 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_22 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         double _candlerange_23;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_23 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_23 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_23 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_23 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl3whitesoldiersLogic( int startIdx,
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
      double[] NearPeriodTotal = new double[3];
      double[] FarPeriodTotal = new double[3];
      double BodyShortPeriodTotal;
      int i;
      int outIdx;
      int totIdx;
      int ShadowVeryShortTrailingIdx;
      int NearTrailingIdx;
      int FarTrailingIdx;
      int BodyShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int Far_rangeType = this.candleSettings.far.rangeType;
      int Far_avgPeriod = this.candleSettings.far.avgPeriod;
      double Far_factor = this.candleSettings.far.factor;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdl3whitesoldiersLookback();
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
      NearPeriodTotal[2] = 0;
      NearPeriodTotal[1] = 0;
      NearPeriodTotal[0] = 0;
      NearTrailingIdx = (startIdx-Near_avgPeriod);
      FarPeriodTotal[2] = 0;
      FarPeriodTotal[1] = 0;
      FarPeriodTotal[0] = 0;
      FarTrailingIdx = (startIdx-Far_avgPeriod);
      BodyShortPeriodTotal = 0;
      BodyShortTrailingIdx = (startIdx-BodyShort_avgPeriod);
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
      i = NearTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_3;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         NearPeriodTotal[2] = (NearPeriodTotal[2]+_candlerange_3);
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(i-1)]-inOpen[(i-1)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(i-1)]-inLow[(i-1)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(i-1)]-inLow[(i-1)])-Math.abs((inClose[(i-1)]-inOpen[(i-1)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal[1] = (NearPeriodTotal[1]+_candlerange_4);
         i += 1;
      }
      i = FarTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_5;
         switch( Far_rangeType )
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
         FarPeriodTotal[2] = (FarPeriodTotal[2]+_candlerange_5);
         double _candlerange_6;
         switch( Far_rangeType )
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
         FarPeriodTotal[1] = (FarPeriodTotal[1]+_candlerange_6);
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_7 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += _candlerange_7;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_8;
         double avg_8 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[2]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_8 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((ShadowVeryShort_factor*avg_8)/divisor_8);
         double _candleaverage_9;
         double avg_9 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[1]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_9 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_9 = ((ShadowVeryShort_factor*avg_9)/divisor_9);
         double _candleaverage_10;
         double avg_10 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal[0]/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_10 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_10 = ((ShadowVeryShort_factor*avg_10)/divisor_10);
         double _candleaverage_11;
         double avg_11 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[2]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_11 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_11 = ((Near_factor*avg_11)/divisor_11);
         double _candleaverage_12;
         double avg_12 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal[1]/Near_avgPeriod)) : (ta_candlerange(Near_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_12 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_12 = ((Near_factor*avg_12)/divisor_12);
         double _candleaverage_13;
         double avg_13 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[2]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_13 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_13 = ((Far_factor*avg_13)/divisor_13);
         double _candleaverage_14;
         double avg_14 = (((Far_avgPeriod!=0)) ? ((FarPeriodTotal[1]/Far_avgPeriod)) : (ta_candlerange(Far_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_14 = (((Far_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_14 = ((Far_factor*avg_14)/divisor_14);
         double _candleaverage_15;
         double avg_15 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_15 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_15 = ((BodyShort_factor*avg_15)/divisor_15);
         if( ((((((((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&((inHigh[(i-2)]-(((inClose[(i-2)]>=inOpen[(i-2)])) ? (inClose[(i-2)]) : (inOpen[(i-2)])))<_candleaverage_8))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==1))&&((inHigh[(i-1)]-(((inClose[(i-1)]>=inOpen[(i-1)])) ? (inClose[(i-1)]) : (inOpen[(i-1)])))<_candleaverage_9))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==1))&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_10))&&(inClose[i]>inClose[(i-1)]))&&(inClose[(i-1)]>inClose[(i-2)]))&&(inOpen[(i-1)]>inOpen[(i-2)]))&&(inOpen[(i-1)]<=(inClose[(i-2)]+_candleaverage_11)))&&(inOpen[i]>inOpen[(i-1)]))&&(inOpen[i]<=(inClose[(i-1)]+_candleaverage_12)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))>(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))-_candleaverage_13)))&&(Math.abs((inClose[i]-inOpen[i]))>(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))-_candleaverage_14)))&&(Math.abs((inClose[i]-inOpen[i]))>_candleaverage_15)) ) {
            outInteger[outIdx++] = 100;
         } else {
            outInteger[outIdx++] = 0;
         }
         for( totIdx = 2; (totIdx>=0); totIdx -= 1 ) {
            double _candlerange_16;
            switch( ShadowVeryShort_rangeType )
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
            switch( ShadowVeryShort_rangeType )
            {
            case 0:
               _candlerange_17 = Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_17 = (inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_17 = ((inHigh[(ShadowVeryShortTrailingIdx-totIdx)]-inLow[(ShadowVeryShortTrailingIdx-totIdx)])-Math.abs((inClose[(ShadowVeryShortTrailingIdx-totIdx)]-inOpen[(ShadowVeryShortTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_17 = 0.0;
               break;
            }
            ShadowVeryShortPeriodTotal[totIdx] = (ShadowVeryShortPeriodTotal[totIdx]+(_candlerange_16-_candlerange_17));
         }
         for( totIdx = 2; (totIdx>=1); totIdx -= 1 ) {
            double _candlerange_18;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_18 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_18 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_18 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_18 = 0.0;
               break;
            }
            double _candlerange_19;
            switch( Far_rangeType )
            {
            case 0:
               _candlerange_19 = Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_19 = (inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_19 = ((inHigh[(FarTrailingIdx-totIdx)]-inLow[(FarTrailingIdx-totIdx)])-Math.abs((inClose[(FarTrailingIdx-totIdx)]-inOpen[(FarTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_19 = 0.0;
               break;
            }
            FarPeriodTotal[totIdx] = (FarPeriodTotal[totIdx]+(_candlerange_18-_candlerange_19));
            double _candlerange_20;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_20 = Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)]));
               break;
            case 1:
               _candlerange_20 = (inHigh[(i-totIdx)]-inLow[(i-totIdx)]);
               break;
            case 2:
               _candlerange_20 = ((inHigh[(i-totIdx)]-inLow[(i-totIdx)])-Math.abs((inClose[(i-totIdx)]-inOpen[(i-totIdx)])));
               break;
            default:
               _candlerange_20 = 0.0;
               break;
            }
            double _candlerange_21;
            switch( Near_rangeType )
            {
            case 0:
               _candlerange_21 = Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)]));
               break;
            case 1:
               _candlerange_21 = (inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)]);
               break;
            case 2:
               _candlerange_21 = ((inHigh[(NearTrailingIdx-totIdx)]-inLow[(NearTrailingIdx-totIdx)])-Math.abs((inClose[(NearTrailingIdx-totIdx)]-inOpen[(NearTrailingIdx-totIdx)])));
               break;
            default:
               _candlerange_21 = 0.0;
               break;
            }
            NearPeriodTotal[totIdx] = (NearPeriodTotal[totIdx]+(_candlerange_20-_candlerange_21));
         }
         double _candlerange_22;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_22 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_22 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_22 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_22 = 0.0;
            break;
         }
         double _candlerange_23;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_23 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_23 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_23 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_23 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_22-_candlerange_23);
         i += 1;
         ShadowVeryShortTrailingIdx += 1;
         NearTrailingIdx += 1;
         FarTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
