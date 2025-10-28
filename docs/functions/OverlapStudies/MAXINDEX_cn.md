# MAXINDEX - 指定周期内最高值的索引

## 概述
MAXINDEX返回指定周期内最高值的索引（位置）。与返回值本身的MAX不同，MAXINDEX告诉您最大值何时发生（多少周期前）。

## 分类
数学运算符

## 计算方法
MAXINDEX识别指定周期内最大值的索引：

### 公式
```
MAXINDEX = max(price[0], price[1], ..., price[period-1])的索引
```

返回最大值发生的周期数（0 = 当前周期）。

## 参数
- **optInTimePeriod**（默认：30）：回望的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`

## 输出
- 绝对索引位置：`int[]`（输入序列的0基索引）
  - 转换为"周期前"：使用`currentIndex - outputValue`

## 含义
MAXINDEX指示：
- **低索引（接近0）**：近期高点（最大值是近期的）
- **高索引（接近周期）**：旧高点（最大值是很久以前的）
- **索引 = 0**：当前周期是最高点
- **索引 = period-1**：高点在周期开始

## 使用方法
1. **峰值识别**：识别峰值何时发生
2. **趋势强度**：近期最大值（低索引）表明强上升趋势
3. **疲软检测**：旧最大值（高索引）表明趋势疲软
4. **突破确认**：索引 = 0确认正在创新高

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MAXINDEX
    TA_RetCode ret = TA_MAXINDEX(
        0,                    // startIdx
        99,                   // endIdx
        high_prices,         // inReal
        30,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        maxIndex             // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        // 使用maxIndex数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (maxIndex[i] == 0) {
                // 新高 - 强上升趋势
            } else if (maxIndex[i] > 20) {
                // 高点是旧的 - 潜在趋势减弱
            }
        }
    }
}
```

## 交易策略
1. **突破交易**：当索引 = 0时入场（新高）
2. **趋势强度**：使用低索引确认趋势强度
3. **反转信号**：高索引可能信号潜在反转
4. **支撑/阻力**：与MININDEX结合进行区间识别

## 优势
- 识别极值的时间
- 对趋势强度评估有用
- 补充MAX函数
- 帮助识别新高与旧高

## 限制
- 不提供实际值（仅索引）
- 解释需要背景
- 可能比其他指标更不直观
- 最好与其他指标一起使用

## 相关函数
- `MAX` - 指定周期内的最高值
- `MININDEX` - 指定周期内最低值的索引
- `MIN` - 指定周期内的最低值
- `MINMAXINDEX` - 最低和最高值的索引
- `MINMAX` - 最低和最高值

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
