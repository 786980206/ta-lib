#!/usr/bin/env python3
"""Auto-generated JSON-RPC server for ta_codegen SWIG/Python output.
Uses the SWIG-generated ta_lib module to call TA functions.
"""
import sys
import os
import json
import time

# Add script directory to path for SWIG module import
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ta_lib

def handle_request(req):
    method = req.get('method', '')
    params = req.get('params', {})

    if method == 'TA_ACCBANDS':
        return handle_accbands(params)
    if method == 'TA_ACOS':
        return handle_acos(params)
    if method == 'TA_AD':
        return handle_ad(params)
    if method == 'TA_ADD':
        return handle_add(params)
    if method == 'TA_ADOSC':
        return handle_adosc(params)
    if method == 'TA_ADX':
        return handle_adx(params)
    if method == 'TA_ADXR':
        return handle_adxr(params)
    if method == 'TA_APO':
        return handle_apo(params)
    if method == 'TA_AROON':
        return handle_aroon(params)
    if method == 'TA_AROONOSC':
        return handle_aroonosc(params)
    if method == 'TA_ASIN':
        return handle_asin(params)
    if method == 'TA_ATAN':
        return handle_atan(params)
    if method == 'TA_ATR':
        return handle_atr(params)
    if method == 'TA_AVGDEV':
        return handle_avgdev(params)
    if method == 'TA_AVGPRICE':
        return handle_avgprice(params)
    if method == 'TA_BBANDS':
        return handle_bbands(params)
    if method == 'TA_BETA':
        return handle_beta(params)
    if method == 'TA_BOP':
        return handle_bop(params)
    if method == 'TA_CCI':
        return handle_cci(params)
    if method == 'TA_CDL2CROWS':
        return handle_cdl2crows(params)
    if method == 'TA_CDL3BLACKCROWS':
        return handle_cdl3blackcrows(params)
    if method == 'TA_CDL3INSIDE':
        return handle_cdl3inside(params)
    if method == 'TA_CDL3LINESTRIKE':
        return handle_cdl3linestrike(params)
    if method == 'TA_CDL3OUTSIDE':
        return handle_cdl3outside(params)
    if method == 'TA_CDL3STARSINSOUTH':
        return handle_cdl3starsinsouth(params)
    if method == 'TA_CDL3WHITESOLDIERS':
        return handle_cdl3whitesoldiers(params)
    if method == 'TA_CDLABANDONEDBABY':
        return handle_cdlabandonedbaby(params)
    if method == 'TA_CDLADVANCEBLOCK':
        return handle_cdladvanceblock(params)
    if method == 'TA_CDLBELTHOLD':
        return handle_cdlbelthold(params)
    if method == 'TA_CDLBREAKAWAY':
        return handle_cdlbreakaway(params)
    if method == 'TA_CDLCLOSINGMARUBOZU':
        return handle_cdlclosingmarubozu(params)
    if method == 'TA_CDLCONCEALBABYSWALL':
        return handle_cdlconcealbabyswall(params)
    if method == 'TA_CDLCOUNTERATTACK':
        return handle_cdlcounterattack(params)
    if method == 'TA_CDLDARKCLOUDCOVER':
        return handle_cdldarkcloudcover(params)
    if method == 'TA_CDLDOJI':
        return handle_cdldoji(params)
    if method == 'TA_CDLDOJISTAR':
        return handle_cdldojistar(params)
    if method == 'TA_CDLDRAGONFLYDOJI':
        return handle_cdldragonflydoji(params)
    if method == 'TA_CDLENGULFING':
        return handle_cdlengulfing(params)
    if method == 'TA_CDLEVENINGDOJISTAR':
        return handle_cdleveningdojistar(params)
    if method == 'TA_CDLEVENINGSTAR':
        return handle_cdleveningstar(params)
    if method == 'TA_CDLGAPSIDESIDEWHITE':
        return handle_cdlgapsidesidewhite(params)
    if method == 'TA_CDLGRAVESTONEDOJI':
        return handle_cdlgravestonedoji(params)
    if method == 'TA_CDLHAMMER':
        return handle_cdlhammer(params)
    if method == 'TA_CDLHANGINGMAN':
        return handle_cdlhangingman(params)
    if method == 'TA_CDLHARAMI':
        return handle_cdlharami(params)
    if method == 'TA_CDLHARAMICROSS':
        return handle_cdlharamicross(params)
    if method == 'TA_CDLHIGHWAVE':
        return handle_cdlhighwave(params)
    if method == 'TA_CDLHIKKAKE':
        return handle_cdlhikkake(params)
    if method == 'TA_CDLHIKKAKEMOD':
        return handle_cdlhikkakemod(params)
    if method == 'TA_CDLHOMINGPIGEON':
        return handle_cdlhomingpigeon(params)
    if method == 'TA_CDLIDENTICAL3CROWS':
        return handle_cdlidentical3crows(params)
    if method == 'TA_CDLINNECK':
        return handle_cdlinneck(params)
    if method == 'TA_CDLINVERTEDHAMMER':
        return handle_cdlinvertedhammer(params)
    if method == 'TA_CDLKICKING':
        return handle_cdlkicking(params)
    if method == 'TA_CDLKICKINGBYLENGTH':
        return handle_cdlkickingbylength(params)
    if method == 'TA_CDLLADDERBOTTOM':
        return handle_cdlladderbottom(params)
    if method == 'TA_CDLLONGLEGGEDDOJI':
        return handle_cdllongleggeddoji(params)
    if method == 'TA_CDLLONGLINE':
        return handle_cdllongline(params)
    if method == 'TA_CDLMARUBOZU':
        return handle_cdlmarubozu(params)
    if method == 'TA_CDLMATCHINGLOW':
        return handle_cdlmatchinglow(params)
    if method == 'TA_CDLMATHOLD':
        return handle_cdlmathold(params)
    if method == 'TA_CDLMORNINGDOJISTAR':
        return handle_cdlmorningdojistar(params)
    if method == 'TA_CDLMORNINGSTAR':
        return handle_cdlmorningstar(params)
    if method == 'TA_CDLONNECK':
        return handle_cdlonneck(params)
    if method == 'TA_CDLPIERCING':
        return handle_cdlpiercing(params)
    if method == 'TA_CDLRICKSHAWMAN':
        return handle_cdlrickshawman(params)
    if method == 'TA_CDLRISEFALL3METHODS':
        return handle_cdlrisefall3methods(params)
    if method == 'TA_CDLSEPARATINGLINES':
        return handle_cdlseparatinglines(params)
    if method == 'TA_CDLSHOOTINGSTAR':
        return handle_cdlshootingstar(params)
    if method == 'TA_CDLSHORTLINE':
        return handle_cdlshortline(params)
    if method == 'TA_CDLSPINNINGTOP':
        return handle_cdlspinningtop(params)
    if method == 'TA_CDLSTALLEDPATTERN':
        return handle_cdlstalledpattern(params)
    if method == 'TA_CDLSTICKSANDWICH':
        return handle_cdlsticksandwich(params)
    if method == 'TA_CDLTAKURI':
        return handle_cdltakuri(params)
    if method == 'TA_CDLTASUKIGAP':
        return handle_cdltasukigap(params)
    if method == 'TA_CDLTHRUSTING':
        return handle_cdlthrusting(params)
    if method == 'TA_CDLTRISTAR':
        return handle_cdltristar(params)
    if method == 'TA_CDLUNIQUE3RIVER':
        return handle_cdlunique3river(params)
    if method == 'TA_CDLUPSIDEGAP2CROWS':
        return handle_cdlupsidegap2crows(params)
    if method == 'TA_CDLXSIDEGAP3METHODS':
        return handle_cdlxsidegap3methods(params)
    if method == 'TA_CEIL':
        return handle_ceil(params)
    if method == 'TA_CMO':
        return handle_cmo(params)
    if method == 'TA_CORREL':
        return handle_correl(params)
    if method == 'TA_COS':
        return handle_cos(params)
    if method == 'TA_COSH':
        return handle_cosh(params)
    if method == 'TA_DEMA':
        return handle_dema(params)
    if method == 'TA_DIV':
        return handle_div(params)
    if method == 'TA_DX':
        return handle_dx(params)
    if method == 'TA_EMA':
        return handle_ema(params)
    if method == 'TA_EXP':
        return handle_exp(params)
    if method == 'TA_FLOOR':
        return handle_floor(params)
    if method == 'TA_HT_DCPERIOD':
        return handle_ht_dcperiod(params)
    if method == 'TA_HT_DCPHASE':
        return handle_ht_dcphase(params)
    if method == 'TA_HT_PHASOR':
        return handle_ht_phasor(params)
    if method == 'TA_HT_SINE':
        return handle_ht_sine(params)
    if method == 'TA_HT_TRENDLINE':
        return handle_ht_trendline(params)
    if method == 'TA_HT_TRENDMODE':
        return handle_ht_trendmode(params)
    if method == 'TA_IMI':
        return handle_imi(params)
    if method == 'TA_KAMA':
        return handle_kama(params)
    if method == 'TA_LINEARREG':
        return handle_linearreg(params)
    if method == 'TA_LINEARREG_ANGLE':
        return handle_linearreg_angle(params)
    if method == 'TA_LINEARREG_INTERCEPT':
        return handle_linearreg_intercept(params)
    if method == 'TA_LINEARREG_SLOPE':
        return handle_linearreg_slope(params)
    if method == 'TA_LN':
        return handle_ln(params)
    if method == 'TA_LOG10':
        return handle_log10(params)
    if method == 'TA_MA':
        return handle_ma(params)
    if method == 'TA_MACD':
        return handle_macd(params)
    if method == 'TA_MACDEXT':
        return handle_macdext(params)
    if method == 'TA_MACDFIX':
        return handle_macdfix(params)
    if method == 'TA_MAMA':
        return handle_mama(params)
    if method == 'TA_MAVP':
        return handle_mavp(params)
    if method == 'TA_MAX':
        return handle_max(params)
    if method == 'TA_MAXINDEX':
        return handle_maxindex(params)
    if method == 'TA_MEDPRICE':
        return handle_medprice(params)
    if method == 'TA_MFI':
        return handle_mfi(params)
    if method == 'TA_MIDPOINT':
        return handle_midpoint(params)
    if method == 'TA_MIDPRICE':
        return handle_midprice(params)
    if method == 'TA_MIN':
        return handle_min(params)
    if method == 'TA_MININDEX':
        return handle_minindex(params)
    if method == 'TA_MINMAX':
        return handle_minmax(params)
    if method == 'TA_MINMAXINDEX':
        return handle_minmaxindex(params)
    if method == 'TA_MINUS_DI':
        return handle_minus_di(params)
    if method == 'TA_MINUS_DM':
        return handle_minus_dm(params)
    if method == 'TA_MOM':
        return handle_mom(params)
    if method == 'TA_MULT':
        return handle_mult(params)
    if method == 'TA_NATR':
        return handle_natr(params)
    if method == 'TA_NVI':
        return handle_nvi(params)
    if method == 'TA_OBV':
        return handle_obv(params)
    if method == 'TA_PLUS_DI':
        return handle_plus_di(params)
    if method == 'TA_PLUS_DM':
        return handle_plus_dm(params)
    if method == 'TA_PPO':
        return handle_ppo(params)
    if method == 'TA_PVI':
        return handle_pvi(params)
    if method == 'TA_ROC':
        return handle_roc(params)
    if method == 'TA_ROCP':
        return handle_rocp(params)
    if method == 'TA_ROCR':
        return handle_rocr(params)
    if method == 'TA_ROCR100':
        return handle_rocr100(params)
    if method == 'TA_RSI':
        return handle_rsi(params)
    if method == 'TA_SAR':
        return handle_sar(params)
    if method == 'TA_SAREXT':
        return handle_sarext(params)
    if method == 'TA_SIN':
        return handle_sin(params)
    if method == 'TA_SINH':
        return handle_sinh(params)
    if method == 'TA_SMA':
        return handle_sma(params)
    if method == 'TA_SQRT':
        return handle_sqrt(params)
    if method == 'TA_STDDEV':
        return handle_stddev(params)
    if method == 'TA_STOCH':
        return handle_stoch(params)
    if method == 'TA_STOCHF':
        return handle_stochf(params)
    if method == 'TA_STOCHRSI':
        return handle_stochrsi(params)
    if method == 'TA_SUB':
        return handle_sub(params)
    if method == 'TA_SUM':
        return handle_sum(params)
    if method == 'TA_T3':
        return handle_t3(params)
    if method == 'TA_TAN':
        return handle_tan(params)
    if method == 'TA_TANH':
        return handle_tanh(params)
    if method == 'TA_TEMA':
        return handle_tema(params)
    if method == 'TA_TRANGE':
        return handle_trange(params)
    if method == 'TA_TRIMA':
        return handle_trima(params)
    if method == 'TA_TRIX':
        return handle_trix(params)
    if method == 'TA_TSF':
        return handle_tsf(params)
    if method == 'TA_TYPPRICE':
        return handle_typprice(params)
    if method == 'TA_ULTOSC':
        return handle_ultosc(params)
    if method == 'TA_VAR':
        return handle_var(params)
    if method == 'TA_WCLPRICE':
        return handle_wclprice(params)
    if method == 'TA_WILLR':
        return handle_willr(params)
    if method == 'TA_WMA':
        return handle_wma(params)
    if method == 'list_functions':
        return handle_list_functions()
    if method == 'set_unstable_period':
        return handle_set_unstable_period(params)
    return {'error': f'Unknown method: {method}'}

