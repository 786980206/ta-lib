# CDLHOMINGPIGEON - 归巢鸽形态

## 概述
归巢鸽形态是一种看涨反转形态，由一根长黑K线后跟一根包含在其内的小黑K线组成。

## 分类
形态识别

## 计算方法
CDLHOMINGPIGEON 函数识别归巢鸽形态：

### 归巢鸽判断标准
- 第一根K线：长黑（看跌）K线
- 第二根K线：短黑实体完全包含在前一天实体内
- 形态出现在下跌趋势中（看涨反转信号）

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
归巢鸽形态表明：
- **看涨信号**：潜在的向上运动
- **看跌信号**：潜在的向下运动
- **市场情绪**：显示当前市场心理
- **交易机会**：提供入场/出场信号

## 使用方法
1. **形态识别**：识别特定的K线形态
2. **确认**：等待形态完成
3. **成交量分析**：用成交量确认
4. **风险管理**：使用适当的止损

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLHOMINGPIGEON
    TA_RetCode ret = TA_CDLHOMINGPIGEON(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 看涨形态
            } else if (pattern[i] == -100) {
                // 看跌形态
            }
        }
    }
}
```

## 交易策略
1. **形态交易**：基于形态信号交易
2. **确认**：等待形态完成
3. **成交量确认**：使用成交量确认信号
4. **风险管理**：实施适当的止损

## 优势
- 清晰的视觉形态
- 易于识别
- 适用于所有时间框架
- 可与其他指标结合使用

## 局限性
- 可能给出虚假信号
- 需要确认
- 最好与其他指标一起使用
- 市场背景重要

## 相关函数
- 其他K线形态函数
- 成交量指标
- 动量指标
- 支撑/阻力分析

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
