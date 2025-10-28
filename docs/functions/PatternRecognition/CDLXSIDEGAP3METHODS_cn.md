# CDLXSIDEGAP3METHODS - 向上/向下跳空三法

## 概述
向上/向下跳空三法（CDLXSIDEGAP3METHODS）是一种五蜡烛延续形态，可以是看涨或看跌。它显示一个跳空，后跟三根相反方向的小蜡烛，然后是一个原始方向的跳空。

## 分类
形态识别

## 计算方法
CDLXSIDEGAP3METHODS 函数识别跳空三法形态：

### 跳空三法判断标准
- 第一根蜡烛：一个方向的大蜡烛
- 第二根蜡烛：同一方向的跳空
- 第三、四、五根蜡烛：相反方向的小蜡烛
- 第六根蜡烛：原始方向的跳空
- 显示原始趋势的延续

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
跳空三法表明：
- **看涨延续**：整理后强向上延续
- **看跌延续**：整理后强向下延续
- **趋势强度**：显示强潜在趋势
- **高可靠性**：强延续信号

## 使用方法
1. **延续信号**：在原始趋势方向入场
2. **趋势强度**：用于确认趋势强度
3. **成交量确认**：更高成交量强化信号
4. **止损**：设置在跳空之外

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLXSIDEGAP3METHODS
    TA_RetCode ret = TA_CDLXSIDEGAP3METHODS(
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
                // 看涨跳空三法
            } else if (pattern[i] == -100) {
                // 看跌跳空三法
            }
        }
    }
}
```

## 交易策略
1. **延续交易**：在原始趋势方向入场
2. **趋势跟踪**：用于确认趋势强度
3. **跳空交易**：交易跳空延续
4. **仓位大小**：由于形态可靠性可增加仓位大小

## 优势
- 高度可靠的延续形态
- 清晰的视觉识别
- 适用于所有时间框架
- 强历史记录

## 局限性
- 需要六根蜡烛完成
- 相对罕见形态
- 没有确认可能有虚假信号
- 在强趋势市场中效果最好

## 相关函数
- `CDL3WHITESOLDIERS` - 三白兵
- `CDL3BLACKCROWS` - 三黑鸦
- `CDLENGULFING` - 吞没形态
- `CDLMARUBOZU` - 光头光脚

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
