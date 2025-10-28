# CDLLONGLINE - 长线蜡烛

## 概述
长线蜡烛（CDLLONGLINE）是一种单蜡烛形态，代表强烈的方向性移动，具有大实体和小影线，表明在一个方向上的强烈信念。

## 分类
形态识别

## 计算方法
CDLLONGLINE 函数识别长线蜡烛：

### 长线判断标准
- 相对于总范围的大实体
- 小或没有上影线
- 小或没有下影线
- 显示强烈的方向性信念

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
长线蜡烛表明：
- **强方向性**：在一个方向的强力移动
- **高信念度**：对价格方向的强烈信念
- **趋势延续**：通常在同一方向延续
- **动量**：显示强动量

## 使用方法
1. **趋势跟踪**：在长线方向入场
2. **动量交易**：用于动量确认
3. **突破交易**：在突破长线时入场
4. **成交量确认**：更高成交量强化信号

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLLONGLINE
    TA_RetCode ret = TA_CDLLONGLINE(
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
                // 看涨长线
            } else if (pattern[i] == -100) {
                // 看跌长线
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：跟随长线方向
2. **动量交易**：用于动量确认
3. **突破交易**：在突破时入场
4. **延续交易**：预期延续

## 优势
- 清晰的方向信号
- 强信念指标
- 易于识别
- 适合动量交易

## 局限性
- 可能是滞后信号
- 在震荡市场中可能给出虚假信号
- 在趋势市场中效果最好
- 需要成交量确认

## 相关函数
- `CDLMARUBOZU` - 光头光脚
- `CDLSHORTLINE` - 短线蜡烛
- `CDLSPINNINGTOP` - 纺锤顶
- `CDLDOJI` - 十字星

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
