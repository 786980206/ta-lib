# CDLCOUNTERATTACK - 反击形态

## 概述
反击形态（CDLCOUNTERATTACK）是一种两根K线的反转形态，可以是看涨或看跌的。它由两根收盘价相同但方向相反的K线组成。

## 分类
形态识别

## 计算方法
CDLCOUNTERATTACK 函数识别反击形态：

### 看涨反击判断标准
- 第一根K线：长黑（看跌）实体
- 第二根K线：长白（看涨）实体，收盘价等于第一根K线的收盘价

### 看跌反击判断标准
- 第一根K线：长白（看涨）实体
- 第二根K线：长黑（看跌）实体，收盘价等于第一根K线的收盘价

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
反击形态表明：
- **看涨反击**：潜在的向上反转
- **看跌反击**：潜在的向下反转
- **市场平衡**：显示买卖双方之间的平衡
- **反转信号**：潜在的趋势变化

## 使用方法
1. **反转信号**：在趋势极值处寻找反击
2. **平衡交易**：交易从平衡的突破
3. **成交量确认**：更高的成交量强化信号
4. **背景分析**：考虑市场条件

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLCOUNTERATTACK
    TA_RetCode ret = TA_CDLCOUNTERATTACK(
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
                // 看涨反击
            } else if (pattern[i] == -100) {
                // 看跌反击
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在与前期趋势相反的方向入场
2. **平衡交易**：交易突破
3. **趋势变化**：寻找趋势反转
4. **风险管理**：使用适当的止损

## 优势
- 清晰的平衡信号
- 易于识别
- 双向有效
- 良好的反转信号

## 局限性
- 需要确认
- 可能给出虚假信号
- 在关键位置最有效
- 需要跟进

## 相关函数
- `CDLDOJI` - 十字星
- `CDLENGULFING` - 吞没形态
- `CDLHARAMI` - 孕线形态
- `CDLSPINNINGTOP` - 纺锤顶

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
