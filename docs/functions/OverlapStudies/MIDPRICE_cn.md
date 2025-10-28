# MIDPRICE - 周期中点价格

## 概述
中点价格计算指定周期内最高价和最低价的平均值。它类似于MIDPOINT，但专门使用最高价和最低价而不是单一价格序列。

## 分类
重叠研究

## 计算方法
MIDPRICE函数计算指定周期内高低范围的中点：

### 公式
```
中点价格 = (最高价 + 最低价) / 2
```

在指定的时间周期内。

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 最高价：`double[]`
- 最低价：`double[]`

## 输出
- 中点价格值：`double[]`

## 含义
中点价格表示：
- **中心趋势**：显示周期内高低范围的中心
- **支撑/阻力**：可以作为动态支撑或阻力
- **价格平衡**：指示价格极值的平衡点
- **趋势参考**：为趋势分析提供参考线

## 使用方法
1. **趋势识别**：价格在中点价格上方表明上升趋势，下方表明下降趋势
2. **支撑/阻力**：用作动态支撑/阻力水平
3. **均值回归**：当价格显著偏离中点价格时交易
4. **突破**：寻找价格突破中点价格

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MIDPRICE
    TA_RetCode ret = TA_MIDPRICE(
        0,                    // startIdx
        99,                   // endIdx
        high_prices,         // inHigh
        low_prices,          // inLow
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        midprice             // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用midprice数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (close_prices[i] > midprice[i]) {
                // 价格在中点价格上方 - 看涨
            } else {
                // 价格在中点价格下方 - 看跌
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：当价格交叉中点价格时入场
2. **均值回归**：逆极值交易回到中点价格
3. **支撑/阻力**：使用中点价格作为动态水平
4. **区间交易**：在高点、低点和中点价格之间交易

## 优势
- 简单直观的计算
- 使用最高价和最低价（捕获完整范围）
- 提供清晰的支撑/阻力水平
- 在区间市场中效果良好

## 限制
- 在趋势市场中滞后
- 在波动条件下可能给出假信号
- 不考虑成交量或动量
- 最好与其他指标一起使用

## 相关函数
- `MIDPOINT` - 周期中点
- `MAX` - 指定周期内的最高值
- `MIN` - 指定周期内的最低值
- `MEDPRICE` - 中位价格
- `SAR` - 抛物线SAR

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
