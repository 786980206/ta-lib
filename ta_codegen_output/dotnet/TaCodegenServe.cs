// Auto-generated JSON-RPC server for ta_codegen .NET output.
// Uses P/Invoke to call the generated C shared library.
// Requires: dotnet 8.0+, libta_codegen_funcs.dylib/.so in bin/
using System;
using System.IO;
using System.Text.Json;
using System.Runtime.InteropServices;
using System.Diagnostics;

public class TaCodegenServe {

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SetUnstablePeriod")]
    static extern void TA_SetUnstablePeriod(int id, int period);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ACCBANDS")]
    static extern int TA_ACCBANDS(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1,
        double[] outArr2);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ACOS")]
    static extern int TA_ACOS(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_AD")]
    static extern int TA_AD(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double[] inVolume,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ADD")]
    static extern int TA_ADD(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ADOSC")]
    static extern int TA_ADOSC(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double[] inVolume,
        int optInFastPeriod,
        int optInSlowPeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ADX")]
    static extern int TA_ADX(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ADXR")]
    static extern int TA_ADXR(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_APO")]
    static extern int TA_APO(
        int startIdx, int endIdx,
        double[] inReal,
        int optInFastPeriod,
        int optInSlowPeriod,
        int optInMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_AROON")]
    static extern int TA_AROON(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_AROONOSC")]
    static extern int TA_AROONOSC(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ASIN")]
    static extern int TA_ASIN(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ATAN")]
    static extern int TA_ATAN(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ATR")]
    static extern int TA_ATR(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_AVGDEV")]
    static extern int TA_AVGDEV(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_AVGPRICE")]
    static extern int TA_AVGPRICE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_BBANDS")]
    static extern int TA_BBANDS(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        double optInNbDevUp,
        double optInNbDevDn,
        int optInMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1,
        double[] outArr2);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_BETA")]
    static extern int TA_BETA(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_BOP")]
    static extern int TA_BOP(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CCI")]
    static extern int TA_CCI(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL2CROWS")]
    static extern int TA_CDL2CROWS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3BLACKCROWS")]
    static extern int TA_CDL3BLACKCROWS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3INSIDE")]
    static extern int TA_CDL3INSIDE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3LINESTRIKE")]
    static extern int TA_CDL3LINESTRIKE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3OUTSIDE")]
    static extern int TA_CDL3OUTSIDE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3STARSINSOUTH")]
    static extern int TA_CDL3STARSINSOUTH(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDL3WHITESOLDIERS")]
    static extern int TA_CDL3WHITESOLDIERS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLABANDONEDBABY")]
    static extern int TA_CDLABANDONEDBABY(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLADVANCEBLOCK")]
    static extern int TA_CDLADVANCEBLOCK(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLBELTHOLD")]
    static extern int TA_CDLBELTHOLD(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLBREAKAWAY")]
    static extern int TA_CDLBREAKAWAY(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLCLOSINGMARUBOZU")]
    static extern int TA_CDLCLOSINGMARUBOZU(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLCONCEALBABYSWALL")]
    static extern int TA_CDLCONCEALBABYSWALL(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLCOUNTERATTACK")]
    static extern int TA_CDLCOUNTERATTACK(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLDARKCLOUDCOVER")]
    static extern int TA_CDLDARKCLOUDCOVER(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLDOJI")]
    static extern int TA_CDLDOJI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLDOJISTAR")]
    static extern int TA_CDLDOJISTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLDRAGONFLYDOJI")]
    static extern int TA_CDLDRAGONFLYDOJI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLENGULFING")]
    static extern int TA_CDLENGULFING(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLEVENINGDOJISTAR")]
    static extern int TA_CDLEVENINGDOJISTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLEVENINGSTAR")]
    static extern int TA_CDLEVENINGSTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLGAPSIDESIDEWHITE")]
    static extern int TA_CDLGAPSIDESIDEWHITE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLGRAVESTONEDOJI")]
    static extern int TA_CDLGRAVESTONEDOJI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHAMMER")]
    static extern int TA_CDLHAMMER(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHANGINGMAN")]
    static extern int TA_CDLHANGINGMAN(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHARAMI")]
    static extern int TA_CDLHARAMI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHARAMICROSS")]
    static extern int TA_CDLHARAMICROSS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHIGHWAVE")]
    static extern int TA_CDLHIGHWAVE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHIKKAKE")]
    static extern int TA_CDLHIKKAKE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHIKKAKEMOD")]
    static extern int TA_CDLHIKKAKEMOD(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLHOMINGPIGEON")]
    static extern int TA_CDLHOMINGPIGEON(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLIDENTICAL3CROWS")]
    static extern int TA_CDLIDENTICAL3CROWS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLINNECK")]
    static extern int TA_CDLINNECK(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLINVERTEDHAMMER")]
    static extern int TA_CDLINVERTEDHAMMER(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLKICKING")]
    static extern int TA_CDLKICKING(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLKICKINGBYLENGTH")]
    static extern int TA_CDLKICKINGBYLENGTH(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLLADDERBOTTOM")]
    static extern int TA_CDLLADDERBOTTOM(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLLONGLEGGEDDOJI")]
    static extern int TA_CDLLONGLEGGEDDOJI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLLONGLINE")]
    static extern int TA_CDLLONGLINE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLMARUBOZU")]
    static extern int TA_CDLMARUBOZU(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLMATCHINGLOW")]
    static extern int TA_CDLMATCHINGLOW(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLMATHOLD")]
    static extern int TA_CDLMATHOLD(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLMORNINGDOJISTAR")]
    static extern int TA_CDLMORNINGDOJISTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLMORNINGSTAR")]
    static extern int TA_CDLMORNINGSTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double optInPenetration,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLONNECK")]
    static extern int TA_CDLONNECK(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLPIERCING")]
    static extern int TA_CDLPIERCING(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLRICKSHAWMAN")]
    static extern int TA_CDLRICKSHAWMAN(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLRISEFALL3METHODS")]
    static extern int TA_CDLRISEFALL3METHODS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSEPARATINGLINES")]
    static extern int TA_CDLSEPARATINGLINES(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSHOOTINGSTAR")]
    static extern int TA_CDLSHOOTINGSTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSHORTLINE")]
    static extern int TA_CDLSHORTLINE(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSPINNINGTOP")]
    static extern int TA_CDLSPINNINGTOP(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSTALLEDPATTERN")]
    static extern int TA_CDLSTALLEDPATTERN(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLSTICKSANDWICH")]
    static extern int TA_CDLSTICKSANDWICH(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLTAKURI")]
    static extern int TA_CDLTAKURI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLTASUKIGAP")]
    static extern int TA_CDLTASUKIGAP(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLTHRUSTING")]
    static extern int TA_CDLTHRUSTING(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLTRISTAR")]
    static extern int TA_CDLTRISTAR(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLUNIQUE3RIVER")]
    static extern int TA_CDLUNIQUE3RIVER(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLUPSIDEGAP2CROWS")]
    static extern int TA_CDLUPSIDEGAP2CROWS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CDLXSIDEGAP3METHODS")]
    static extern int TA_CDLXSIDEGAP3METHODS(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CEIL")]
    static extern int TA_CEIL(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CMO")]
    static extern int TA_CMO(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_CORREL")]
    static extern int TA_CORREL(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_COS")]
    static extern int TA_COS(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_COSH")]
    static extern int TA_COSH(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_DEMA")]
    static extern int TA_DEMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_DIV")]
    static extern int TA_DIV(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_DX")]
    static extern int TA_DX(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_EMA")]
    static extern int TA_EMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_EXP")]
    static extern int TA_EXP(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_FLOOR")]
    static extern int TA_FLOOR(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_DCPERIOD")]
    static extern int TA_HT_DCPERIOD(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_DCPHASE")]
    static extern int TA_HT_DCPHASE(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_PHASOR")]
    static extern int TA_HT_PHASOR(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_SINE")]
    static extern int TA_HT_SINE(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_TRENDLINE")]
    static extern int TA_HT_TRENDLINE(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_HT_TRENDMODE")]
    static extern int TA_HT_TRENDMODE(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_IMI")]
    static extern int TA_IMI(
        int startIdx, int endIdx,
        double[] inOpen,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_KAMA")]
    static extern int TA_KAMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LINEARREG")]
    static extern int TA_LINEARREG(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LINEARREG_ANGLE")]
    static extern int TA_LINEARREG_ANGLE(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LINEARREG_INTERCEPT")]
    static extern int TA_LINEARREG_INTERCEPT(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LINEARREG_SLOPE")]
    static extern int TA_LINEARREG_SLOPE(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LN")]
    static extern int TA_LN(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_LOG10")]
    static extern int TA_LOG10(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MA")]
    static extern int TA_MA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        int optInMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MACD")]
    static extern int TA_MACD(
        int startIdx, int endIdx,
        double[] inReal,
        int optInFastPeriod,
        int optInSlowPeriod,
        int optInSignalPeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1,
        double[] outArr2);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MACDEXT")]
    static extern int TA_MACDEXT(
        int startIdx, int endIdx,
        double[] inReal,
        int optInFastPeriod,
        int optInFastMAType,
        int optInSlowPeriod,
        int optInSlowMAType,
        int optInSignalPeriod,
        int optInSignalMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1,
        double[] outArr2);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MACDFIX")]
    static extern int TA_MACDFIX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInSignalPeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1,
        double[] outArr2);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MAMA")]
    static extern int TA_MAMA(
        int startIdx, int endIdx,
        double[] inReal,
        double optInFastLimit,
        double optInSlowLimit,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MAVP")]
    static extern int TA_MAVP(
        int startIdx, int endIdx,
        double[] inReal,
        double[] inPeriods,
        int optInMinPeriod,
        int optInMaxPeriod,
        int optInMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MAX")]
    static extern int TA_MAX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MAXINDEX")]
    static extern int TA_MAXINDEX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MEDPRICE")]
    static extern int TA_MEDPRICE(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MFI")]
    static extern int TA_MFI(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        double[] inVolume,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MIDPOINT")]
    static extern int TA_MIDPOINT(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MIDPRICE")]
    static extern int TA_MIDPRICE(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MIN")]
    static extern int TA_MIN(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MININDEX")]
    static extern int TA_MININDEX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        int[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MINMAX")]
    static extern int TA_MINMAX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MINMAXINDEX")]
    static extern int TA_MINMAXINDEX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        int[] outArr0,
        int[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MINUS_DI")]
    static extern int TA_MINUS_DI(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MINUS_DM")]
    static extern int TA_MINUS_DM(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MOM")]
    static extern int TA_MOM(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_MULT")]
    static extern int TA_MULT(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_NATR")]
    static extern int TA_NATR(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_NVI")]
    static extern int TA_NVI(
        int startIdx, int endIdx,
        double[] inClose,
        double[] inVolume,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_OBV")]
    static extern int TA_OBV(
        int startIdx, int endIdx,
        double[] inReal,
        double[] inVolume,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_PLUS_DI")]
    static extern int TA_PLUS_DI(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_PLUS_DM")]
    static extern int TA_PLUS_DM(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_PPO")]
    static extern int TA_PPO(
        int startIdx, int endIdx,
        double[] inReal,
        int optInFastPeriod,
        int optInSlowPeriod,
        int optInMAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_PVI")]
    static extern int TA_PVI(
        int startIdx, int endIdx,
        double[] inClose,
        double[] inVolume,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ROC")]
    static extern int TA_ROC(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ROCP")]
    static extern int TA_ROCP(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ROCR")]
    static extern int TA_ROCR(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ROCR100")]
    static extern int TA_ROCR100(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_RSI")]
    static extern int TA_RSI(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SAR")]
    static extern int TA_SAR(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double optInAcceleration,
        double optInMaximum,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SAREXT")]
    static extern int TA_SAREXT(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double optInStartValue,
        double optInOffsetOnReverse,
        double optInAccelerationInitLong,
        double optInAccelerationLong,
        double optInAccelerationMaxLong,
        double optInAccelerationInitShort,
        double optInAccelerationShort,
        double optInAccelerationMaxShort,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SIN")]
    static extern int TA_SIN(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SINH")]
    static extern int TA_SINH(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SMA")]
    static extern int TA_SMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SQRT")]
    static extern int TA_SQRT(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_STDDEV")]
    static extern int TA_STDDEV(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        double optInNbDev,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_STOCH")]
    static extern int TA_STOCH(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInFastK_Period,
        int optInSlowK_Period,
        int optInSlowK_MAType,
        int optInSlowD_Period,
        int optInSlowD_MAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_STOCHF")]
    static extern int TA_STOCHF(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInFastK_Period,
        int optInFastD_Period,
        int optInFastD_MAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_STOCHRSI")]
    static extern int TA_STOCHRSI(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        int optInFastK_Period,
        int optInFastD_Period,
        int optInFastD_MAType,
        out int outBegIdx, out int outNBElement,
        double[] outArr0,
        double[] outArr1);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SUB")]
    static extern int TA_SUB(
        int startIdx, int endIdx,
        double[] inReal0,
        double[] inReal1,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_SUM")]
    static extern int TA_SUM(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_T3")]
    static extern int TA_T3(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        double optInVFactor,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TAN")]
    static extern int TA_TAN(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TANH")]
    static extern int TA_TANH(
        int startIdx, int endIdx,
        double[] inReal,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TEMA")]
    static extern int TA_TEMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TRANGE")]
    static extern int TA_TRANGE(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TRIMA")]
    static extern int TA_TRIMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TRIX")]
    static extern int TA_TRIX(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TSF")]
    static extern int TA_TSF(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_TYPPRICE")]
    static extern int TA_TYPPRICE(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_ULTOSC")]
    static extern int TA_ULTOSC(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod1,
        int optInTimePeriod2,
        int optInTimePeriod3,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_VAR")]
    static extern int TA_VAR(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        double optInNbDev,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_WCLPRICE")]
    static extern int TA_WCLPRICE(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_WILLR")]
    static extern int TA_WILLR(
        int startIdx, int endIdx,
        double[] inHigh,
        double[] inLow,
        double[] inClose,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    [DllImport("ta_codegen_funcs", EntryPoint = "TA_WMA")]
    static extern int TA_WMA(
        int startIdx, int endIdx,
        double[] inReal,
        int optInTimePeriod,
        out int outBegIdx, out int outNBElement,
        double[] outArr0);

    static string HandleRequest(string json) {
        try {
            using var doc = JsonDocument.Parse(json);
            var root = doc.RootElement;
            string method = root.GetProperty("method").GetString()!;
            var p = root.GetProperty("params");
            int startIdx = p.GetProperty("startIdx").GetInt32();
            int endIdx = p.GetProperty("endIdx").GetInt32();
            int n = endIdx - startIdx + 1;

            if (method == "TA_ACCBANDS") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 20;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                double[] outArr2 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ACCBANDS(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1, outArr2);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"outReal2\":"); sb.Append(FormatArray(outArr2, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ACOS") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ACOS(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_AD") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_AD(startIdx, endIdx, inHigh, inLow, inClose, inVolume, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ADD") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ADD(startIdx, endIdx, inReal0, inReal1, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ADOSC") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                int optInFastPeriod = p.TryGetProperty("optInFastPeriod", out var _optInFastPeriodVal) ? _optInFastPeriodVal.GetInt32() : 3;
                int optInSlowPeriod = p.TryGetProperty("optInSlowPeriod", out var _optInSlowPeriodVal) ? _optInSlowPeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ADOSC(startIdx, endIdx, inHigh, inLow, inClose, inVolume, optInFastPeriod, optInSlowPeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ADX") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(0, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ADX(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ADXR") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(1, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ADXR(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_APO") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInFastPeriod = p.TryGetProperty("optInFastPeriod", out var _optInFastPeriodVal) ? _optInFastPeriodVal.GetInt32() : 12;
                int optInSlowPeriod = p.TryGetProperty("optInSlowPeriod", out var _optInSlowPeriodVal) ? _optInSlowPeriodVal.GetInt32() : 26;
                int optInMAType = p.TryGetProperty("optInMAType", out var _optInMATypeVal) ? _optInMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_APO(startIdx, endIdx, inReal, optInFastPeriod, optInSlowPeriod, optInMAType, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_AROON") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_AROON(startIdx, endIdx, inHigh, inLow, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_AROONOSC") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_AROONOSC(startIdx, endIdx, inHigh, inLow, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ASIN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ASIN(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ATAN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ATAN(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ATR") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(2, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ATR(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_AVGDEV") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_AVGDEV(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_AVGPRICE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_AVGPRICE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_BBANDS") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 5;
                double optInNbDevUp = p.TryGetProperty("optInNbDevUp", out var _optInNbDevUpVal) ? _optInNbDevUpVal.GetDouble() : 2;
                double optInNbDevDn = p.TryGetProperty("optInNbDevDn", out var _optInNbDevDnVal) ? _optInNbDevDnVal.GetDouble() : 2;
                int optInMAType = p.TryGetProperty("optInMAType", out var _optInMATypeVal) ? _optInMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                double[] outArr2 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_BBANDS(startIdx, endIdx, inReal, optInTimePeriod, optInNbDevUp, optInNbDevDn, optInMAType, out int outBegIdx, out int outNBElement, outArr0, outArr1, outArr2);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"outReal2\":"); sb.Append(FormatArray(outArr2, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_BETA") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 5;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_BETA(startIdx, endIdx, inReal0, inReal1, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_BOP") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_BOP(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CCI") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CCI(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL2CROWS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL2CROWS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3BLACKCROWS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3BLACKCROWS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3INSIDE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3INSIDE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3LINESTRIKE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3LINESTRIKE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3OUTSIDE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3OUTSIDE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3STARSINSOUTH") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3STARSINSOUTH(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDL3WHITESOLDIERS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDL3WHITESOLDIERS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLABANDONEDBABY") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.3;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLABANDONEDBABY(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLADVANCEBLOCK") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLADVANCEBLOCK(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLBELTHOLD") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLBELTHOLD(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLBREAKAWAY") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLBREAKAWAY(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLCLOSINGMARUBOZU") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLCLOSINGMARUBOZU(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLCONCEALBABYSWALL") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLCONCEALBABYSWALL(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLCOUNTERATTACK") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLCOUNTERATTACK(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLDARKCLOUDCOVER") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.5;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLDARKCLOUDCOVER(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLDOJI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLDOJI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLDOJISTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLDOJISTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLDRAGONFLYDOJI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLDRAGONFLYDOJI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLENGULFING") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLENGULFING(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLEVENINGDOJISTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.3;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLEVENINGDOJISTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLEVENINGSTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.3;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLEVENINGSTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLGAPSIDESIDEWHITE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLGAPSIDESIDEWHITE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLGRAVESTONEDOJI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLGRAVESTONEDOJI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHAMMER") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHAMMER(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHANGINGMAN") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHANGINGMAN(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHARAMI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHARAMI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHARAMICROSS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHARAMICROSS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHIGHWAVE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHIGHWAVE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHIKKAKE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHIKKAKE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHIKKAKEMOD") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHIKKAKEMOD(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLHOMINGPIGEON") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLHOMINGPIGEON(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLIDENTICAL3CROWS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLIDENTICAL3CROWS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLINNECK") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLINNECK(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLINVERTEDHAMMER") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLINVERTEDHAMMER(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLKICKING") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLKICKING(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLKICKINGBYLENGTH") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLKICKINGBYLENGTH(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLLADDERBOTTOM") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLLADDERBOTTOM(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLLONGLEGGEDDOJI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLLONGLEGGEDDOJI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLLONGLINE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLLONGLINE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLMARUBOZU") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLMARUBOZU(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLMATCHINGLOW") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLMATCHINGLOW(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLMATHOLD") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.5;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLMATHOLD(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLMORNINGDOJISTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.3;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLMORNINGDOJISTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLMORNINGSTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double optInPenetration = p.TryGetProperty("optInPenetration", out var _optInPenetrationVal) ? _optInPenetrationVal.GetDouble() : 0.3;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLMORNINGSTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, optInPenetration, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLONNECK") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLONNECK(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLPIERCING") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLPIERCING(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLRICKSHAWMAN") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLRICKSHAWMAN(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLRISEFALL3METHODS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLRISEFALL3METHODS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSEPARATINGLINES") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSEPARATINGLINES(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSHOOTINGSTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSHOOTINGSTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSHORTLINE") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSHORTLINE(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSPINNINGTOP") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSPINNINGTOP(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSTALLEDPATTERN") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSTALLEDPATTERN(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLSTICKSANDWICH") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLSTICKSANDWICH(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLTAKURI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLTAKURI(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLTASUKIGAP") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLTASUKIGAP(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLTHRUSTING") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLTHRUSTING(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLTRISTAR") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLTRISTAR(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLUNIQUE3RIVER") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLUNIQUE3RIVER(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLUPSIDEGAP2CROWS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLUPSIDEGAP2CROWS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CDLXSIDEGAP3METHODS") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CDLXSIDEGAP3METHODS(startIdx, endIdx, inOpen, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CEIL") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CEIL(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CMO") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(3, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CMO(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_CORREL") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_CORREL(startIdx, endIdx, inReal0, inReal1, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_COS") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_COS(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_COSH") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_COSH(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_DEMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_DEMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_DIV") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_DIV(startIdx, endIdx, inReal0, inReal1, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_DX") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(4, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_DX(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_EMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(5, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_EMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_EXP") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_EXP(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_FLOOR") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_FLOOR(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_DCPERIOD") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(6, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_DCPERIOD(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_DCPHASE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(7, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_DCPHASE(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_PHASOR") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(8, unstablePeriod);
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_PHASOR(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_SINE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(9, unstablePeriod);
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_SINE(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_TRENDLINE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(10, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_TRENDLINE(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_HT_TRENDMODE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(11, unstablePeriod);
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_HT_TRENDMODE(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_IMI") {
                double[] inOpen = GetDoubleArray(p, "inOpen");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(12, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_IMI(startIdx, endIdx, inOpen, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_KAMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(13, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_KAMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LINEARREG") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LINEARREG(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LINEARREG_ANGLE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LINEARREG_ANGLE(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LINEARREG_INTERCEPT") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LINEARREG_INTERCEPT(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LINEARREG_SLOPE") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LINEARREG_SLOPE(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LN(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_LOG10") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_LOG10(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int optInMAType = p.TryGetProperty("optInMAType", out var _optInMATypeVal) ? _optInMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MA(startIdx, endIdx, inReal, optInTimePeriod, optInMAType, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MACD") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInFastPeriod = p.TryGetProperty("optInFastPeriod", out var _optInFastPeriodVal) ? _optInFastPeriodVal.GetInt32() : 12;
                int optInSlowPeriod = p.TryGetProperty("optInSlowPeriod", out var _optInSlowPeriodVal) ? _optInSlowPeriodVal.GetInt32() : 26;
                int optInSignalPeriod = p.TryGetProperty("optInSignalPeriod", out var _optInSignalPeriodVal) ? _optInSignalPeriodVal.GetInt32() : 9;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                double[] outArr2 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MACD(startIdx, endIdx, inReal, optInFastPeriod, optInSlowPeriod, optInSignalPeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1, outArr2);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"outReal2\":"); sb.Append(FormatArray(outArr2, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MACDEXT") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInFastPeriod = p.TryGetProperty("optInFastPeriod", out var _optInFastPeriodVal) ? _optInFastPeriodVal.GetInt32() : 12;
                int optInFastMAType = p.TryGetProperty("optInFastMAType", out var _optInFastMATypeVal) ? _optInFastMATypeVal.GetInt32() : 0;
                int optInSlowPeriod = p.TryGetProperty("optInSlowPeriod", out var _optInSlowPeriodVal) ? _optInSlowPeriodVal.GetInt32() : 26;
                int optInSlowMAType = p.TryGetProperty("optInSlowMAType", out var _optInSlowMATypeVal) ? _optInSlowMATypeVal.GetInt32() : 0;
                int optInSignalPeriod = p.TryGetProperty("optInSignalPeriod", out var _optInSignalPeriodVal) ? _optInSignalPeriodVal.GetInt32() : 9;
                int optInSignalMAType = p.TryGetProperty("optInSignalMAType", out var _optInSignalMATypeVal) ? _optInSignalMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                double[] outArr2 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MACDEXT(startIdx, endIdx, inReal, optInFastPeriod, optInFastMAType, optInSlowPeriod, optInSlowMAType, optInSignalPeriod, optInSignalMAType, out int outBegIdx, out int outNBElement, outArr0, outArr1, outArr2);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"outReal2\":"); sb.Append(FormatArray(outArr2, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MACDFIX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInSignalPeriod = p.TryGetProperty("optInSignalPeriod", out var _optInSignalPeriodVal) ? _optInSignalPeriodVal.GetInt32() : 9;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                double[] outArr2 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MACDFIX(startIdx, endIdx, inReal, optInSignalPeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1, outArr2);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"outReal2\":"); sb.Append(FormatArray(outArr2, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MAMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double optInFastLimit = p.TryGetProperty("optInFastLimit", out var _optInFastLimitVal) ? _optInFastLimitVal.GetDouble() : 0.5;
                double optInSlowLimit = p.TryGetProperty("optInSlowLimit", out var _optInSlowLimitVal) ? _optInSlowLimitVal.GetDouble() : 0.05;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(14, unstablePeriod);
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MAMA(startIdx, endIdx, inReal, optInFastLimit, optInSlowLimit, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MAVP") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] inPeriods = GetDoubleArray(p, "inPeriods");
                int optInMinPeriod = p.TryGetProperty("optInMinPeriod", out var _optInMinPeriodVal) ? _optInMinPeriodVal.GetInt32() : 2;
                int optInMaxPeriod = p.TryGetProperty("optInMaxPeriod", out var _optInMaxPeriodVal) ? _optInMaxPeriodVal.GetInt32() : 30;
                int optInMAType = p.TryGetProperty("optInMAType", out var _optInMATypeVal) ? _optInMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MAVP(startIdx, endIdx, inReal, inPeriods, optInMinPeriod, optInMaxPeriod, optInMAType, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MAX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MAX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MAXINDEX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MAXINDEX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MEDPRICE") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MEDPRICE(startIdx, endIdx, inHigh, inLow, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MFI") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(15, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MFI(startIdx, endIdx, inHigh, inLow, inClose, inVolume, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MIDPOINT") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MIDPOINT(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MIDPRICE") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MIDPRICE(startIdx, endIdx, inHigh, inLow, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MIN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MIN(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MININDEX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int[] outArr0 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MININDEX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MINMAX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MINMAX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MINMAXINDEX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                int[] outArr0 = new int[n];
                int[] outArr1 = new int[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MINMAXINDEX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outInteger\":"); sb.Append(FormatIntArray(outArr0, outNBElement));
                sb.Append($",\"outInteger1\":"); sb.Append(FormatIntArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MINUS_DI") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(16, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MINUS_DI(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MINUS_DM") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(17, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MINUS_DM(startIdx, endIdx, inHigh, inLow, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MOM") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MOM(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_MULT") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_MULT(startIdx, endIdx, inReal0, inReal1, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_NATR") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(18, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_NATR(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_NVI") {
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_NVI(startIdx, endIdx, inClose, inVolume, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_OBV") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_OBV(startIdx, endIdx, inReal, inVolume, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_PLUS_DI") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(19, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_PLUS_DI(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_PLUS_DM") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(20, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_PLUS_DM(startIdx, endIdx, inHigh, inLow, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_PPO") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInFastPeriod = p.TryGetProperty("optInFastPeriod", out var _optInFastPeriodVal) ? _optInFastPeriodVal.GetInt32() : 12;
                int optInSlowPeriod = p.TryGetProperty("optInSlowPeriod", out var _optInSlowPeriodVal) ? _optInSlowPeriodVal.GetInt32() : 26;
                int optInMAType = p.TryGetProperty("optInMAType", out var _optInMATypeVal) ? _optInMATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_PPO(startIdx, endIdx, inReal, optInFastPeriod, optInSlowPeriod, optInMAType, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_PVI") {
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] inVolume = GetDoubleArray(p, "inVolume");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_PVI(startIdx, endIdx, inClose, inVolume, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ROC") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ROC(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ROCP") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ROCP(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ROCR") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ROCR(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ROCR100") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 10;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ROCR100(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_RSI") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(21, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_RSI(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SAR") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double optInAcceleration = p.TryGetProperty("optInAcceleration", out var _optInAccelerationVal) ? _optInAccelerationVal.GetDouble() : 0.02;
                double optInMaximum = p.TryGetProperty("optInMaximum", out var _optInMaximumVal) ? _optInMaximumVal.GetDouble() : 0.2;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SAR(startIdx, endIdx, inHigh, inLow, optInAcceleration, optInMaximum, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SAREXT") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double optInStartValue = p.TryGetProperty("optInStartValue", out var _optInStartValueVal) ? _optInStartValueVal.GetDouble() : 0;
                double optInOffsetOnReverse = p.TryGetProperty("optInOffsetOnReverse", out var _optInOffsetOnReverseVal) ? _optInOffsetOnReverseVal.GetDouble() : 0;
                double optInAccelerationInitLong = p.TryGetProperty("optInAccelerationInitLong", out var _optInAccelerationInitLongVal) ? _optInAccelerationInitLongVal.GetDouble() : 0.02;
                double optInAccelerationLong = p.TryGetProperty("optInAccelerationLong", out var _optInAccelerationLongVal) ? _optInAccelerationLongVal.GetDouble() : 0.02;
                double optInAccelerationMaxLong = p.TryGetProperty("optInAccelerationMaxLong", out var _optInAccelerationMaxLongVal) ? _optInAccelerationMaxLongVal.GetDouble() : 0.2;
                double optInAccelerationInitShort = p.TryGetProperty("optInAccelerationInitShort", out var _optInAccelerationInitShortVal) ? _optInAccelerationInitShortVal.GetDouble() : 0.02;
                double optInAccelerationShort = p.TryGetProperty("optInAccelerationShort", out var _optInAccelerationShortVal) ? _optInAccelerationShortVal.GetDouble() : 0.02;
                double optInAccelerationMaxShort = p.TryGetProperty("optInAccelerationMaxShort", out var _optInAccelerationMaxShortVal) ? _optInAccelerationMaxShortVal.GetDouble() : 0.2;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SAREXT(startIdx, endIdx, inHigh, inLow, optInStartValue, optInOffsetOnReverse, optInAccelerationInitLong, optInAccelerationLong, optInAccelerationMaxLong, optInAccelerationInitShort, optInAccelerationShort, optInAccelerationMaxShort, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SIN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SIN(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SINH") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SINH(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SQRT") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SQRT(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_STDDEV") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 5;
                double optInNbDev = p.TryGetProperty("optInNbDev", out var _optInNbDevVal) ? _optInNbDevVal.GetDouble() : 1;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_STDDEV(startIdx, endIdx, inReal, optInTimePeriod, optInNbDev, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_STOCH") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInFastK_Period = p.TryGetProperty("optInFastK_Period", out var _optInFastK_PeriodVal) ? _optInFastK_PeriodVal.GetInt32() : 5;
                int optInSlowK_Period = p.TryGetProperty("optInSlowK_Period", out var _optInSlowK_PeriodVal) ? _optInSlowK_PeriodVal.GetInt32() : 3;
                int optInSlowK_MAType = p.TryGetProperty("optInSlowK_MAType", out var _optInSlowK_MATypeVal) ? _optInSlowK_MATypeVal.GetInt32() : 0;
                int optInSlowD_Period = p.TryGetProperty("optInSlowD_Period", out var _optInSlowD_PeriodVal) ? _optInSlowD_PeriodVal.GetInt32() : 3;
                int optInSlowD_MAType = p.TryGetProperty("optInSlowD_MAType", out var _optInSlowD_MATypeVal) ? _optInSlowD_MATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_STOCH(startIdx, endIdx, inHigh, inLow, inClose, optInFastK_Period, optInSlowK_Period, optInSlowK_MAType, optInSlowD_Period, optInSlowD_MAType, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_STOCHF") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInFastK_Period = p.TryGetProperty("optInFastK_Period", out var _optInFastK_PeriodVal) ? _optInFastK_PeriodVal.GetInt32() : 5;
                int optInFastD_Period = p.TryGetProperty("optInFastD_Period", out var _optInFastD_PeriodVal) ? _optInFastD_PeriodVal.GetInt32() : 3;
                int optInFastD_MAType = p.TryGetProperty("optInFastD_MAType", out var _optInFastD_MATypeVal) ? _optInFastD_MATypeVal.GetInt32() : 0;
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_STOCHF(startIdx, endIdx, inHigh, inLow, inClose, optInFastK_Period, optInFastD_Period, optInFastD_MAType, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_STOCHRSI") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                int optInFastK_Period = p.TryGetProperty("optInFastK_Period", out var _optInFastK_PeriodVal) ? _optInFastK_PeriodVal.GetInt32() : 5;
                int optInFastD_Period = p.TryGetProperty("optInFastD_Period", out var _optInFastD_PeriodVal) ? _optInFastD_PeriodVal.GetInt32() : 3;
                int optInFastD_MAType = p.TryGetProperty("optInFastD_MAType", out var _optInFastD_MATypeVal) ? _optInFastD_MATypeVal.GetInt32() : 0;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(22, unstablePeriod);
                double[] outArr0 = new double[n];
                double[] outArr1 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_STOCHRSI(startIdx, endIdx, inReal, optInTimePeriod, optInFastK_Period, optInFastD_Period, optInFastD_MAType, out int outBegIdx, out int outNBElement, outArr0, outArr1);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"outReal1\":"); sb.Append(FormatArray(outArr1, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SUB") {
                double[] inReal0 = GetDoubleArray(p, "inReal0");
                double[] inReal1 = GetDoubleArray(p, "inReal1");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SUB(startIdx, endIdx, inReal0, inReal1, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_SUM") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_SUM(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_T3") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 5;
                double optInVFactor = p.TryGetProperty("optInVFactor", out var _optInVFactorVal) ? _optInVFactorVal.GetDouble() : 0.7;
                int unstablePeriod = p.TryGetProperty("unstablePeriod", out var _upVal) ? _upVal.GetInt32() : 0;
                TA_SetUnstablePeriod(23, unstablePeriod);
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_T3(startIdx, endIdx, inReal, optInTimePeriod, optInVFactor, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TAN") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TAN(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TANH") {
                double[] inReal = GetDoubleArray(p, "inReal");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TANH(startIdx, endIdx, inReal, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TEMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TEMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TRANGE") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TRANGE(startIdx, endIdx, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TRIMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TRIMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TRIX") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TRIX(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TSF") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TSF(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_TYPPRICE") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_TYPPRICE(startIdx, endIdx, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_ULTOSC") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod1 = p.TryGetProperty("optInTimePeriod1", out var _optInTimePeriod1Val) ? _optInTimePeriod1Val.GetInt32() : 7;
                int optInTimePeriod2 = p.TryGetProperty("optInTimePeriod2", out var _optInTimePeriod2Val) ? _optInTimePeriod2Val.GetInt32() : 14;
                int optInTimePeriod3 = p.TryGetProperty("optInTimePeriod3", out var _optInTimePeriod3Val) ? _optInTimePeriod3Val.GetInt32() : 28;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_ULTOSC(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod1, optInTimePeriod2, optInTimePeriod3, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_VAR") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 5;
                double optInNbDev = p.TryGetProperty("optInNbDev", out var _optInNbDevVal) ? _optInNbDevVal.GetDouble() : 1;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_VAR(startIdx, endIdx, inReal, optInTimePeriod, optInNbDev, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_WCLPRICE") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_WCLPRICE(startIdx, endIdx, inHigh, inLow, inClose, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_WILLR") {
                double[] inHigh = GetDoubleArray(p, "inHigh");
                double[] inLow = GetDoubleArray(p, "inLow");
                double[] inClose = GetDoubleArray(p, "inClose");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 14;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_WILLR(startIdx, endIdx, inHigh, inLow, inClose, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "TA_WMA") {
                double[] inReal = GetDoubleArray(p, "inReal");
                int optInTimePeriod = p.TryGetProperty("optInTimePeriod", out var _optInTimePeriodVal) ? _optInTimePeriodVal.GetInt32() : 30;
                double[] outArr0 = new double[n];
                var timer = Stopwatch.StartNew();
                int rc = TA_WMA(startIdx, endIdx, inReal, optInTimePeriod, out int outBegIdx, out int outNBElement, outArr0);
                timer.Stop();
                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;
                var sb = new System.Text.StringBuilder();
                sb.Append($"{{\"retCode\":{rc},\"outBegIdx\":{outBegIdx},\"outNBElement\":{outNBElement}");
                sb.Append($",\"outReal\":"); sb.Append(FormatArray(outArr0, outNBElement));
                sb.Append($",\"timing_ns\":{elapsedNs}");
                sb.Append("}");
                return sb.ToString();
            }
            else if (method == "list_functions") {
                var sb = new System.Text.StringBuilder();
                sb.Append("[\n");
                sb.Append("  {\"name\":\"TA_ACCBANDS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ACOS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_AD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ADD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ADOSC\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ADX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ADXR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_APO\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_AROON\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_AROONOSC\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ASIN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ATAN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ATR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_AVGDEV\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_AVGPRICE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_BBANDS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_BETA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_BOP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CCI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL2CROWS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3BLACKCROWS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3INSIDE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3LINESTRIKE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3OUTSIDE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3STARSINSOUTH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDL3WHITESOLDIERS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLABANDONEDBABY\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLADVANCEBLOCK\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLBELTHOLD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLBREAKAWAY\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLCLOSINGMARUBOZU\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLCONCEALBABYSWALL\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLCOUNTERATTACK\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLDARKCLOUDCOVER\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLDOJI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLDOJISTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLDRAGONFLYDOJI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLENGULFING\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLEVENINGDOJISTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLEVENINGSTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLGAPSIDESIDEWHITE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLGRAVESTONEDOJI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHAMMER\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHANGINGMAN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHARAMI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHARAMICROSS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHIGHWAVE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHIKKAKE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHIKKAKEMOD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLHOMINGPIGEON\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLIDENTICAL3CROWS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLINNECK\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLINVERTEDHAMMER\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLKICKING\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLKICKINGBYLENGTH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLLADDERBOTTOM\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLLONGLEGGEDDOJI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLLONGLINE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLMARUBOZU\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLMATCHINGLOW\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLMATHOLD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLMORNINGDOJISTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLMORNINGSTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLONNECK\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLPIERCING\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLRICKSHAWMAN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLRISEFALL3METHODS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSEPARATINGLINES\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSHOOTINGSTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSHORTLINE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSPINNINGTOP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSTALLEDPATTERN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLSTICKSANDWICH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLTAKURI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLTASUKIGAP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLTHRUSTING\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLTRISTAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLUNIQUE3RIVER\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLUPSIDEGAP2CROWS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CDLXSIDEGAP3METHODS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CEIL\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CMO\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_CORREL\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_COS\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_COSH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_DEMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_DIV\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_DX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_EMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_EXP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_FLOOR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_DCPERIOD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_DCPHASE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_PHASOR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_SINE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_TRENDLINE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_HT_TRENDMODE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_IMI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_KAMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LINEARREG\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LINEARREG_ANGLE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LINEARREG_INTERCEPT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LINEARREG_SLOPE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_LOG10\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MACD\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MACDEXT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MACDFIX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MAMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MAVP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MAX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MAXINDEX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MEDPRICE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MFI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MIDPOINT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MIDPRICE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MIN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MININDEX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MINMAX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MINMAXINDEX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MINUS_DI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MINUS_DM\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MOM\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_MULT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_NATR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_NVI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_OBV\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_PLUS_DI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_PLUS_DM\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_PPO\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_PVI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ROC\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ROCP\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ROCR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ROCR100\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_RSI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SAREXT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SIN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SINH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SQRT\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_STDDEV\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_STOCH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_STOCHF\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_STOCHRSI\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SUB\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_SUM\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_T3\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TAN\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TANH\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TEMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TRANGE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TRIMA\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TRIX\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TSF\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_TYPPRICE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_ULTOSC\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_VAR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_WCLPRICE\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_WILLR\"}");
                sb.Append(",\n");
                sb.Append("  {\"name\":\"TA_WMA\"}");
                sb.Append("\n]");
                return sb.ToString();
            }
            else if (method == "set_unstable_period") {
                int id = p.GetProperty("id").GetInt32();
                int period = p.GetProperty("period").GetInt32();
                TA_SetUnstablePeriod(id, period);
                return "{\"success\":true}";
            }
            else {
                return $"{{\"error\":\"Unknown method: {method}\"}}";
            }
        } catch (Exception ex) {
            return $"{{\"error\":\"{ex.Message.Replace("\"", "'")}\"}}";
        }
    }

    static double[] GetDoubleArray(JsonElement p, string name) {
        var arr = p.GetProperty(name);
        double[] result = new double[arr.GetArrayLength()];
        for (int i = 0; i < result.Length; i++)
            result[i] = arr[i].GetDouble();
        return result;
    }

    static string FormatArray(double[] arr, int count) {
        var parts = new string[count];
        for (int i = 0; i < count; i++)
            parts[i] = arr[i].ToString("G15");
        return "[" + string.Join(",", parts) + "]";
    }

    static string FormatIntArray(int[] arr, int count) {
        var parts = new string[count];
        for (int i = 0; i < count; i++)
            parts[i] = arr[i].ToString();
        return "[" + string.Join(",", parts) + "]";
    }

    static void Main(string[] args) {
        string? line;
        while ((line = Console.ReadLine()) != null) {
            if (string.IsNullOrWhiteSpace(line)) continue;
            Console.WriteLine(HandleRequest(line));
            Console.Out.Flush();
        }
    }
}
