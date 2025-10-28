# LINEARREG - 线性回归

## 概述
线性回归使用最小二乘法在指定周期内为价格数据拟合直线。它提供统计推导的趋势线，最小化线与数据点之间的距离。

## 分类
统计函数

## 计算方法
线性回归计算通过价格数据的最佳拟合线：

### 公式
```
y = a + b × x

其中：
b（斜率）= Σ((x - x̄)(y - ȳ)) / Σ((x - x̄)²)
a（截距）= ȳ - b × x̄
```

输出是回归线在当前点的值。

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`（通常是收盘价）

## 输出
- 线性回归线值：`double[]`

## 含义
线性回归线表示：
- **趋势方向**：显示整体趋势方向
- **统计趋势线**：客观确定的趋势线
- **支撑/阻力**：可以作为动态支撑或阻力
- **价格预测**：基于趋势预测价格"应该"的位置

## 使用方法
1. **趋势识别**：使用线的斜率识别趋势方向
2. **支撑/阻力**：用作动态支撑/阻力水平
3. **偏离分析**：测量价格偏离回归线的程度
4. **趋势强度**：更陡的斜率表示更强的趋势

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算LINEARREG
    TA_RetCode ret = TA_LINEARREG(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        linearReg            // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用linearReg数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (close_prices[i] > linearReg[i]) {
                // 价格在回归线上方 - 看涨
            } else {
                // 价格在回归线下方 - 看跌
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在回归线方向上入场
2. **均值回归**：当价格显著偏离线时交易
3. **突破**：寻找价格突破回归线
4. **通道交易**：与标准差带结合用于通道

## 优势
- 统计推导和客观
- 消除趋势线绘制的主观性
- 在趋势市场中效果良好
- 可以与其他回归指标结合

## 限制
- 在快速移动的市场中滞后
- 假设线性关系（可能不总是合适）
- 最好在趋势市场中使用
- 在波动条件下可能给出假信号

## 相关函数
- `LINEARREG_ANGLE` - 线性回归角度
- `LINEARREG_INTERCEPT` - 线性回归截距
- `LINEARREG_SLOPE` - 线性回归斜率
- `TSF` - 时间序列预测
- `STDDEV` - 标准差

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
