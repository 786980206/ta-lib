# CDLGAPSIDESIDEWHITE - 跳空并列白线

## 概述
跳空并列白线形态由跳空后的两根并列白K线组成，表明趋势延续。

## 分类
形态识别

## 计算方法
CDLGAPSIDESIDEWHITE 函数识别跳空并列白线形态：

### 跳空并列白线判断标准
- 向上或向下跳空（实体之间）
- 跳空后第一根K线：白（看涨）K线
- 跳空后第二根K线：白K线，大小相似，开盘价与前期相似
- 第二根K线不封闭跳空

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
跳空并列白线形态表明：
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
    // 计算CDLGAPSIDESIDEWHITE
    TA_RetCode ret = TA_CDLGAPSIDESIDEWHITE(
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
