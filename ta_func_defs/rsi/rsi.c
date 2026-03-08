int rsi_lookback(int optInTimePeriod)
{
    int retValue;
    retValue = optInTimePeriod + TA_GetUnstablePeriod(RSI);
    if( TA_GetCompatibility() == TA_COMPATIBILITY_METASTOCK ) {
        retValue = retValue - 1;
    }
    return retValue;
}

TA_RetCode rsi_logic(int startIdx, int endIdx,
                  const double inReal[],
                  int optInTimePeriod,
                  int *outBegIdx, int *outNBElement,
                  double outReal[])
{
    size_t outIdx = 0;
    size_t today;
    size_t lookbackTotal;
    int unstablePeriod;
    int i;
    double prevGain;
    double prevLoss;
    double prevValue;
    double savePrevValue;
    double tempValue1;
    double tempValue2;

    *outBegIdx = 0;
    *outNBElement = 0;

    lookbackTotal = (size_t)rsi_lookback(optInTimePeriod);

    if( startIdx < lookbackTotal ) {
        startIdx = lookbackTotal;
    }

    if( startIdx > endIdx ) {
        return TA_SUCCESS;
    }

    outIdx = 0;

    if( optInTimePeriod == 1 ) {
        *outBegIdx = startIdx;
        i = (int)((endIdx - startIdx) + 1);
        *outNBElement = (size_t)i;
        TA_ARRAY_COPY(outReal, 0, inReal, startIdx, i);
        return TA_SUCCESS;
    }

    today = startIdx - lookbackTotal;
    prevValue = (double)inReal[today];

    unstablePeriod = TA_GetUnstablePeriod(RSI);

    if( (unstablePeriod == 0) && (TA_GetCompatibility() == TA_COMPATIBILITY_METASTOCK) ) {
        savePrevValue = prevValue;
        prevGain = 0.0;
        prevLoss = 0.0;
        for( i = optInTimePeriod; i > 0; i-- ) {
            tempValue1 = (double)inReal[today]; today = today + 1;
            tempValue2 = tempValue1 - prevValue;
            prevValue = tempValue1;
            if( tempValue2 < 0.0 ) {
                prevLoss -= tempValue2;
            } else {
                prevGain += tempValue2;
            }
        }

        tempValue1 = prevLoss / (double)optInTimePeriod;
        tempValue2 = prevGain / (double)optInTimePeriod;

        tempValue1 = tempValue2 + tempValue1;
        if( !TA_IS_ZERO(tempValue1) ) {
            outReal[outIdx] = 100.0 * (tempValue2 / tempValue1); outIdx = outIdx + 1;
        } else {
            outReal[outIdx] = 0.0; outIdx = outIdx + 1;
        }

        if( today > endIdx ) {
            *outBegIdx = startIdx;
            *outNBElement = outIdx;
            return TA_SUCCESS;
        }

        today = today - (size_t)optInTimePeriod;
        prevValue = savePrevValue;
    }

    prevGain = 0.0;
    prevLoss = 0.0;
    today = today + 1;
    for( i = optInTimePeriod; i > 0; i-- ) {
        tempValue1 = (double)inReal[today]; today = today + 1;
        tempValue2 = tempValue1 - prevValue;
        prevValue = tempValue1;
        if( tempValue2 < 0.0 ) {
            prevLoss -= tempValue2;
        } else {
            prevGain += tempValue2;
        }
    }

    prevLoss /= (double)optInTimePeriod;
    prevGain /= (double)optInTimePeriod;

    if( today > startIdx ) {
        tempValue1 = prevGain + prevLoss;
        if( !TA_IS_ZERO(tempValue1) ) {
            outReal[outIdx] = 100.0 * (prevGain / tempValue1); outIdx = outIdx + 1;
        } else {
            outReal[outIdx] = 0.0; outIdx = outIdx + 1;
        }
    } else {
        while( today < startIdx ) {
            tempValue1 = (double)inReal[today];
            tempValue2 = tempValue1 - prevValue;
            prevValue = tempValue1;

            prevLoss *= (double)(optInTimePeriod - 1);
            prevGain *= (double)(optInTimePeriod - 1);
            if( tempValue2 < 0.0 ) {
                prevLoss -= tempValue2;
            } else {
                prevGain += tempValue2;
            }

            prevLoss /= (double)optInTimePeriod;
            prevGain /= (double)optInTimePeriod;

            today = today + 1;
        }
    }

    while( today <= endIdx ) {
        tempValue1 = (double)inReal[today]; today = today + 1;
        tempValue2 = tempValue1 - prevValue;
        prevValue = tempValue1;

        prevLoss *= (double)(optInTimePeriod - 1);
        prevGain *= (double)(optInTimePeriod - 1);
        if( tempValue2 < 0.0 ) {
            prevLoss -= tempValue2;
        } else {
            prevGain += tempValue2;
        }

        prevLoss /= (double)optInTimePeriod;
        prevGain /= (double)optInTimePeriod;
        tempValue1 = prevGain + prevLoss;
        if( !TA_IS_ZERO(tempValue1) ) {
            outReal[outIdx] = 100.0 * (prevGain / tempValue1); outIdx = outIdx + 1;
        } else {
            outReal[outIdx] = 0.0; outIdx = outIdx + 1;
        }
    }

    *outBegIdx = startIdx;
    *outNBElement = outIdx;

    return TA_SUCCESS;
}
