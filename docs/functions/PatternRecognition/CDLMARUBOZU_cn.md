# CDLMARUBOZU - 光头光脚形态

## 概述
光头光脚形态（CDLMARUBOZU）是一种K线形态，由一根没有影线（或影线很小）且实体很大的蜡烛组成。它表明强烈的方向性运动和当前趋势的延续。

## 分类
形态识别

## 计算方法
CDLMARUBOZU 函数通过分析蜡烛的实体和影线特征来识别光头光脚形态：

### 看涨光头光脚
- 大的看涨实体（收盘价 > 开盘价）
- 无或很小的上影线
- 无或很小的下影线
- 强买入压力

### 看跌光头光脚
- 大的看跌实体（收盘价 < 开盘价）
- 无或很小的上影线
- 无或很小的下影线
- 强卖出压力

## 实现说明

**此形态使用TA-Lib的自适应阈值系统**来确定蜡烛特征，如"长实体"、"短实体"、"十字星"等。这些阈值会根据最近的市场行为自动调整，而不是使用固定百分比。

有关详细信息，请参阅：
- 自适应阈值的工作原理
- 配置形态检测敏感度
- 理解输出值
- 技术实现细节

参见：[K线形态识别概述](CANDLESTICK_PATTERNS_OVERVIEW.md)


## 参数
- **输入**：OHLC数据（开盘价、最高价、最低价、收盘价）
- **输出**：形态识别数组（100表示看涨，-100表示看跌，0表示无形态）

## 含义
光头光脚形态表明：
- **看涨光头光脚**：强买入压力和潜在的向上延续
- **看跌光头光脚**：强卖出压力和潜在的向下延续
- **趋势强度**：显示强烈的方向性运动
- **延续**：经常预示趋势延续

## 使用方法
1. **趋势延续**：在趋势市场中寻找光头光脚形态
2. **成交量确认**：通过成交量分析确认
3. **支撑/阻力**：在关键支撑/阻力位使用
4. **趋势背景**：考虑整体趋势方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLMARUBOZU
    TA_RetCode ret = TA_CDLMARUBOZU(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,      // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        // 使用形态数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 看涨光头光脚形态
            } else if (pattern[i] == -100) {
                // 看跌光头光脚形态
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在光头光脚的方向入场
2. **突破交易**：用于确认突破信号
3. **趋势跟踪**：跟随光头光脚的方向
4. **风险管理**：基于形态大小使用止损

## 优势
- 显示强烈的方向性运动
- 易于视觉识别
- 适用于所有时间框架
- 可与其他指标结合使用

## 局限性
- 在震荡市场中可能给出虚假信号
- 需要其他指标确认
- 最好在趋势市场中使用
- 在快速移动的市场中可能滞后

## 相关函数
- `CDLHAMMER` - 锤子线形态
- `CDLDOJI` - 十字星形态
- `CDLENGULFING` - 吞没形态
- `CDLHARAMI` - 孕线形态
- `CDLSPINNINGTOP` - 纺锤顶形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
