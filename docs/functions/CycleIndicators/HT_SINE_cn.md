# HT_SINE - Hilbert变换 - 正弦波

## 概述
Hilbert变换 - 正弦波（HT_SINE）是一个周期指标，计算Hilbert变换的正弦组成部分。它是John Ehlers开发的MESA（MESA自适应移动平均线）指标套件的一部分。

## 分类
周期指标

## 计算方法
HT_SINE函数计算Hilbert变换的正弦组成部分，它表示周期的正弦波组成部分。

### 公式
```
正弦 = sin(相位)
```

其中：
- `相位`是从同相和正交组成部分计算的
- `相位 = arctan(正交 / 同相)`

## 参数
- **输入**：价格数据（通常是收盘价）
- **输出**：正弦组成部分数组

## 含义
HT_SINE表示周期的正弦波组成部分：
- **数值范围**：-1到+1
- **正值**：表示向上周期相位
- **负值**：表示向下周期相位
- **零交叉**：通常信号周期转折点
- **极值**：表示周期峰值和谷值

## 使用方法
1. **周期转折点**：寻找正弦组成部分的零交叉
2. **相位分析**：使用符号和幅度来评估周期相位
3. **趋势变化**：与其他Hilbert变换指标结合
4. **周期强度**：使用幅度来过滤弱周期

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算HT_SINE
    TA_RetCode ret = TA_HT_SINE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        sine                 // outSine
    );
    
    if (ret == TA_SUCCESS) {
        // 使用sine数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (sine[i] > 0.8) {
                // 接近周期峰值
            } else if (sine[i] < -0.8) {
                // 接近周期谷值
            } else if (sine[i] > 0) {
                // 向上周期相位
            } else {
                // 向下周期相位
            }
        }
    }
}
```

## 交易策略
1. **零交叉信号**：当正弦交叉零时入场
2. **极值交易**：在极值处逆周期交易
3. **相位跟随**：跟随正弦动量的方向
4. **周期过滤**：只有当正弦幅度显著时才交易

## 优势
- 提供清晰的周期相位信号
- 在趋势和区间市场中效果良好
- 可以与其他Hilbert变换指标结合
- 提供客观周期测量

## 限制
- 需要足够的数据进行准确计算
- 在极短时间框架中可能有噪音
- 最好与其他指标结合使用
- 需要理解周期分析

## 相关函数
- `HT_DCPERIOD` - 主导周期
- `HT_DCPHASE` - 主导周期相位
- `HT_PHASOR` - 相量组成部分
- `HT_TRENDLINE` - 趋势线
- `HT_TRENDMODE` - 趋势模式

## 参考文献
- Ehlers, J. F. (2001). "交易者的火箭科学"
- Ehlers, J. F. (2004). "股票和期货的网络分析"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
