# SAREXT - 抛物线SAR - 扩展版

## 概述
SAREXT（抛物线SAR扩展版）是抛物线SAR指标的增强版本，提供对上升趋势和下降趋势的加速因子的额外控制。

## 类别
重叠研究

## 计算
SAREXT计算抛物线SAR，对上升趋势和下降趋势的加速进行单独控制：

### 公式
```
SAR(今天) = SAR(昨天) + AF × (EP - SAR(昨天))

其中：
AF = 加速因子（随每个新极值增加）
EP = 极值点（上升趋势中的最高价，下降趋势中的最低价）
```

### 扩展参数
- **起始AF**：初始加速因子（默认：0.02）
- **增量AF**：每个新极值的AF增量（默认：0.02）
- **最大AF**：最大加速因子（默认：0.20）
- **反转偏移**：趋势反转时的偏移百分比
- **起始AF偏移**：新趋势的起始AF
- **最大AF偏移**：最大AF偏移

## 参数
- **输入**：最高价和最低价
- **起始AF**：初始加速因子
- **最大AF**：最大加速因子
- **输出**：SAR数组

## 含义
SAREXT解释：
- **SAR低于价格**：上升趋势（看涨）
- **SAR高于价格**：下降趋势（看跌）
- **SAR翻转**：趋势反转信号
- **SAR距离**：表示趋势强度

## 使用方法
1. **趋势跟踪**：按SAR指示的方向交易
2. **止损**：使用SAR作为跟踪止损
3. **趋势反转**：SAR翻转时入场/出场
4. **自定义参数**：为不同市场调整加速因子

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算SAREXT
    TA_RetCode ret = TA_SAREXT(
        0,                    // startIdx
        99,                   // endIdx
        high_prices,         // inHigh
        low_prices,          // inLow
        0.02,                // startValue
        0.0,                 // offsetOnReverse
        0.02,                // accelerationInitLong
        0.02,                // accelerationLong
        0.20,                // accelerationMaxLong
        0.02,                // accelerationInitShort
        0.02,                // accelerationShort
        0.20,                // accelerationMaxShort
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        sar                  // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用SAR数组进行分析
        for (int i = 1; i < outNBElement; i++) {
            if (close_prices[i] > sar[i] && close_prices[i-1] <= sar[i-1]) {
                // SAR翻转到价格下方 - 买入信号
            } else if (close_prices[i] < sar[i] && close_prices[i-1] >= sar[i-1]) {
                // SAR翻转到价格上方 - 卖出信号
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：SAR翻转时入场
2. **跟踪止损**：使用SAR作为动态止损
3. **趋势确认**：与其他指标结合
4. **自定义优化**：为特定市场或时间框架调整加速因子

## 优势
- 具有单独的多头/空头参数的高度可定制性
- 可以为不同市场条件进行优化
- 提供趋势方向和止损水平
- 在趋势市场中表现良好

## 局限性
- 比标准SAR更复杂
- 可能过度优化
- 在横盘市场中表现不佳
- 需要调整许多参数

## 相关函数
- `SAR` - 抛物线SAR
- `HT_TRENDLINE` - 希尔伯特变换趋势线
- `MAMA` - MESA自适应移动平均线
- `EMA` - 指数移动平均线

## 参考文献
- 威尔德，J.韦尔斯（1978年）。《技术交易系统的新概念》
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
