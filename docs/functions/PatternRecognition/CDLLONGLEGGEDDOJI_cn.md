# CDLLONGLEGGEDDOJI - 长腿十字星

## 概述
长腿十字星（CDLLONGLEGGEDDOJI）是一种有很长上影线和下影线的十字星形态，表明极端的市场犹豫不决和高波动性。

## 分类
形态识别

## 计算方法
CDLLONGLEGGEDDOJI 函数识别长腿十字星形态：

### 长腿十字星判断标准
- 开盘价和收盘价几乎相等（十字星）
- 很长的上影线
- 很长的下影线
- 显示极端犹豫不决

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
长腿十字星表明：
- **极端犹豫**：买卖双方之间的最大不确定性
- **高波动性**：两个方向的显著价格波动
- **潜在反转**：经常出现在主要转折点
- **市场衰竭**：可能预示趋势衰竭

## 使用方法
1. **主要反转信号**：在重要位置寻找
2. **成交量确认**：更高的成交量强化信号
3. **背景分析**：考虑市场条件
4. **跟进**：等待下一根K线方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLLONGLEGGEDDOJI
    TA_RetCode ret = TA_CDLLONGLEGGEDDOJI(
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
                // 检测到长腿十字星
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态后寻找反转
2. **突破交易**：交易从犹豫中的突破
3. **波动性交易**：用于极端波动性信号
4. **衰竭交易**：交易趋势衰竭

## 优势
- 强犹豫信号
- 清晰的视觉形态
- 在重要位置有效
- 适合波动性分析

## 局限性
- 罕见的形态
- 需要强确认
- 可能不提供清晰方向
- 最好与其他指标一起使用

## 相关函数
- `CDLDOJI` - 十字星
- `CDLHIGHWAVE` - 高浪线
- `CDLSPINNINGTOP` - 纺锤顶
- `CDLDRAGONFLYDOJI` - 蜻蜓十字星

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
