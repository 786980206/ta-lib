# MINMAXINDEX - 指定周期内最低和最高值的索引

## 概述
MINMAXINDEX在单个函数调用中返回指定周期内最低值和最高值的索引（位置）。它结合了MININDEX和MAXINDEX功能。

## 分类
数学运算符

## 计算方法
MINMAXINDEX识别最小值和最大值的索引：

### 公式
```
MININDEX = min(price[0], price[1], ..., price[period-1])的索引
MAXINDEX = max(price[0], price[1], ..., price[period-1])的索引
```

返回极值发生的周期数（0 = 当前周期）。

## 参数
- **optInTimePeriod**（默认：30）：回望的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`

## 输出
- 最小绝对索引位置：`int[]`（输入序列的0基索引）
- 最大绝对索引位置：`int[]`
  - 转换为"周期前"：使用`currentIndex - outputValue`

## 含义
MINMAXINDEX提供：
- **极值时间**：高点和低点何时发生
- **趋势强度**：近期极值表明强趋势
- **范围位置**：当前价格相对于近期极值的位置

## 使用方法
1. **趋势强度**：低索引表示新极值（强趋势）
2. **疲软检测**：高索引表明旧极值（趋势减弱）
3. **突破确认**：索引 = 0确认新高/新低
4. **范围分析**：比较索引以评估范围位置

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算MINMAXINDEX
    TA_RetCode ret = TA_MINMAXINDEX(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        30,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        minIndex,            // outMinIdx
        maxIndex             // outMaxIdx
    );
    
    if (ret == TA_SUCCESS) {
        // 使用minIndex和maxIndex数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (maxIndex[i] == 0) {
                // 新高 - 潜在上升趋势
            }
            if (minIndex[i] == 0) {
                // 新低 - 潜在下降趋势
            }
            
            if (maxIndex[i] > 20 && minIndex[i] > 20) {
                // 两个极值都是旧的 - 盘整
            }
        }
    }
}
```

## 交易策略
1. **突破交易**：当任一索引 = 0时入场（新极值）
2. **趋势强度**：使用索引评估趋势强度
3. **盘整检测**：两个高索引表明区间市场
4. **反转信号**：索引背离可能信号反转

## 优势
- 为两个极值提供时间信息
- 高效（在单次遍历中计算两者）
- 对趋势强度评估有用
- 帮助识别新极值与旧极值

## 限制
- 不提供实际值（仅索引）
- 解释需要背景
- 可能比其他指标更不直观
- 最好与补充指标一起使用

## 相关函数
- `MININDEX` - 最低值的索引
- `MAXINDEX` - 最高值的索引
- `MINMAX` - 最低和最高值
- `MIN` - 指定周期内的最低值
- `MAX` - 指定周期内的最高值

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
