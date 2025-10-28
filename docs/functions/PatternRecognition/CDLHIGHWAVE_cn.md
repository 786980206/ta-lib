# CDLHIGHWAVE - 高浪线

## 概述
高浪线（CDLHIGHWAVE）是一种单根K线形态，表明市场犹豫不决。它有小实体和长上影线及下影线，显示买卖双方都很活跃。

## 分类
形态识别

## 计算方法
CDLHIGHWAVE 函数识别高浪线：

### 高浪线判断标准
- 相对于总范围的小实体
- 长上影线
- 长下影线
- 显示高波动性和犹豫不决

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
高浪线表明：
- **市场犹豫**：买卖双方之间的强烈不确定性
- **高波动性**：两个方向的显著价格运动
- **潜在反转**：经常出现在趋势极值处
- **盘整**：可能预示盘整阶段

## 使用方法
1. **犹豫信号**：在极值处寻找高浪线
2. **成交量分析**：结合成交量确认
3. **背景**：考虑前期趋势
4. **跟进**：等待下一根K线方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLHIGHWAVE
    TA_RetCode ret = TA_CDLHIGHWAVE(
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
                // 检测到高浪线
            }
        }
    }
}
```

## 交易策略
1. **犹豫交易**：等待从犹豫中突破
2. **反转交易**：在高浪线后寻找反转
3. **波动性交易**：用于波动性评估
4. **盘整**：在高浪线后交易区间

## 优势
- 清晰的犹豫信号
- 易于识别
- 显示市场不确定性
- 适合波动性分析

## 局限性
- 需要确认
- 可能不提供清晰方向
- 最好与其他指标一起使用
- 在某些市场中可能嘈杂

## 相关函数
- `CDLSPINNINGTOP` - 纺锤顶
- `CDLDOJI` - 十字星
- `CDLLONGLEGGEDDOJI` - 长腿十字星
- `CDLHAMMER` - 锤子线

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
