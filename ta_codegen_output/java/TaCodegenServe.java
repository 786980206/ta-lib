/* Auto-generated JSON-RPC server for ta_codegen Java output.
 * Build: javac TaCodegenServe.java && java TaCodegenServe
 */
import java.io.*;
import java.util.*;

enum RetCode {
    Success, BadParam, OutOfRangeStartIndex, OutOfRangeEndIndex, AllocErr, InternalError;
    public int toInt() {
        switch(this) {
            case Success: return 0;
            case BadParam: return 2;
            case OutOfRangeStartIndex: return 12;
            case OutOfRangeEndIndex: return 13;
            case AllocErr: return 3;
            default: return 5000;
        }
    }
}

class MInteger { public int value; }

enum FuncUnstId {
    Adx, Adxr, Atr, Cmo, Dx, Ema,
    HtDcPeriod, HtDcPhase, HtPhasor, HtSine, HtTrendline, HtTrendMode,
    Imi, Kama, Mama, Mfi, MinusDI, MinusDM,
    Natr, PlusDI, PlusDM, Rsi, StochRsi, T3, None;
}

enum Compatibility {
    Default, Metastock;
}

class Core {
    int lookbackTotal, i, outIdx, trailingIdx;
    int[] unstablePeriod = new int[FuncUnstId.values().length];
    Compatibility compatibility = Compatibility.Default;
    int nbElement;

    // WARNING: ../../ta_codegen_output/java/Core_ACCBANDS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ACOS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_AD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ADD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ADOSC.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ADX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ADXR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_APO.java not found
    // WARNING: ../../ta_codegen_output/java/Core_AROON.java not found
    // WARNING: ../../ta_codegen_output/java/Core_AROONOSC.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ASIN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ATAN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ATR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_AVGDEV.java not found
    // WARNING: ../../ta_codegen_output/java/Core_AVGPRICE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_BBANDS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_BETA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_BOP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CCI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL2CROWS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3BLACKCROWS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3INSIDE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3LINESTRIKE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3OUTSIDE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3STARSINSOUTH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDL3WHITESOLDIERS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLABANDONEDBABY.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLADVANCEBLOCK.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLBELTHOLD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLBREAKAWAY.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLCLOSINGMARUBOZU.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLCONCEALBABYSWALL.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLCOUNTERATTACK.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLDARKCLOUDCOVER.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLDOJI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLDOJISTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLDRAGONFLYDOJI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLENGULFING.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLEVENINGDOJISTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLEVENINGSTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLGAPSIDESIDEWHITE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLGRAVESTONEDOJI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHAMMER.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHANGINGMAN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHARAMI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHARAMICROSS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHIGHWAVE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHIKKAKE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHIKKAKEMOD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLHOMINGPIGEON.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLIDENTICAL3CROWS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLINNECK.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLINVERTEDHAMMER.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLKICKING.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLKICKINGBYLENGTH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLLADDERBOTTOM.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLLONGLEGGEDDOJI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLLONGLINE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLMARUBOZU.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLMATCHINGLOW.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLMATHOLD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLMORNINGDOJISTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLMORNINGSTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLONNECK.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLPIERCING.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLRICKSHAWMAN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLRISEFALL3METHODS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSEPARATINGLINES.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSHOOTINGSTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSHORTLINE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSPINNINGTOP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSTALLEDPATTERN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLSTICKSANDWICH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLTAKURI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLTASUKIGAP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLTHRUSTING.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLTRISTAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLUNIQUE3RIVER.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLUPSIDEGAP2CROWS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CDLXSIDEGAP3METHODS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CEIL.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CMO.java not found
    // WARNING: ../../ta_codegen_output/java/Core_CORREL.java not found
    // WARNING: ../../ta_codegen_output/java/Core_COS.java not found
    // WARNING: ../../ta_codegen_output/java/Core_COSH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_DEMA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_DIV.java not found
    // WARNING: ../../ta_codegen_output/java/Core_DX.java not found

       public int emaLookback( int optInTimePeriod )
       {
          return ((optInTimePeriod-1)+this.unstablePeriod[FuncUnstId.Ema.ordinal()]) ;

       }
       public RetCode ema( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          double tempReal;
          double prevMA;
          int i;
          int today;
          int outIdx;
          int lookbackTotal;
          double optInK_1;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          lookbackTotal = ((int)emaLookback(optInTimePeriod));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          optInK_1 = (2.0 / ((double)(optInTimePeriod) + 1.0));
          outBegIdx.value = startIdx;
          if( (this.compatibility==Compatibility.Default) ) {
             today = (startIdx-lookbackTotal);
             i = optInTimePeriod;
             tempReal = 0;
             for( i = optInTimePeriod; (i>0); i -= 1 ) {
                tempReal += ((double)inReal[today]);
                today = (today+1);
             }
             prevMA = (tempReal/((double)optInTimePeriod));
          } else {
             prevMA = ((double)inReal[0]);
             today = 1;
          }
          while( (today<=startIdx) ) {
             prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
             today = (today+1);
          }
          outReal[0] = prevMA;
          outIdx = 1;
          while( (today<=endIdx) ) {
             prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
             today = (today+1);
             outReal[outIdx] = prevMA;
             outIdx = (outIdx+1);
          }
          outNBElement.value = outIdx;
          return RetCode.Success ;
       }
       public RetCode ema( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          double tempReal;
          double prevMA;
          int i;
          int today;
          int outIdx;
          int lookbackTotal;
          double optInK_1;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          lookbackTotal = ((int)emaLookback(optInTimePeriod));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          optInK_1 = (2.0 / ((double)(optInTimePeriod) + 1.0));
          outBegIdx.value = startIdx;
          if( (this.compatibility==Compatibility.Default) ) {
             today = (startIdx-lookbackTotal);
             i = optInTimePeriod;
             tempReal = 0;
             for( i = optInTimePeriod; (i>0); i -= 1 ) {
                tempReal += ((double)inReal[today]);
                today = (today+1);
             }
             prevMA = (tempReal/((double)optInTimePeriod));
          } else {
             prevMA = ((double)inReal[0]);
             today = 1;
          }
          while( (today<=startIdx) ) {
             prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
             today = (today+1);
          }
          outReal[0] = prevMA;
          outIdx = 1;
          while( (today<=endIdx) ) {
             prevMA = (((((double)inReal[today])-prevMA)*optInK_1)+prevMA);
             today = (today+1);
             outReal[outIdx] = prevMA;
             outIdx = (outIdx+1);
          }
          outNBElement.value = outIdx;
          return RetCode.Success ;
       }
    // WARNING: ../../ta_codegen_output/java/Core_EXP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_FLOOR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_DCPERIOD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_DCPHASE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_PHASOR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_SINE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_TRENDLINE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_HT_TRENDMODE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_IMI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_KAMA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LINEARREG.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LINEARREG_ANGLE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LINEARREG_INTERCEPT.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LINEARREG_SLOPE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_LOG10.java not found

