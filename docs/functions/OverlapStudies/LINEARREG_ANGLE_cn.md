# LINEARREG_ANGLE - 线性回归角度

## 概述
线性回归角度计算线性回归线的角度（以度为单位）。它提供了趋势陡峭度和方向的测量。

## 分类
统计函数

## 计算方法
线性回归角度计算最佳拟合线的角度：

### 公式
```
角度 = arctan(斜率) × (180 / π)

其中斜率是线性回归斜率
```

角度以度为单位表示，从-90到+90。

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`（通常是收盘价）

## 输出
- 角度值（度）：`double[]`

## 含义
线性回归角度表示：
- **正角度**：上升趋势（0°到+90°）
- **负角度**：下降趋势（-90°到0°）
- **角度接近0°**：横盘/平坦趋势
- **陡峭角度**：强趋势（|角度| > 45°）
- **浅角度**：弱趋势（|角度| < 15°）

## 使用方法
1. **趋势强度**：更高的绝对角度表示更强的趋势
2. **趋势方向**：正/负角度表示上升/下降趋势
3. **趋势变化**：寻找角度反转
4. **过滤**：仅当角度超过阈值时交易

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算LINEARREG_ANGLE
    TA_RetCode ret = TA_LINEARREG_ANGLE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        angle                // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用angle数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (angle[i] > 45) {
                // 强上升趋势
            } else if (angle[i] < -45) {
                // 强下降趋势
            } else if (fabs(angle[i]) < 15) {
                // 弱趋势 / 横盘
            }
        }
    }
}
```

## 交易策略
1. **趋势强度过滤器**：仅当角度超过阈值时交易
2. **趋势跟踪**：在角度方向上入场
3. **角度反转**：寻找角度改变方向
4. **动量确认**：与动量指标结合

## 优势
- 趋势强度的直观测量
- 易于解释（度）
- 客观和系统
- 用于过滤弱趋势

## 限制
- 在快速移动的市场中滞后
- 对周期选择敏感
- 在波动条件下可能给出假信号
- 最好与其他指标一起使用

## 相关函数
- `LINEARREG` - 线性回归
- `LINEARREG_INTERCEPT` - 线性回归截距
- `LINEARREG_SLOPE` - 线性回归斜率
- `TSF` - 时间序列预测
- `ADX` - 平均方向移动指数

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
