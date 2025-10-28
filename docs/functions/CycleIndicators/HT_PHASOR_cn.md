# HT_PHASOR - Hilbert变换 - 相量组成部分

## 概述
Hilbert变换 - 相量组成部分（HT_PHASOR）是一个周期指标，使用Hilbert变换将价格数据分解为同相和正交组成部分。它是John Ehlers开发的MESA（MESA自适应移动平均线）指标套件的一部分。

## 分类
周期指标

## 计算方法
HT_PHASOR函数计算两个组成部分：
- **同相组成部分（I）**：复相量的实部
- **正交组成部分（Q）**：复相量的虚部

### 公式
```
I = 0.5 * (价格 - 价格[2])
Q = 0.5 * (价格[1] - 价格[3])
```

其中：
- `价格`是当前价格
- `价格[1]`、`价格[2]`、`价格[3]`是之前的价格

## 参数
- **输入**：价格数据（通常是收盘价）
- **输出**：两个数组 - 同相和正交组成部分

## 含义
HT_PHASOR将价格移动分解为两个正交组成部分：
- **同相（I）**：表示周期的"实"或"同相"组成部分
- **正交（Q）**：表示周期的"虚"或"正交"组成部分

这些组成部分可以一起用于：
- 确定周期相位
- 计算周期幅度
- 识别周期转折点
- 测量周期强度

## 使用方法
1. **周期分析**：使用I和Q组成部分来理解市场周期的当前相位
2. **幅度计算**：计算周期幅度为√(I² + Q²)
3. **相位计算**：计算相位为arctan(Q/I)
4. **趋势识别**：使用I和Q之间的关系来识别趋势变化

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算HT_PHASOR
    TA_RetCode ret = TA_HT_PHASOR(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        inPhase,             // outInPhase
        quadrature           // outQuadrature
    );
    
    if (ret == TA_SUCCESS) {
        // 使用inPhase和quadrature数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            double amplitude = sqrt(inPhase[i] * inPhase[i] + 
                                  quadrature[i] * quadrature[i]);
            double phase = atan2(quadrature[i], inPhase[i]);
        }
    }
}
```

## 交易策略
1. **周期相位交易**：当相位变化指示周期转折点时入场
2. **幅度过滤**：只有当周期幅度超过阈值时才交易
3. **趋势跟踪**：使用I和Q之间的关系来跟踪趋势
4. **均值回归**：当幅度高时逆周期交易

## 优势
- 为周期分析提供数学基础
- 在趋势和区间市场中效果良好
- 可以与其他Hilbert变换指标结合
- 提供客观周期测量

## 限制
- 需要足够的数据进行准确计算
- 在极短时间框架中可能有噪音
- 最好与其他指标结合使用
- 需要理解复数理论

## 相关函数
- `HT_DCPERIOD` - 主导周期
- `HT_DCPHASE` - 主导周期相位
- `HT_SINE` - 正弦波
- `HT_TRENDLINE` - 趋势线
- `HT_TRENDMODE` - 趋势模式
- `MAMA` - MESA自适应移动平均线

## 参考文献
- Ehlers, J. F. (2001). "交易者的火箭科学"
- Ehlers, J. F. (2004). "股票和期货的网络分析"
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
