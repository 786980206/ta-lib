/* Generated */
   public int cdltristarLookback( )
   {
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      return (BodyDoji_avgPeriod+2) ;

   }
   public RetCode cdltristar( int startIdx,
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
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdltristarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = ((startIdx-2)-BodyDoji_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         if( (((Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<=_candleaverage_1)&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_2))&&(Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)) ) {
            outInteger[outIdx] = 0;
            if( ((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))&&(Math.max(inOpen[i], inClose[i])<Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = (0-100);
            }
            if( ((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))&&(Math.min(inOpen[i], inClose[i])>Math.min(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = 100;
            }
            outIdx += 1;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltristarLogic( int startIdx,
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
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      lookbackTotal = cdltristarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = ((startIdx-2)-BodyDoji_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         if( (((Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<=_candleaverage_1)&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_2))&&(Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)) ) {
            outInteger[outIdx] = 0;
            if( ((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))&&(Math.max(inOpen[i], inClose[i])<Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = (0-100);
            }
            if( ((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))&&(Math.min(inOpen[i], inClose[i])>Math.min(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = 100;
            }
            outIdx += 1;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltristar( int startIdx,
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
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdltristarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = ((startIdx-2)-BodyDoji_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         if( (((Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<=_candleaverage_1)&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_2))&&(Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)) ) {
            outInteger[outIdx] = 0;
            if( ((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))&&(Math.max(inOpen[i], inClose[i])<Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = (0-100);
            }
            if( ((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))&&(Math.min(inOpen[i], inClose[i])>Math.min(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = 100;
            }
            outIdx += 1;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdltristarLogic( int startIdx,
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
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int lookbackTotal;
      int BodyDoji_rangeType = this.candleSettings.bodyDoji.rangeType;
      int BodyDoji_avgPeriod = this.candleSettings.bodyDoji.avgPeriod;
      double BodyDoji_factor = this.candleSettings.bodyDoji.factor;
      lookbackTotal = cdltristarLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = ((startIdx-2)-BodyDoji_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<(startIdx-2)) ) {
         double _candlerange_0;
         switch( BodyDoji_rangeType )
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
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_1;
         double avg_1 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_1 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((BodyDoji_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double avg_2 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_2 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyDoji_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((BodyDoji_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyDoji_avgPeriod)) : (ta_candlerange(BodyDoji_rangeType, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])));
         double divisor_3 = (((BodyDoji_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((BodyDoji_factor*avg_3)/divisor_3);
         if( (((Math.abs((inClose[(i-2)]-inOpen[(i-2)]))<=_candleaverage_1)&&(Math.abs((inClose[(i-1)]-inOpen[(i-1)]))<=_candleaverage_2))&&(Math.abs((inClose[i]-inOpen[i]))<=_candleaverage_3)) ) {
            outInteger[outIdx] = 0;
            if( ((Math.min(inOpen[(i-1)], inClose[(i-1)])>Math.max(inOpen[(i-2)], inClose[(i-2)]))&&(Math.max(inOpen[i], inClose[i])<Math.max(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = (0-100);
            }
            if( ((Math.max(inOpen[(i-1)], inClose[(i-1)])<Math.min(inOpen[(i-2)], inClose[(i-2)]))&&(Math.min(inOpen[i], inClose[i])>Math.min(inOpen[(i-1)], inClose[(i-1)]))) ) {
               outInteger[outIdx] = 100;
            }
            outIdx += 1;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_4;
         switch( BodyDoji_rangeType )
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
         switch( BodyDoji_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_5 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_4-_candlerange_5);
         i += 1;
         BodyTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
