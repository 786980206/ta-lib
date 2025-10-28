# CDLABANDONEDBABY - 弃婴形态

## 概述
弃婴形态（CDLABANDONEDBABY）是一种三根K线的反转形态，可以是看涨或看跌的。它由一根大K线、一根跳空离开的十字星和另一根相反方向的大K线组成。

## 分类
形态识别

## 计算方法
CDLABANDONEDBABY 函数识别弃婴形态：

### 看涨弃婴判断标准
- 第一根K线：长黑（看跌）实体
- 第二根K线：向上跳空的十字星（影线不接触第一根K线）
- 第三根K线：白（看涨）实体，与十字星向下跳空（影线不接触），收盘价深入第一根K线的实体

### 看跌弃婴判断标准
- 第一根K线：长白（看涨）实体
- 第二根K线：向下跳空的十字星（影线不接触第一根K线）
- 第三根K线：黑（看跌）实体，与十字星向上跳空（影线不接触），收盘价深入第一根K线的实体

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
- **穿透度**：第三根K线必须收盘深入第一根K线的程度（默认：0.3 = 30%）
- **输出**：形态识别数组（100表示看涨，-100表示看跌，0表示无形态）

## 含义
弃婴形态表明：
- **看涨弃婴**：下跌趋势后的强向上反转
- **看跌弃婴**：上涨趋势后的强向下反转
- **市场衰竭**：显示趋势衰竭和反转
- **高可靠性**：非常强的反转信号

## 使用方法
1. **反转信号**：在趋势极值处寻找弃婴
2. **成交量确认**：更高的成交量强化信号
3. **背景分析**：考虑市场条件
4. **跟进**：等待形态完成

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLABANDONEDBABY
    TA_RetCode ret = TA_CDLABANDONEDBABY(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        0.3,                 // penetration
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // 看涨弃婴
            } else if (pattern[i] == -100) {
                // 看跌弃婴
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在与前期趋势相反的方向入场
2. **衰竭交易**：交易趋势衰竭
3. **重要位置**：在重要支撑/阻力位使用
4. **仓位大小**：鉴于可靠性增加仓位大小

## 优势
- 非常高的可靠性
- 清晰的衰竭信号
- 在重要位置有效
- 强反转指标

## 局限性
- 非常罕见的形态
- 需要三根K线
- 可能有虚假信号
- 在重要位置最有效

## 相关函数
- `CDLMORNINGSTAR` - 晨星
- `CDLEVENINGSTAR` - 暮星
- `CDLDOJI` - 十字星
- `CDLSTAR` - 星形形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
