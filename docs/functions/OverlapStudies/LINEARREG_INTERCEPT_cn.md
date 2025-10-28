# LINEARREG_INTERCEPT - 线性回归截距

## 概述
线性回归截距计算线性回归线的y截距。它表示回归线与y轴交叉的位置。

## 分类
统计函数

## 计算方法
线性回归截距计算最佳拟合线的截距：

### 公式
```
截距 = ȳ - 斜率 × x̄

其中：
ȳ = y值的平均值（价格）
x̄ = x值的平均值（时间）
斜率 = 线性回归斜率
```

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`（通常是收盘价）

## 输出
- 截距值：`double[]`

## 含义
线性回归截距表示：
- **起始点**：回归线开始的位置
- **基线值**：时间零点的理论价格
- **趋势背景**：与斜率结合，定义完整的回归线
- **价格水平**：为价格定位提供背景

## 使用方法
1. **趋势分析**：与斜率结合理解完整趋势
2. **价格水平**：用作价格定位的参考
3. **趋势变化**：监控截距随时间的变化
4. **通道构建**：与标准差一起用于通道

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算LINEARREG_INTERCEPT
    TA_RetCode ret = TA_LINEARREG_INTERCEPT(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        intercept            // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用intercept数组进行分析
        // 通常与斜率和其他回归函数结合
        for (int i = 0; i < outNBElement; i++) {
            printf("截距: %.2f\n", intercept[i]);
        }
    }
}
```

## 交易策略
1. **趋势分析**：与斜率结合获得完整趋势图
2. **通道交易**：与标准差一起用于通道构建
3. **支撑/阻力**：用作动态支撑/阻力水平
4. **价格预测**：与斜率结合预测未来价格

## 优势
- 完整线性回归分析的一部分
- 统计推导和客观
- 对趋势分析有用
- 可以与其他回归指标结合

## 限制
- 比其他回归输出更不直观
- 最好与斜率结合使用
- 在快速移动的市场中滞后
- 作为更广泛分析的组成部分最有用

## 相关函数
- `LINEARREG` - 线性回归
- `LINEARREG_ANGLE` - 线性回归角度
- `LINEARREG_SLOPE` - 线性回归斜率
- `TSF` - 时间序列预测
- `STDDEV` - 标准差

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
