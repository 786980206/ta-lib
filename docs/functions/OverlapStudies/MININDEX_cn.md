# MININDEX - 指定周期内最低值的索引

## 概述
MININDEX返回指定周期内最低值的索引（位置）。与返回值本身的MIN不同，MININDEX告诉您最小值何时发生（多少周期前）。

## 分类
数学运算符

## 计算方法
MININDEX识别指定周期内最小值的索引：

### 公式
```
MININDEX = min(price[0], price[1], ..., price[period-1])的索引
```

返回最小值发生的周期数（0 = 当前周期）。

## 参数
- **optInTimePeriod**（默认：30）：回望的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`

## 输出
- 绝对索引位置：`int[]`（输入序列的0基索引）
  - 转换为"周期前"：使用`currentIndex - outputValue`

## 含义
MININDEX指示：
- **低索引（接近0）**：近期低点（最小值是近期的）
- **高索引（接近周期）**：旧低点（最小值是很久以前的）
- **索引 = 0**：当前周期是最低点
- **索引 = period-1**：低点在周期开始

## 使用方法
1. **谷值识别**：识别谷值何时发生
2. **趋势强度**：近期最小值（低索引）表明强下降趋势
3. **强度检测**：旧最小值（高索引）表明下降趋势疲软
4. **突破确认**：索引 = 0确认正在创新低

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MININDEX
    TA_RetCode ret = TA_MININDEX(
        0,                    // startIdx
        99,                   // endIdx
        low_prices,          // inReal
        30,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        minIndex             // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        // 使用minIndex数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (minIndex[i] == 0) {
                // 新低 - 强下降趋势
            } else if (minIndex[i] > 20) {
                // 低点是旧的 - 潜在下降趋势减弱
            }
        }
    }
}
```

## 交易策略
1. **跌破交易**：当索引 = 0时出场（新低）
2. **趋势强度**：使用低索引确认趋势强度
3. **反转信号**：高索引可能信号潜在反转
4. **支撑/阻力**：与MAXINDEX结合进行区间识别

## 优势
- 识别极值的时间
- 对趋势强度评估有用
- 补充MIN函数
- 帮助识别新低与旧低

## 限制
- 不提供实际值（仅索引）
- 解释需要背景
- 可能比其他指标更不直观
- 最好与其他指标一起使用

## 相关函数
- `MIN` - 指定周期内的最低值
- `MAXINDEX` - 指定周期内最高值的索引
- `MAX` - 指定周期内的最高值
- `MINMAXINDEX` - 最低和最高值的索引
- `MINMAX` - 最低和最高值

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
