/* Generated */
   public int cdlupsidegap2crowsLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      return (Math.max(BodyShort_avgPeriod, BodyLong_avgPeriod)+2) ;

   }
   public RetCode cdlupsidegap2crows( int startIdx,
                                      int endIdx,
                                      double inOpen[],
                                      double inHigh[],
                                      double inLow[],
                                      double inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double BodyShortPeriodTotal;
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
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
      lookbackTotal = cdlupsidegap2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyShortPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
      BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         double _candlerange_6;
         switch( BodyShort_rangeType )
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
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_6-_candlerange_7);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlupsidegap2crowsLogic( int startIdx,
                                           int endIdx,
                                           double inOpen[],
                                           double inHigh[],
                                           double inLow[],
                                           double inClose[],
                                           MInteger outBegIdx,
                                           MInteger outNBElement,
                                           int outInteger[] )
   {
      double BodyShortPeriodTotal;
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      lookbackTotal = cdlupsidegap2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyShortPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
      BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         double _candlerange_6;
         switch( BodyShort_rangeType )
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
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_6-_candlerange_7);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlupsidegap2crows( int startIdx,
                                      int endIdx,
                                      float inOpen[],
                                      float inHigh[],
                                      float inLow[],
                                      float inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double BodyShortPeriodTotal;
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
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
      lookbackTotal = cdlupsidegap2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyShortPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
      BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         double _candlerange_6;
         switch( BodyShort_rangeType )
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
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_6-_candlerange_7);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlupsidegap2crowsLogic( int startIdx,
                                           int endIdx,
                                           float inOpen[],
                                           float inHigh[],
                                           float inLow[],
                                           float inClose[],
                                           MInteger outBegIdx,
                                           MInteger outNBElement,
                                           int outInteger[] )
   {
      double BodyShortPeriodTotal;
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyShortTrailingIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int BodyShort_rangeType = this.candleSettings.bodyShort.rangeType;
      int BodyShort_avgPeriod = this.candleSettings.bodyShort.avgPeriod;
      double BodyShort_factor = this.candleSettings.bodyShort.factor;
      lookbackTotal = cdlupsidegap2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyShortPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
      BodyShortTrailingIdx = ((startIdx-1)-BodyShort_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
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
         BodyLongPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = BodyShortTrailingIdx;
      while( (i<(startIdx-1)) ) {
         double _candlerange_1;
         switch( BodyShort_rangeType )
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
         BodyShortPeriodTotal += _candlerange_1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyShort_avgPeriod!=0)) ? ((BodyShortPeriodTotal/BodyShort_avgPeriod)) : (ta_candlerange(BodyShort_rangeType, inOpen[(i-1)], inHigh[(i-1)], inLow[(i-1)], inClose[(i-1)])));
         double divisor_3 = (((BodyShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyShort_factor*avg_3)/divisor_3);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_2))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_3))&&(((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))) ? (1) : (0)))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]>inOpen[(i-1)]))&&(inClose[i]<inClose[(i-1)]))&&(inClose[i]>inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyLong_rangeType )
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
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_4-_candlerange_5);
         double _candlerange_6;
         switch( BodyShort_rangeType )
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
         double _candlerange_7;
         switch( BodyShort_rangeType )
         {
         case 0:
            _candlerange_7 = Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx]));
            break;
         case 1:
            _candlerange_7 = (inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx]);
            break;
         case 2:
            _candlerange_7 = ((inHigh[BodyShortTrailingIdx]-inLow[BodyShortTrailingIdx])-Math.abs((inClose[BodyShortTrailingIdx]-inOpen[BodyShortTrailingIdx])));
            break;
         default:
            _candlerange_7 = 0.0;
            break;
         }
         BodyShortPeriodTotal += (_candlerange_6-_candlerange_7);
         i += 1;
         BodyLongTrailingIdx += 1;
         BodyShortTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
