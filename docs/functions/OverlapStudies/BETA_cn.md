# BETA - Beta系数

## 概述
Beta衡量证券相对于整个市场的波动性或系统性风险。它是投资组合管理和风险评估中的关键指标。

## 分类
统计函数

## 计算方法
Beta使用证券收益与市场收益之间的线性回归计算：

### 公式
```
Beta = 协方差(证券收益, 市场收益) / 方差(市场收益)
     = 相关性(证券, 市场) × (标准差(证券) / 标准差(市场))
```

## 参数
- **optInTimePeriod**（默认：5）：计算的周期数
  - 有效范围：1 到 100000

## 输入
- 两个价格序列（通常是证券和市场/基准）：`double[]`, `double[]`

## 输出
- Beta系数数值：`double[]`

## 含义
Beta值解释如下：
- **Beta = 1.0**：证券与市场同步移动
- **Beta > 1.0**：证券比市场更波动（放大市场移动）
- **Beta < 1.0**：证券比市场波动性小（抑制市场移动）
- **Beta = 0**：证券独立于市场移动
- **Beta < 0**：证券与市场反向移动

## 使用方法
1. **风险评估**：衡量证券的系统性风险
2. **投资组合构建**：平衡投资组合beta以匹配风险承受能力
3. **绩效归因**：理解收益来源
4. **对冲**：使用beta确定对冲比率

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算BETA
    TA_RetCode ret = TA_BETA(
        0,                    // startIdx
        99,                   // endIdx
        security_prices,      // inReal0 (证券)
        market_prices,        // inReal1 (市场/基准)
        5,                    // timePeriod
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        beta                 // outReal
    );
    
    if (ret == TA_SUCCESS) {
        // 使用beta数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (beta[i] > 1.5) {
                // 高beta股票 - 比市场更波动
            } else if (beta[i] < 0.5) {
                // 低beta股票 - 比市场波动性小
            }
        }
    }
}
```

## 交易策略
1. **高Beta股票**：在趋势市场中交易（放大收益/损失）
2. **低Beta股票**：在不确定市场中持有（减少波动性）
3. **市场时机**：根据市场前景调整投资组合beta
4. **对冲**：使用beta计算风险管理对冲比率

## 优势
- 广泛使用和理解的测量
- 对投资组合管理有用
- 帮助评估系统性风险
- 对CAPM计算重要

## 限制
- 假设与市场线性关系
- 历史beta可能不预测未来beta
- 单因子模型（忽略其他风险因子）
- 可能随时间和市场条件变化

## 相关函数
- `CORREL` - 皮尔逊相关系数
- `VAR` - 方差
- `STDDEV` - 标准差
- `LINEARREG` - 线性回归

## 参考文献
- Sharpe, W. F. (1964). "资本资产价格：市场均衡理论"
- Martin Pring的《技术分析解释》
- TA-Lib文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
