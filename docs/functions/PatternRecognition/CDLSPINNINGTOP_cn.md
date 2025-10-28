# CDLSPINNINGTOP - 纺锤顶形态

## 概述
纺锤顶形态（CDLSPINNINGTOP）是一种K线形态，由一根具有小实体和长上下影线的蜡烛组成。它表明市场犹豫不决和潜在的趋势变化。

## 分类
形态识别

## 计算方法
CDLSPINNINGTOP 函数通过分析蜡烛的实体和影线特征来识别纺锤顶形态：

### 纺锤顶判断标准
- 相对于总范围的小实体
- 长上影线
- 长下影线
- 实体相对于影线较小

### 公式
```
实体大小 = |收盘价 - 开盘价|
总范围 = 最高价 - 最低价
影线比率 = 实体大小 / 总范围
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
- **输出**：形态识别数组（100表示纺锤顶，0表示无形态）

## 含义
纺锤顶形态表明：
- **市场犹豫**：显示买卖双方之间的不确定性
- **潜在反转**：可能发出趋势变化信号
- **整理**：经常出现在整理阶段
- **确认**：应该被其他指标确认

## 使用方法
1. **犹豫信号**：在趋势极值寻找纺锤顶
2. **成交量确认**：用成交量分析确认
3. **支撑/阻力**：在关键支撑/阻力位使用
4. **趋势背景**：考虑整体趋势方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLSPINNINGTOP
    TA_RetCode ret = TA_CDLSPINNINGTOP(
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
                // 纺锤顶形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在与前一趋势相反的方向入场
2. **突破确认**：用于确认突破信号
3. **趋势变化**：在趋势变化点寻找形态
4. **风险管理**：基于形态大小使用止损

## 优势
- 清晰显示市场犹豫
- 视觉上易于识别
- 适用于所有时间框架
- 可与其他指标结合使用

## 局限性
- 在震荡市场中可能给出虚假信号
- 需要其他指标确认
- 在关键支撑/阻力位效果最好
- 在快速移动市场中可能滞后

## 相关函数
- `CDLHAMMER` - 锤子形态
- `CDLDOJI` - 十字星形态
- `CDLENGULFING` - 吞没形态
- `CDLHARAMI` - 孕线形态
- `CDLMARUBOZU` - 光头光脚形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib