# CDLMATCHINGLOW - 相同低点

## 概述
相同低点（CDLMATCHINGLOW）是一种两蜡烛看涨反转形态，其中两根蜡烛具有相同的低价格，表明潜在的支撑和反转。

## 分类
形态识别

## 计算方法
CDLMATCHINGLOW 函数识别相同低点形态：

### 相同低点判断标准
- 第一根蜡烛：看跌蜡烛
- 第二根蜡烛：与第一根具有相同低点的看跌蜡烛
- 形态出现在下跌趋势后
- 显示潜在支撑位

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
- **输出**：形态识别数组（100表示形态，0表示无形态）

## 含义
相同低点表明：
- **支撑位**：相同低点显示支撑
- **看涨反转**：潜在的向上反转
- **双底**：类似于双底形态
- **需要确认**：需要看涨跟进

## 使用方法
1. **支撑交易**：在相同低点寻找支撑
2. **反转信号**：在形态后做多
3. **确认**：等待看涨跟进
4. **止损**：设置在相同低点下方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLMATCHINGLOW
    TA_RetCode ret = TA_CDLMATCHINGLOW(
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
                // 相同低点形态
            }
        }
    }
}
```

## 交易策略
1. **支撑交易**：交易支撑位
2. **反转交易**：在形态后做多
3. **双底**：类似于双底交易
4. **确认**：等待看涨跟进

## 优势
- 清晰的支撑位
- 易于识别
- 良好的反转信号
- 在关键位置有效

## 局限性
- 需要确认
- 可能给出虚假信号
- 在重要支撑位效果最好
- 需要看涨跟进

## 相关函数
- `CDLDOJI` - 十字星
- `CDLHAMMER` - 锤子
- `CDLENGULFING` - 吞没形态
- `CDLPIERCING` - 刺透形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
