# MIDPOINT - 周期中点

## 概述
中点计算指定周期内最高值和最低值的中点（平均值）。它提供了价格随时间中心趋势的简单表示。

## 分类
重叠研究

## 计算方法
MIDPOINT函数计算指定周期内范围的中点：

### 公式
```
中点 = (最高值 + 最低值) / 2
```

在指定的时间周期内。

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`

## 输出
- 中点值：`double[]`

## 含义
中点表示：
- **中心趋势**：显示周期内价格范围的中心
- **支撑/阻力**：可以作为动态支撑或阻力
- **价格平衡**：指示价格随时间的平衡点
- **趋势参考**：为趋势分析提供参考线

## 使用方法
1. **趋势识别**：价格在中点上方表明上升趋势，下方表明下降趋势
2. **支撑/阻力**：用作动态支撑/阻力水平
3. **均值回归**：当价格显著偏离中点时交易
4. **突破**：寻找价格突破中点

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MIDPOINT
    TA_RetCode ret = TA_MIDPOINT(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        midpoint             // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用midpoint数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (close_prices[i] > midpoint[i]) {
                // 价格在中点上方 - 看涨
            } else {
                // 价格在中点下方 - 看跌
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：当价格交叉中点时入场
2. **均值回归**：逆极值交易回到中点
3. **支撑/阻力**：使用中点作为动态水平
4. **区间交易**：在高点、低点和中点之间交易

## 优势
- 简单直观的计算
- 提供清晰的支撑/阻力水平
- 在区间市场中效果良好
- 对均值回归策略有用

## 限制
- 在趋势市场中滞后
- 在波动条件下可能给出假信号
- 不考虑成交量或动量
- 最好与其他指标一起使用

## 相关函数
- `MIDPRICE` - 周期中点价格
- `MAX` - 指定周期内的最高值
- `MIN` - 指定周期内的最低值
- `MEDPRICE` - 中位价格
- `SMA` - 简单移动平均线

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
