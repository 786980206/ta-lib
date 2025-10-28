# CDLHARAMICROSS - 十字孕线形态

## 概述
十字孕线（CDLHARAMICROSS）是一种两蜡烛反转形态，其中第二根蜡烛是完全包含在第一根蜡烛实体内的十字星。它是孕线形态的变体。

## 分类
形态识别

## 计算方法
CDLHARAMICROSS 函数识别十字孕线形态：

### 十字孕线判断标准
- 第一根蜡烛：大实体蜡烛
- 第二根蜡烛：完全包含在第一根蜡烛实体内的十字星
- 形态可以是看涨或看跌
- 显示市场犹豫不决

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
十字孕线表明：
- **看涨十字孕线**：下跌趋势后潜在的向上反转
- **看跌十字孕线**：上升趋势后潜在的向下反转
- **市场犹豫**：十字星显示不确定性
- **反转信号**：潜在的趋势变化

## 使用方法
1. **反转信号**：在趋势极值寻找形态
2. **确认**：等待下一根蜡烛确认
3. **成交量**：更高成交量强化信号
4. **支撑/阻力**：在关键位置使用

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLHARAMICROSS
    TA_RetCode ret = TA_CDLHARAMICROSS(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 看涨十字孕线
            } else if (pattern[i] == -100) {
                // 看跌十字孕线
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在与前一趋势相反的方向入场
2. **确认**：等待跟进
3. **犹豫交易**：交易从犹豫中的突破
4. **风险管理**：使用紧密止损

## 优势
- 显示清晰的市场犹豫
- 易于识别
- 双向有效
- 良好的反转信号

## 局限性
- 需要确认
- 可能给出虚假信号
- 在关键位置效果最好
- 不如吞没形态可靠

## 相关函数
- `CDLHARAMI` - 孕线形态
- `CDLDOJI` - 十字星
- `CDLENGULFING` - 吞没形态
- `CDLSPINNINGTOP` - 纺锤顶

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
