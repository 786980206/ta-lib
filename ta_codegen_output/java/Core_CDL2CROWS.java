/* Generated */
   public int cdl2crowsLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      return (BodyLong_avgPeriod+2) ;

   }
   public RetCode cdl2crows( int startIdx,
                             int endIdx,
                             double inOpen[],
                             double inHigh[],
                             double inLow[],
                             double inClose[],
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             int outInteger[] )
   {
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-2)]))&&(inClose[i]<inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl2crowsLogic( int startIdx,
                                  int endIdx,
                                  double inOpen[],
                                  double inHigh[],
                                  double inLow[],
                                  double inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      lookbackTotal = cdl2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-2)]))&&(inClose[i]<inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl2crows( int startIdx,
                             int endIdx,
                             float inOpen[],
                             float inHigh[],
                             float inLow[],
                             float inClose[],
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             int outInteger[] )
   {
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdl2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-2)]))&&(inClose[i]<inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdl2crowsLogic( int startIdx,
                                  int endIdx,
                                  float inOpen[],
                                  float inHigh[],
                                  float inLow[],
                                  float inClose[],
                                  MInteger outBegIdx,
                                  MInteger outNBElement,
                                  int outInteger[] )
   {
      double BodyLongPeriodTotal;
      int i;
      int outIdx;
      int BodyLongTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      lookbackTotal = cdl2crowsLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = ((startIdx-2)-BodyLong_avgPeriod);
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( ((((((((((((inClose[(i-2)]>=inOpen[(i-2)])) ? (1) : ((0-1)))==1)&&(Math.abs((inClose[(i-2)]-inOpen[(i-2)]))>_candleaverage_1))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-1)))&&(Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)])))&&((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))==(0-1)))&&(inOpen[i]<inOpen[(i-1)]))&&(inOpen[i]>inClose[(i-1)]))&&(inClose[i]>inOpen[(i-2)]))&&(inClose[i]<inClose[(i-2)])) ) {
            outInteger[outIdx++] = (0-100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx]));
            break;
         case 1:
            _candlerange_3 = (inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[BodyLongTrailingIdx]-inLow[BodyLongTrailingIdx])-Math.abs((inClose[BodyLongTrailingIdx]-inOpen[BodyLongTrailingIdx])));
            break;
         default:
            _candlerange_3 = 0.0;
            break;
         }
         BodyLongPeriodTotal += (_candlerange_2-_candlerange_3);
         i += 1;
         BodyLongTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
