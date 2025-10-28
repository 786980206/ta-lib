# CDLKICKING - 踢脚形态

## 概述
踢脚形态（CDLKICKING）是一种K线形态，由两根K线组成，其中第二根K线在第一根K线相反方向跳空并继续朝该方向运动。这是一个强反转形态，可以预示趋势变化。

## 分类
形态识别

## 计算方法
CDLKICKING 函数通过比较当前和前期K线来识别踢脚形态：

### 看涨踢脚
- 前期K线是看跌的（收盘价 < 开盘价）
- 当前K线是看涨的（收盘价 > 开盘价）
- 当前K线从前期K线向上跳空
- 两根K线都有大实体
- 当前K线继续看涨方向

### 看跌踢脚
- 前期K线是看涨的（收盘价 > 开盘价）
- 当前K线是看跌的（收盘价 < 开盘价）
- 当前K线从前期K线向下跳空
- 两根K线都有大实体
- 当前K线继续看跌方向

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
- **输出**：形态识别数组（100表示看涨，-100表示看跌，0表示无形态）

## 含义
踢脚形态表明：
- **看涨踢脚**：下跌趋势后的强向上反转
- **看跌踢脚**：上涨趋势后的强向下反转
- **跳空反转**：显示带跳空的强反转
- **确认**：应通过其他指标确认

## 使用方法
1. **反转信号**：在趋势极值处寻找踢脚形态
2. **成交量确认**：通过成交量分析确认
3. **支撑/阻力**：在关键支撑/阻力位使用
4. **趋势背景**：考虑整体趋势方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLKICKING
    TA_RetCode ret = TA_CDLKICKING(
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
                // 看涨踢脚形态
            } else if (pattern[i] == -100) {
                // 看跌踢脚形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在与前期趋势相反的方向入场
2. **突破确认**：用于确认突破信号
3. **趋势变化**：在趋势变化点寻找形态
4. **风险管理**：基于形态大小使用止损

## 优势
- 显示强反转信号
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
