# MINMAX - 指定周期内的最低和最高值

## 概述
MINMAX在单个函数调用中返回指定周期内的最低值和最高值。它是一个便利函数，结合了MIN和MAX。

## 分类
数学运算符

## 计算方法
MINMAX识别指定周期内的最小值和最大值：

### 公式
```
MIN = min(price[0], price[1], ..., price[period-1])
MAX = max(price[0], price[1], ..., price[period-1])
```

## 参数
- **optInTimePeriod**（默认：30）：回望的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`

## 输出
- 最小值：`double[]`
- 最大值：`double[]`

## 含义
MINMAX提供：
- **范围**：MAX和MIN之间的差异显示价格范围
- **支撑**：MIN作为支撑水平
- **阻力**：MAX作为阻力水平
- **波动性**：大范围表示高波动性

## 使用方法
1. **区间交易**：在MIN（支撑）和MAX（阻力）之间交易
2. **突破交易**：当价格突破MAX上方或跌破MIN下方时入场
3. **波动性评估**：使用范围进行波动性测量
4. **通道构建**：使用MIN和MAX作为通道边界

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MINMAX
    TA_RetCode ret = TA_MINMAX(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        30,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        min,                 // outMin
        max                  // outMax
    );
    
    if (ret == TA_SUCCESS) {
        // 使用min和max数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            double range = max[i] - min[i];
            double midpoint = (max[i] + min[i]) / 2.0;
            
            if (close_prices[i] > max[i]) {
                // 突破范围上方
            } else if (close_prices[i] < min[i]) {
                // 跌破范围下方
            } else if (close_prices[i] > midpoint) {
                // 范围的上半部分
            }
        }
    }
}
```

## 交易策略
1. **区间交易**：在MIN附近买入，在MAX附近卖出
2. **突破交易**：当价格突破区间时入场
3. **均值回归**：从极值向中点交易
4. **通道交易**：使用MIN/MAX作为动态通道边界

## 优势
- 在一次调用中提供支撑和阻力
- 高效（在单次遍历中计算两者）
- 对区间和通道交易有用
- 清晰的支撑/阻力水平

## 限制
- 不指示极值的时间
- 在趋势市场中可能滞后
- 最适合区间市场
- 不考虑成交量

## 相关函数
- `MIN` - 指定周期内的最低值
- `MAX` - 指定周期内的最高值
- `MININDEX` - 最低值的索引
- `MAXINDEX` - 最高值的索引
- `MINMAXINDEX` - 最低和最高值的索引

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
