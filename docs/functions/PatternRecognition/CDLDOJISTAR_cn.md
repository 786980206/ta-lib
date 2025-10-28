# CDLDOJISTAR - 十字星形态

## 概述
十字星形态（CDLDOJISTAR）是一种三根K线的反转形态，根据背景可以是看涨或看跌的。它由一根大K线、一根十字星（"星"）和另一根相反方向的大K线组成。

## 分类
形态识别

## 计算方法
CDLDOJISTAR 函数识别十字星形态：

### 看涨十字星判断标准
- 第一根K线：长白（看涨）实体
- 第二根K线：向上跳空的十字星

### 看跌十字星判断标准
- 第一根K线：长黑（看跌）实体
- 第二根K线：向下跳空的十字星
- 形态可以是看涨或看跌的

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
- **穿透度**：第三根K线必须收盘深入第一根K线的程度（默认：0.3 = 30%）
- **输出**：形态识别数组（100表示看涨，-100表示看跌，0表示无形态）

## 含义
十字星形态表明：
- **看涨十字星**：下跌趋势后潜在的向上反转
- **看跌十字星**：上涨趋势后潜在的向下反转
- **市场犹豫**：十字星显示反转前的平衡
- **高可靠性**：强反转信号

## 使用方法
1. **背景分析**：根据前期趋势确定形态是看涨还是看跌
2. **确认**：等待形态完成
3. **成交量**：更高的成交量强化信号
4. **支撑/阻力**：在关键位置使用

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLDOJISTAR
    TA_RetCode ret = TA_CDLDOJISTAR(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        0.3,                 // penetration
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 看涨十字星
            } else if (pattern[i] == -100) {
                // 看跌十字星
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在第三根K线方向入场
2. **背景交易**：考虑前期趋势
3. **确认**：等待形态完成
4. **风险管理**：使用适当的止损

## 优势
- 高可靠性
- 清晰的犹豫信号
- 双向有效
- 强反转指标

## 局限性
- 需要三根K线
- 依赖背景的解释
- 可能给出虚假信号
- 在关键位置最有效

## 相关函数
- `CDLDOJI` - 十字星
- `CDLMORNINGDOJISTAR` - 晨星十字星
- `CDLEVENINGDOJISTAR` - 暮星十字星
- `CDLSTAR` - 星形形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