       public int maLookback( int optInTimePeriod, MAType optInMAType )
       {
          int retValue;
          if( (optInTimePeriod<=1) ) {
             return 0 ;
          }
          switch( optInMAType )
          {
          case MAType.Sma:
             retValue = smaLookback(optInTimePeriod);
             break;
          case MAType.Ema:
             retValue = emaLookback(optInTimePeriod);
             break;
          default:
             retValue = 0;
             break;
          }
          return retValue ;

       }
       public RetCode ma( int startIdx,
                          int endIdx,
                          double inReal[],
                          int optInTimePeriod,
                          MAType optInMAType,
                          MInteger outBegIdx,
                          MInteger outNBElement,
                          double outReal[] )
       {
          int nbElement;
          int outIdx;
          int todayIdx;
          RetCode retCode;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          if( (optInTimePeriod==1) ) {
             nbElement = ((endIdx-startIdx)+1);
             outNBElement.value = nbElement;
             todayIdx = startIdx;
             outIdx = 0;
             while( (outIdx<nbElement) ) {
                outReal[outIdx] = ((double)inReal[todayIdx]);
                outIdx = (outIdx+1);
                todayIdx = (todayIdx+1);
             }
             outBegIdx.value = startIdx;
             return RetCode.Success ;
          }
          switch( optInMAType )
          {
          case MAType.Sma:
             retCode = sma(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
             break;
          case MAType.Ema:
             retCode = ema(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
             break;
          default:
             retCode = RetCode.BadParam;
             break;
          }
          return retCode ;
       }
       public RetCode ma( int startIdx,
                          int endIdx,
                          float inReal[],
                          int optInTimePeriod,
                          MAType optInMAType,
                          MInteger outBegIdx,
                          MInteger outNBElement,
                          double outReal[] )
       {
          int nbElement;
          int outIdx;
          int todayIdx;
          RetCode retCode;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          if( (optInTimePeriod==1) ) {
             nbElement = ((endIdx-startIdx)+1);
             outNBElement.value = nbElement;
             todayIdx = startIdx;
             outIdx = 0;
             while( (outIdx<nbElement) ) {
                outReal[outIdx] = ((double)inReal[todayIdx]);
                outIdx = (outIdx+1);
                todayIdx = (todayIdx+1);
             }
             outBegIdx.value = startIdx;
             return RetCode.Success ;
          }
          switch( optInMAType )
          {
          case MAType.Sma:
             retCode = sma(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
             break;
          case MAType.Ema:
             retCode = ema(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
             break;
          default:
             retCode = RetCode.BadParam;
             break;
          }
          return retCode ;
       }
    // WARNING: ../../ta_codegen_output/java/Core_MACD.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MACDEXT.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MACDFIX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MAMA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MAVP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MAX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MAXINDEX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MEDPRICE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MFI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MIDPOINT.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MIDPRICE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MIN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MININDEX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MINMAX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MINMAXINDEX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MINUS_DI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MINUS_DM.java not found
    // WARNING: ../../ta_codegen_output/java/Core_MOM.java not found

       public int multLookback( )
       {
          return 0 ;

       }
       public RetCode mult( int startIdx,
                            int endIdx,
                            double inReal0[],
                            double inReal1[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
       {
          int outIdx;
          int i;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          outIdx = 0;
          i = ((int)startIdx);
          while( (i<=((int)endIdx)) ) {
             outReal[outIdx] = (inReal0[i]*inReal1[i]);
             outIdx += 1;
             i += 1;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
       public RetCode mult( int startIdx,
                            int endIdx,
                            float inReal0[],
                            float inReal1[],
                            MInteger outBegIdx,
                            MInteger outNBElement,
                            double outReal[] )
       {
          int outIdx;
          int i;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          outIdx = 0;
          i = ((int)startIdx);
          while( (i<=((int)endIdx)) ) {
             outReal[outIdx] = (inReal0[i]*inReal1[i]);
             outIdx += 1;
             i += 1;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
    // WARNING: ../../ta_codegen_output/java/Core_NATR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_NVI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_OBV.java not found
    // WARNING: ../../ta_codegen_output/java/Core_PLUS_DI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_PLUS_DM.java not found
    // WARNING: ../../ta_codegen_output/java/Core_PPO.java not found
    // WARNING: ../../ta_codegen_output/java/Core_PVI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ROC.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ROCP.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ROCR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ROCR100.java not found

       public int rsiLookback( int optInTimePeriod )
       {
          int retValue;
          retValue = (optInTimePeriod+this.unstablePeriod[FuncUnstId.Rsi.ordinal()]);
          if( (this.compatibility==Compatibility.Metastock) ) {
             retValue = (retValue-1);
          }
          return retValue ;

       }
       public RetCode rsi( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          int outIdx;
          int today;
          int lookbackTotal;
          int unstablePeriod;
          int i;
          double prevGain;
          double prevLoss;
          double prevValue;
          double savePrevValue;
          double tempValue1;
          double tempValue2;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          outIdx = 0;
          outBegIdx.value = 0;
          outNBElement.value = 0;
          lookbackTotal = ((int)rsiLookback(optInTimePeriod));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             return RetCode.Success ;
          }
          outIdx = 0;
          if( (optInTimePeriod==1) ) {
             outBegIdx.value = startIdx;
             i = ((int)((endIdx-startIdx)+1));
             outNBElement.value = ((int)i);
             System.arraycopy(inReal,startIdx,outReal,0,i);
             return RetCode.Success ;
          }
          today = (startIdx-lookbackTotal);
          prevValue = ((double)inReal[today]);
          unstablePeriod = this.unstablePeriod[FuncUnstId.Rsi.ordinal()];
          if( ((unstablePeriod==0)&&(this.compatibility==Compatibility.Metastock)) ) {
             savePrevValue = prevValue;
             prevGain = 0;
             prevLoss = 0;
             for( i = optInTimePeriod; (i>0); i -= 1 ) {
                tempValue1 = ((double)inReal[today]);
                today = (today+1);
                tempValue2 = (tempValue1-prevValue);
                prevValue = tempValue1;
                if( (tempValue2<0) ) {
                   prevLoss -= tempValue2;
                } else {
                   prevGain += tempValue2;
                }
             }
             tempValue1 = (prevLoss/((double)optInTimePeriod));
             tempValue2 = (prevGain/((double)optInTimePeriod));
             tempValue1 = (tempValue2+tempValue1);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(tempValue2/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
             if( (today>endIdx) ) {
                outBegIdx.value = startIdx;
                outNBElement.value = outIdx;
                return RetCode.Success ;
             }
             today = (today-((int)optInTimePeriod));
             prevValue = savePrevValue;
          }
          prevGain = 0;
          prevLoss = 0;
          today = (today+1);
          for( i = optInTimePeriod; (i>0); i -= 1 ) {
             tempValue1 = ((double)inReal[today]);
             today = (today+1);
             tempValue2 = (tempValue1-prevValue);
             prevValue = tempValue1;
             if( (tempValue2<0) ) {
                prevLoss -= tempValue2;
             } else {
                prevGain += tempValue2;
             }
          }
          prevLoss /= ((double)optInTimePeriod);
          prevGain /= ((double)optInTimePeriod);
          if( (today>startIdx) ) {
             tempValue1 = (prevGain+prevLoss);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(prevGain/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
          } else {
             while( (today<startIdx) ) {
                tempValue1 = ((double)inReal[today]);
                tempValue2 = (tempValue1-prevValue);
                prevValue = tempValue1;
                prevLoss *= ((double)(optInTimePeriod-1));
                prevGain *= ((double)(optInTimePeriod-1));
                if( (tempValue2<0) ) {
                   prevLoss -= tempValue2;
                } else {
                   prevGain += tempValue2;
                }
                prevLoss /= ((double)optInTimePeriod);
                prevGain /= ((double)optInTimePeriod);
                today = (today+1);
             }
          }
          while( (today<=endIdx) ) {
             tempValue1 = ((double)inReal[today]);
             today = (today+1);
             tempValue2 = (tempValue1-prevValue);
             prevValue = tempValue1;
             prevLoss *= ((double)(optInTimePeriod-1));
             prevGain *= ((double)(optInTimePeriod-1));
             if( (tempValue2<0) ) {
                prevLoss -= tempValue2;
             } else {
                prevGain += tempValue2;
             }
             prevLoss /= ((double)optInTimePeriod);
             prevGain /= ((double)optInTimePeriod);
             tempValue1 = (prevGain+prevLoss);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(prevGain/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
          }
          outBegIdx.value = startIdx;
          outNBElement.value = outIdx;
          return RetCode.Success ;
       }
       public RetCode rsi( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          int outIdx;
          int today;
          int lookbackTotal;
          int unstablePeriod;
          int i;
          double prevGain;
          double prevLoss;
          double prevValue;
          double savePrevValue;
          double tempValue1;
          double tempValue2;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          outIdx = 0;
          outBegIdx.value = 0;
          outNBElement.value = 0;
          lookbackTotal = ((int)rsiLookback(optInTimePeriod));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             return RetCode.Success ;
          }
          outIdx = 0;
          if( (optInTimePeriod==1) ) {
             outBegIdx.value = startIdx;
             i = ((int)((endIdx-startIdx)+1));
             outNBElement.value = ((int)i);
             System.arraycopy(inReal,startIdx,outReal,0,i);
             return RetCode.Success ;
          }
          today = (startIdx-lookbackTotal);
          prevValue = ((double)inReal[today]);
          unstablePeriod = this.unstablePeriod[FuncUnstId.Rsi.ordinal()];
          if( ((unstablePeriod==0)&&(this.compatibility==Compatibility.Metastock)) ) {
             savePrevValue = prevValue;
             prevGain = 0;
             prevLoss = 0;
             for( i = optInTimePeriod; (i>0); i -= 1 ) {
                tempValue1 = ((double)inReal[today]);
                today = (today+1);
                tempValue2 = (tempValue1-prevValue);
                prevValue = tempValue1;
                if( (tempValue2<0) ) {
                   prevLoss -= tempValue2;
                } else {
                   prevGain += tempValue2;
                }
             }
             tempValue1 = (prevLoss/((double)optInTimePeriod));
             tempValue2 = (prevGain/((double)optInTimePeriod));
             tempValue1 = (tempValue2+tempValue1);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(tempValue2/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
             if( (today>endIdx) ) {
                outBegIdx.value = startIdx;
                outNBElement.value = outIdx;
                return RetCode.Success ;
             }
             today = (today-((int)optInTimePeriod));
             prevValue = savePrevValue;
          }
          prevGain = 0;
          prevLoss = 0;
          today = (today+1);
          for( i = optInTimePeriod; (i>0); i -= 1 ) {
             tempValue1 = ((double)inReal[today]);
             today = (today+1);
             tempValue2 = (tempValue1-prevValue);
             prevValue = tempValue1;
             if( (tempValue2<0) ) {
                prevLoss -= tempValue2;
             } else {
                prevGain += tempValue2;
             }
          }
          prevLoss /= ((double)optInTimePeriod);
          prevGain /= ((double)optInTimePeriod);
          if( (today>startIdx) ) {
             tempValue1 = (prevGain+prevLoss);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(prevGain/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
          } else {
             while( (today<startIdx) ) {
                tempValue1 = ((double)inReal[today]);
                tempValue2 = (tempValue1-prevValue);
                prevValue = tempValue1;
                prevLoss *= ((double)(optInTimePeriod-1));
                prevGain *= ((double)(optInTimePeriod-1));
                if( (tempValue2<0) ) {
                   prevLoss -= tempValue2;
                } else {
                   prevGain += tempValue2;
                }
                prevLoss /= ((double)optInTimePeriod);
                prevGain /= ((double)optInTimePeriod);
                today = (today+1);
             }
          }
          while( (today<=endIdx) ) {
             tempValue1 = ((double)inReal[today]);
             today = (today+1);
             tempValue2 = (tempValue1-prevValue);
             prevValue = tempValue1;
             prevLoss *= ((double)(optInTimePeriod-1));
             prevGain *= ((double)(optInTimePeriod-1));
             if( (tempValue2<0) ) {
                prevLoss -= tempValue2;
             } else {
                prevGain += tempValue2;
             }
             prevLoss /= ((double)optInTimePeriod);
             prevGain /= ((double)optInTimePeriod);
             tempValue1 = (prevGain+prevLoss);
             if( !(((-0.00000000000001 < tempValue1) && (tempValue1 < 0.00000000000001))) ) {
                outReal[outIdx] = (100*(prevGain/tempValue1));
                outIdx = (outIdx+1);
             } else {
                outReal[outIdx] = 0;
                outIdx = (outIdx+1);
             }
          }
          outBegIdx.value = startIdx;
          outNBElement.value = outIdx;
          return RetCode.Success ;
       }
    // WARNING: ../../ta_codegen_output/java/Core_SAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_SAREXT.java not found
    // WARNING: ../../ta_codegen_output/java/Core_SIN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_SINH.java not found

       public int smaLookback( int optInTimePeriod )
       {
          return (optInTimePeriod-1) ;

       }
       public RetCode sma( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          double periodTotal;
          double tempReal;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          periodTotal = 0;
          lookbackTotal = ((int)(optInTimePeriod-1));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          periodTotal = 0;
          trailingIdx = (startIdx-lookbackTotal);
          i = trailingIdx;
          if( (optInTimePeriod>1) ) {
             while( (i<startIdx) ) {
                periodTotal += ((double)inReal[i]);
                i += 1;
             }
          }
          outIdx = 0;
          while( (i<=endIdx) ) {
             periodTotal += ((double)inReal[i]);
             i += 1;
             tempReal = periodTotal;
             periodTotal -= ((double)inReal[trailingIdx]);
             trailingIdx += 1;
             outReal[outIdx] = (tempReal/((double)optInTimePeriod));
             outIdx += 1;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
       public RetCode sma( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          double periodTotal;
          double tempReal;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          periodTotal = 0;
          lookbackTotal = ((int)(optInTimePeriod-1));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          periodTotal = 0;
          trailingIdx = (startIdx-lookbackTotal);
          i = trailingIdx;
          if( (optInTimePeriod>1) ) {
             while( (i<startIdx) ) {
                periodTotal += ((double)inReal[i]);
                i += 1;
             }
          }
          outIdx = 0;
          while( (i<=endIdx) ) {
             periodTotal += ((double)inReal[i]);
             i += 1;
             tempReal = periodTotal;
             periodTotal -= ((double)inReal[trailingIdx]);
             trailingIdx += 1;
             outReal[outIdx] = (tempReal/((double)optInTimePeriod));
             outIdx += 1;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
    // WARNING: ../../ta_codegen_output/java/Core_SQRT.java not found
    // WARNING: ../../ta_codegen_output/java/Core_STDDEV.java not found
    // WARNING: ../../ta_codegen_output/java/Core_STOCH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_STOCHF.java not found
    // WARNING: ../../ta_codegen_output/java/Core_STOCHRSI.java not found
    // WARNING: ../../ta_codegen_output/java/Core_SUB.java not found
    // WARNING: ../../ta_codegen_output/java/Core_SUM.java not found
    // WARNING: ../../ta_codegen_output/java/Core_T3.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TAN.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TANH.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TEMA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TRANGE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TRIMA.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TRIX.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TSF.java not found
    // WARNING: ../../ta_codegen_output/java/Core_TYPPRICE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_ULTOSC.java not found
    // WARNING: ../../ta_codegen_output/java/Core_VAR.java not found
    // WARNING: ../../ta_codegen_output/java/Core_WCLPRICE.java not found
    // WARNING: ../../ta_codegen_output/java/Core_WILLR.java not found

       public int wmaLookback( int optInTimePeriod )
       {
          return (optInTimePeriod-1) ;

       }
       public RetCode wma( int startIdx,
                           int endIdx,
                           double inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          int divider;
          double periodSum;
          double periodSub;
          double tempReal;
          double trailingValue;
          int inIdx;
          int outIdx;
          int trailingIdx;
          int lookbackTotal;
          int i;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          periodSum = 0;
          periodSub = 0;
          lookbackTotal = ((int)(optInTimePeriod-1));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          if( (optInTimePeriod==1) ) {
             outNBElement.value = nbElement;
             outBegIdx.value = startIdx;
             System.arraycopy(inReal,startIdx,outReal,0,nbElement);
             return RetCode.Success ;
          }
          divider = ((optInTimePeriod*(optInTimePeriod+1))/2);
          outIdx = 0;
          trailingIdx = (startIdx-lookbackTotal);
          inIdx = trailingIdx;
          i = 1;
          while( (inIdx<startIdx) ) {
             tempReal = ((double)inReal[inIdx]);
             periodSub += tempReal;
             periodSum += (tempReal*((double)i));
             i += 1;
             inIdx += 1;
          }
          trailingValue = 0;
          while( (inIdx<=endIdx) ) {
             tempReal = ((double)inReal[inIdx]);
             inIdx += 1;
             periodSub += tempReal;
             periodSub -= trailingValue;
             periodSum += (tempReal*((double)optInTimePeriod));
             trailingValue = ((double)inReal[trailingIdx]);
             trailingIdx += 1;
             outReal[outIdx] = (periodSum/((double)divider));
             outIdx += 1;
             periodSum -= periodSub;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
       public RetCode wma( int startIdx,
                           int endIdx,
                           float inReal[],
                           int optInTimePeriod,
                           MInteger outBegIdx,
                           MInteger outNBElement,
                           double outReal[] )
       {
          int divider;
          double periodSum;
          double periodSub;
          double tempReal;
          double trailingValue;
          int inIdx;
          int outIdx;
          int trailingIdx;
          int lookbackTotal;
          int i;
          if( startIdx < 0 ) {
             return RetCode.OutOfRangeStartIndex ;
          }
          if( (endIdx < 0) || (endIdx < startIdx)) {
             return RetCode.OutOfRangeEndIndex ;
          }
          periodSum = 0;
          periodSub = 0;
          lookbackTotal = ((int)(optInTimePeriod-1));
          if( (startIdx<lookbackTotal) ) {
             startIdx = lookbackTotal;
          }
          if( (startIdx>endIdx) ) {
             outBegIdx.value = 0;
             outNBElement.value = 0;
             return RetCode.Success ;
          }
          if( (optInTimePeriod==1) ) {
             outNBElement.value = nbElement;
             outBegIdx.value = startIdx;
             System.arraycopy(inReal,startIdx,outReal,0,nbElement);
             return RetCode.Success ;
          }
          divider = ((optInTimePeriod*(optInTimePeriod+1))/2);
          outIdx = 0;
          trailingIdx = (startIdx-lookbackTotal);
          inIdx = trailingIdx;
          i = 1;
          while( (inIdx<startIdx) ) {
             tempReal = ((double)inReal[inIdx]);
             periodSub += tempReal;
             periodSum += (tempReal*((double)i));
             i += 1;
             inIdx += 1;
          }
          trailingValue = 0;
          while( (inIdx<=endIdx) ) {
             tempReal = ((double)inReal[inIdx]);
             inIdx += 1;
             periodSub += tempReal;
             periodSub -= trailingValue;
             periodSum += (tempReal*((double)optInTimePeriod));
             trailingValue = ((double)inReal[trailingIdx]);
             trailingIdx += 1;
             outReal[outIdx] = (periodSum/((double)divider));
             outIdx += 1;
             periodSum -= periodSub;
          }
          outNBElement.value = outIdx;
          outBegIdx.value = startIdx;
          return RetCode.Success ;
       }
}

public class TaCodegenServe {
    static Core core = new Core();

    static int jsonInt(String json, String field) {
        int idx = json.indexOf('"' + field + '"');
        if (idx < 0) return 0;
        idx = json.indexOf(':', idx) + 1;
        while (idx < json.length() && json.charAt(idx) == ' ') idx++;
        int end = idx;
        while (end < json.length() && "0123456789-".indexOf(json.charAt(end)) >= 0) end++;
        return Integer.parseInt(json.substring(idx, end));
    }

    static double jsonDouble(String json, String field) {
        int idx = json.indexOf('"' + field + '"');
        if (idx < 0) return 0.0;
        idx = json.indexOf(':', idx) + 1;
        while (idx < json.length() && json.charAt(idx) == ' ') idx++;
        int end = idx;
        while (end < json.length() && "0123456789-.eE+".indexOf(json.charAt(end)) >= 0) end++;
        return Double.parseDouble(json.substring(idx, end));
    }

    static double[] jsonDoubleArray(String json, String field) {
        int idx = json.indexOf('"' + field + '"');
        if (idx < 0) return new double[0];
        idx = json.indexOf('[', idx);
        int end = json.indexOf(']', idx);
        String inner = json.substring(idx + 1, end).trim();
        if (inner.isEmpty()) return new double[0];
        String[] parts = inner.split(",");
        double[] result = new double[parts.length];
        for (int i = 0; i < parts.length; i++)
            result[i] = Double.parseDouble(parts[i].trim());
        return result;
    }

    static String doubleArrayToJson(double[] arr, int count) {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < count; i++) {
            if (i > 0) sb.append(',');
            sb.append(arr[i]);
        }
        sb.append(']');
        return sb.toString();
    }

    static String intArrayToJson(int[] arr, int count) {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < count; i++) {
            if (i > 0) sb.append(',');
            sb.append(arr[i]);
        }
        sb.append(']');
        return sb.toString();
    }

    static String handleRequest(String json) {
        if (json.contains("\"TA_ACCBANDS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            double[] outArr2 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.accbands(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0, outArr1, outArr2);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"outReal2\":").append(doubleArrayToJson(outArr2, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ACOS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.acos(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_AD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ad(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                inVolume,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ADD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.add(
                startIdx, endIdx,
                inReal0,
                inReal1,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ADOSC\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            int optInFastPeriod = jsonInt(json, "optInFastPeriod");
            int optInSlowPeriod = jsonInt(json, "optInSlowPeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.adosc(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                inVolume,
                optInFastPeriod,
                optInSlowPeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ADX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[0] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.adx(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ADXR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[1] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.adxr(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_APO\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInFastPeriod = jsonInt(json, "optInFastPeriod");
            int optInSlowPeriod = jsonInt(json, "optInSlowPeriod");
            int optInMAType = jsonInt(json, "optInMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.apo(
                startIdx, endIdx,
                inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInMAType,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_AROON\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.aroon(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_AROONOSC\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.aroonosc(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ASIN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.asin(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ATAN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.atan(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ATR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[2] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.atr(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_AVGDEV\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.avgdev(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_AVGPRICE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.avgprice(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_BBANDS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double optInNbDevUp = jsonDouble(json, "optInNbDevUp");
            double optInNbDevDn = jsonDouble(json, "optInNbDevDn");
            int optInMAType = jsonInt(json, "optInMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            double[] outArr2 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.bbands(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInNbDevUp,
                optInNbDevDn,
                optInMAType,
                outBegIdx, outNBElement, outArr0, outArr1, outArr2);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"outReal2\":").append(doubleArrayToJson(outArr2, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_BETA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.beta(
                startIdx, endIdx,
                inReal0,
                inReal1,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_BOP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.bop(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CCI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cci(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL2CROWS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl2crows(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3BLACKCROWS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3blackcrows(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3INSIDE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3inside(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3LINESTRIKE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3linestrike(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3OUTSIDE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3outside(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3STARSINSOUTH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3starsinsouth(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDL3WHITESOLDIERS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdl3whitesoldiers(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLABANDONEDBABY\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlabandonedbaby(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLADVANCEBLOCK\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdladvanceblock(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLBELTHOLD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlbelthold(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLBREAKAWAY\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlbreakaway(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLCLOSINGMARUBOZU\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlclosingmarubozu(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLCONCEALBABYSWALL\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlconcealbabyswall(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLCOUNTERATTACK\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlcounterattack(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLDARKCLOUDCOVER\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdldarkcloudcover(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLDOJI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdldoji(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLDOJISTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdldojistar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLDRAGONFLYDOJI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdldragonflydoji(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLENGULFING\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlengulfing(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLEVENINGDOJISTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdleveningdojistar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLEVENINGSTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdleveningstar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLGAPSIDESIDEWHITE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlgapsidesidewhite(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLGRAVESTONEDOJI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlgravestonedoji(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHAMMER\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhammer(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHANGINGMAN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhangingman(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHARAMI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlharami(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHARAMICROSS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlharamicross(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHIGHWAVE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhighwave(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHIKKAKE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhikkake(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHIKKAKEMOD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhikkakemod(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLHOMINGPIGEON\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlhomingpigeon(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLIDENTICAL3CROWS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlidentical3crows(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLINNECK\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlinneck(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLINVERTEDHAMMER\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlinvertedhammer(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLKICKING\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlkicking(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLKICKINGBYLENGTH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlkickingbylength(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLLADDERBOTTOM\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlladderbottom(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLLONGLEGGEDDOJI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdllongleggeddoji(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLLONGLINE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdllongline(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLMARUBOZU\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlmarubozu(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLMATCHINGLOW\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlmatchinglow(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLMATHOLD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlmathold(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLMORNINGDOJISTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlmorningdojistar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLMORNINGSTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double optInPenetration = jsonDouble(json, "optInPenetration");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlmorningstar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                optInPenetration,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLONNECK\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlonneck(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLPIERCING\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlpiercing(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLRICKSHAWMAN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlrickshawman(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLRISEFALL3METHODS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlrisefall3methods(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSEPARATINGLINES\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlseparatinglines(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSHOOTINGSTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlshootingstar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSHORTLINE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlshortline(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSPINNINGTOP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlspinningtop(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSTALLEDPATTERN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlstalledpattern(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLSTICKSANDWICH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlsticksandwich(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLTAKURI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdltakuri(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLTASUKIGAP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdltasukigap(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLTHRUSTING\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlthrusting(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLTRISTAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdltristar(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLUNIQUE3RIVER\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlunique3river(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLUPSIDEGAP2CROWS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlupsidegap2crows(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CDLXSIDEGAP3METHODS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cdlxsidegap3methods(
                startIdx, endIdx,
                inOpen,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CEIL\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ceil(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CMO\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[3] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cmo(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_CORREL\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.correl(
                startIdx, endIdx,
                inReal0,
                inReal1,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_COS\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cos(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_COSH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.cosh(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_DEMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.dema(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_DIV\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.div(
                startIdx, endIdx,
                inReal0,
                inReal1,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_DX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[4] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.dx(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_EMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[5] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ema(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_EXP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.exp(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_FLOOR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.floor(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_DCPERIOD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[6] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_dcperiod(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_DCPHASE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[7] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_dcphase(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_PHASOR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[8] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_phasor(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_SINE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[9] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_sine(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_TRENDLINE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[10] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_trendline(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_HT_TRENDMODE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            core.unstablePeriod[11] = jsonInt(json, "unstablePeriod");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ht_trendmode(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_IMI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inOpen = jsonDoubleArray(json, "inOpen");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[12] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.imi(
                startIdx, endIdx,
                inOpen,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_KAMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[13] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.kama(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LINEARREG\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.linearreg(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LINEARREG_ANGLE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.linearreg_angle(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LINEARREG_INTERCEPT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.linearreg_intercept(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LINEARREG_SLOPE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.linearreg_slope(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ln(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_LOG10\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.log10(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            int optInMAType = jsonInt(json, "optInMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ma(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInMAType,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MACD\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInFastPeriod = jsonInt(json, "optInFastPeriod");
            int optInSlowPeriod = jsonInt(json, "optInSlowPeriod");
            int optInSignalPeriod = jsonInt(json, "optInSignalPeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            double[] outArr2 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.macd(
                startIdx, endIdx,
                inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInSignalPeriod,
                outBegIdx, outNBElement, outArr0, outArr1, outArr2);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"outReal2\":").append(doubleArrayToJson(outArr2, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MACDEXT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInFastPeriod = jsonInt(json, "optInFastPeriod");
            int optInFastMAType = jsonInt(json, "optInFastMAType");
            int optInSlowPeriod = jsonInt(json, "optInSlowPeriod");
            int optInSlowMAType = jsonInt(json, "optInSlowMAType");
            int optInSignalPeriod = jsonInt(json, "optInSignalPeriod");
            int optInSignalMAType = jsonInt(json, "optInSignalMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            double[] outArr2 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.macdext(
                startIdx, endIdx,
                inReal,
                optInFastPeriod,
                optInFastMAType,
                optInSlowPeriod,
                optInSlowMAType,
                optInSignalPeriod,
                optInSignalMAType,
                outBegIdx, outNBElement, outArr0, outArr1, outArr2);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"outReal2\":").append(doubleArrayToJson(outArr2, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MACDFIX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInSignalPeriod = jsonInt(json, "optInSignalPeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            double[] outArr2 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.macdfix(
                startIdx, endIdx,
                inReal,
                optInSignalPeriod,
                outBegIdx, outNBElement, outArr0, outArr1, outArr2);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"outReal2\":").append(doubleArrayToJson(outArr2, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MAMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double optInFastLimit = jsonDouble(json, "optInFastLimit");
            double optInSlowLimit = jsonDouble(json, "optInSlowLimit");
            core.unstablePeriod[14] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.mama(
                startIdx, endIdx,
                inReal,
                optInFastLimit,
                optInSlowLimit,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MAVP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] inPeriods = jsonDoubleArray(json, "inPeriods");
            int optInMinPeriod = jsonInt(json, "optInMinPeriod");
            int optInMaxPeriod = jsonInt(json, "optInMaxPeriod");
            int optInMAType = jsonInt(json, "optInMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.mavp(
                startIdx, endIdx,
                inReal,
                inPeriods,
                optInMinPeriod,
                optInMaxPeriod,
                optInMAType,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MAX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.max(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MAXINDEX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.maxindex(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MEDPRICE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.medprice(
                startIdx, endIdx,
                inHigh,
                inLow,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MFI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[15] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.mfi(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                inVolume,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MIDPOINT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.midpoint(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MIDPRICE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.midprice(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MIN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.min(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MININDEX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.minindex(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MINMAX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.minmax(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MINMAXINDEX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            int[] outArr0 = new int[endIdx - startIdx + 1];
            int[] outArr1 = new int[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.minmaxindex(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outInteger\":").append(intArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outInteger1\":").append(intArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MINUS_DI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[16] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.minus_di(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MINUS_DM\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[17] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.minus_dm(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MOM\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.mom(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_MULT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.mult(
                startIdx, endIdx,
                inReal0,
                inReal1,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_NATR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[18] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.natr(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_NVI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.nvi(
                startIdx, endIdx,
                inClose,
                inVolume,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_OBV\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.obv(
                startIdx, endIdx,
                inReal,
                inVolume,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_PLUS_DI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[19] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.plus_di(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_PLUS_DM\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[20] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.plus_dm(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_PPO\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInFastPeriod = jsonInt(json, "optInFastPeriod");
            int optInSlowPeriod = jsonInt(json, "optInSlowPeriod");
            int optInMAType = jsonInt(json, "optInMAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ppo(
                startIdx, endIdx,
                inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInMAType,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_PVI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] inVolume = jsonDoubleArray(json, "inVolume");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.pvi(
                startIdx, endIdx,
                inClose,
                inVolume,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ROC\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.roc(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ROCP\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.rocp(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ROCR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.rocr(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ROCR100\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.rocr100(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_RSI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            core.unstablePeriod[21] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.rsi(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double optInAcceleration = jsonDouble(json, "optInAcceleration");
            double optInMaximum = jsonDouble(json, "optInMaximum");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sar(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInAcceleration,
                optInMaximum,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SAREXT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double optInStartValue = jsonDouble(json, "optInStartValue");
            double optInOffsetOnReverse = jsonDouble(json, "optInOffsetOnReverse");
            double optInAccelerationInitLong = jsonDouble(json, "optInAccelerationInitLong");
            double optInAccelerationLong = jsonDouble(json, "optInAccelerationLong");
            double optInAccelerationMaxLong = jsonDouble(json, "optInAccelerationMaxLong");
            double optInAccelerationInitShort = jsonDouble(json, "optInAccelerationInitShort");
            double optInAccelerationShort = jsonDouble(json, "optInAccelerationShort");
            double optInAccelerationMaxShort = jsonDouble(json, "optInAccelerationMaxShort");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sarext(
                startIdx, endIdx,
                inHigh,
                inLow,
                optInStartValue,
                optInOffsetOnReverse,
                optInAccelerationInitLong,
                optInAccelerationLong,
                optInAccelerationMaxLong,
                optInAccelerationInitShort,
                optInAccelerationShort,
                optInAccelerationMaxShort,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SIN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sin(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SINH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sinh(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sma(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SQRT\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sqrt(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_STDDEV\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double optInNbDev = jsonDouble(json, "optInNbDev");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.stddev(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInNbDev,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_STOCH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInFastK_Period = jsonInt(json, "optInFastK_Period");
            int optInSlowK_Period = jsonInt(json, "optInSlowK_Period");
            int optInSlowK_MAType = jsonInt(json, "optInSlowK_MAType");
            int optInSlowD_Period = jsonInt(json, "optInSlowD_Period");
            int optInSlowD_MAType = jsonInt(json, "optInSlowD_MAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.stoch(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInFastK_Period,
                optInSlowK_Period,
                optInSlowK_MAType,
                optInSlowD_Period,
                optInSlowD_MAType,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_STOCHF\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInFastK_Period = jsonInt(json, "optInFastK_Period");
            int optInFastD_Period = jsonInt(json, "optInFastD_Period");
            int optInFastD_MAType = jsonInt(json, "optInFastD_MAType");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.stochf(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInFastK_Period,
                optInFastD_Period,
                optInFastD_MAType,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_STOCHRSI\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            int optInFastK_Period = jsonInt(json, "optInFastK_Period");
            int optInFastD_Period = jsonInt(json, "optInFastD_Period");
            int optInFastD_MAType = jsonInt(json, "optInFastD_MAType");
            core.unstablePeriod[22] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            double[] outArr1 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.stochrsi(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInFastK_Period,
                optInFastD_Period,
                optInFastD_MAType,
                outBegIdx, outNBElement, outArr0, outArr1);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"outReal1\":").append(doubleArrayToJson(outArr1, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SUB\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal0 = jsonDoubleArray(json, "inReal0");
            double[] inReal1 = jsonDoubleArray(json, "inReal1");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sub(
                startIdx, endIdx,
                inReal0,
                inReal1,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_SUM\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.sum(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_T3\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double optInVFactor = jsonDouble(json, "optInVFactor");
            core.unstablePeriod[23] = jsonInt(json, "unstablePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.t3(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInVFactor,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TAN\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.tan(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TANH\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.tanh(
                startIdx, endIdx,
                inReal,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TEMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.tema(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TRANGE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.trange(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TRIMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.trima(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TRIX\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.trix(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TSF\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.tsf(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_TYPPRICE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.typprice(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_ULTOSC\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod1 = jsonInt(json, "optInTimePeriod1");
            int optInTimePeriod2 = jsonInt(json, "optInTimePeriod2");
            int optInTimePeriod3 = jsonInt(json, "optInTimePeriod3");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.ultosc(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod1,
                optInTimePeriod2,
                optInTimePeriod3,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_VAR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double optInNbDev = jsonDouble(json, "optInNbDev");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.var(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                optInNbDev,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_WCLPRICE\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.wclprice(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_WILLR\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inHigh = jsonDoubleArray(json, "inHigh");
            double[] inLow = jsonDoubleArray(json, "inLow");
            double[] inClose = jsonDoubleArray(json, "inClose");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.willr(
                startIdx, endIdx,
                inHigh,
                inLow,
                inClose,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"TA_WMA\"")) {
            int startIdx = jsonInt(json, "startIdx");
            int endIdx = jsonInt(json, "endIdx");
            double[] inReal = jsonDoubleArray(json, "inReal");
            int optInTimePeriod = jsonInt(json, "optInTimePeriod");
            double[] outArr0 = new double[endIdx - startIdx + 1];
            MInteger outBegIdx = new MInteger();
            MInteger outNBElement = new MInteger();
            long startNs = System.nanoTime();
            RetCode rc = core.wma(
                startIdx, endIdx,
                inReal,
                optInTimePeriod,
                outBegIdx, outNBElement, outArr0);
            long endNs = System.nanoTime();
            long elapsedNs = endNs - startNs;
            StringBuilder sb = new StringBuilder();
            sb.append("{\"retCode\":").append(rc.toInt());
            sb.append(",\"outBegIdx\":").append(outBegIdx.value);
            sb.append(",\"outNBElement\":").append(outNBElement.value);
            sb.append(",\"outReal\":").append(doubleArrayToJson(outArr0, outNBElement.value));
            sb.append(",\"timing_ns\":").append(elapsedNs);
            sb.append("}");
            return sb.toString();
        }
        else if (json.contains("\"list_functions\"")) {
            StringBuilder sb = new StringBuilder("[");
            sb.append("{\"name\":\"TA_ACCBANDS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ACOS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_AD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ADD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ADOSC\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ADX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ADXR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_APO\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_AROON\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_AROONOSC\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ASIN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ATAN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ATR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_AVGDEV\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_AVGPRICE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_BBANDS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_BETA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_BOP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CCI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL2CROWS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3BLACKCROWS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3INSIDE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3LINESTRIKE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3OUTSIDE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3STARSINSOUTH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDL3WHITESOLDIERS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLABANDONEDBABY\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLADVANCEBLOCK\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLBELTHOLD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLBREAKAWAY\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLCLOSINGMARUBOZU\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLCONCEALBABYSWALL\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLCOUNTERATTACK\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLDARKCLOUDCOVER\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLDOJI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLDOJISTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLDRAGONFLYDOJI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLENGULFING\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLEVENINGDOJISTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLEVENINGSTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLGAPSIDESIDEWHITE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLGRAVESTONEDOJI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHAMMER\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHANGINGMAN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHARAMI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHARAMICROSS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHIGHWAVE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHIKKAKE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHIKKAKEMOD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLHOMINGPIGEON\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLIDENTICAL3CROWS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLINNECK\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLINVERTEDHAMMER\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLKICKING\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLKICKINGBYLENGTH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLLADDERBOTTOM\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLLONGLEGGEDDOJI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLLONGLINE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLMARUBOZU\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLMATCHINGLOW\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLMATHOLD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLMORNINGDOJISTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLMORNINGSTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLONNECK\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLPIERCING\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLRICKSHAWMAN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLRISEFALL3METHODS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSEPARATINGLINES\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSHOOTINGSTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSHORTLINE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSPINNINGTOP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSTALLEDPATTERN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLSTICKSANDWICH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLTAKURI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLTASUKIGAP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLTHRUSTING\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLTRISTAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLUNIQUE3RIVER\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLUPSIDEGAP2CROWS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CDLXSIDEGAP3METHODS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CEIL\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CMO\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_CORREL\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_COS\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_COSH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_DEMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_DIV\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_DX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_EMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_EXP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_FLOOR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_DCPERIOD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_DCPHASE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_PHASOR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_SINE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_TRENDLINE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_HT_TRENDMODE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_IMI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_KAMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LINEARREG\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LINEARREG_ANGLE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LINEARREG_INTERCEPT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LINEARREG_SLOPE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_LOG10\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MACD\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MACDEXT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MACDFIX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MAMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MAVP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MAX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MAXINDEX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MEDPRICE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MFI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MIDPOINT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MIDPRICE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MIN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MININDEX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MINMAX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MINMAXINDEX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MINUS_DI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MINUS_DM\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MOM\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_MULT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_NATR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_NVI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_OBV\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_PLUS_DI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_PLUS_DM\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_PPO\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_PVI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ROC\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ROCP\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ROCR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ROCR100\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_RSI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SAREXT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SIN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SINH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SQRT\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_STDDEV\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_STOCH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_STOCHF\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_STOCHRSI\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SUB\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_SUM\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_T3\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TAN\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TANH\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TEMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TRANGE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TRIMA\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TRIX\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TSF\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_TYPPRICE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_ULTOSC\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_VAR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_WCLPRICE\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_WILLR\"}");
            sb.append(",");
            sb.append("{\"name\":\"TA_WMA\"}");
            sb.append("]");
            return sb.toString();
        }
        else if (json.contains("\"set_unstable_period\"")) {
            int func_id = jsonInt(json, "func_id");
            int period = jsonInt(json, "period");
            if (func_id >= 0 && func_id < core.unstablePeriod.length) {
                core.unstablePeriod[func_id] = period;
                return "{\"status\":\"ok\"}"; 
            }
            return "{\"error\":\"Invalid func_id\"}"; 
        }
        else {
            return "{\"error\":\"Unknown method\"}";
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.trim().isEmpty()) continue;
            System.out.println(handleRequest(line));
            System.out.flush();
        }
    }
}
