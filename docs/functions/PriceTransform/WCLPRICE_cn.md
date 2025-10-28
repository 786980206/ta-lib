# WCLPRICE - 加权收盘价

## 概述
加权收盘价（WCLPRICE）计算一个强调收盘价的加权平均值，给予收盘价双倍于最高价和最低价的权重。它提供了一个优先考虑收盘值的价格表示。

## 类别
价格变换

## 计算
WCLPRICE函数计算一个强调收盘价的加权平均值：

### 公式
```
加权收盘价 = (最高价 + 最低价 + 收盘价 + 收盘价) / 4
           = (最高价 + 最低价 + 2 × 收盘价) / 4
```

## 参数
- **输入**：HLC数据（最高价、最低价、收盘价）
- **输出**：加权收盘价数组

## 含义
加权收盘价表示：
- **收盘价强调**：给予收盘价双倍权重
- **价格平衡**：平衡最高价、最低价和收盘价，强调收盘价
- **市场情绪**：反映价格收盘位置的重要性
- **平滑**：提供价格变动的平滑表示

## 使用方法
1. **趋势分析**：用作平滑价格参考
2. **支撑/阻力**：使用加权收盘价识别关键水平
3. **比较**：与其他价格变换比较
4. **指标输入**：用作其他技术指标的输入

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算WCLPRICE
    TA_RetCode ret = TA_WCLPRICE(
        0,                    // startIdx
        99,                   // endIdx
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        wclPrice             // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用wclPrice数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            printf("加权收盘价: %.2f\n", wclPrice[i]);
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：用作趋势识别的基础
2. **均值回归**：当价格偏离加权收盘价时交易
3. **支撑/阻力**：用作动态支撑/阻力水平
4. **指标输入**：用作移动平均线和振荡器的输入

## 优势
- 强调收盘价（对许多交易者最重要）
- 计算简单
- 用于平滑价格数据
- 可用作其他指标的输入

## 局限性
- 任意加权方案
- 可能不适合所有市场条件
- 比更复杂的价格变换更简单
- 不考虑开盘价

## 相关函数
- `TYPPRICE` - 典型价格
- `MEDPRICE` - 中位价格
- `AVGPRICE` - 平均价格
- `SMA` - 简单移动平均线
- `EMA` - 指数移动平均线

## 参考文献
- 马丁·普林格的《技术分析详解》
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
