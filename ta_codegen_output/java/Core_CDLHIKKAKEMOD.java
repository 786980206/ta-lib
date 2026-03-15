/* Generated */
   public int cdlhikkakemodLookback( )
   {
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      return (Math.max(1, Near_avgPeriod)+5) ;

   }
   public RetCode cdlhikkakemod( int startIdx,
                                 int endIdx,
                                 double inOpen[],
                                 double inHigh[],
                                 double inLow[],
                                 double inClose[],
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int patternIdx = 0;
      int patternResult = 0;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhikkakemodLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<(startIdx-3)) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      patternIdx = 0;
      patternResult = 0;
      i = (startIdx-3);
      while( (i<startIdx) ) {
         double _candleaverage_1;
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
         double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
         double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double _candlerange_4;
         switch( Near_rangeType )
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
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_5-_candlerange_6);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_7;
         double _candlerange_9;
         switch( Near_rangeType )
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
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
         double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_11-_candlerange_12);
         NearTrailingIdx += 1;
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhikkakemodLogic( int startIdx,
                                      int endIdx,
                                      double inOpen[],
                                      double inHigh[],
                                      double inLow[],
                                      double inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int patternIdx = 0;
      int patternResult = 0;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdlhikkakemodLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<(startIdx-3)) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      patternIdx = 0;
      patternResult = 0;
      i = (startIdx-3);
      while( (i<startIdx) ) {
         double _candleaverage_1;
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
         double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
         double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double _candlerange_4;
         switch( Near_rangeType )
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
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_5-_candlerange_6);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_7;
         double _candlerange_9;
         switch( Near_rangeType )
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
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
         double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_11-_candlerange_12);
         NearTrailingIdx += 1;
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhikkakemod( int startIdx,
                                 int endIdx,
                                 float inOpen[],
                                 float inHigh[],
                                 float inLow[],
                                 float inClose[],
                                 MInteger outBegIdx,
                                 MInteger outNBElement,
                                 int outInteger[] )
   {
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int patternIdx = 0;
      int patternResult = 0;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdlhikkakemodLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<(startIdx-3)) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      patternIdx = 0;
      patternResult = 0;
      i = (startIdx-3);
      while( (i<startIdx) ) {
         double _candleaverage_1;
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
         double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
         double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double _candlerange_4;
         switch( Near_rangeType )
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
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_5-_candlerange_6);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_7;
         double _candlerange_9;
         switch( Near_rangeType )
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
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
         double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_11-_candlerange_12);
         NearTrailingIdx += 1;
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdlhikkakemodLogic( int startIdx,
                                      int endIdx,
                                      float inOpen[],
                                      float inHigh[],
                                      float inLow[],
                                      float inClose[],
                                      MInteger outBegIdx,
                                      MInteger outNBElement,
                                      int outInteger[] )
   {
      double NearPeriodTotal = 0;
      int i = 0;
      int outIdx = 0;
      int NearTrailingIdx = 0;
      int lookbackTotal = 0;
      int patternIdx = 0;
      int patternResult = 0;
      int Near_rangeType = this.candleSettings.near.rangeType;
      int Near_avgPeriod = this.candleSettings.near.avgPeriod;
      double Near_factor = this.candleSettings.near.factor;
      lookbackTotal = cdlhikkakemodLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      NearPeriodTotal = 0;
      NearTrailingIdx = ((startIdx-3)-Near_avgPeriod);
      i = NearTrailingIdx;
      while( (i<(startIdx-3)) ) {
         double _candlerange_0;
         switch( Near_rangeType )
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
         NearPeriodTotal += _candlerange_0;
         i += 1;
      }
      patternIdx = 0;
      patternResult = 0;
      i = (startIdx-3);
      while( (i<startIdx) ) {
         double _candleaverage_1;
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
         double avg_1 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_3));
         double divisor_1 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_1 = ((Near_factor*avg_1)/divisor_1);
         double _candleaverage_2;
         double _candlerange_4;
         switch( Near_rangeType )
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
         double avg_2 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_4));
         double divisor_2 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((Near_factor*avg_2)/divisor_2);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_1)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_2))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_6;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_6 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_5-_candlerange_6);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         double _candleaverage_7;
         double _candlerange_9;
         switch( Near_rangeType )
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
         double avg_7 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_9));
         double divisor_7 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_7 = ((Near_factor*avg_7)/divisor_7);
         double _candleaverage_8;
         double _candlerange_10;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_10 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_10 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_10 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_10 = 0.0;
            break;
         }
         double avg_8 = (((Near_avgPeriod!=0)) ? ((NearPeriodTotal/Near_avgPeriod)) : (_candlerange_10));
         double divisor_8 = (((Near_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_8 = ((Near_factor*avg_8)/divisor_8);
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+_candleaverage_7)))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-_candleaverage_8))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_11;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_11 = Math.abs((inClose[(i-2)]-inOpen[(i-2)]));
            break;
         case 1:
            _candlerange_11 = (inHigh[(i-2)]-inLow[(i-2)]);
            break;
         case 2:
            _candlerange_11 = ((inHigh[(i-2)]-inLow[(i-2)])-Math.abs((inClose[(i-2)]-inOpen[(i-2)])));
            break;
         default:
            _candlerange_11 = 0.0;
            break;
         }
         double _candlerange_12;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_12 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_12 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_12 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_12 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_11-_candlerange_12);
         NearTrailingIdx += 1;
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
