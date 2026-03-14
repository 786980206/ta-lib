/* Generated */
   public int betaLookback( int optInTimePeriod )
   {
      return optInTimePeriod ;

   }
   public RetCode beta( int startIdx,
                        int endIdx,
                        double inReal0[],
                        double inReal1[],
                        int optInTimePeriod,
                        MInteger outBegIdx,
                        MInteger outNBElement,
                        double outReal[] )
   {
      double S_xx;
      double S_xy;
      double S_x;
      double S_y;
      double last_price_x;
      double last_price_y;
      double trailing_last_price_x;
      double trailing_last_price_y;
      double tmp_real;
      double x;
      double y;
      double n;
      int i;
      int outIdx;
      int trailingIdx;
      int nbInitialElementNeeded;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      S_xx = 0.0;
      S_xy = 0.0;
      S_x = 0.0;
      S_y = 0.0;
      last_price_x = 0.0;
      last_price_y = 0.0;
      trailing_last_price_x = 0.0;
      trailing_last_price_y = 0.0;
      tmp_real = 0.0;
      n = 0.0;
      nbInitialElementNeeded = optInTimePeriod;
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      trailingIdx = (startIdx-nbInitialElementNeeded);
      trailing_last_price_x = inReal0[trailingIdx];
      last_price_x = trailing_last_price_x;
      trailing_last_price_y = inReal1[trailingIdx];
      last_price_y = trailing_last_price_y;
      i = ++trailingIdx;
      while( (i<startIdx) ) {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
      }
      outIdx = 0;
      n = ((double)optInTimePeriod);
      do {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
         tmp_real = inReal0[trailingIdx];
         if( !((((0-0.00000001)<trailing_last_price_x)&&(trailing_last_price_x<0.00000001))) ) {
            x = ((tmp_real-trailing_last_price_x)/trailing_last_price_x);
         } else {
            x = 0.0;
         }
         trailing_last_price_x = tmp_real;
         tmp_real = inReal1[trailingIdx++];
         if( !((((0-0.00000001)<trailing_last_price_y)&&(trailing_last_price_y<0.00000001))) ) {
            y = ((tmp_real-trailing_last_price_y)/trailing_last_price_y);
         } else {
            y = 0.0;
         }
         trailing_last_price_y = tmp_real;
         tmp_real = ((n*S_xx)-(S_x*S_x));
         if( !((((0-0.00000001)<tmp_real)&&(tmp_real<0.00000001))) ) {
            outReal[outIdx++] = (((n*S_xy)-(S_x*S_y))/tmp_real);
         } else {
            outReal[outIdx++] = 0.0;
         }
         S_xx -= (x*x);
         S_xy -= (x*y);
         S_x -= x;
         S_y -= y;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode betaLogic( int startIdx,
                             int endIdx,
                             double inReal0[],
                             double inReal1[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      double S_xx;
      double S_xy;
      double S_x;
      double S_y;
      double last_price_x;
      double last_price_y;
      double trailing_last_price_x;
      double trailing_last_price_y;
      double tmp_real;
      double x;
      double y;
      double n;
      int i;
      int outIdx;
      int trailingIdx;
      int nbInitialElementNeeded;
      S_xx = 0.0;
      S_xy = 0.0;
      S_x = 0.0;
      S_y = 0.0;
      last_price_x = 0.0;
      last_price_y = 0.0;
      trailing_last_price_x = 0.0;
      trailing_last_price_y = 0.0;
      tmp_real = 0.0;
      n = 0.0;
      nbInitialElementNeeded = optInTimePeriod;
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      trailingIdx = (startIdx-nbInitialElementNeeded);
      trailing_last_price_x = inReal0[trailingIdx];
      last_price_x = trailing_last_price_x;
      trailing_last_price_y = inReal1[trailingIdx];
      last_price_y = trailing_last_price_y;
      i = ++trailingIdx;
      while( (i<startIdx) ) {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
      }
      outIdx = 0;
      n = ((double)optInTimePeriod);
      do {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
         tmp_real = inReal0[trailingIdx];
         if( !((((0-0.00000001)<trailing_last_price_x)&&(trailing_last_price_x<0.00000001))) ) {
            x = ((tmp_real-trailing_last_price_x)/trailing_last_price_x);
         } else {
            x = 0.0;
         }
         trailing_last_price_x = tmp_real;
         tmp_real = inReal1[trailingIdx++];
         if( !((((0-0.00000001)<trailing_last_price_y)&&(trailing_last_price_y<0.00000001))) ) {
            y = ((tmp_real-trailing_last_price_y)/trailing_last_price_y);
         } else {
            y = 0.0;
         }
         trailing_last_price_y = tmp_real;
         tmp_real = ((n*S_xx)-(S_x*S_x));
         if( !((((0-0.00000001)<tmp_real)&&(tmp_real<0.00000001))) ) {
            outReal[outIdx++] = (((n*S_xy)-(S_x*S_y))/tmp_real);
         } else {
            outReal[outIdx++] = 0.0;
         }
         S_xx -= (x*x);
         S_xy -= (x*y);
         S_x -= x;
         S_y -= y;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode beta( int startIdx,
                        int endIdx,
                        float inReal0[],
                        float inReal1[],
                        int optInTimePeriod,
                        MInteger outBegIdx,
                        MInteger outNBElement,
                        double outReal[] )
   {
      double S_xx;
      double S_xy;
      double S_x;
      double S_y;
      double last_price_x;
      double last_price_y;
      double trailing_last_price_x;
      double trailing_last_price_y;
      double tmp_real;
      double x;
      double y;
      double n;
      int i;
      int outIdx;
      int trailingIdx;
      int nbInitialElementNeeded;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      S_xx = 0.0;
      S_xy = 0.0;
      S_x = 0.0;
      S_y = 0.0;
      last_price_x = 0.0;
      last_price_y = 0.0;
      trailing_last_price_x = 0.0;
      trailing_last_price_y = 0.0;
      tmp_real = 0.0;
      n = 0.0;
      nbInitialElementNeeded = optInTimePeriod;
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      trailingIdx = (startIdx-nbInitialElementNeeded);
      trailing_last_price_x = inReal0[trailingIdx];
      last_price_x = trailing_last_price_x;
      trailing_last_price_y = inReal1[trailingIdx];
      last_price_y = trailing_last_price_y;
      i = ++trailingIdx;
      while( (i<startIdx) ) {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
      }
      outIdx = 0;
      n = ((double)optInTimePeriod);
      do {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
         tmp_real = inReal0[trailingIdx];
         if( !((((0-0.00000001)<trailing_last_price_x)&&(trailing_last_price_x<0.00000001))) ) {
            x = ((tmp_real-trailing_last_price_x)/trailing_last_price_x);
         } else {
            x = 0.0;
         }
         trailing_last_price_x = tmp_real;
         tmp_real = inReal1[trailingIdx++];
         if( !((((0-0.00000001)<trailing_last_price_y)&&(trailing_last_price_y<0.00000001))) ) {
            y = ((tmp_real-trailing_last_price_y)/trailing_last_price_y);
         } else {
            y = 0.0;
         }
         trailing_last_price_y = tmp_real;
         tmp_real = ((n*S_xx)-(S_x*S_x));
         if( !((((0-0.00000001)<tmp_real)&&(tmp_real<0.00000001))) ) {
            outReal[outIdx++] = (((n*S_xy)-(S_x*S_y))/tmp_real);
         } else {
            outReal[outIdx++] = 0.0;
         }
         S_xx -= (x*x);
         S_xy -= (x*y);
         S_x -= x;
         S_y -= y;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
   public RetCode betaLogic( int startIdx,
                             int endIdx,
                             float inReal0[],
                             float inReal1[],
                             int optInTimePeriod,
                             MInteger outBegIdx,
                             MInteger outNBElement,
                             double outReal[] )
   {
      double S_xx;
      double S_xy;
      double S_x;
      double S_y;
      double last_price_x;
      double last_price_y;
      double trailing_last_price_x;
      double trailing_last_price_y;
      double tmp_real;
      double x;
      double y;
      double n;
      int i;
      int outIdx;
      int trailingIdx;
      int nbInitialElementNeeded;
      S_xx = 0.0;
      S_xy = 0.0;
      S_x = 0.0;
      S_y = 0.0;
      last_price_x = 0.0;
      last_price_y = 0.0;
      trailing_last_price_x = 0.0;
      trailing_last_price_y = 0.0;
      tmp_real = 0.0;
      n = 0.0;
      nbInitialElementNeeded = optInTimePeriod;
      if( (startIdx<nbInitialElementNeeded) ) {
         startIdx = nbInitialElementNeeded;
      }
      if( (startIdx>endIdx) ) {
         outBegIdx.value = 0;
         outNBElement.value = 0;
         return RetCode.Success ;
      }
      trailingIdx = (startIdx-nbInitialElementNeeded);
      trailing_last_price_x = inReal0[trailingIdx];
      last_price_x = trailing_last_price_x;
      trailing_last_price_y = inReal1[trailingIdx];
      last_price_y = trailing_last_price_y;
      i = ++trailingIdx;
      while( (i<startIdx) ) {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
      }
      outIdx = 0;
      n = ((double)optInTimePeriod);
      do {
         tmp_real = inReal0[i];
         if( !((((0-0.00000001)<last_price_x)&&(last_price_x<0.00000001))) ) {
            x = ((tmp_real-last_price_x)/last_price_x);
         } else {
            x = 0.0;
         }
         last_price_x = tmp_real;
         tmp_real = inReal1[i++];
         if( !((((0-0.00000001)<last_price_y)&&(last_price_y<0.00000001))) ) {
            y = ((tmp_real-last_price_y)/last_price_y);
         } else {
            y = 0.0;
         }
         last_price_y = tmp_real;
         S_xx += (x*x);
         S_xy += (x*y);
         S_x += x;
         S_y += y;
         tmp_real = inReal0[trailingIdx];
         if( !((((0-0.00000001)<trailing_last_price_x)&&(trailing_last_price_x<0.00000001))) ) {
            x = ((tmp_real-trailing_last_price_x)/trailing_last_price_x);
         } else {
            x = 0.0;
         }
         trailing_last_price_x = tmp_real;
         tmp_real = inReal1[trailingIdx++];
         if( !((((0-0.00000001)<trailing_last_price_y)&&(trailing_last_price_y<0.00000001))) ) {
            y = ((tmp_real-trailing_last_price_y)/trailing_last_price_y);
         } else {
            y = 0.0;
         }
         trailing_last_price_y = tmp_real;
         tmp_real = ((n*S_xx)-(S_x*S_x));
         if( !((((0-0.00000001)<tmp_real)&&(tmp_real<0.00000001))) ) {
            outReal[outIdx++] = (((n*S_xy)-(S_x*S_y))/tmp_real);
         } else {
            outReal[outIdx++] = 0.0;
         }
         S_xx -= (x*x);
         S_xy -= (x*y);
         S_x -= x;
         S_y -= y;
      } while( (i<=endIdx) );
      outNBElement.value = outIdx;
      outBegIdx.value = startIdx;
      return RetCode.Success ;
   }
