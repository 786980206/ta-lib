/* Generated */
   public int cdlshootingstarLookback( )
   {
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      return (Math.max(Math.max(BodyShort_avgPeriod, ShadowLong_avgPeriod), ShadowVeryShort_avgPeriod)+1) ;

   }
   public RetCode cdlshootingstar( int startIdx,
                                   int endIdx,
                                   double inOpen[],
                                   double inHigh[],
                                   double inLow[],
                                   double inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowLongPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
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
      lookbackTotal = cdlshootingstarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowLong_rangeType )
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
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlshootingstarLogic( int startIdx,
                                        int endIdx,
                                        double inOpen[],
                                        double inHigh[],
                                        double inLow[],
                                        double inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowLongPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlshootingstarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowLong_rangeType )
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
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlshootingstar( int startIdx,
                                   int endIdx,
                                   float inOpen[],
                                   float inHigh[],
                                   float inLow[],
                                   float inClose[],
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowLongPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
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
      lookbackTotal = cdlshootingstarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowLong_rangeType )
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
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlshootingstarLogic( int startIdx,
                                        int endIdx,
                                        float inOpen[],
                                        float inHigh[],
                                        float inLow[],
                                        float inClose[],
                                        MInteger outBegIdx,
                                        MInteger outNBElement,
                                        int outInteger[] )
   {
      double BodyPeriodTotal;
      double ShadowLongPeriodTotal;
      double ShadowVeryShortPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowLongTrailingIdx;
      int ShadowVeryShortTrailingIdx;
      int lookbackTotal;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      int ShadowLong_rangeType = this.candleSettings.shadowLong.rangeType;
      int ShadowLong_avgPeriod = this.candleSettings.shadowLong.avgPeriod;
      double ShadowLong_factor = this.candleSettings.shadowLong.factor;
      int ShadowVeryShort_rangeType = this.candleSettings.shadowVeryShort.rangeType;
      int ShadowVeryShort_avgPeriod = this.candleSettings.shadowVeryShort.avgPeriod;
      double ShadowVeryShort_factor = this.candleSettings.shadowVeryShort.factor;
      lookbackTotal = cdlshootingstarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyShort_avgPeriod);
      ShadowLongPeriodTotal = 0;
      ShadowLongTrailingIdx = (startIdx-ShadowLong_avgPeriod);
      ShadowVeryShortPeriodTotal = 0;
      ShadowVeryShortTrailingIdx = (startIdx-ShadowVeryShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_0 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_0 = 0.0;
            break;
         }
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowLong_rangeType )
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
         ShadowLongPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = ShadowVeryShortTrailingIdx;
      while( (i<startIdx) ) {
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
         ShadowVeryShortPeriodTotal += _candlerange_2;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowLong_avgPeriod!=0)) ? ((ShadowLongPeriodTotal/ShadowLong_avgPeriod)) : (ta_candlerange(ShadowLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowLong_factor*avg_4)/divisor_4);
         double _candleaverage_5;
         double avg_5 = (((ShadowVeryShort_avgPeriod!=0)) ? ((ShadowVeryShortPeriodTotal/ShadowVeryShort_avgPeriod)) : (ta_candlerange(ShadowVeryShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_5 = (((ShadowVeryShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_5 = ((ShadowVeryShort_factor*avg_5)/divisor_5);
         if( ((((Math.abs((inClose[i]-inOpen[i]))<_candleaverage_3)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))>_candleaverage_4))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_5))&&(Math.min(inOpen[i], inClose[i])>Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_6;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_6 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_6-_candlerange_7);
         double _candlerange_8;
         switch( ShadowLong_rangeType )
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
         double _candlerange_9;
         switch( ShadowLong_rangeType )
         {
         case 0:
            _candlerange_9 = Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx]));
            break;
         case 1:
            _candlerange_9 = (inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx]);
            break;
         case 2:
            _candlerange_9 = ((inHigh[ShadowLongTrailingIdx]-inLow[ShadowLongTrailingIdx])-Math.abs((inClose[ShadowLongTrailingIdx]-inOpen[ShadowLongTrailingIdx])));
            break;
         default:
            _candlerange_9 = 0.0;
            break;
         }
         ShadowLongPeriodTotal += (_candlerange_8-_candlerange_9);
         double _candlerange_10;
         switch( ShadowVeryShort_rangeType )
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
         switch( ShadowVeryShort_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx]));
            break;
         case 1:
            _candlerange_11 = (inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[ShadowVeryShortTrailingIdx]-inLow[ShadowVeryShortTrailingIdx])-Math.abs((inClose[ShadowVeryShortTrailingIdx]-inOpen[ShadowVeryShortTrailingIdx])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         ShadowVeryShortPeriodTotal += (_candlerange_10-_candlerange_11);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowLongTrailingIdx += 1;
         ShadowVeryShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
