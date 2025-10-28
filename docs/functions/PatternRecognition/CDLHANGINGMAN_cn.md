# CDLHANGINGMAN - 上吊线形态

## 概述
上吊线形态（CDLHANGINGMAN）是一种K线形态，由一根在区间顶部有小实体和长下影线的蜡烛组成。这是一个看跌反转形态，可以预示趋势变化。

## 分类
形态识别

## 计算方法
CDLHANGINGMAN 函数通过分析蜡烛的实体和影线特征来识别上吊线形态：

### 上吊线判断标准
- 区间顶部的小实体
- 长下影线（明显长于实体 - 自适应阈值）
- 很少或无上影线
- 出现在上涨趋势后
- 实体可以是看涨或看跌的

### 公式
```
实体大小 = |收盘价 - 开盘价|
下影线 = 开盘价 - 最低价（或收盘价 - 最低价）
影线比例 = 下影线 / 实体大小
```

## 实现说明

**此形态使用TA-Lib的自适应阈值系统**来确定蜡烛特征，如"长实体"、"短实体"、"十字星"等。这些阈值会根据最近的市场行为自动调整，而不是使用固定百分比。

有关详细信息，请参阅：
- 自适应阈值的工作原理
- 配置形态检测敏感度
- 理解输出值
- 技术实现细节

参见：[K线形态识别概述](CANDLESTICK_PATTERNS_OVERVIEW.md)


## 参数
- **输入**：OHLC数据（开盘价、最高价、最低价、收盘价）
- **输出**：形态识别数组（100表示上吊线，0表示无形态）

## 含义
上吊线形态表明：
- **看跌反转**：上涨趋势后潜在的向下反转
- **市场犹豫**：显示买卖双方之间的不确定性
- **支撑测试**：经常出现在关键阻力位
- **确认**：应通过其他指标确认

## 使用方法
1. **反转信号**：在趋势极值处寻找上吊线形态
2. **成交量确认**：通过成交量分析确认
3. **支撑/阻力**：在关键支撑/阻力位使用
4. **趋势背景**：考虑整体趋势方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLHANGINGMAN
    TA_RetCode ret = TA_CDLHANGINGMAN(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,      // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        // 使用形态数组进行分析
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 上吊线形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在上吊线后进入空头头寸
2. **突破确认**：用于确认突破信号
3. **趋势变化**：在趋势变化点寻找形态
4. **风险管理**：基于形态大小使用止损

## 优势
- 显示潜在的看跌反转
- 易于视觉识别
- 适用于所有时间框架
- 可与其他指标结合使用

## 局限性
- 在震荡市场中可能给出虚假信号
- 需要其他指标确认
- 最好在关键支撑/阻力位使用
- 在快速移动的市场中可能滞后

## 相关函数
- `CDLHAMMER` - 锤子线形态
- `CDLDOJI` - 十字星形态
- `CDLENGULFING` - 吞没形态
- `CDLHARAMI` - 孕线形态
- `CDLSPINNINGTOP` - 纺锤顶形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
