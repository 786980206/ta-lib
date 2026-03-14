/* Generated */
   public int cdlbreakawayLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      return (BodyLong_avgPeriod+4) ;

   }
   public RetCode cdlbreakaway( int startIdx,
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
      lookbackTotal = cdlbreakawayLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
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
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( (((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_1)&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])<Math.min(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]<inHigh[(i-3)]))&&(inLow[(i-2)]<inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]<inLow[(i-2)]))&&(inClose[i]>inOpen[(i-3)]))&&(inClose[i]<inClose[(i-4)]))||(((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==1)&&(Math.min(inOpen[(i-3)], inClose[(i-3)])>Math.max(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]>inHigh[(i-3)]))&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]>inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&(inClose[i]<inOpen[(i-3)]))&&(inClose[i]>inClose[(i-4)])))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
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
   public RetCode cdlbreakawayLogic( int startIdx,
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
      lookbackTotal = cdlbreakawayLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
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
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( (((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_1)&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])<Math.min(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]<inHigh[(i-3)]))&&(inLow[(i-2)]<inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]<inLow[(i-2)]))&&(inClose[i]>inOpen[(i-3)]))&&(inClose[i]<inClose[(i-4)]))||(((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==1)&&(Math.min(inOpen[(i-3)], inClose[(i-3)])>Math.max(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]>inHigh[(i-3)]))&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]>inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&(inClose[i]<inOpen[(i-3)]))&&(inClose[i]>inClose[(i-4)])))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
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
   public RetCode cdlbreakaway( int startIdx,
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
      lookbackTotal = cdlbreakawayLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
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
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( (((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_1)&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])<Math.min(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]<inHigh[(i-3)]))&&(inLow[(i-2)]<inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]<inLow[(i-2)]))&&(inClose[i]>inOpen[(i-3)]))&&(inClose[i]<inClose[(i-4)]))||(((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==1)&&(Math.min(inOpen[(i-3)], inClose[(i-3)])>Math.max(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]>inHigh[(i-3)]))&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]>inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&(inClose[i]<inOpen[(i-3)]))&&(inClose[i]>inClose[(i-4)])))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
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
   public RetCode cdlbreakawayLogic( int startIdx,
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
      lookbackTotal = cdlbreakawayLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyLongPeriodTotal = 0;
      BodyLongTrailingIdx = (startIdx-BodyLong_avgPeriod);
      i = BodyLongTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_0;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_0 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_0 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_0 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
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
         double avg_1 = (((BodyLong_avgPeriod!=0)) ? ((BodyLongPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[(i-4)], inHigh[(i-4)], inLow[(i-4)], inClose[(i-4)])));
         double divisor_1 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyLong_factor*avg_1)/divisor_1);
         if( (((((Math.abs((inClose[(i-4)]-inOpen[(i-4)]))>_candleaverage_1)&&((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))))&&((((inClose[(i-3)]>=inOpen[(i-3)])) ? (1) : ((0-1)))==(((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))))&&((((inClose[(i-1)]>=inOpen[(i-1)])) ? (1) : ((0-1)))==(0-(((inClose[i]>=inOpen[i])) ? (1) : ((0-1))))))&&((((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==(0-1))&&(Math.max(inOpen[(i-3)], inClose[(i-3)])<Math.min(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]<inHigh[(i-3)]))&&(inLow[(i-2)]<inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]<inLow[(i-2)]))&&(inClose[i]>inOpen[(i-3)]))&&(inClose[i]<inClose[(i-4)]))||(((((((((((inClose[(i-4)]>=inOpen[(i-4)])) ? (1) : ((0-1)))==1)&&(Math.min(inOpen[(i-3)], inClose[(i-3)])>Math.max(inOpen[(i-4)], inClose[(i-4)])))&&(inHigh[(i-2)]>inHigh[(i-3)]))&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]>inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&(inClose[i]<inOpen[(i-3)]))&&(inClose[i]>inClose[(i-4)])))) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_2;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(i-4)]-inOpen[(i-4)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(i-4)]-inLow[(i-4)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(i-4)]-inLow[(i-4)])-Math.abs((inClose[(i-4)]-inOpen[(i-4)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         double _candlerange_3;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_3 = Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)]));
            break;
         case 1:
            _candlerange_3 = (inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)]);
            break;
         case 2:
            _candlerange_3 = ((inHigh[(BodyLongTrailingIdx-4)]-inLow[(BodyLongTrailingIdx-4)])-Math.abs((inClose[(BodyLongTrailingIdx-4)]-inOpen[(BodyLongTrailingIdx-4)])));
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
