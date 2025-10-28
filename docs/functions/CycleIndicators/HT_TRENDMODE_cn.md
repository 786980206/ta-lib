# HT_TRENDMODE - Hilbert变换 - 趋势模式

## 概述
Hilbert变换 - 趋势模式（HT_TRENDMODE）是一个周期指标，确定市场是处于趋势模式还是区间模式。它是John Ehlers开发的MESA（MESA自适应移动平均线）指标套件的一部分。

## 分类
周期指标

## 计算方法
HT_TRENDMODE函数计算二进制值（0或1），指示市场是处于趋势模式还是区间模式。

### 输出值
- **1**：趋势模式
- **0**：区间/周期模式

### 算法
该函数使用多个标准来确定趋势与周期模式：

1. **正弦波分析**：从DCPhase计算Sine和LeadSine
   ```
   Sine = sin(DCPhase)
   LeadSine = sin(DCPhase + 45°)
   ```

2. **默认假设**：从trend = 1开始

3. **检查正弦波交叉**：
   - 如果Sine交叉LeadSine（任一方向），重置daysInTrend = 0并设置trend = 0

4. **检查趋势中的天数**：
   - 如果daysInTrend < 0.5 × smoothPeriod，设置trend = 0

5. **检查相位变化率**：
   - 计算Delta Phase = DCPhase - 之前的DCPhase
   - 如果Delta Phase在周期周期的预期范围内，设置trend = 0

6. **检查价格偏离趋势线**：
   - 如果|价格 - 趋势线| / 趋势线 >= 0.015（1.5%），设置trend = 1

**注意**：该函数返回二进制指标，不是连续值。它使用正弦波交叉和相位分析来区分趋势市场（方向性策略有效）和周期市场（振荡策略有效）。

## 参数
- **输入**：价格数据（通常是收盘价）
- **输出**：趋势模式数组（0.0到1.0）

## 含义
HT_TRENDMODE指示市场模式：
- **1.0（趋势）**：市场处于清晰趋势
- **0.0（区间）**：市场处于区间/盘整阶段
- **中间值**：混合或过渡模式

## 使用方法
1. **模式识别**：用于识别当前市场模式
2. **策略选择**：根据模式选择适当的交易策略
3. **过滤信号**：根据市场模式过滤其他指标
4. **风险管理**：根据市场模式调整头寸规模

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算HT_TRENDMODE
    TA_RetCode ret = TA_HT_TRENDMODE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        trendmode           // outTrendMode
    );
    
    if (ret == TA_SUCCESS) {
        // 使用trendmode数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (trendmode[i] > 0.8) {
                // 趋势模式 - 使用趋势跟踪策略
            } else if (trendmode[i] < 0.2) {
                // 区间模式 - 使用均值回归策略
            } else {
                // 混合模式 - 使用谨慎
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：当模式 > 0.8时使用趋势跟踪策略
2. **均值回归**：当模式 < 0.2时使用均值回归策略
3. **模式过滤**：根据市场模式过滤其他指标
4. **策略切换**：根据模式变化切换策略

## 优势
- 提供清晰的市场模式识别
- 帮助选择适当的交易策略
- 在所有市场条件下效果良好
- 可以与其他指标结合

## 限制
- 需要足够的数据进行准确计算
- 在快速变化的市场中可能滞后
- 最好与其他指标结合使用
- 需要理解周期分析

## 相关函数
- `HT_DCPERIOD` - 主导周期
- `HT_DCPHASE` - 主导周期相位
- `HT_PHASOR` - 相量组成部分
- `HT_QUADRA` - 正交
- `HT_SINE` - 正弦波
- `HT_TRENDLINE` - 趋势线

## 参考文献
- Ehlers, J. F. (2001). "交易者的火箭科学"
- Ehlers, J. F. (2004). "股票和期货的网络分析"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
