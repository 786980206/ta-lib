# CDL3BLACKCROWS - 三只乌鸦形态

## 概述
三只乌鸦形态（CDL3BLACKCROWS）是一种K线形态，由三根连续的看跌蜡烛组成，具有相似特征。这是一个强看跌延续形态，可以预示趋势延续。

## 分类
形态识别

## 计算方法
CDL3BLACKCROWS 函数通过分析三根连续蜡烛来识别三只乌鸦形态：

### 三只乌鸦判断标准
- 前期蜡烛：看涨（白）蜡烛
- 第一根黑蜡烛：看跌，下影线很短，收盘价低于前期白蜡烛的高点
- 第二根黑蜡烛：看跌，下影线很短，开盘价在第一根黑蜡烛实体内
- 第三根黑蜡烛：看跌，下影线很短，开盘价在第二根黑蜡烛实体内
- 三根连续下跌的收盘价（每根收盘价都低于前一根）

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
- **输出**：形态识别数组（100表示三只乌鸦，0表示无形态）

## 含义
三只乌鸦形态表明：
- **看跌延续**：强向下延续
- **卖出压力**：显示持续的卖出兴趣
- **趋势强度**：表明强看跌动量
- **确认**：应通过其他指标确认

## 使用方法
1. **延续信号**：在下跌趋势中寻找三只乌鸦
2. **成交量确认**：通过成交量分析确认
3. **支撑/阻力**：在关键支撑/阻力位使用
4. **趋势背景**：考虑整体趋势方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDL3BLACKCROWS
    TA_RetCode ret = TA_CDL3BLACKCROWS(
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
                // 三只乌鸦形态
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在下跌趋势中进入空头头寸
2. **突破确认**：用于确认突破信号
3. **趋势延续**：在趋势市场中寻找形态
4. **风险管理**：基于形态大小使用止损

## 优势
- 显示强看跌延续
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