def handle_accbands(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 20))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ACCBANDS(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        out_arr2 = list(result[4])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'outReal2': out_arr2,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_acos(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ACOS(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ad(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_AD(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            inVolume,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_add(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ADD(
            start_idx, end_idx,
            inReal0,
            inReal1,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_adosc(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    optInFastPeriod = int(params.get('optInFastPeriod', 3))
    optInSlowPeriod = int(params.get('optInSlowPeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ADOSC(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            inVolume,
            optInFastPeriod,
            optInSlowPeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_adx(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(0, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ADX(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_adxr(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(1, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ADXR(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_apo(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInFastPeriod = int(params.get('optInFastPeriod', 12))
    optInSlowPeriod = int(params.get('optInSlowPeriod', 26))
    optInMAType = int(params.get('optInMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_APO(
            start_idx, end_idx,
            inReal,
            optInFastPeriod,
            optInSlowPeriod,
            optInMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_aroon(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_AROON(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_aroonosc(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_AROONOSC(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_asin(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ASIN(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_atan(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ATAN(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_atr(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(2, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ATR(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_avgdev(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_AVGDEV(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_avgprice(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_AVGPRICE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_bbands(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 5))
    optInNbDevUp = float(params.get('optInNbDevUp', 2))
    optInNbDevDn = float(params.get('optInNbDevDn', 2))
    optInMAType = int(params.get('optInMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_BBANDS(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInNbDevUp,
            optInNbDevDn,
            optInMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        out_arr2 = list(result[4])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'outReal2': out_arr2,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_beta(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 5))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_BETA(
            start_idx, end_idx,
            inReal0,
            inReal1,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_bop(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_BOP(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cci(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CCI(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl2crows(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL2CROWS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3blackcrows(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3BLACKCROWS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3inside(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3INSIDE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3linestrike(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3LINESTRIKE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3outside(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3OUTSIDE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3starsinsouth(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3STARSINSOUTH(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdl3whitesoldiers(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDL3WHITESOLDIERS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlabandonedbaby(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.3))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLABANDONEDBABY(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdladvanceblock(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLADVANCEBLOCK(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlbelthold(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLBELTHOLD(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlbreakaway(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLBREAKAWAY(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlclosingmarubozu(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLCLOSINGMARUBOZU(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlconcealbabyswall(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLCONCEALBABYSWALL(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlcounterattack(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLCOUNTERATTACK(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdldarkcloudcover(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.5))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLDARKCLOUDCOVER(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdldoji(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLDOJI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdldojistar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLDOJISTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdldragonflydoji(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLDRAGONFLYDOJI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlengulfing(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLENGULFING(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdleveningdojistar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.3))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLEVENINGDOJISTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdleveningstar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.3))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLEVENINGSTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlgapsidesidewhite(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLGAPSIDESIDEWHITE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlgravestonedoji(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLGRAVESTONEDOJI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhammer(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHAMMER(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhangingman(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHANGINGMAN(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlharami(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHARAMI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlharamicross(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHARAMICROSS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhighwave(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHIGHWAVE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhikkake(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHIKKAKE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhikkakemod(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHIKKAKEMOD(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlhomingpigeon(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLHOMINGPIGEON(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlidentical3crows(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLIDENTICAL3CROWS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlinneck(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLINNECK(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlinvertedhammer(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLINVERTEDHAMMER(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlkicking(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLKICKING(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlkickingbylength(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLKICKINGBYLENGTH(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlladderbottom(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLLADDERBOTTOM(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdllongleggeddoji(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLLONGLEGGEDDOJI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdllongline(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLLONGLINE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlmarubozu(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLMARUBOZU(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlmatchinglow(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLMATCHINGLOW(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlmathold(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.5))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLMATHOLD(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlmorningdojistar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.3))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLMORNINGDOJISTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlmorningstar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInPenetration = float(params.get('optInPenetration', 0.3))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLMORNINGSTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
            optInPenetration,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlonneck(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLONNECK(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlpiercing(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLPIERCING(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlrickshawman(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLRICKSHAWMAN(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlrisefall3methods(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLRISEFALL3METHODS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlseparatinglines(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSEPARATINGLINES(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlshootingstar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSHOOTINGSTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlshortline(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSHORTLINE(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlspinningtop(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSPINNINGTOP(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlstalledpattern(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSTALLEDPATTERN(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlsticksandwich(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLSTICKSANDWICH(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdltakuri(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLTAKURI(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdltasukigap(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLTASUKIGAP(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlthrusting(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLTHRUSTING(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdltristar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLTRISTAR(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlunique3river(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLUNIQUE3RIVER(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlupsidegap2crows(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLUPSIDEGAP2CROWS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cdlxsidegap3methods(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CDLXSIDEGAP3METHODS(
            start_idx, end_idx,
            inOpen,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ceil(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CEIL(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cmo(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(3, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CMO(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_correl(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_CORREL(
            start_idx, end_idx,
            inReal0,
            inReal1,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cos(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_COS(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_cosh(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_COSH(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_dema(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_DEMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_div(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_DIV(
            start_idx, end_idx,
            inReal0,
            inReal1,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_dx(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(4, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_DX(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ema(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    ta_lib.TA_SetUnstablePeriod(5, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_EMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_exp(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_EXP(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_floor(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_FLOOR(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_dcperiod(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(6, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_DCPERIOD(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_dcphase(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(7, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_DCPHASE(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_phasor(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(8, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_PHASOR(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_sine(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(9, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_SINE(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_trendline(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(10, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_TRENDLINE(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ht_trendmode(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    ta_lib.TA_SetUnstablePeriod(11, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_HT_TRENDMODE(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_imi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inOpen = [float(x) for x in params.get('inOpen', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(12, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_IMI(
            start_idx, end_idx,
            inOpen,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_kama(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    ta_lib.TA_SetUnstablePeriod(13, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_KAMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_linearreg(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LINEARREG(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_linearreg_angle(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LINEARREG_ANGLE(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_linearreg_intercept(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LINEARREG_INTERCEPT(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_linearreg_slope(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LINEARREG_SLOPE(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ln(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LN(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_log10(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_LOG10(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ma(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    optInMAType = int(params.get('optInMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_macd(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInFastPeriod = int(params.get('optInFastPeriod', 12))
    optInSlowPeriod = int(params.get('optInSlowPeriod', 26))
    optInSignalPeriod = int(params.get('optInSignalPeriod', 9))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MACD(
            start_idx, end_idx,
            inReal,
            optInFastPeriod,
            optInSlowPeriod,
            optInSignalPeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        out_arr2 = list(result[4])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'outReal2': out_arr2,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_macdext(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInFastPeriod = int(params.get('optInFastPeriod', 12))
    optInFastMAType = int(params.get('optInFastMAType', 0))
    optInSlowPeriod = int(params.get('optInSlowPeriod', 26))
    optInSlowMAType = int(params.get('optInSlowMAType', 0))
    optInSignalPeriod = int(params.get('optInSignalPeriod', 9))
    optInSignalMAType = int(params.get('optInSignalMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MACDEXT(
            start_idx, end_idx,
            inReal,
            optInFastPeriod,
            optInFastMAType,
            optInSlowPeriod,
            optInSlowMAType,
            optInSignalPeriod,
            optInSignalMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        out_arr2 = list(result[4])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'outReal2': out_arr2,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_macdfix(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInSignalPeriod = int(params.get('optInSignalPeriod', 9))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MACDFIX(
            start_idx, end_idx,
            inReal,
            optInSignalPeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        out_arr2 = list(result[4])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'outReal2': out_arr2,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_mama(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInFastLimit = float(params.get('optInFastLimit', 0.5))
    optInSlowLimit = float(params.get('optInSlowLimit', 0.05))
    ta_lib.TA_SetUnstablePeriod(14, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MAMA(
            start_idx, end_idx,
            inReal,
            optInFastLimit,
            optInSlowLimit,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_mavp(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    inPeriods = [float(x) for x in params.get('inPeriods', [])]
    optInMinPeriod = int(params.get('optInMinPeriod', 2))
    optInMaxPeriod = int(params.get('optInMaxPeriod', 30))
    optInMAType = int(params.get('optInMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MAVP(
            start_idx, end_idx,
            inReal,
            inPeriods,
            optInMinPeriod,
            optInMaxPeriod,
            optInMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_max(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MAX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_maxindex(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MAXINDEX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_medprice(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MEDPRICE(
            start_idx, end_idx,
            inHigh,
            inLow,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_mfi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(15, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MFI(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            inVolume,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_midpoint(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MIDPOINT(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_midprice(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MIDPRICE(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_min(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MIN(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_minindex(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MININDEX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_minmax(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MINMAX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_minmaxindex(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MINMAXINDEX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outInteger': out_arr0,
            'outInteger1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_minus_di(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(16, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MINUS_DI(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_minus_dm(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(17, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MINUS_DM(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_mom(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MOM(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_mult(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_MULT(
            start_idx, end_idx,
            inReal0,
            inReal1,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_natr(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(18, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_NATR(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_nvi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inClose = [float(x) for x in params.get('inClose', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_NVI(
            start_idx, end_idx,
            inClose,
            inVolume,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_obv(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_OBV(
            start_idx, end_idx,
            inReal,
            inVolume,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_plus_di(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(19, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_PLUS_DI(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_plus_dm(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(20, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_PLUS_DM(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ppo(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInFastPeriod = int(params.get('optInFastPeriod', 12))
    optInSlowPeriod = int(params.get('optInSlowPeriod', 26))
    optInMAType = int(params.get('optInMAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_PPO(
            start_idx, end_idx,
            inReal,
            optInFastPeriod,
            optInSlowPeriod,
            optInMAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_pvi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inClose = [float(x) for x in params.get('inClose', [])]
    inVolume = [float(x) for x in params.get('inVolume', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_PVI(
            start_idx, end_idx,
            inClose,
            inVolume,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_roc(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ROC(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_rocp(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ROCP(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_rocr(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ROCR(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_rocr100(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 10))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ROCR100(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_rsi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    ta_lib.TA_SetUnstablePeriod(21, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_RSI(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sar(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInAcceleration = float(params.get('optInAcceleration', 0.02))
    optInMaximum = float(params.get('optInMaximum', 0.2))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SAR(
            start_idx, end_idx,
            inHigh,
            inLow,
            optInAcceleration,
            optInMaximum,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sarext(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    optInStartValue = float(params.get('optInStartValue', 0))
    optInOffsetOnReverse = float(params.get('optInOffsetOnReverse', 0))
    optInAccelerationInitLong = float(params.get('optInAccelerationInitLong', 0.02))
    optInAccelerationLong = float(params.get('optInAccelerationLong', 0.02))
    optInAccelerationMaxLong = float(params.get('optInAccelerationMaxLong', 0.2))
    optInAccelerationInitShort = float(params.get('optInAccelerationInitShort', 0.02))
    optInAccelerationShort = float(params.get('optInAccelerationShort', 0.02))
    optInAccelerationMaxShort = float(params.get('optInAccelerationMaxShort', 0.2))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SAREXT(
            start_idx, end_idx,
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
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sin(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SIN(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sinh(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SINH(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sma(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sqrt(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SQRT(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_stddev(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 5))
    optInNbDev = float(params.get('optInNbDev', 1))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_STDDEV(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInNbDev,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_stoch(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInFastK_Period = int(params.get('optInFastK_Period', 5))
    optInSlowK_Period = int(params.get('optInSlowK_Period', 3))
    optInSlowK_MAType = int(params.get('optInSlowK_MAType', 0))
    optInSlowD_Period = int(params.get('optInSlowD_Period', 3))
    optInSlowD_MAType = int(params.get('optInSlowD_MAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_STOCH(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInFastK_Period,
            optInSlowK_Period,
            optInSlowK_MAType,
            optInSlowD_Period,
            optInSlowD_MAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_stochf(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInFastK_Period = int(params.get('optInFastK_Period', 5))
    optInFastD_Period = int(params.get('optInFastD_Period', 3))
    optInFastD_MAType = int(params.get('optInFastD_MAType', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_STOCHF(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInFastK_Period,
            optInFastD_Period,
            optInFastD_MAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_stochrsi(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    optInFastK_Period = int(params.get('optInFastK_Period', 5))
    optInFastD_Period = int(params.get('optInFastD_Period', 3))
    optInFastD_MAType = int(params.get('optInFastD_MAType', 0))
    ta_lib.TA_SetUnstablePeriod(22, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_STOCHRSI(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInFastK_Period,
            optInFastD_Period,
            optInFastD_MAType,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        out_arr1 = list(result[3])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'outReal1': out_arr1,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sub(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal0 = [float(x) for x in params.get('inReal0', [])]
    inReal1 = [float(x) for x in params.get('inReal1', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SUB(
            start_idx, end_idx,
            inReal0,
            inReal1,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_sum(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_SUM(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_t3(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 5))
    optInVFactor = float(params.get('optInVFactor', 0.7))
    ta_lib.TA_SetUnstablePeriod(23, params.get('unstablePeriod', 0))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_T3(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInVFactor,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_tan(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TAN(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_tanh(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TANH(
            start_idx, end_idx,
            inReal,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_tema(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TEMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_trange(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TRANGE(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_trima(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TRIMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_trix(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TRIX(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_tsf(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TSF(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_typprice(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_TYPPRICE(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_ultosc(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod1 = int(params.get('optInTimePeriod1', 7))
    optInTimePeriod2 = int(params.get('optInTimePeriod2', 14))
    optInTimePeriod3 = int(params.get('optInTimePeriod3', 28))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_ULTOSC(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod1,
            optInTimePeriod2,
            optInTimePeriod3,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_var(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 5))
    optInNbDev = float(params.get('optInNbDev', 1))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_VAR(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
            optInNbDev,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_wclprice(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_WCLPRICE(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_willr(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inHigh = [float(x) for x in params.get('inHigh', [])]
    inLow = [float(x) for x in params.get('inLow', [])]
    inClose = [float(x) for x in params.get('inClose', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 14))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_WILLR(
            start_idx, end_idx,
            inHigh,
            inLow,
            inClose,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_wma(params):
    start_idx = params.get('startIdx', 0)
    end_idx = params.get('endIdx', 0)
    inReal = [float(x) for x in params.get('inReal', [])]
    optInTimePeriod = int(params.get('optInTimePeriod', 30))
    try:
        start_time = time.perf_counter()
        result = ta_lib.TA_WMA(
            start_idx, end_idx,
            inReal,
            optInTimePeriod,
        )
        end_time = time.perf_counter()
        elapsed_ns = int((end_time - start_time) * 1_000_000_000)
        out_beg = result[1]
        out_arr0 = list(result[2])
        resp = {
            'retCode': 0,
            'outBegIdx': out_beg,
            'outNBElement': len(out_arr0),
            'outReal': out_arr0,
            'timing_ns': elapsed_ns,
        }
        return resp
    except RuntimeError as e:
        return {'error': str(e)}

def handle_list_functions():
    functions = [
        'TA_ACCBANDS',
        'TA_ACOS',
        'TA_AD',
        'TA_ADD',
        'TA_ADOSC',
        'TA_ADX',
        'TA_ADXR',
        'TA_APO',
        'TA_AROON',
        'TA_AROONOSC',
        'TA_ASIN',
        'TA_ATAN',
        'TA_ATR',
        'TA_AVGDEV',
        'TA_AVGPRICE',
        'TA_BBANDS',
        'TA_BETA',
        'TA_BOP',
        'TA_CCI',
        'TA_CDL2CROWS',
        'TA_CDL3BLACKCROWS',
        'TA_CDL3INSIDE',
        'TA_CDL3LINESTRIKE',
        'TA_CDL3OUTSIDE',
        'TA_CDL3STARSINSOUTH',
        'TA_CDL3WHITESOLDIERS',
        'TA_CDLABANDONEDBABY',
        'TA_CDLADVANCEBLOCK',
        'TA_CDLBELTHOLD',
        'TA_CDLBREAKAWAY',
        'TA_CDLCLOSINGMARUBOZU',
        'TA_CDLCONCEALBABYSWALL',
        'TA_CDLCOUNTERATTACK',
        'TA_CDLDARKCLOUDCOVER',
        'TA_CDLDOJI',
        'TA_CDLDOJISTAR',
        'TA_CDLDRAGONFLYDOJI',
        'TA_CDLENGULFING',
        'TA_CDLEVENINGDOJISTAR',
        'TA_CDLEVENINGSTAR',
        'TA_CDLGAPSIDESIDEWHITE',
        'TA_CDLGRAVESTONEDOJI',
        'TA_CDLHAMMER',
        'TA_CDLHANGINGMAN',
        'TA_CDLHARAMI',
        'TA_CDLHARAMICROSS',
        'TA_CDLHIGHWAVE',
        'TA_CDLHIKKAKE',
        'TA_CDLHIKKAKEMOD',
        'TA_CDLHOMINGPIGEON',
        'TA_CDLIDENTICAL3CROWS',
        'TA_CDLINNECK',
        'TA_CDLINVERTEDHAMMER',
        'TA_CDLKICKING',
        'TA_CDLKICKINGBYLENGTH',
        'TA_CDLLADDERBOTTOM',
        'TA_CDLLONGLEGGEDDOJI',
        'TA_CDLLONGLINE',
        'TA_CDLMARUBOZU',
        'TA_CDLMATCHINGLOW',
        'TA_CDLMATHOLD',
        'TA_CDLMORNINGDOJISTAR',
        'TA_CDLMORNINGSTAR',
        'TA_CDLONNECK',
        'TA_CDLPIERCING',
        'TA_CDLRICKSHAWMAN',
        'TA_CDLRISEFALL3METHODS',
        'TA_CDLSEPARATINGLINES',
        'TA_CDLSHOOTINGSTAR',
        'TA_CDLSHORTLINE',
        'TA_CDLSPINNINGTOP',
        'TA_CDLSTALLEDPATTERN',
        'TA_CDLSTICKSANDWICH',
        'TA_CDLTAKURI',
        'TA_CDLTASUKIGAP',
        'TA_CDLTHRUSTING',
        'TA_CDLTRISTAR',
        'TA_CDLUNIQUE3RIVER',
        'TA_CDLUPSIDEGAP2CROWS',
        'TA_CDLXSIDEGAP3METHODS',
        'TA_CEIL',
        'TA_CMO',
        'TA_CORREL',
        'TA_COS',
        'TA_COSH',
        'TA_DEMA',
        'TA_DIV',
        'TA_DX',
        'TA_EMA',
        'TA_EXP',
        'TA_FLOOR',
        'TA_HT_DCPERIOD',
        'TA_HT_DCPHASE',
        'TA_HT_PHASOR',
        'TA_HT_SINE',
        'TA_HT_TRENDLINE',
        'TA_HT_TRENDMODE',
        'TA_IMI',
        'TA_KAMA',
        'TA_LINEARREG',
        'TA_LINEARREG_ANGLE',
        'TA_LINEARREG_INTERCEPT',
        'TA_LINEARREG_SLOPE',
        'TA_LN',
        'TA_LOG10',
        'TA_MA',
        'TA_MACD',
        'TA_MACDEXT',
        'TA_MACDFIX',
        'TA_MAMA',
        'TA_MAVP',
        'TA_MAX',
        'TA_MAXINDEX',
        'TA_MEDPRICE',
        'TA_MFI',
        'TA_MIDPOINT',
        'TA_MIDPRICE',
        'TA_MIN',
        'TA_MININDEX',
        'TA_MINMAX',
        'TA_MINMAXINDEX',
        'TA_MINUS_DI',
        'TA_MINUS_DM',
        'TA_MOM',
        'TA_MULT',
        'TA_NATR',
        'TA_NVI',
        'TA_OBV',
        'TA_PLUS_DI',
        'TA_PLUS_DM',
        'TA_PPO',
        'TA_PVI',
        'TA_ROC',
        'TA_ROCP',
        'TA_ROCR',
        'TA_ROCR100',
        'TA_RSI',
        'TA_SAR',
        'TA_SAREXT',
        'TA_SIN',
        'TA_SINH',
        'TA_SMA',
        'TA_SQRT',
        'TA_STDDEV',
        'TA_STOCH',
        'TA_STOCHF',
        'TA_STOCHRSI',
        'TA_SUB',
        'TA_SUM',
        'TA_T3',
        'TA_TAN',
        'TA_TANH',
        'TA_TEMA',
        'TA_TRANGE',
        'TA_TRIMA',
        'TA_TRIX',
        'TA_TSF',
        'TA_TYPPRICE',
        'TA_ULTOSC',
        'TA_VAR',
        'TA_WCLPRICE',
        'TA_WILLR',
        'TA_WMA',
    ]
    return {'functions': functions}

def handle_set_unstable_period(params):
    func_id = params.get('id', 0)
    period = params.get('period', 0)
    ta_lib.TA_SetUnstablePeriod(func_id, period)
    return {'retCode': 0}

if __name__ == '__main__':
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        try:
            req = json.loads(line)
            resp = handle_request(req)
            print(json.dumps(resp), flush=True)
        except Exception as e:
            print(json.dumps({'error': str(e)}), flush=True)
