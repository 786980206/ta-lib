# CDLTHRUSTING - 推入形态

## 概述
推入形态（CDLTHRUSTING）是一种两蜡烛看跌延续形态，其中第二根蜡烛在第一根蜡烛的收盘价下方开盘，但收盘价在第一根蜡烛的实体内，显示看跌疲软。

## 分类
形态识别

## 计算方法
CDLTHRUSTING 函数识别推入形态：

### 推入判断标准
- 第一根蜡烛：大看跌蜡烛
- 第二根蜡烛：在第一根蜡烛收盘价下方开盘
- 第二根蜡烛：收盘价在第一根蜡烛的实体内
- 显示看跌延续

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
- **输出**：形态识别数组（-100表示形态，0表示无形态）

## 含义
推入形态表明：
- **看跌延续**：潜在的向下延续
- **疲软**：显示无法显著恢复
- **阻力**：第一根蜡烛的实体充当阻力
- **需要确认**：需要看跌跟进

## 使用方法
1. **延续信号**：寻找看跌延续
2. **阻力交易**：使用第一根蜡烛的实体作为阻力
3. **确认**：等待看跌跟进
4. **止损**：设置在形态高点上方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLTHRUSTING
    TA_RetCode ret = TA_CDLTHRUSTING(
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
            if (pattern[i] == -100) {
                // 推入形态
            }
        }
    }
}
```

## 交易策略
1. **延续交易**：在形态后做空
2. **阻力交易**：用作阻力位
3. **疲软交易**：交易疲软
4. **确认**：等待看跌跟进

## 优势
- 清晰的延续信号
- 易于识别
- 良好的阻力位
- 在下跌趋势中有效

## 局限性
- 需要确认
- 可能给出虚假信号
- 在下跌趋势中效果最好
- 需要看跌跟进

## 相关函数
- `CDLINNECK` - 颈内形态
- `CDLONNECK` - 颈上形态
- `CDLENGULFING` - 吞没形态
- `CDLHARAMI` - 孕线形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
