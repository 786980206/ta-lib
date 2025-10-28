# MACDEXT - 可控MA类型的MACD

## 概述
MACDEXT（MACD扩展）是MACD指标的增强版本，允许您为每个组成部分指定要使用的移动平均线类型。与仅使用指数移动平均线的标准MACD相比，这提供了更大的灵活性。

## 分类
动量指标

## 计算方法
MACDEXT使用可定制的移动平均线类型计算MACD：

### 公式
```
MACD线 = MA_快速(价格) - MA_慢速(价格)
信号线 = MA_信号(MACD线)
柱状图 = MACD线 - 信号线

其中MA可以是：
- SMA（简单移动平均线）
- EMA（指数移动平均线）
- WMA（加权移动平均线）
- DEMA、TEMA、TRIMA、KAMA、MAMA、T3等
```

## 参数
- **optInFastPeriod**（默认：12）：快速MA的周期
  - 有效范围：2到100000
- **optInFastMAType**（默认：EMA）：快速线的MA类型
  - 有效范围：0到8
- **optInSlowPeriod**（默认：26）：慢速MA的周期
  - 有效范围：2到100000
- **optInSlowMAType**（默认：EMA）：慢速线的MA类型
  - 有效范围：0到8
- **optInSignalPeriod**（默认：9）：信号线的周期
  - 有效范围：1到100000
- **optInSignalMAType**（默认：SMA）：信号线的MA类型
  - 有效范围：0到8

## 输入
- 价格数据：`double[]`

## 输出
- MACD线、信号线、柱状图：`double[]`、`double[]`、`double[]`

## 含义
MACDEXT解释取决于选择的MA类型，但通常：
- **MACD > 0**：看涨动量
- **MACD < 0**：看跌动量
- **MACD交叉信号线上方**：看涨信号
- **MACD交叉信号线下方**：看跌信号
- **柱状图扩展**：动量增加
- **柱状图收缩**：动量减少

## 使用方法
1. **MA类型选择**：根据市场条件选择MA类型
2. **信号线交叉**：寻找MACD/信号线交叉
3. **零线交叉**：监控MACD交叉零线
4. **背离**：比较MACD与价格寻找背离
5. **柱状图分析**：监控柱状图的动量变化

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MACDEXT
    TA_RetCode ret = TA_MACDEXT(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        12,                   // fastPeriod
        TA_MAType_EMA,       // fastMAType
        26,                   // slowPeriod
        TA_MAType_EMA,       // slowMAType
        9,                    // signalPeriod
        TA_MAType_SMA,       // signalMAType
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
5. **自定义MA组合**：为不同市场试验不同MA类型

## 优势
- 使用不同MA类型高度可定制
- 可以为不同市场条件优化
- 提供标准MACD缺乏的灵活性
- 对测试不同MA组合有用

## 限制
- 比标准MACD更复杂
- 需要理解不同MA类型
- 可能过度优化
- 在波动市场中可能给出假信号

## 相关函数
- `MACD` - 移动平均收敛/发散
- `MACDFIX` - MACD固定12/26
- `PPO` - 百分比价格振荡器
- `APO` - 绝对价格振荡器
- `EMA` - 指数移动平均线

## 参考文献
- Appel, Gerald (1979). "移动平均收敛-发散方法"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
