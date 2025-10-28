# TSF - 时间序列预测

## 概述
时间序列预测（TSF）将线性回归线向前延伸一个周期。它基于当前趋势预测价格预期位置。

## 分类
统计函数

## 计算方法
TSF通过延伸线性回归线计算预测值：

### 公式
```
TSF = 截距 + 斜率 × (周期 + 1)

其中：
截距 = 线性回归截距
斜率 = 线性回归斜率
周期 = 当前时间周期
```

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`（通常是收盘价）

## 输出
- 预测价格值：`double[]`

## 含义
时间序列预测表示：
- **价格预测**：基于当前趋势的预期价格
- **趋势延伸**：趋势线向前延伸一个周期
- **目标价格**：价格移动的统计目标
- **趋势强度**：与当前价格的距离表示趋势强度

## 使用方法
1. **价格目标**：用作下一个周期的目标价格
2. **趋势跟踪**：在TSF相对于当前价格的方向入场
3. **偏差分析**：测量当前价格偏离预测的程度
4. **趋势确认**：上升TSF确认上升趋势，下降TSF确认下降趋势

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算TSF
    TA_RetCode ret = TA_TSF(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        tsf                  // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用TSF数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (tsf[i] > close_prices[i]) {
                // 预测高于当前价格 - 看涨
            } else {
                // 预测低于当前价格 - 看跌
            }
            
            double deviation = (close_prices[i] - tsf[i]) / tsf[i];
            if (fabs(deviation) > 0.05) {
                // 价格显著偏离预测
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在TSF方向入场
2. **价格目标**：使用TSF作为利润目标
3. **均值回归**：当价格显著偏离TSF时交易
4. **突破**：寻找价格突破TSF水平

## 优势
- 提供前瞻性价格预测
- 统计推导且客观
- 用于设置价格目标有用
- 在趋势市场中效果良好

## 限制
- 假设趋势将继续（在反转中可能不会）
- 在快速移动市场中滞后
- 在波动条件下准确性较低
- 单周期预测可能不够

## 相关函数
- `LINEARREG` - 线性回归
- `LINEARREG_ANGLE` - 线性回归角度
- `LINEARREG_INTERCEPT` - 线性回归截距
- `LINEARREG_SLOPE` - 线性回归斜率
- `EMA` - 指数移动平均

## 参考文献
- Martin Pring的《技术分析解释》
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
