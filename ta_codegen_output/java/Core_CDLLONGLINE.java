/* Generated */
   public int cdllonglineLookback( )
   {
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      return Math.max(BodyLong_avgPeriod, ShadowShort_avgPeriod) ;

   }
   public RetCode cdllongline( int startIdx,
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
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdllonglineLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
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
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))>_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_4)) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowShort_rangeType )
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
         double _candlerange_8;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdllonglineLogic( int startIdx,
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
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      lookbackTotal = cdllonglineLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
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
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))>_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_4)) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowShort_rangeType )
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
         double _candlerange_8;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdllongline( int startIdx,
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
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      lookbackTotal = cdllonglineLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
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
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))>_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_4)) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowShort_rangeType )
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
         double _candlerange_8;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode cdllonglineLogic( int startIdx,
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
      double ShadowPeriodTotal;
      int i;
      int outIdx;
      int BodyTrailingIdx;
      int ShadowTrailingIdx;
      int lookbackTotal;
      int BodyLong_rangeType = this.candleSettings.bodyLong.rangeType;
      int BodyLong_avgPeriod = this.candleSettings.bodyLong.avgPeriod;
      double BodyLong_factor = this.candleSettings.bodyLong.factor;
      int ShadowShort_rangeType = this.candleSettings.shadowShort.rangeType;
      int ShadowShort_avgPeriod = this.candleSettings.shadowShort.avgPeriod;
      double ShadowShort_factor = this.candleSettings.shadowShort.factor;
      lookbackTotal = cdllonglineLookback();
      if( (startIdx<lookbackTotal) ) {
         startIdx = lookbackTotal;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      BodyPeriodTotal = 0;
      BodyTrailingIdx = (startIdx-BodyLong_avgPeriod);
      ShadowPeriodTotal = 0;
      ShadowTrailingIdx = (startIdx-ShadowShort_avgPeriod);
      i = BodyTrailingIdx;
      while( (i<startIdx) ) {
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
         BodyPeriodTotal += _candlerange_0;
         i += 1;
      }
      i = ShadowTrailingIdx;
      while( (i<startIdx) ) {
         double _candlerange_1;
         switch( ShadowShort_rangeType )
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
         ShadowPeriodTotal += _candlerange_1;
         i += 1;
      }
      outIdx = 0;
      do {
         double _candleaverage_2;
         double avg_2 = (((BodyLong_avgPeriod!=0)) ? ((BodyPeriodTotal/BodyLong_avgPeriod)) : (ta_candlerange(BodyLong_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_2 = (((BodyLong_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_2 = ((BodyLong_factor*avg_2)/divisor_2);
         double _candleaverage_3;
         double avg_3 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_3 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_3 = ((ShadowShort_factor*avg_3)/divisor_3);
         double _candleaverage_4;
         double avg_4 = (((ShadowShort_avgPeriod!=0)) ? ((ShadowPeriodTotal/ShadowShort_avgPeriod)) : (ta_candlerange(ShadowShort_rangeType, inOpen[i], inHigh[i], inLow[i], inClose[i])));
         double divisor_4 = (((ShadowShort_rangeType==2)) ? (2.0) : (1.0));
         _candleaverage_4 = ((ShadowShort_factor*avg_4)/divisor_4);
         if( (((Math.abs((inClose[i]-inOpen[i]))>_candleaverage_2)&&((inHigh[i]-(((inClose[i]>=inOpen[i])) ? (inClose[i]) : (inOpen[i])))<_candleaverage_3))&&(((((inClose[i]>=inOpen[i])) ? (inOpen[i]) : (inClose[i]))-inLow[i])<_candleaverage_4)) ) {
            outInteger[outIdx++] = ((((inClose[i]>=inOpen[i])) ? (1) : ((0-1)))*100);
         } else {
            outInteger[outIdx++] = 0;
         }
         double _candlerange_5;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_5 = Math.abs((inClose[i]-inOpen[i]));
            break;
         case 1:
            _candlerange_5 = (inHigh[i]-inLow[i]);
            break;
         case 2:
            _candlerange_5 = ((inHigh[i]-inLow[i])-Math.abs((inClose[i]-inOpen[i])));
            break;
         default:
            _candlerange_5 = 0.0;
            break;
         }
         double _candlerange_6;
         switch( BodyLong_rangeType )
         {
         case 0:
            _candlerange_6 = Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx]));
            break;
         case 1:
            _candlerange_6 = (inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx]);
            break;
         case 2:
            _candlerange_6 = ((inHigh[BodyTrailingIdx]-inLow[BodyTrailingIdx])-Math.abs((inClose[BodyTrailingIdx]-inOpen[BodyTrailingIdx])));
            break;
         default:
            _candlerange_6 = 0.0;
            break;
         }
         BodyPeriodTotal += (_candlerange_5-_candlerange_6);
         double _candlerange_7;
         switch( ShadowShort_rangeType )
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
         double _candlerange_8;
         switch( ShadowShort_rangeType )
         {
         case 0:
            _candlerange_8 = Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx]));
            break;
         case 1:
            _candlerange_8 = (inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx]);
            break;
         case 2:
            _candlerange_8 = ((inHigh[ShadowTrailingIdx]-inLow[ShadowTrailingIdx])-Math.abs((inClose[ShadowTrailingIdx]-inOpen[ShadowTrailingIdx])));
            break;
         default:
            _candlerange_8 = 0.0;
            break;
         }
         ShadowPeriodTotal += (_candlerange_7-_candlerange_8);
         i += 1;
         BodyTrailingIdx += 1;
         ShadowTrailingIdx += 1;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
