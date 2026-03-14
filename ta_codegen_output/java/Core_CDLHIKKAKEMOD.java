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
      double NearPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int patternIdx;
      int patternResult;
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
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_2;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_1-_candlerange_2);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
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
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_3-_candlerange_4);
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
      double NearPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int patternIdx;
      int patternResult;
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
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_2;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_1-_candlerange_2);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
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
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_3-_candlerange_4);
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
      double NearPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int patternIdx;
      int patternResult;
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
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_2;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_1-_candlerange_2);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
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
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_3-_candlerange_4);
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
      double NearPeriodTotal;
      int i;
      int outIdx;
      int NearTrailingIdx;
      int lookbackTotal;
      int patternIdx;
      int patternResult;
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
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            patternIdx = 0;
         }
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
         double _candlerange_2;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_2 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_2 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_2 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_2 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_1-_candlerange_2);
         NearTrailingIdx += 1;
         i += 1;
      }
      i = startIdx;
      outIdx = 0;
      do {
         if( (((((inHigh[(i-2)]<inHigh[(i-3)])&&(inLow[(i-2)]>inLow[(i-3)]))&&(inHigh[(i-1)]<inHigh[(i-2)]))&&(inLow[(i-1)]>inLow[(i-2)]))&&((((inHigh[i]<inHigh[(i-1)])&&(inLow[i]<inLow[(i-1)]))&&(inClose[(i-2)]<=(inLow[(i-2)]+ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)]))))||(((inHigh[i]>inHigh[(i-1)])&&(inLow[i]>inLow[(i-1)]))&&(inClose[(i-2)]>=(inHigh[(i-2)]-ta_candleaverage(Near_rangeType, Near_avgPeriod, Near_factor, NearPeriodTotal, inOpen[(i-2)], inHigh[(i-2)], inLow[(i-2)], inClose[(i-2)])))))) ) {
            patternResult = (100*(((inHigh[i]<inHigh[(i-1)])) ? (1) : ((0-1))));
            patternIdx = i;
            outInteger[outIdx++] = patternResult;
         } else if( ((i<=(patternIdx+3))&&(((patternResult>0)&&(inClose[i]>inHigh[(patternIdx-1)]))||((patternResult<0)&&(inClose[i]<inLow[(patternIdx-1)])))) ) {
            outInteger[outIdx++] = (patternResult+(100*(((patternResult>0)) ? (1) : ((0-1)))));
            patternIdx = 0;
         } else {
            outInteger[outIdx++] = 0;
         }
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
         double _candlerange_4;
         switch( Near_rangeType )
         {
         case 0:
            _candlerange_4 = Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)]));
            break;
         case 1:
            _candlerange_4 = (inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)]);
            break;
         case 2:
            _candlerange_4 = ((inHigh[(NearTrailingIdx-2)]-inLow[(NearTrailingIdx-2)])-Math.abs((inClose[(NearTrailingIdx-2)]-inOpen[(NearTrailingIdx-2)])));
            break;
         default:
            _candlerange_4 = 0.0;
            break;
         }
         NearPeriodTotal += (_candlerange_3-_candlerange_4);
         NearTrailingIdx += 1;
         i += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
