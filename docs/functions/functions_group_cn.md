# TA-Lib 函数组

本文档提供了所有 TA-Lib 函数组及其组织的全面概述。

## 函数组概述

TA-Lib 函数按以下类别组织：

### 1. 重叠研究 (Overlap Studies)
移动平均线和趋势跟踪指标，叠加在价格图表上。

**函数数量：** 31 个函数  
**目录：** [OverlapStudies/](OverlapStudies/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| BBANDS | [BBANDS.md](OverlapStudies/BBANDS.md) | [BBANDS_cn.md](OverlapStudies/BBANDS_cn.md) |
| DEMA | [DEMA.md](OverlapStudies/DEMA.md) | [DEMA_cn.md](OverlapStudies/DEMA_cn.md) |
| EMA | [EMA.md](OverlapStudies/EMA.md) | [EMA_cn.md](OverlapStudies/EMA_cn.md) |
| HT_TRENDLINE | [HT_TRENDLINE.md](OverlapStudies/HT_TRENDLINE.md) | [HT_TRENDLINE_cn.md](OverlapStudies/HT_TRENDLINE_cn.md) |
| KAMA | [KAMA.md](OverlapStudies/KAMA.md) | [KAMA_cn.md](OverlapStudies/KAMA_cn.md) |
| MA | [MA.md](OverlapStudies/MA.md) | [MA_cn.md](OverlapStudies/MA_cn.md) |
| MAMA | [MAMA.md](OverlapStudies/MAMA.md) | [MAMA_cn.md](OverlapStudies/MAMA_cn.md) |
| MAVP | [MAVP.md](OverlapStudies/MAVP.md) | [MAVP_cn.md](OverlapStudies/MAVP_cn.md) |
| MIDPOINT | [MIDPOINT.md](OverlapStudies/MIDPOINT.md) | [MIDPOINT_cn.md](OverlapStudies/MIDPOINT_cn.md) |
| MIDPRICE | [MIDPRICE.md](OverlapStudies/MIDPRICE.md) | [MIDPRICE_cn.md](OverlapStudies/MIDPRICE_cn.md) |
| SAR | [SAR.md](OverlapStudies/SAR.md) | [SAR_cn.md](OverlapStudies/SAR_cn.md) |
| SAREXT | [SAREXT.md](OverlapStudies/SAREXT.md) | [SAREXT_cn.md](OverlapStudies/SAREXT_cn.md) |
| SMA | [SMA.md](OverlapStudies/SMA.md) | [SMA_cn.md](OverlapStudies/SMA_cn.md) |
| T3 | [T3.md](OverlapStudies/T3.md) | [T3_cn.md](OverlapStudies/T3_cn.md) |
| TEMA | [TEMA.md](OverlapStudies/TEMA.md) | [TEMA_cn.md](OverlapStudies/TEMA_cn.md) |
| TRIMA | [TRIMA.md](OverlapStudies/TRIMA.md) | [TRIMA_cn.md](OverlapStudies/TRIMA_cn.md) |
| WMA | [WMA.md](OverlapStudies/WMA.md) | [WMA_cn.md](OverlapStudies/WMA_cn.md) |

#### 描述
重叠研究包括各种类型的移动平均线和趋势跟踪指标，通常绘制在价格图表顶部。这些指标有助于识别趋势方向、支撑和阻力位以及潜在的入场/出场点。

**主要类别：**
- **简单移动平均线**：SMA、EMA、DEMA、TEMA
- **加权移动平均线**：WMA、T3
- **自适应移动平均线**：KAMA、MAMA
- **布林带**：BBANDS
- **抛物线 SAR**：SAR、SAREXT
- **基于价格的指标**：MIDPOINT、MIDPRICE

---

### 2. 动量指标 (Momentum Indicators)
振荡器和动量指标，有助于识别趋势强度和潜在反转。

**函数数量：** 32 个函数  
**目录：** [MomentumIndicators/](MomentumIndicators/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| ADX | [ADX.md](MomentumIndicators/ADX.md) | [ADX_cn.md](MomentumIndicators/ADX_cn.md) |
| ADXR | [ADXR.md](MomentumIndicators/ADXR.md) | [ADXR_cn.md](MomentumIndicators/ADXR_cn.md) |
| APO | [APO.md](MomentumIndicators/APO.md) | [APO_cn.md](MomentumIndicators/APO_cn.md) |
| AROON | [AROON.md](MomentumIndicators/AROON.md) | [AROON_cn.md](MomentumIndicators/AROON_cn.md) |
| AROONOSC | [AROONOSC.md](MomentumIndicators/AROONOSC.md) | [AROONOSC_cn.md](MomentumIndicators/AROONOSC_cn.md) |
| BOP | [BOP.md](MomentumIndicators/BOP.md) | [BOP_cn.md](MomentumIndicators/BOP_cn.md) |
| CCI | [CCI.md](MomentumIndicators/CCI.md) | [CCI_cn.md](MomentumIndicators/CCI_cn.md) |
| CMO | [CMO.md](MomentumIndicators/CMO.md) | [CMO_cn.md](MomentumIndicators/CMO_cn.md) |
| DX | [DX.md](MomentumIndicators/DX.md) | [DX_cn.md](MomentumIndicators/DX_cn.md) |
| MACD | [MACD.md](MomentumIndicators/MACD.md) | [MACD_cn.md](MomentumIndicators/MACD_cn.md) |
| MACDEXT | [MACDEXT.md](MomentumIndicators/MACDEXT.md) | [MACDEXT_cn.md](MomentumIndicators/MACDEXT_cn.md) |
| MACDFIX | [MACDFIX.md](MomentumIndicators/MACDFIX.md) | [MACDFIX_cn.md](MomentumIndicators/MACDFIX_cn.md) |
| MFI | [MFI.md](MomentumIndicators/MFI.md) | [MFI_cn.md](MomentumIndicators/MFI_cn.md) |
| MINUS_DI | [MINUS_DI.md](MomentumIndicators/MINUS_DI.md) | [MINUS_DI_cn.md](MomentumIndicators/MINUS_DI_cn.md) |
| MINUS_DM | [MINUS_DM.md](MomentumIndicators/MINUS_DM.md) | [MINUS_DM_cn.md](MomentumIndicators/MINUS_DM_cn.md) |
| MOM | [MOM.md](MomentumIndicators/MOM.md) | [MOM_cn.md](MomentumIndicators/MOM_cn.md) |
| PLUS_DI | [PLUS_DI.md](MomentumIndicators/PLUS_DI.md) | [PLUS_DI_cn.md](MomentumIndicators/PLUS_DI_cn.md) |
| PLUS_DM | [PLUS_DM.md](MomentumIndicators/PLUS_DM.md) | [PLUS_DM_cn.md](MomentumIndicators/PLUS_DM_cn.md) |
| PPO | [PPO.md](MomentumIndicators/PPO.md) | [PPO_cn.md](MomentumIndicators/PPO_cn.md) |
| ROC | [ROC.md](MomentumIndicators/ROC.md) | [ROC_cn.md](MomentumIndicators/ROC_cn.md) |
| ROCP | [ROCP.md](MomentumIndicators/ROCP.md) | [ROCP_cn.md](MomentumIndicators/ROCP_cn.md) |
| ROCR | [ROCR.md](MomentumIndicators/ROCR.md) | [ROCR_cn.md](MomentumIndicators/ROCR_cn.md) |
| ROCR100 | [ROCR100.md](MomentumIndicators/ROCR100.md) | [ROCR100_cn.md](MomentumIndicators/ROCR100_cn.md) |
| RSI | [RSI.md](MomentumIndicators/RSI.md) | [RSI_cn.md](MomentumIndicators/RSI_cn.md) |
| STOCH | [STOCH.md](MomentumIndicators/STOCH.md) | [STOCH_cn.md](MomentumIndicators/STOCH_cn.md) |
| STOCHF | [STOCHF.md](MomentumIndicators/STOCHF.md) | [STOCHF_cn.md](MomentumIndicators/STOCHF_cn.md) |
| STOCHMI | [STOCHMI.md](MomentumIndicators/STOCHMI.md) | [STOCHMI_cn.md](MomentumIndicators/STOCHMI_cn.md) |
| STOCHRSI | [STOCHRSI.md](MomentumIndicators/STOCHRSI.md) | [STOCHRSI_cn.md](MomentumIndicators/STOCHRSI_cn.md) |
| TRIX | [TRIX.md](MomentumIndicators/TRIX.md) | [TRIX_cn.md](MomentumIndicators/TRIX_cn.md) |
| ULTOSC | [ULTOSC.md](MomentumIndicators/ULTOSC.md) | [ULTOSC_cn.md](MomentumIndicators/ULTOSC_cn.md) |
| WILLR | [WILLR.md](MomentumIndicators/WILLR.md) | [WILLR_cn.md](MomentumIndicators/WILLR_cn.md) |

#### 描述
动量指标是振荡器，有助于识别趋势强度、动量变化和潜在反转点。这些指标通常在固定范围内振荡，并在达到极值时提供信号。

**主要类别：**
- **趋势强度**：ADX、ADXR、DX
- **方向性运动**：PLUS_DI、MINUS_DI、PLUS_DM、MINUS_DM
- **MACD 系列**：MACD、MACDEXT、MACDFIX、APO、PPO
- **变化率**：ROC、ROCP、ROCR、ROCR100、MOM
- **随机振荡器**：STOCH、STOCHF、STOCHRSI、STOCHMI
- **相对强度**：RSI、CCI、WILLR、ULTOSC
- **基于成交量**：MFI、BOP
- **趋势检测**：AROON、AROONOSC、TRIX、CMO

---

### 3. 成交量指标 (Volume Indicators)
分析交易成交量模式及其与价格关系的指标。

**函数数量：** 4 个函数  
**目录：** [VolumeIndicators/](VolumeIndicators/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| AD | [AD.md](VolumeIndicators/AD.md) | [AD_cn.md](VolumeIndicators/AD_cn.md) |
| ADOSC | [ADOSC.md](VolumeIndicators/ADOSC.md) | [ADOSC_cn.md](VolumeIndicators/ADOSC_cn.md) |
| OBV | [OBV.md](VolumeIndicators/OBV.md) | [OBV_cn.md](VolumeIndicators/OBV_cn.md) |

#### 描述
成交量指标分析交易成交量模式及其与价格运动的关系。这些指标有助于确认价格趋势并基于成交量分析识别潜在反转。

**主要类别：**
- **累积/派发**：AD（累积/派发线）
- **成交量振荡器**：ADOSC（累积/派发振荡器）
- **成交量趋势**：OBV（平衡成交量）

---

### 4. 波动率指标 (Volatility Indicators)
测量价格波动率和市场不确定性的指标。

**函数数量：** 5 个函数  
**目录：** [VolatilityIndicators/](VolatilityIndicators/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| ATR | [ATR.md](VolatilityIndicators/ATR.md) | [ATR_cn.md](VolatilityIndicators/ATR_cn.md) |
| NATR | [NATR.md](VolatilityIndicators/NATR.md) | [NATR_cn.md](VolatilityIndicators/NATR_cn.md) |
| TRANGE | [TRANGE.md](VolatilityIndicators/TRANGE.md) | [TRANGE_cn.md](VolatilityIndicators/TRANGE_cn.md) |

#### 描述
波动率指标测量价格随时间变化的程度。这些指标有助于评估市场不确定性、设置止损位并识别高或低波动率期间。

**主要类别：**
- **真实范围**：ATR（平均真实范围）、NATR（标准化 ATR）、TRANGE（真实范围）
- **波动率测量**：用于仓位大小、止损放置和市场条件评估

---

### 5. 价格变换 (Price Transform)
将价格数据转换为不同表示形式的函数。

**函数数量：** 4 个函数  
**目录：** [PriceTransform/](PriceTransform/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| AVGPRICE | [AVGPRICE.md](PriceTransform/AVGPRICE.md) | [AVGPRICE_cn.md](PriceTransform/AVGPRICE_cn.md) |
| MEDPRICE | [MEDPRICE.md](PriceTransform/MEDPRICE.md) | [MEDPRICE_cn.md](PriceTransform/MEDPRICE_cn.md) |
| TYPPRICE | [TYPPRICE.md](PriceTransform/TYPPRICE.md) | [TYPPRICE_cn.md](PriceTransform/TYPPRICE_cn.md) |
| WCLPRICE | [WCLPRICE.md](PriceTransform/WCLPRICE.md) | [WCLPRICE_cn.md](PriceTransform/WCLPRICE_cn.md) |

#### 描述
价格变换函数将 OHLC（开盘价、最高价、最低价、收盘价）价格数据转换为不同的价格表示形式。这些变换后的价格通常用作其他技术指标的输入。

**主要类别：**
- **平均价格**：AVGPRICE（平均价格）
- **中位价格**：MEDPRICE（中位价格）
- **典型价格**：TYPPRICE（典型价格）
- **加权收盘价**：WCLPRICE（加权收盘价）

---

### 6. 周期指标 (Cycle Indicators)
分析价格数据中周期性模式的指标。

**函数数量：** 5 个函数  
**目录：** [CycleIndicators/](CycleIndicators/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| HT_DCPERIOD | [HT_DCPERIOD.md](CycleIndicators/HT_DCPERIOD.md) | [HT_DCPERIOD_cn.md](CycleIndicators/HT_DCPERIOD_cn.md) |
| HT_DCPHASE | [HT_DCPHASE.md](CycleIndicators/HT_DCPHASE.md) | [HT_DCPHASE_cn.md](CycleIndicators/HT_DCPHASE_cn.md) |
| HT_PHASOR | [HT_PHASOR.md](CycleIndicators/HT_PHASOR.md) | [HT_PHASOR_cn.md](CycleIndicators/HT_PHASOR_cn.md) |
| HT_SINE | [HT_SINE.md](CycleIndicators/HT_SINE.md) | [HT_SINE_cn.md](CycleIndicators/HT_SINE_cn.md) |
| HT_TRENDMODE | [HT_TRENDMODE.md](CycleIndicators/HT_TRENDMODE.md) | [HT_TRENDMODE_cn.md](CycleIndicators/HT_TRENDMODE_cn.md) |

#### 描述
周期指标使用希尔伯特变换技术分析价格数据中的周期性模式。这些指标有助于识别市场数据中的主导周期和相位关系。

**主要类别：**
- **周期分析**：HT_DCPERIOD（希尔伯特变换 - 主导周期周期）
- **相位分析**：HT_DCPHASE（希尔伯特变换 - 主导周期相位）
- **相量分量**：HT_PHASOR（希尔伯特变换 - 相量分量）
- **正弦波**：HT_SINE（希尔伯特变换 - 正弦波）
- **趋势模式**：HT_TRENDMODE（希尔伯特变换 - 趋势 vs 周期模式）

---

### 7. 数学运算符 (Math Operators)
向量算术运算的基本数学运算符。

**函数数量：** 11 个函数  
**目录：** [MathOperators/](MathOperators/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| ADD | [ADD.md](MathOperators/ADD.md) | [ADD_cn.md](MathOperators/ADD_cn.md) |
| DIV | [DIV.md](MathOperators/DIV.md) | [DIV_cn.md](MathOperators/DIV_cn.md) |
| MAX | [MAX.md](MathOperators/MAX.md) | [MAX_cn.md](MathOperators/MAX_cn.md) |
| MAXINDEX | [MAXINDEX.md](MathOperators/MAXINDEX.md) | [MAXINDEX_cn.md](MathOperators/MAXINDEX_cn.md) |
| MIN | [MIN.md](MathOperators/MIN.md) | [MIN_cn.md](MathOperators/MIN_cn.md) |
| MININDEX | [MININDEX.md](MathOperators/MININDEX.md) | [MININDEX_cn.md](MathOperators/MININDEX_cn.md) |
| MINMAX | [MINMAX.md](MathOperators/MINMAX.md) | [MINMAX_cn.md](MathOperators/MINMAX_cn.md) |
| MINMAXINDEX | [MINMAXINDEX.md](MathOperators/MINMAXINDEX.md) | [MINMAXINDEX_cn.md](MathOperators/MINMAXINDEX_cn.md) |
| MULT | [MULT.md](MathOperators/MULT.md) | [MULT_cn.md](MathOperators/MULT_cn.md) |
| SUB | [SUB.md](MathOperators/SUB.md) | [SUB_cn.md](MathOperators/SUB_cn.md) |
| SUM | [SUM.md](MathOperators/SUM.md) | [SUM_cn.md](MathOperators/SUM_cn.md) |

#### 描述
数学运算符提供向量算术的基本数学运算。这些函数对输入数组执行逐元素运算，是更复杂技术指标的基本构建块。

**主要类别：**
- **算术运算**: ADD, SUB, MULT, DIV
- **统计运算**: SUM, MAX, MIN
- **索引运算**: MAXINDEX, MININDEX, MINMAXINDEX
- **范围运算**: MINMAX

---

### 8. 形态识别 (Pattern Recognition)
用于识别特定价格形态的蜡烛图形态识别函数。

**函数数量：** 63 个函数  
**目录：** [PatternRecognition/](PatternRecognition/)

#### 函数列表

| 函数名称 | 英文文档 | 中文文档 |
|----------|----------|----------|
| CDL2CROWS | [CDL2CROWS.md](PatternRecognition/CDL2CROWS.md) | [CDL2CROWS_cn.md](PatternRecognition/CDL2CROWS_cn.md) |
| CDL3BLACKCROWS | [CDL3BLACKCROWS.md](PatternRecognition/CDL3BLACKCROWS.md) | [CDL3BLACKCROWS_cn.md](PatternRecognition/CDL3BLACKCROWS_cn.md) |
| CDL3INSIDE | [CDL3INSIDE.md](PatternRecognition/CDL3INSIDE.md) | [CDL3INSIDE_cn.md](PatternRecognition/CDL3INSIDE_cn.md) |
| CDL3LINESTRIKE | [CDL3LINESTRIKE.md](PatternRecognition/CDL3LINESTRIKE.md) | [CDL3LINESTRIKE_cn.md](PatternRecognition/CDL3LINESTRIKE_cn.md) |
| CDL3OUTSIDE | [CDL3OUTSIDE.md](PatternRecognition/CDL3OUTSIDE.md) | [CDL3OUTSIDE_cn.md](PatternRecognition/CDL3OUTSIDE_cn.md) |
| CDL3STARSINSOUTH | [CDL3STARSINSOUTH.md](PatternRecognition/CDL3STARSINSOUTH.md) | [CDL3STARSINSOUTH_cn.md](PatternRecognition/CDL3STARSINSOUTH_cn.md) |
| CDL3WHITESOLDIERS | [CDL3WHITESOLDIERS.md](PatternRecognition/CDL3WHITESOLDIERS.md) | [CDL3WHITESOLDIERS_cn.md](PatternRecognition/CDL3WHITESOLDIERS_cn.md) |
| CDLABANDONEDBABY | [CDLABANDONEDBABY.md](PatternRecognition/CDLABANDONEDBABY.md) | [CDLABANDONEDBABY_cn.md](PatternRecognition/CDLABANDONEDBABY_cn.md) |
| CDLADVANCEBLOCK | [CDLADVANCEBLOCK.md](PatternRecognition/CDLADVANCEBLOCK.md) | [CDLADVANCEBLOCK_cn.md](PatternRecognition/CDLADVANCEBLOCK_cn.md) |
| CDLBELTHOLD | [CDLBELTHOLD.md](PatternRecognition/CDLBELTHOLD.md) | [CDLBELTHOLD_cn.md](PatternRecognition/CDLBELTHOLD_cn.md) |
| CDLBREAKAWAY | [CDLBREAKAWAY.md](PatternRecognition/CDLBREAKAWAY.md) | [CDLBREAKAWAY_cn.md](PatternRecognition/CDLBREAKAWAY_cn.md) |
| CDLCLOSINGMARUBOZU | [CDLCLOSINGMARUBOZU.md](PatternRecognition/CDLCLOSINGMARUBOZU.md) | [CDLCLOSINGMARUBOZU_cn.md](PatternRecognition/CDLCLOSINGMARUBOZU_cn.md) |
| CDLCONCEALBABYSWALL | [CDLCONCEALBABYSWALL.md](PatternRecognition/CDLCONCEALBABYSWALL.md) | [CDLCONCEALBABYSWALL_cn.md](PatternRecognition/CDLCONCEALBABYSWALL_cn.md) |
| CDLCOUNTERATTACK | [CDLCOUNTERATTACK.md](PatternRecognition/CDLCOUNTERATTACK.md) | [CDLCOUNTERATTACK_cn.md](PatternRecognition/CDLCOUNTERATTACK_cn.md) |
| CDLDARKCLOUDCOVER | [CDLDARKCLOUDCOVER.md](PatternRecognition/CDLDARKCLOUDCOVER.md) | [CDLDARKCLOUDCOVER_cn.md](PatternRecognition/CDLDARKCLOUDCOVER_cn.md) |
| CDLDOJI | [CDLDOJI.md](PatternRecognition/CDLDOJI.md) | [CDLDOJI_cn.md](PatternRecognition/CDLDOJI_cn.md) |
| CDLDOJISTAR | [CDLDOJISTAR.md](PatternRecognition/CDLDOJISTAR.md) | [CDLDOJISTAR_cn.md](PatternRecognition/CDLDOJISTAR_cn.md) |
| CDLDRAGONFLYDOJI | [CDLDRAGONFLYDOJI.md](PatternRecognition/CDLDRAGONFLYDOJI.md) | [CDLDRAGONFLYDOJI_cn.md](PatternRecognition/CDLDRAGONFLYDOJI_cn.md) |
| CDLENGULFING | [CDLENGULFING.md](PatternRecognition/CDLENGULFING.md) | [CDLENGULFING_cn.md](PatternRecognition/CDLENGULFING_cn.md) |
| CDLEVENINGDOJISTAR | [CDLEVENINGDOJISTAR.md](PatternRecognition/CDLEVENINGDOJISTAR.md) | [CDLEVENINGDOJISTAR_cn.md](PatternRecognition/CDLEVENINGDOJISTAR_cn.md) |
| CDLEVENINGSTAR | [CDLEVENINGSTAR.md](PatternRecognition/CDLEVENINGSTAR.md) | [CDLEVENINGSTAR_cn.md](PatternRecognition/CDLEVENINGSTAR_cn.md) |
| CDLGAPSIDESIDEWHITE | [CDLGAPSIDESIDEWHITE.md](PatternRecognition/CDLGAPSIDESIDEWHITE.md) | [CDLGAPSIDESIDEWHITE_cn.md](PatternRecognition/CDLGAPSIDESIDEWHITE_cn.md) |
| CDLGRAVESTONEDOJI | [CDLGRAVESTONEDOJI.md](PatternRecognition/CDLGRAVESTONEDOJI.md) | [CDLGRAVESTONEDOJI_cn.md](PatternRecognition/CDLGRAVESTONEDOJI_cn.md) |
| CDLHAMMER | [CDLHAMMER.md](PatternRecognition/CDLHAMMER.md) | [CDLHAMMER_cn.md](PatternRecognition/CDLHAMMER_cn.md) |
| CDLHANGINGMAN | [CDLHANGINGMAN.md](PatternRecognition/CDLHANGINGMAN.md) | [CDLHANGINGMAN_cn.md](PatternRecognition/CDLHANGINGMAN_cn.md) |
| CDLHARAMI | [CDLHARAMI.md](PatternRecognition/CDLHARAMI.md) | [CDLHARAMI_cn.md](PatternRecognition/CDLHARAMI_cn.md) |
| CDLHARAMICROSS | [CDLHARAMICROSS.md](PatternRecognition/CDLHARAMICROSS.md) | [CDLHARAMICROSS_cn.md](PatternRecognition/CDLHARAMICROSS_cn.md) |
| CDLHIGHWAVE | [CDLHIGHWAVE.md](PatternRecognition/CDLHIGHWAVE.md) | [CDLHIGHWAVE_cn.md](PatternRecognition/CDLHIGHWAVE_cn.md) |
| CDLHIKKAKE | [CDLHIKKAKE.md](PatternRecognition/CDLHIKKAKE.md) | [CDLHIKKAKE_cn.md](PatternRecognition/CDLHIKKAKE_cn.md) |
| CDLHIKKAKEMOD | [CDLHIKKAKEMOD.md](PatternRecognition/CDLHIKKAKEMOD.md) | [CDLHIKKAKEMOD_cn.md](PatternRecognition/CDLHIKKAKEMOD_cn.md) |
| CDLHOMINGPIGEON | [CDLHOMINGPIGEON.md](PatternRecognition/CDLHOMINGPIGEON.md) | [CDLHOMINGPIGEON_cn.md](PatternRecognition/CDLHOMINGPIGEON_cn.md) |
| CDLIDENTICAL3CROWS | [CDLIDENTICAL3CROWS.md](PatternRecognition/CDLIDENTICAL3CROWS.md) | [CDLIDENTICAL3CROWS_cn.md](PatternRecognition/CDLIDENTICAL3CROWS_cn.md) |
| CDLINNECK | [CDLINNECK.md](PatternRecognition/CDLINNECK.md) | [CDLINNECK_cn.md](PatternRecognition/CDLINNECK_cn.md) |
| CDLINVERTEDHAMMER | [CDLINVERTEDHAMMER.md](PatternRecognition/CDLINVERTEDHAMMER.md) | [CDLINVERTEDHAMMER_cn.md](PatternRecognition/CDLINVERTEDHAMMER_cn.md) |
| CDLKICKING | [CDLKICKING.md](PatternRecognition/CDLKICKING.md) | [CDLKICKING_cn.md](PatternRecognition/CDLKICKING_cn.md) |
| CDLKICKINGBYLENGTH | [CDLKICKINGBYLENGTH.md](PatternRecognition/CDLKICKINGBYLENGTH.md) | [CDLKICKINGBYLENGTH_cn.md](PatternRecognition/CDLKICKINGBYLENGTH_cn.md) |
| CDLLADDERBOTTOM | [CDLLADDERBOTTOM.md](PatternRecognition/CDLLADDERBOTTOM.md) | [CDLLADDERBOTTOM_cn.md](PatternRecognition/CDLLADDERBOTTOM_cn.md) |
| CDLLONGLEGGEDDOJI | [CDLLONGLEGGEDDOJI.md](PatternRecognition/CDLLONGLEGGEDDOJI.md) | [CDLLONGLEGGEDDOJI_cn.md](PatternRecognition/CDLLONGLEGGEDDOJI_cn.md) |
| CDLLONGLINE | [CDLLONGLINE.md](PatternRecognition/CDLLONGLINE.md) | [CDLLONGLINE_cn.md](PatternRecognition/CDLLONGLINE_cn.md) |
| CDLMARUBOZU | [CDLMARUBOZU.md](PatternRecognition/CDLMARUBOZU.md) | [CDLMARUBOZU_cn.md](PatternRecognition/CDLMARUBOZU_cn.md) |
| CDLMATCHINGLOW | [CDLMATCHINGLOW.md](PatternRecognition/CDLMATCHINGLOW.md) | [CDLMATCHINGLOW_cn.md](PatternRecognition/CDLMATCHINGLOW_cn.md) |
| CDLMATHOLD | [CDLMATHOLD.md](PatternRecognition/CDLMATHOLD.md) | [CDLMATHOLD_cn.md](PatternRecognition/CDLMATHOLD_cn.md) |
| CDLMORNINGDOJISTAR | [CDLMORNINGDOJISTAR.md](PatternRecognition/CDLMORNINGDOJISTAR.md) | [CDLMORNINGDOJISTAR_cn.md](PatternRecognition/CDLMORNINGDOJISTAR_cn.md) |
| CDLMORNINGSTAR | [CDLMORNINGSTAR.md](PatternRecognition/CDLMORNINGSTAR.md) | [CDLMORNINGSTAR_cn.md](PatternRecognition/CDLMORNINGSTAR_cn.md) |
| CDLONNECK | [CDLONNECK.md](PatternRecognition/CDLONNECK.md) | [CDLONNECK_cn.md](PatternRecognition/CDLONNECK_cn.md) |
| CDLPIERCING | [CDLPIERCING.md](PatternRecognition/CDLPIERCING.md) | [CDLPIERCING_cn.md](PatternRecognition/CDLPIERCING_cn.md) |
| CDLRICKSHAWMAN | [CDLRICKSHAWMAN.md](PatternRecognition/CDLRICKSHAWMAN.md) | [CDLRICKSHAWMAN_cn.md](PatternRecognition/CDLRICKSHAWMAN_cn.md) |
| CDLRISEFALL3METHODS | [CDLRISEFALL3METHODS.md](PatternRecognition/CDLRISEFALL3METHODS.md) | [CDLRISEFALL3METHODS_cn.md](PatternRecognition/CDLRISEFALL3METHODS_cn.md) |
| CDLSEPARATINGLINES | [CDLSEPARATINGLINES.md](PatternRecognition/CDLSEPARATINGLINES.md) | [CDLSEPARATINGLINES_cn.md](PatternRecognition/CDLSEPARATINGLINES_cn.md) |
| CDLSHOOTINGSTAR | [CDLSHOOTINGSTAR.md](PatternRecognition/CDLSHOOTINGSTAR.md) | [CDLSHOOTINGSTAR_cn.md](PatternRecognition/CDLSHOOTINGSTAR_cn.md) |
| CDLSHORTLINE | [CDLSHORTLINE.md](PatternRecognition/CDLSHORTLINE.md) | [CDLSHORTLINE_cn.md](PatternRecognition/CDLSHORTLINE_cn.md) |
| CDLSPINNINGTOP | [CDLSPINNINGTOP.md](PatternRecognition/CDLSPINNINGTOP.md) | [CDLSPINNINGTOP_cn.md](PatternRecognition/CDLSPINNINGTOP_cn.md) |
| CDLSTALLEDPATTERN | [CDLSTALLEDPATTERN.md](PatternRecognition/CDLSTALLEDPATTERN.md) | [CDLSTALLEDPATTERN_cn.md](PatternRecognition/CDLSTALLEDPATTERN_cn.md) |
| CDLSTICKSANDWICH | [CDLSTICKSANDWICH.md](PatternRecognition/CDLSTICKSANDWICH.md) | [CDLSTICKSANDWICH_cn.md](PatternRecognition/CDLSTICKSANDWICH_cn.md) |
| CDLTAKURI | [CDLTAKURI.md](PatternRecognition/CDLTAKURI.md) | [CDLTAKURI_cn.md](PatternRecognition/CDLTAKURI_cn.md) |
| CDLTASUKIGAP | [CDLTASUKIGAP.md](PatternRecognition/CDLTASUKIGAP.md) | [CDLTASUKIGAP_cn.md](PatternRecognition/CDLTASUKIGAP_cn.md) |
| CDLTHRUSTING | [CDLTHRUSTING.md](PatternRecognition/CDLTHRUSTING.md) | [CDLTHRUSTING_cn.md](PatternRecognition/CDLTHRUSTING_cn.md) |
| CDLTRISTAR | [CDLTRISTAR.md](PatternRecognition/CDLTRISTAR.md) | [CDLTRISTAR_cn.md](PatternRecognition/CDLTRISTAR_cn.md) |
| CDLUNIQUE3RIVER | [CDLUNIQUE3RIVER.md](PatternRecognition/CDLUNIQUE3RIVER.md) | [CDLUNIQUE3RIVER_cn.md](PatternRecognition/CDLUNIQUE3RIVER_cn.md) |
| CDLUPSIDEGAP2CROWS | [CDLUPSIDEGAP2CROWS.md](PatternRecognition/CDLUPSIDEGAP2CROWS.md) | [CDLUPSIDEGAP2CROWS_cn.md](PatternRecognition/CDLUPSIDEGAP2CROWS_cn.md) |
| CDLXSIDEGAP3METHODS | [CDLXSIDEGAP3METHODS.md](PatternRecognition/CDLXSIDEGAP3METHODS.md) | [CDLXSIDEGAP3METHODS_cn.md](PatternRecognition/CDLXSIDEGAP3METHODS_cn.md) |

#### 描述
形态识别函数识别特定的蜡烛图形态，这些形态可以信号潜在的价格反转、延续或市场犹豫不决。这些形态基于日本蜡烛图技术。

**主要类别：**
- **单蜡烛形态**：DOJI、HAMMER、HANGINGMAN、SHOOTINGSTAR、MARUBOZU、SPINNINGTOP
- **双蜡烛形态**：ENGULFING、HARAMI、PIERCING、DARKCLOUDCOVER、COUNTERATTACK
- **三蜡烛形态**：MORNINGSTAR、EVENINGSTAR、THREE WHITE SOLDIERS、THREE BLACK CROWS
- **复杂形态**：ABANDONEDBABY、BREAKAWAY、KICKING、TASUKIGAP、UNIQUE3RIVER
- **十字星变体**：DRAGONFLYDOJI、GRAVESTONEDOJI、LONGLEGGEDDOJI、RICKSHAWMAN
- **星形形态**：DOJISTAR、MORNINGDOJISTAR、EVENINGDOJISTAR、TRISTAR

---

## 文档结构

每个函数组包含：
- 英文文档文件（`.md`）
- 中文文档文件（`_cn.md`）
- 组特定概述表
- 详细函数描述和使用信息

## 使用方法

导航到特定函数组目录以查找：
- 个别函数文档
- 英文和中文版本
- 函数特定示例和使用说明

## 总函数数

**TA-Lib 总函数数：** 8 个类别中的 153 个函数

---

*此文档根据官方 TA-Lib Python 库结构组织。*
