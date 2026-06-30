/* Generated */
   public int stdDevLookback( int optInTimePeriod, double optInNbDev )
   {
      return varianceLookback(optInTimePeriod, optInNbDev) ;

   }
   public RetCode stdDev( int startIdx,
                          int endIdx,
                          double inReal[],
                          int optInTimePeriod,
                          double optInNbDev,
                          MInteger outBegIdx,
                          MInteger outNBElement,
                          double outReal[] )
   {
      int i = 0;
      RetCode retCode;
      double tempReal = 0;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      retCode = varianceUnguarded(startIdx, endIdx, inReal, optInTimePeriod, 1.0, outBegIdx, outNBElement, outReal);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      if( (optInNbDev!=1.0) ) {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = (Math.sqrt(tempReal)*optInNbDev);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      } else {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = Math.sqrt(tempReal);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      }
      return RetCode.Success ;
   }
   public RetCode stdDevUnguarded( int startIdx,
                                   int endIdx,
                                   double inReal[],
                                   int optInTimePeriod,
                                   double optInNbDev,
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   double outReal[] )
   {
      int i = 0;
      RetCode retCode;
      double tempReal = 0;
      retCode = varianceUnguarded(startIdx, endIdx, inReal, optInTimePeriod, 1.0, outBegIdx, outNBElement, outReal);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      if( (optInNbDev!=1.0) ) {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = (Math.sqrt(tempReal)*optInNbDev);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      } else {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = Math.sqrt(tempReal);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      }
      return RetCode.Success ;
   }
   public RetCode stdDev( int startIdx,
                          int endIdx,
                          float inReal[],
                          int optInTimePeriod,
                          double optInNbDev,
                          MInteger outBegIdx,
                          MInteger outNBElement,
                          double outReal[] )
   {
      int i = 0;
      RetCode retCode;
      double tempReal = 0;
      if( startIdx < 0 ) {
         return RetCode.OutOfRangeStartIndex ;
      }
      if( (endIdx < 0) || (endIdx < startIdx)) {
         return RetCode.OutOfRangeEndIndex ;
      }
      retCode = varianceUnguarded(startIdx, endIdx, inReal, optInTimePeriod, 1.0, outBegIdx, outNBElement, outReal);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      if( (optInNbDev!=1.0) ) {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = (Math.sqrt(tempReal)*optInNbDev);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      } else {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = Math.sqrt(tempReal);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      }
      return RetCode.Success ;
   }
   public RetCode stdDevUnguarded( int startIdx,
                                   int endIdx,
                                   float inReal[],
                                   int optInTimePeriod,
                                   double optInNbDev,
                                   MInteger outBegIdx,
                                   MInteger outNBElement,
                                   double outReal[] )
   {
      int i = 0;
      RetCode retCode;
      double tempReal = 0;
      retCode = varianceUnguarded(startIdx, endIdx, inReal, optInTimePeriod, 1.0, outBegIdx, outNBElement, outReal);
      if( (retCode!=RetCode.Success) ) {
         return retCode ;
      }
      if( (optInNbDev!=1.0) ) {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = (Math.sqrt(tempReal)*optInNbDev);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      } else {
         for( i = 0; (i<((int)outNBElement.value)); i += 1 ) {
            tempReal = outReal[i];
            if( !((tempReal < 0.00000000000001)) ) {
               outReal[i] = Math.sqrt(tempReal);
            } else {
               outReal[i] = ((double)0.0);
            }
         }
      }
      return RetCode.Success ;
   }
