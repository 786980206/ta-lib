%module ta_lib

%{
typedef int TA_RetCode;
typedef double TA_Real;
typedef int TA_Integer;
#define TA_SUCCESS 0
#define TA_INTEGER_DEFAULT (-2147483648)
#define TA_REAL_DEFAULT (-4e+37)
extern void TA_SetUnstablePeriod(int id, int period);
extern TA_RetCode TA_ACCBANDS(int, int, const double*, const double*, const double*, int, int*, int*, double*, double*, double*);
extern int TA_ACCBANDS_Lookback(int);
extern TA_RetCode TA_ACOS(int, int, const double*, int*, int*, double*);
extern int TA_ACOS_Lookback(void);
extern TA_RetCode TA_AD(int, int, const double*, const double*, const double*, const double*, int*, int*, double*);
extern int TA_AD_Lookback(void);
extern TA_RetCode TA_ADD(int, int, const double*, const double*, int*, int*, double*);
extern int TA_ADD_Lookback(void);
extern TA_RetCode TA_ADOSC(int, int, const double*, const double*, const double*, const double*, int, int, int*, int*, double*);
extern int TA_ADOSC_Lookback(int, int);
extern TA_RetCode TA_ADX(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_ADX_Lookback(int);
extern TA_RetCode TA_ADXR(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_ADXR_Lookback(int);
extern TA_RetCode TA_APO(int, int, const double*, int, int, int, int*, int*, double*);
extern int TA_APO_Lookback(int, int, int);
extern TA_RetCode TA_AROON(int, int, const double*, const double*, int, int*, int*, double*, double*);
extern int TA_AROON_Lookback(int);
extern TA_RetCode TA_AROONOSC(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_AROONOSC_Lookback(int);
extern TA_RetCode TA_ASIN(int, int, const double*, int*, int*, double*);
extern int TA_ASIN_Lookback(void);
extern TA_RetCode TA_ATAN(int, int, const double*, int*, int*, double*);
extern int TA_ATAN_Lookback(void);
extern TA_RetCode TA_ATR(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_ATR_Lookback(int);
extern TA_RetCode TA_AVGDEV(int, int, const double*, int, int*, int*, double*);
extern int TA_AVGDEV_Lookback(int);
extern TA_RetCode TA_AVGPRICE(int, int, const double*, const double*, const double*, const double*, int*, int*, double*);
extern int TA_AVGPRICE_Lookback(void);
extern TA_RetCode TA_BBANDS(int, int, const double*, int, double, double, int, int*, int*, double*, double*, double*);
extern int TA_BBANDS_Lookback(int, double, double, int);
extern TA_RetCode TA_BETA(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_BETA_Lookback(int);
extern TA_RetCode TA_BOP(int, int, const double*, const double*, const double*, const double*, int*, int*, double*);
extern int TA_BOP_Lookback(void);
extern TA_RetCode TA_CCI(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_CCI_Lookback(int);
extern TA_RetCode TA_CDL2CROWS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL2CROWS_Lookback(void);
extern TA_RetCode TA_CDL3BLACKCROWS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3BLACKCROWS_Lookback(void);
extern TA_RetCode TA_CDL3INSIDE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3INSIDE_Lookback(void);
extern TA_RetCode TA_CDL3LINESTRIKE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3LINESTRIKE_Lookback(void);
extern TA_RetCode TA_CDL3OUTSIDE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3OUTSIDE_Lookback(void);
extern TA_RetCode TA_CDL3STARSINSOUTH(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3STARSINSOUTH_Lookback(void);
extern TA_RetCode TA_CDL3WHITESOLDIERS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDL3WHITESOLDIERS_Lookback(void);
extern TA_RetCode TA_CDLABANDONEDBABY(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLABANDONEDBABY_Lookback(double);
extern TA_RetCode TA_CDLADVANCEBLOCK(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLADVANCEBLOCK_Lookback(void);
extern TA_RetCode TA_CDLBELTHOLD(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLBELTHOLD_Lookback(void);
extern TA_RetCode TA_CDLBREAKAWAY(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLBREAKAWAY_Lookback(void);
extern TA_RetCode TA_CDLCLOSINGMARUBOZU(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLCLOSINGMARUBOZU_Lookback(void);
extern TA_RetCode TA_CDLCONCEALBABYSWALL(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLCONCEALBABYSWALL_Lookback(void);
extern TA_RetCode TA_CDLCOUNTERATTACK(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLCOUNTERATTACK_Lookback(void);
extern TA_RetCode TA_CDLDARKCLOUDCOVER(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLDARKCLOUDCOVER_Lookback(double);
extern TA_RetCode TA_CDLDOJI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLDOJI_Lookback(void);
extern TA_RetCode TA_CDLDOJISTAR(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLDOJISTAR_Lookback(void);
extern TA_RetCode TA_CDLDRAGONFLYDOJI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLDRAGONFLYDOJI_Lookback(void);
extern TA_RetCode TA_CDLENGULFING(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLENGULFING_Lookback(void);
extern TA_RetCode TA_CDLEVENINGDOJISTAR(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLEVENINGDOJISTAR_Lookback(double);
extern TA_RetCode TA_CDLEVENINGSTAR(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLEVENINGSTAR_Lookback(double);
extern TA_RetCode TA_CDLGAPSIDESIDEWHITE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLGAPSIDESIDEWHITE_Lookback(void);
extern TA_RetCode TA_CDLGRAVESTONEDOJI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLGRAVESTONEDOJI_Lookback(void);
extern TA_RetCode TA_CDLHAMMER(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHAMMER_Lookback(void);
extern TA_RetCode TA_CDLHANGINGMAN(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHANGINGMAN_Lookback(void);
extern TA_RetCode TA_CDLHARAMI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHARAMI_Lookback(void);
extern TA_RetCode TA_CDLHARAMICROSS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHARAMICROSS_Lookback(void);
extern TA_RetCode TA_CDLHIGHWAVE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHIGHWAVE_Lookback(void);
extern TA_RetCode TA_CDLHIKKAKE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHIKKAKE_Lookback(void);
extern TA_RetCode TA_CDLHIKKAKEMOD(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHIKKAKEMOD_Lookback(void);
extern TA_RetCode TA_CDLHOMINGPIGEON(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLHOMINGPIGEON_Lookback(void);
extern TA_RetCode TA_CDLIDENTICAL3CROWS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLIDENTICAL3CROWS_Lookback(void);
extern TA_RetCode TA_CDLINNECK(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLINNECK_Lookback(void);
extern TA_RetCode TA_CDLINVERTEDHAMMER(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLINVERTEDHAMMER_Lookback(void);
extern TA_RetCode TA_CDLKICKING(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLKICKING_Lookback(void);
extern TA_RetCode TA_CDLKICKINGBYLENGTH(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLKICKINGBYLENGTH_Lookback(void);
extern TA_RetCode TA_CDLLADDERBOTTOM(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLLADDERBOTTOM_Lookback(void);
extern TA_RetCode TA_CDLLONGLEGGEDDOJI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLLONGLEGGEDDOJI_Lookback(void);
extern TA_RetCode TA_CDLLONGLINE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLLONGLINE_Lookback(void);
extern TA_RetCode TA_CDLMARUBOZU(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLMARUBOZU_Lookback(void);
extern TA_RetCode TA_CDLMATCHINGLOW(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLMATCHINGLOW_Lookback(void);
extern TA_RetCode TA_CDLMATHOLD(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLMATHOLD_Lookback(double);
extern TA_RetCode TA_CDLMORNINGDOJISTAR(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLMORNINGDOJISTAR_Lookback(double);
extern TA_RetCode TA_CDLMORNINGSTAR(int, int, const double*, const double*, const double*, const double*, double, int*, int*, int*);
extern int TA_CDLMORNINGSTAR_Lookback(double);
extern TA_RetCode TA_CDLONNECK(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLONNECK_Lookback(void);
extern TA_RetCode TA_CDLPIERCING(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLPIERCING_Lookback(void);
extern TA_RetCode TA_CDLRICKSHAWMAN(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLRICKSHAWMAN_Lookback(void);
extern TA_RetCode TA_CDLRISEFALL3METHODS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLRISEFALL3METHODS_Lookback(void);
extern TA_RetCode TA_CDLSEPARATINGLINES(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSEPARATINGLINES_Lookback(void);
extern TA_RetCode TA_CDLSHOOTINGSTAR(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSHOOTINGSTAR_Lookback(void);
extern TA_RetCode TA_CDLSHORTLINE(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSHORTLINE_Lookback(void);
extern TA_RetCode TA_CDLSPINNINGTOP(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSPINNINGTOP_Lookback(void);
extern TA_RetCode TA_CDLSTALLEDPATTERN(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSTALLEDPATTERN_Lookback(void);
extern TA_RetCode TA_CDLSTICKSANDWICH(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLSTICKSANDWICH_Lookback(void);
extern TA_RetCode TA_CDLTAKURI(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLTAKURI_Lookback(void);
extern TA_RetCode TA_CDLTASUKIGAP(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLTASUKIGAP_Lookback(void);
extern TA_RetCode TA_CDLTHRUSTING(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLTHRUSTING_Lookback(void);
extern TA_RetCode TA_CDLTRISTAR(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLTRISTAR_Lookback(void);
extern TA_RetCode TA_CDLUNIQUE3RIVER(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLUNIQUE3RIVER_Lookback(void);
extern TA_RetCode TA_CDLUPSIDEGAP2CROWS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLUPSIDEGAP2CROWS_Lookback(void);
extern TA_RetCode TA_CDLXSIDEGAP3METHODS(int, int, const double*, const double*, const double*, const double*, int*, int*, int*);
extern int TA_CDLXSIDEGAP3METHODS_Lookback(void);
extern TA_RetCode TA_CEIL(int, int, const double*, int*, int*, double*);
extern int TA_CEIL_Lookback(void);
extern TA_RetCode TA_CMO(int, int, const double*, int, int*, int*, double*);
extern int TA_CMO_Lookback(int);
extern TA_RetCode TA_CORREL(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_CORREL_Lookback(int);
extern TA_RetCode TA_COS(int, int, const double*, int*, int*, double*);
extern int TA_COS_Lookback(void);
extern TA_RetCode TA_COSH(int, int, const double*, int*, int*, double*);
extern int TA_COSH_Lookback(void);
extern TA_RetCode TA_DEMA(int, int, const double*, int, int*, int*, double*);
extern int TA_DEMA_Lookback(int);
extern TA_RetCode TA_DIV(int, int, const double*, const double*, int*, int*, double*);
extern int TA_DIV_Lookback(void);
extern TA_RetCode TA_DX(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_DX_Lookback(int);
extern TA_RetCode TA_EMA(int, int, const double*, int, int*, int*, double*);
extern int TA_EMA_Lookback(int);
extern TA_RetCode TA_EXP(int, int, const double*, int*, int*, double*);
extern int TA_EXP_Lookback(void);
extern TA_RetCode TA_FLOOR(int, int, const double*, int*, int*, double*);
extern int TA_FLOOR_Lookback(void);
extern TA_RetCode TA_HT_DCPERIOD(int, int, const double*, int*, int*, double*);
extern int TA_HT_DCPERIOD_Lookback(void);
extern TA_RetCode TA_HT_DCPHASE(int, int, const double*, int*, int*, double*);
extern int TA_HT_DCPHASE_Lookback(void);
extern TA_RetCode TA_HT_PHASOR(int, int, const double*, int*, int*, double*, double*);
extern int TA_HT_PHASOR_Lookback(void);
extern TA_RetCode TA_HT_SINE(int, int, const double*, int*, int*, double*, double*);
extern int TA_HT_SINE_Lookback(void);
extern TA_RetCode TA_HT_TRENDLINE(int, int, const double*, int*, int*, double*);
extern int TA_HT_TRENDLINE_Lookback(void);
extern TA_RetCode TA_HT_TRENDMODE(int, int, const double*, int*, int*, int*);
extern int TA_HT_TRENDMODE_Lookback(void);
extern TA_RetCode TA_IMI(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_IMI_Lookback(int);
extern TA_RetCode TA_KAMA(int, int, const double*, int, int*, int*, double*);
extern int TA_KAMA_Lookback(int);
extern TA_RetCode TA_LINEARREG(int, int, const double*, int, int*, int*, double*);
extern int TA_LINEARREG_Lookback(int);
extern TA_RetCode TA_LINEARREG_ANGLE(int, int, const double*, int, int*, int*, double*);
extern int TA_LINEARREG_ANGLE_Lookback(int);
extern TA_RetCode TA_LINEARREG_INTERCEPT(int, int, const double*, int, int*, int*, double*);
extern int TA_LINEARREG_INTERCEPT_Lookback(int);
extern TA_RetCode TA_LINEARREG_SLOPE(int, int, const double*, int, int*, int*, double*);
extern int TA_LINEARREG_SLOPE_Lookback(int);
extern TA_RetCode TA_LN(int, int, const double*, int*, int*, double*);
extern int TA_LN_Lookback(void);
extern TA_RetCode TA_LOG10(int, int, const double*, int*, int*, double*);
extern int TA_LOG10_Lookback(void);
extern TA_RetCode TA_MA(int, int, const double*, int, int, int*, int*, double*);
extern int TA_MA_Lookback(int, int);
extern TA_RetCode TA_MACD(int, int, const double*, int, int, int, int*, int*, double*, double*, double*);
extern int TA_MACD_Lookback(int, int, int);
extern TA_RetCode TA_MACDEXT(int, int, const double*, int, int, int, int, int, int, int*, int*, double*, double*, double*);
extern int TA_MACDEXT_Lookback(int, int, int, int, int, int);
extern TA_RetCode TA_MACDFIX(int, int, const double*, int, int*, int*, double*, double*, double*);
extern int TA_MACDFIX_Lookback(int);
extern TA_RetCode TA_MAMA(int, int, const double*, double, double, int*, int*, double*, double*);
extern int TA_MAMA_Lookback(double, double);
extern TA_RetCode TA_MAVP(int, int, const double*, const double*, int, int, int, int*, int*, double*);
extern int TA_MAVP_Lookback(int, int, int);
extern TA_RetCode TA_MAX(int, int, const double*, int, int*, int*, double*);
extern int TA_MAX_Lookback(int);
extern TA_RetCode TA_MAXINDEX(int, int, const double*, int, int*, int*, int*);
extern int TA_MAXINDEX_Lookback(int);
extern TA_RetCode TA_MEDPRICE(int, int, const double*, const double*, int*, int*, double*);
extern int TA_MEDPRICE_Lookback(void);
extern TA_RetCode TA_MFI(int, int, const double*, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_MFI_Lookback(int);
extern TA_RetCode TA_MIDPOINT(int, int, const double*, int, int*, int*, double*);
extern int TA_MIDPOINT_Lookback(int);
extern TA_RetCode TA_MIDPRICE(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_MIDPRICE_Lookback(int);
extern TA_RetCode TA_MIN(int, int, const double*, int, int*, int*, double*);
extern int TA_MIN_Lookback(int);
extern TA_RetCode TA_MININDEX(int, int, const double*, int, int*, int*, int*);
extern int TA_MININDEX_Lookback(int);
extern TA_RetCode TA_MINMAX(int, int, const double*, int, int*, int*, double*, double*);
extern int TA_MINMAX_Lookback(int);
extern TA_RetCode TA_MINMAXINDEX(int, int, const double*, int, int*, int*, int*, int*);
extern int TA_MINMAXINDEX_Lookback(int);
extern TA_RetCode TA_MINUS_DI(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_MINUS_DI_Lookback(int);
extern TA_RetCode TA_MINUS_DM(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_MINUS_DM_Lookback(int);
extern TA_RetCode TA_MOM(int, int, const double*, int, int*, int*, double*);
extern int TA_MOM_Lookback(int);
extern TA_RetCode TA_MULT(int, int, const double*, const double*, int*, int*, double*);
extern int TA_MULT_Lookback(void);
extern TA_RetCode TA_NATR(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_NATR_Lookback(int);
extern TA_RetCode TA_NVI(int, int, const double*, const double*, int*, int*, double*);
extern int TA_NVI_Lookback(void);
extern TA_RetCode TA_OBV(int, int, const double*, const double*, int*, int*, double*);
extern int TA_OBV_Lookback(void);
extern TA_RetCode TA_PLUS_DI(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_PLUS_DI_Lookback(int);
extern TA_RetCode TA_PLUS_DM(int, int, const double*, const double*, int, int*, int*, double*);
extern int TA_PLUS_DM_Lookback(int);
extern TA_RetCode TA_PPO(int, int, const double*, int, int, int, int*, int*, double*);
extern int TA_PPO_Lookback(int, int, int);
extern TA_RetCode TA_PVI(int, int, const double*, const double*, int*, int*, double*);
extern int TA_PVI_Lookback(void);
extern TA_RetCode TA_ROC(int, int, const double*, int, int*, int*, double*);
extern int TA_ROC_Lookback(int);
extern TA_RetCode TA_ROCP(int, int, const double*, int, int*, int*, double*);
extern int TA_ROCP_Lookback(int);
extern TA_RetCode TA_ROCR(int, int, const double*, int, int*, int*, double*);
extern int TA_ROCR_Lookback(int);
extern TA_RetCode TA_ROCR100(int, int, const double*, int, int*, int*, double*);
extern int TA_ROCR100_Lookback(int);
extern TA_RetCode TA_RSI(int, int, const double*, int, int*, int*, double*);
extern int TA_RSI_Lookback(int);
extern TA_RetCode TA_SAR(int, int, const double*, const double*, double, double, int*, int*, double*);
extern int TA_SAR_Lookback(double, double);
extern TA_RetCode TA_SAREXT(int, int, const double*, const double*, double, double, double, double, double, double, double, double, int*, int*, double*);
extern int TA_SAREXT_Lookback(double, double, double, double, double, double, double, double);
extern TA_RetCode TA_SIN(int, int, const double*, int*, int*, double*);
extern int TA_SIN_Lookback(void);
extern TA_RetCode TA_SINH(int, int, const double*, int*, int*, double*);
extern int TA_SINH_Lookback(void);
extern TA_RetCode TA_SMA(int, int, const double*, int, int*, int*, double*);
extern int TA_SMA_Lookback(int);
extern TA_RetCode TA_SQRT(int, int, const double*, int*, int*, double*);
extern int TA_SQRT_Lookback(void);
extern TA_RetCode TA_STDDEV(int, int, const double*, int, double, int*, int*, double*);
extern int TA_STDDEV_Lookback(int, double);
extern TA_RetCode TA_STOCH(int, int, const double*, const double*, const double*, int, int, int, int, int, int*, int*, double*, double*);
extern int TA_STOCH_Lookback(int, int, int, int, int);
extern TA_RetCode TA_STOCHF(int, int, const double*, const double*, const double*, int, int, int, int*, int*, double*, double*);
extern int TA_STOCHF_Lookback(int, int, int);
extern TA_RetCode TA_STOCHRSI(int, int, const double*, int, int, int, int, int*, int*, double*, double*);
extern int TA_STOCHRSI_Lookback(int, int, int, int);
extern TA_RetCode TA_SUB(int, int, const double*, const double*, int*, int*, double*);
extern int TA_SUB_Lookback(void);
extern TA_RetCode TA_SUM(int, int, const double*, int, int*, int*, double*);
extern int TA_SUM_Lookback(int);
extern TA_RetCode TA_T3(int, int, const double*, int, double, int*, int*, double*);
extern int TA_T3_Lookback(int, double);
extern TA_RetCode TA_TAN(int, int, const double*, int*, int*, double*);
extern int TA_TAN_Lookback(void);
extern TA_RetCode TA_TANH(int, int, const double*, int*, int*, double*);
extern int TA_TANH_Lookback(void);
extern TA_RetCode TA_TEMA(int, int, const double*, int, int*, int*, double*);
extern int TA_TEMA_Lookback(int);
extern TA_RetCode TA_TRANGE(int, int, const double*, const double*, const double*, int*, int*, double*);
extern int TA_TRANGE_Lookback(void);
extern TA_RetCode TA_TRIMA(int, int, const double*, int, int*, int*, double*);
extern int TA_TRIMA_Lookback(int);
extern TA_RetCode TA_TRIX(int, int, const double*, int, int*, int*, double*);
extern int TA_TRIX_Lookback(int);
extern TA_RetCode TA_TSF(int, int, const double*, int, int*, int*, double*);
extern int TA_TSF_Lookback(int);
extern TA_RetCode TA_TYPPRICE(int, int, const double*, const double*, const double*, int*, int*, double*);
extern int TA_TYPPRICE_Lookback(void);
extern TA_RetCode TA_ULTOSC(int, int, const double*, const double*, const double*, int, int, int, int*, int*, double*);
extern int TA_ULTOSC_Lookback(int, int, int);
extern TA_RetCode TA_VAR(int, int, const double*, int, double, int*, int*, double*);
extern int TA_VAR_Lookback(int, double);
extern TA_RetCode TA_WCLPRICE(int, int, const double*, const double*, const double*, int*, int*, double*);
extern int TA_WCLPRICE_Lookback(void);
extern TA_RetCode TA_WILLR(int, int, const double*, const double*, const double*, int, int*, int*, double*);
extern int TA_WILLR_Lookback(int);
extern TA_RetCode TA_WMA(int, int, const double*, int, int*, int*, double*);
extern int TA_WMA_Lookback(int);
%}

#define TA_SUCCESS 0
#define TA_FUNC_UNST_ADX 0
#define TA_FUNC_UNST_ADXR 1
#define TA_FUNC_UNST_ATR 2
#define TA_FUNC_UNST_CMO 3
#define TA_FUNC_UNST_DX 4
#define TA_FUNC_UNST_EMA 5
#define TA_FUNC_UNST_HT_DCPERIOD 6
#define TA_FUNC_UNST_HT_DCPHASE 7
#define TA_FUNC_UNST_HT_PHASOR 8
#define TA_FUNC_UNST_HT_SINE 9
#define TA_FUNC_UNST_HT_TRENDLINE 10
#define TA_FUNC_UNST_HT_TRENDMODE 11
#define TA_FUNC_UNST_IMI 12
#define TA_FUNC_UNST_KAMA 13
#define TA_FUNC_UNST_MAMA 14
#define TA_FUNC_UNST_MFI 15
#define TA_FUNC_UNST_MINUS_DI 16
#define TA_FUNC_UNST_MINUS_DM 17
#define TA_FUNC_UNST_NATR 18
#define TA_FUNC_UNST_PLUS_DI 19
#define TA_FUNC_UNST_PLUS_DM 20
#define TA_FUNC_UNST_RSI 21
#define TA_FUNC_UNST_STOCHRSI 22
#define TA_FUNC_UNST_T3 23
extern void TA_SetUnstablePeriod(int id, int period);

/* ---- Python 3 typemaps for TA-Lib functions ---- */

%{
static int convert_darray(PyObject *input, double *ptr, int size) {
    int i, len;
    if (!PySequence_Check(input)) {
        PyErr_SetString(PyExc_TypeError, "Expecting a sequence");
        return 0;
    }
    len = (int)PyObject_Length(input);
    if (len > size) len = size;
    for (i = 0; i < len; i++) {
        PyObject *o = PySequence_GetItem(input, i);
        if (PyFloat_Check(o)) {
            ptr[i] = PyFloat_AsDouble(o);
        } else if (PyLong_Check(o)) {
            ptr[i] = (double)PyLong_AsLong(o);
        } else {
            PyErr_SetString(PyExc_ValueError, "Expecting a sequence of numbers");
            Py_DECREF(o);
            return 0;
        }
        Py_DECREF(o);
    }
    return 1;
}
%}

/* TA_RetCode: return None on success, raise exception on failure */
%typemap(out) TA_RetCode {
    if ($1 != TA_SUCCESS) {
        char text[200];
        snprintf(text, sizeof(text)-1, "TA function failed with code %d", $1);
        PyErr_SetString(PyExc_RuntimeError, text);
        SWIG_fail;
    }
    Py_INCREF(Py_None);
    $result = Py_None;
}

/* START_IDX and END_IDX */
%typemap(in) int START_IDX (int startIdx) {
    $1 = (int)PyLong_AsLong($input);
    if ($1 < 0) $1 = 0;
    startIdx = $1;
}

%typemap(in) int END_IDX (int endIdx) {
    $1 = (int)PyLong_AsLong($input);
    if ($1 < startIdx1) $1 = startIdx1;
    endIdx = $1;
}

/* Input arrays */
%typemap(in) const double *IN_ARRAY {
    int array_size = endIdx2 + 1;
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
    if (!convert_darray($input, $1, array_size)) goto fail;
}

%typemap(freearg) const double *IN_ARRAY
    "free($1);";

/* Optional integer params */
%typemap(default) int OPT_INT
    "$1 = TA_INTEGER_DEFAULT;"

%typemap(in) int OPT_INT {
    if (PyLong_Check($input)) {
        $1 = ($1_ltype)PyLong_AsLong($input);
    }
}

/* outBegIdx */
%typemap(in,numinputs=0) int *BEG_IDX(int temp = 0)
    "$1 = &temp;";

%typemap(argout) int *BEG_IDX {
    if (result == TA_SUCCESS) {
        PyObject *o = PyLong_FromLong((long)(*$1));
        $result = SWIG_Python_AppendOutput($result, o, 0);
    }
}

/* outNBElement */
%typemap(arginit) int *OUT_SIZE
    "int outNbElement = 0;";

%typemap(in,numinputs=0) int *OUT_SIZE
    "$1 = &outNbElement;";

/* Output arrays */
%typemap(in,numinputs=0) double *OUT_ARRAY, int *OUT_ARRAY
    "/* $1 ignored on input */";

%typemap(check) double *OUT_ARRAY, int *OUT_ARRAY {
    int array_size = endIdx2 - startIdx1 + 1;
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
}

%typemap(argout) double *OUT_ARRAY {
    if (result == TA_SUCCESS) {
        int idx;
        PyObject *list = PyList_New(outNbElement);
        for (idx = 0; idx < outNbElement; idx++) {
            PyObject *o = PyFloat_FromDouble($1[idx]);
            PyList_SET_ITEM(list, idx, o);
        }
        $result = SWIG_Python_AppendOutput($result, list, 0);
    }
}

%typemap(argout) int *OUT_ARRAY {
    if (result == TA_SUCCESS) {
        int idx;
        PyObject *list = PyList_New(outNbElement);
        for (idx = 0; idx < outNbElement; idx++) {
            PyObject *o = PyLong_FromLong($1[idx]);
            PyList_SET_ITEM(list, idx, o);
        }
        $result = SWIG_Python_AppendOutput($result, list, 0);
    }
}

%typemap(freearg) double *OUT_ARRAY, int *OUT_ARRAY
    "free($1);";


/* TA_ACCBANDS */
%include "ta_ACCBANDS.swg"

/* TA_ACOS */
%include "ta_ACOS.swg"

/* TA_AD */
%include "ta_AD.swg"

/* TA_ADD */
%include "ta_ADD.swg"

/* TA_ADOSC */
%include "ta_ADOSC.swg"

/* TA_ADX */
%include "ta_ADX.swg"

/* TA_ADXR */
%include "ta_ADXR.swg"

/* TA_APO */
%include "ta_APO.swg"

/* TA_AROON */
%include "ta_AROON.swg"

/* TA_AROONOSC */
%include "ta_AROONOSC.swg"

/* TA_ASIN */
%include "ta_ASIN.swg"

/* TA_ATAN */
%include "ta_ATAN.swg"

/* TA_ATR */
%include "ta_ATR.swg"

/* TA_AVGDEV */
%include "ta_AVGDEV.swg"

/* TA_AVGPRICE */
%include "ta_AVGPRICE.swg"

/* TA_BBANDS */
%include "ta_BBANDS.swg"

/* TA_BETA */
%include "ta_BETA.swg"

/* TA_BOP */
%include "ta_BOP.swg"

/* TA_CCI */
%include "ta_CCI.swg"

/* TA_CDL2CROWS */
%include "ta_CDL2CROWS.swg"

/* TA_CDL3BLACKCROWS */
%include "ta_CDL3BLACKCROWS.swg"

/* TA_CDL3INSIDE */
%include "ta_CDL3INSIDE.swg"

/* TA_CDL3LINESTRIKE */
%include "ta_CDL3LINESTRIKE.swg"

/* TA_CDL3OUTSIDE */
%include "ta_CDL3OUTSIDE.swg"

/* TA_CDL3STARSINSOUTH */
%include "ta_CDL3STARSINSOUTH.swg"

/* TA_CDL3WHITESOLDIERS */
%include "ta_CDL3WHITESOLDIERS.swg"

/* TA_CDLABANDONEDBABY */
%include "ta_CDLABANDONEDBABY.swg"

/* TA_CDLADVANCEBLOCK */
%include "ta_CDLADVANCEBLOCK.swg"

/* TA_CDLBELTHOLD */
%include "ta_CDLBELTHOLD.swg"

/* TA_CDLBREAKAWAY */
%include "ta_CDLBREAKAWAY.swg"

/* TA_CDLCLOSINGMARUBOZU */
%include "ta_CDLCLOSINGMARUBOZU.swg"

/* TA_CDLCONCEALBABYSWALL */
%include "ta_CDLCONCEALBABYSWALL.swg"

/* TA_CDLCOUNTERATTACK */
%include "ta_CDLCOUNTERATTACK.swg"

/* TA_CDLDARKCLOUDCOVER */
%include "ta_CDLDARKCLOUDCOVER.swg"

/* TA_CDLDOJI */
%include "ta_CDLDOJI.swg"

/* TA_CDLDOJISTAR */
%include "ta_CDLDOJISTAR.swg"

/* TA_CDLDRAGONFLYDOJI */
%include "ta_CDLDRAGONFLYDOJI.swg"

/* TA_CDLENGULFING */
%include "ta_CDLENGULFING.swg"

/* TA_CDLEVENINGDOJISTAR */
%include "ta_CDLEVENINGDOJISTAR.swg"

/* TA_CDLEVENINGSTAR */
%include "ta_CDLEVENINGSTAR.swg"

/* TA_CDLGAPSIDESIDEWHITE */
%include "ta_CDLGAPSIDESIDEWHITE.swg"

/* TA_CDLGRAVESTONEDOJI */
%include "ta_CDLGRAVESTONEDOJI.swg"

/* TA_CDLHAMMER */
%include "ta_CDLHAMMER.swg"

/* TA_CDLHANGINGMAN */
%include "ta_CDLHANGINGMAN.swg"

/* TA_CDLHARAMI */
%include "ta_CDLHARAMI.swg"

/* TA_CDLHARAMICROSS */
%include "ta_CDLHARAMICROSS.swg"

/* TA_CDLHIGHWAVE */
%include "ta_CDLHIGHWAVE.swg"

/* TA_CDLHIKKAKE */
%include "ta_CDLHIKKAKE.swg"

/* TA_CDLHIKKAKEMOD */
%include "ta_CDLHIKKAKEMOD.swg"

/* TA_CDLHOMINGPIGEON */
%include "ta_CDLHOMINGPIGEON.swg"

/* TA_CDLIDENTICAL3CROWS */
%include "ta_CDLIDENTICAL3CROWS.swg"

/* TA_CDLINNECK */
%include "ta_CDLINNECK.swg"

/* TA_CDLINVERTEDHAMMER */
%include "ta_CDLINVERTEDHAMMER.swg"

/* TA_CDLKICKING */
%include "ta_CDLKICKING.swg"

/* TA_CDLKICKINGBYLENGTH */
%include "ta_CDLKICKINGBYLENGTH.swg"

/* TA_CDLLADDERBOTTOM */
%include "ta_CDLLADDERBOTTOM.swg"

/* TA_CDLLONGLEGGEDDOJI */
%include "ta_CDLLONGLEGGEDDOJI.swg"

/* TA_CDLLONGLINE */
%include "ta_CDLLONGLINE.swg"

/* TA_CDLMARUBOZU */
%include "ta_CDLMARUBOZU.swg"

/* TA_CDLMATCHINGLOW */
%include "ta_CDLMATCHINGLOW.swg"

/* TA_CDLMATHOLD */
%include "ta_CDLMATHOLD.swg"

/* TA_CDLMORNINGDOJISTAR */
%include "ta_CDLMORNINGDOJISTAR.swg"

/* TA_CDLMORNINGSTAR */
%include "ta_CDLMORNINGSTAR.swg"

/* TA_CDLONNECK */
%include "ta_CDLONNECK.swg"

/* TA_CDLPIERCING */
%include "ta_CDLPIERCING.swg"

/* TA_CDLRICKSHAWMAN */
%include "ta_CDLRICKSHAWMAN.swg"

/* TA_CDLRISEFALL3METHODS */
%include "ta_CDLRISEFALL3METHODS.swg"

/* TA_CDLSEPARATINGLINES */
%include "ta_CDLSEPARATINGLINES.swg"

/* TA_CDLSHOOTINGSTAR */
%include "ta_CDLSHOOTINGSTAR.swg"

/* TA_CDLSHORTLINE */
%include "ta_CDLSHORTLINE.swg"

/* TA_CDLSPINNINGTOP */
%include "ta_CDLSPINNINGTOP.swg"

/* TA_CDLSTALLEDPATTERN */
%include "ta_CDLSTALLEDPATTERN.swg"

/* TA_CDLSTICKSANDWICH */
%include "ta_CDLSTICKSANDWICH.swg"

/* TA_CDLTAKURI */
%include "ta_CDLTAKURI.swg"

/* TA_CDLTASUKIGAP */
%include "ta_CDLTASUKIGAP.swg"

/* TA_CDLTHRUSTING */
%include "ta_CDLTHRUSTING.swg"

/* TA_CDLTRISTAR */
%include "ta_CDLTRISTAR.swg"

/* TA_CDLUNIQUE3RIVER */
%include "ta_CDLUNIQUE3RIVER.swg"

/* TA_CDLUPSIDEGAP2CROWS */
%include "ta_CDLUPSIDEGAP2CROWS.swg"

/* TA_CDLXSIDEGAP3METHODS */
%include "ta_CDLXSIDEGAP3METHODS.swg"

/* TA_CEIL */
%include "ta_CEIL.swg"

/* TA_CMO */
%include "ta_CMO.swg"

/* TA_CORREL */
%include "ta_CORREL.swg"

/* TA_COS */
%include "ta_COS.swg"

/* TA_COSH */
%include "ta_COSH.swg"

/* TA_DEMA */
%include "ta_DEMA.swg"

/* TA_DIV */
%include "ta_DIV.swg"

/* TA_DX */
%include "ta_DX.swg"

/* TA_EMA */
%include "ta_EMA.swg"

/* TA_EXP */
%include "ta_EXP.swg"

/* TA_FLOOR */
%include "ta_FLOOR.swg"

/* TA_HT_DCPERIOD */
%include "ta_HT_DCPERIOD.swg"

/* TA_HT_DCPHASE */
%include "ta_HT_DCPHASE.swg"

/* TA_HT_PHASOR */
%include "ta_HT_PHASOR.swg"

/* TA_HT_SINE */
%include "ta_HT_SINE.swg"

/* TA_HT_TRENDLINE */
%include "ta_HT_TRENDLINE.swg"

/* TA_HT_TRENDMODE */
%include "ta_HT_TRENDMODE.swg"

/* TA_IMI */
%include "ta_IMI.swg"

/* TA_KAMA */
%include "ta_KAMA.swg"

/* TA_LINEARREG */
%include "ta_LINEARREG.swg"

/* TA_LINEARREG_ANGLE */
%include "ta_LINEARREG_ANGLE.swg"

/* TA_LINEARREG_INTERCEPT */
%include "ta_LINEARREG_INTERCEPT.swg"

/* TA_LINEARREG_SLOPE */
%include "ta_LINEARREG_SLOPE.swg"

/* TA_LN */
%include "ta_LN.swg"

/* TA_LOG10 */
%include "ta_LOG10.swg"

/* TA_MA */
%include "ta_MA.swg"

/* TA_MACD */
%include "ta_MACD.swg"

/* TA_MACDEXT */
%include "ta_MACDEXT.swg"

/* TA_MACDFIX */
%include "ta_MACDFIX.swg"

/* TA_MAMA */
%include "ta_MAMA.swg"

/* TA_MAVP */
%include "ta_MAVP.swg"

/* TA_MAX */
%include "ta_MAX.swg"

/* TA_MAXINDEX */
%include "ta_MAXINDEX.swg"

/* TA_MEDPRICE */
%include "ta_MEDPRICE.swg"

/* TA_MFI */
%include "ta_MFI.swg"

/* TA_MIDPOINT */
%include "ta_MIDPOINT.swg"

/* TA_MIDPRICE */
%include "ta_MIDPRICE.swg"

/* TA_MIN */
%include "ta_MIN.swg"

/* TA_MININDEX */
%include "ta_MININDEX.swg"

/* TA_MINMAX */
%include "ta_MINMAX.swg"

/* TA_MINMAXINDEX */
%include "ta_MINMAXINDEX.swg"

/* TA_MINUS_DI */
%include "ta_MINUS_DI.swg"

/* TA_MINUS_DM */
%include "ta_MINUS_DM.swg"

/* TA_MOM */
%include "ta_MOM.swg"

/* TA_MULT */
%include "ta_MULT.swg"

/* TA_NATR */
%include "ta_NATR.swg"

/* TA_NVI */
%include "ta_NVI.swg"

/* TA_OBV */
%include "ta_OBV.swg"

/* TA_PLUS_DI */
%include "ta_PLUS_DI.swg"

/* TA_PLUS_DM */
%include "ta_PLUS_DM.swg"

/* TA_PPO */
%include "ta_PPO.swg"

/* TA_PVI */
%include "ta_PVI.swg"

/* TA_ROC */
%include "ta_ROC.swg"

/* TA_ROCP */
%include "ta_ROCP.swg"

/* TA_ROCR */
%include "ta_ROCR.swg"

/* TA_ROCR100 */
%include "ta_ROCR100.swg"

/* TA_RSI */
%include "ta_RSI.swg"

/* TA_SAR */
%include "ta_SAR.swg"

/* TA_SAREXT */
%include "ta_SAREXT.swg"

/* TA_SIN */
%include "ta_SIN.swg"

/* TA_SINH */
%include "ta_SINH.swg"

/* TA_SMA */
%include "ta_SMA.swg"

/* TA_SQRT */
%include "ta_SQRT.swg"

/* TA_STDDEV */
%include "ta_STDDEV.swg"

/* TA_STOCH */
%include "ta_STOCH.swg"

/* TA_STOCHF */
%include "ta_STOCHF.swg"

/* TA_STOCHRSI */
%include "ta_STOCHRSI.swg"

/* TA_SUB */
%include "ta_SUB.swg"

/* TA_SUM */
%include "ta_SUM.swg"

/* TA_T3 */
%include "ta_T3.swg"

/* TA_TAN */
%include "ta_TAN.swg"

/* TA_TANH */
%include "ta_TANH.swg"

/* TA_TEMA */
%include "ta_TEMA.swg"

/* TA_TRANGE */
%include "ta_TRANGE.swg"

/* TA_TRIMA */
%include "ta_TRIMA.swg"

/* TA_TRIX */
%include "ta_TRIX.swg"

/* TA_TSF */
%include "ta_TSF.swg"

/* TA_TYPPRICE */
%include "ta_TYPPRICE.swg"

/* TA_ULTOSC */
%include "ta_ULTOSC.swg"

/* TA_VAR */
%include "ta_VAR.swg"

/* TA_WCLPRICE */
%include "ta_WCLPRICE.swg"

/* TA_WILLR */
%include "ta_WILLR.swg"

/* TA_WMA */
%include "ta_WMA.swg"
