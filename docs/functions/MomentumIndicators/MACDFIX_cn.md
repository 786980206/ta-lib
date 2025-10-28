# MACDFIX - 移动平均收敛/发散固定12/26

## 概述
MACDFIX是MACD指标的固定参数版本，使用标准的12/26/9周期。它设计用于快速计算，无需指定参数。

## 分类
动量指标

## 计算方法
MACDFIX使用固定周期进行计算：

### 公式
```
MACD线 = EMA(12) - EMA(26)
信号线 = MACD线的EMA(9)
柱状图 = MACD线 - 信号线
```

其中：
- **快速EMA**：12周期指数移动平均线
- **慢速EMA**：26周期指数移动平均线
- **信号**：MACD线的9周期EMA

## 参数
- **optInSignalPeriod**（默认：9）：信号线周期
  - 有效范围：1到100000

## 输入
- 价格数据：`double[]`

## 输出
- MACD线、信号线、柱状图：`double[]`、`double[]`、`double[]`

## 含义
MACDFIX解释：
- **MACD > 0**：看涨动量（12 EMA在26 EMA上方）
- **MACD < 0**：看跌动量（12 EMA在26 EMA下方）
- **MACD交叉信号线上方**：看涨信号
- **MACD交叉信号线下方**：看跌信号
- **柱状图扩展**：动量增加
- **柱状图收缩**：动量减少

## 使用方法
1. **信号线交叉**：寻找MACD/信号线交叉
2. **零线交叉**：监控MACD交叉零线
3. **背离**：比较MACD与价格寻找背离
4. **柱状图分析**：监控柱状图的动量变化

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MACDFIX
    TA_RetCode ret = TA_MACDFIX(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        9,                    // signalPeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        macd,                // outMACD
        signal,              // outMACDSignal
        histogram            // outMACDHist
    );
    
    if (ret == TA_SUCCESS) {
        // 使用MACD数组进行分析
        for (int i = 1; i < outNBElement; i++) {
            if (macd[i] > signal[i] && macd[i-1] <= signal[i-1]) {
                // 看涨交叉
            } else if (macd[i] < signal[i] && macd[i-1] >= signal[i-1]) {
                // 看跌交叉
            }
        }
    }
}
```

## 交易策略
1. **交叉交易**：在MACD/信号交叉时入场
2. **趋势跟踪**：在MACD方向上交易
3. **背离交易**：寻找价格/MACD背离
4. **零线交易**：当MACD交叉零线时入场
5. **柱状图交易**：当柱状图改变方向时入场

## 优势
- 标准行业参数
- 简单易用（最少参数化）
- 经过良好测试和广泛接受
- 快速计算

## 限制
- 固定参数可能不适合所有市场
- 比MACD或MACDEXT灵活性较低
- 在快速移动的市场中可能滞后
- 在波动市场中可能给出假信号

## 相关函数
- `MACD` - 移动平均收敛/发散
- `MACDEXT` - 可控MA类型的MACD
- `PPO` - 百分比价格振荡器
- `APO` - 绝对价格振荡器
- `EMA` - 指数移动平均线

## 参考文献
- Appel, Gerald (1979). "移动平均收敛-发散方法"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
