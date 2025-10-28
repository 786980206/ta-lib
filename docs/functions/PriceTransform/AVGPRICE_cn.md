# AVGPRICE - 平均价格

## 概述
平均价格（AVGPRICE）计算每个周期的开盘价、最高价、最低价和收盘价的平均值。它提供了周期内典型价格的简单表示。

## 分类
价格变换

## 计算方法
AVGPRICE函数计算所有四个价格值的平均值：

### 公式
```
平均价格 = (开盘价 + 最高价 + 最低价 + 收盘价) / 4
```

## 参数
- **输入**：OHLC数据（开盘价、最高价、最低价、收盘价）
- **输出**：平均价格数组

## 含义
平均价格表示：
- **中心趋势**：显示价格区间的中心点
- **价格平衡**：平等平衡所有四个价格组成部分
- **平滑**：提供价格移动的平滑表示
- **支撑/阻力**：可以作为支撑和阻力水平的参考

## 使用方法
1. **趋势分析**：用作平滑价格参考
2. **支撑/阻力**：使用平均价格识别关键水平
3. **比较**：与其他价格变换（典型、加权、中位数）比较
4. **指标输入**：用作其他技术指标的输入

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算AVGPRICE
    TA_RetCode ret = TA_AVGPRICE(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        avgPrice             // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用avgPrice数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            printf("平均价格: %.2f\n", avgPrice[i]);
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：用作趋势识别的基线
2. **均值回归**：当价格偏离平均值时交易
3. **支撑/阻力**：用作动态支撑/阻力水平
4. **指标输入**：用作移动平均线和振荡器的输入

## 优势
- 简单直观的计算
- 平衡所有四个价格组成部分
- 对平滑价格数据有用
- 可以用作其他指标的输入

## 限制
- 平等权重所有价格组成部分（可能不反映重要性）
- 提供的信息比单独的OHLC少
- 可能不适合所有市场条件
- 比更复杂的价格变换更简单

## 相关函数
- `TYPPRICE` - 典型价格
- `MEDPRICE` - 中位数价格
- `WCLPRICE` - 加权收盘价
- `SMA` - 简单移动平均线
- `EMA` - 指数移动平均线

## 参考文献
- Martin Pring的《技术分析解释》
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
