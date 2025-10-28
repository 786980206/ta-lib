# HT_TRENDLINE - Hilbert变换 - 趋势线

## 概述
Hilbert变换 - 趋势线（HT_TRENDLINE）是一个周期指标，基于Hilbert变换计算趋势线。它是John Ehlers开发的MESA（MESA自适应移动平均线）指标套件的一部分。

## 分类
周期指标

## 计算方法
HT_TRENDLINE函数使用Hilbert变换计算自适应趋势线，识别主导周期周期，然后在该周期上平滑价格。

### 步骤
1. **平滑价格**：对输入价格应用4周期WMA
2. **应用Hilbert变换**：计算去趋势器、I和Q组成部分、周期
3. **计算主导周期周期（DCP）**：从Hilbert变换分析
4. **在DCP上平均价格**：计算主导周期周期上的平均价格
5. **计算ITrend**：当前和之前趋势值的加权平均

### 公式
```
周期平均 = 平均(价格, 主导周期周期)
趋势线 = (4.0×周期平均 + 3.0×ITrend[1] + 2.0×ITrend[2] + ITrend[3]) / 10.0
```

其中：
- `周期平均` = 主导周期周期上的平均价格
- `ITrend[1]` = 之前的趋势线值
- `ITrend[2]` = 2个柱前的趋势线
- `ITrend[3]` = 3个柱前的趋势线

**注意**：趋势线使用加权移动平均，强调最近的基于周期的平均值，提供平滑的自适应趋势跟踪。

## 参数
- **输入**：价格数据（通常是收盘价）
- **输出**：趋势线数组

## 含义
HT_TRENDLINE表示自适应趋势线，它：
- **适应周期**：随主导周期周期变化
- **平滑价格**：提供价格移动的平滑表示
- **趋势方向**：指示整体趋势方向
- **支撑/阻力**：可以作为动态支撑或阻力

## 使用方法
1. **趋势识别**：使用趋势线识别整体趋势方向
2. **支撑/阻力**：用作动态支撑或阻力水平
3. **入场/出场信号**：当价格交叉趋势线时入场
4. **趋势变化**：寻找趋势线斜率变化

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算HT_TRENDLINE
    TA_RetCode ret = TA_HT_TRENDLINE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        trendline            // outTrendline
    );
    
    if (ret == TA_SUCCESS) {
        // 使用trendline数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (close_prices[i] > trendline[i]) {
                // 价格在趋势线上方 - 看涨
            } else if (close_prices[i] < trendline[i]) {
                // 价格在趋势线下方 - 看跌
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在趋势线方向上入场
2. **均值回归**：当价格显著偏离趋势线时逆趋势交易
3. **突破交易**：当价格突破趋势线时入场
4. **趋势确认**：与其他指标一起使用进行趋势确认

## 优势
- 适应变化的市场周期
- 提供清晰的趋势信号
- 在趋势市场中效果良好
- 可以与其他Hilbert变换指标结合

## 限制
- 需要足够的数据进行准确计算
- 在快速移动的市场中可能滞后
- 最好与其他指标结合使用
- 需要理解周期分析

## 相关函数
- `HT_DCPERIOD` - 主导周期
- `HT_DCPHASE` - 主导周期相位
- `HT_PHASOR` - 相量组成部分
- `HT_SINE` - 正弦波
- `HT_TRENDMODE` - 趋势模式

## 参考文献
- Ehlers, J. F. (2001). "交易者的火箭科学"
- Ehlers, J. F. (2004). "股票和期货的网络分析"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
