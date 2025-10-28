# LINEARREG_SLOPE - 线性回归斜率

## 概述
线性回归斜率计算线性回归线的斜率。它测量指定周期内趋势的变化率。

## 分类
统计函数

## 计算方法
线性回归斜率计算最佳拟合线的斜率：

### 公式
```
斜率 = Σ((x - x̄)(y - ȳ)) / Σ((x - x̄)²)

其中：
x = 时间周期
y = 价格
x̄ = 时间周期的平均值
ȳ = 价格的平均值
```

## 参数
- **optInTimePeriod**（默认：14）：计算的周期数
  - 有效范围：2到100000

## 输入
- 价格数据：`double[]`（通常是收盘价）

## 输出
- 斜率值：`double[]`

## 含义
线性回归斜率表示：
- **正斜率**：上升趋势（价格上涨）
- **负斜率**：下降趋势（价格下跌）
- **斜率接近0**：横盘/平坦趋势
- **大绝对斜率**：强趋势
- **小绝对斜率**：弱趋势

## 使用方法
1. **趋势方向**：正/负斜率表示上升/下降趋势
2. **趋势强度**：更大的绝对斜率表示更强的趋势
3. **趋势变化**：寻找斜率反转
4. **变化率**：测量价格变化的速度

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算LINEARREG_SLOPE
    TA_RetCode ret = TA_LINEARREG_SLOPE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        14,                   // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        slope                // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用slope数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (slope[i] > 0.5) {
                // 强上升趋势
            } else if (slope[i] < -0.5) {
                // 强下降趋势
            } else if (fabs(slope[i]) < 0.1) {
                // 弱趋势 / 横盘
            }
        }
    }
}
```

## 交易策略
1. **趋势跟踪**：在斜率方向上入场
2. **趋势强度过滤器**：仅当斜率超过阈值时交易
3. **斜率反转**：寻找斜率改变方向
4. **背离**：比较斜率与价格行为寻找背离

## 优势
- 趋势强度的直接测量
- 统计推导和客观
- 易于解释
- 用于过滤弱趋势

## 限制
- 在快速移动的市场中滞后
- 对周期选择敏感
- 在波动条件下可能给出假信号
- 最好与其他指标一起使用

## 相关函数
- `LINEARREG` - 线性回归
- `LINEARREG_ANGLE` - 线性回归角度
- `LINEARREG_INTERCEPT` - 线性回归截距
- `TSF` - 时间序列预测
- `MOM` - 动量

## 参考文献
- Martin Pring的技术分析解释
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
