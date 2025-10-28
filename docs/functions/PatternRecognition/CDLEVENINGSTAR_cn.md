# CDLEVENINGSTAR - 暮星

## 概述
暮星（CDLEVENINGSTAR）是一种三根K线的看跌反转形态，出现在上涨趋势的顶部。它由一根大的看涨K线、一根小实体K线（"星"）和一根大的看跌K线组成。

## 分类
形态识别

## 计算方法
CDLEVENINGSTAR 函数识别暮星形态：

### 暮星判断标准
- 第一根K线：大的看涨K线
- 第二根K线：小实体（星），向上跳空
- 第三根K线：大的看跌K线，收盘价深入第一根K线的实体
- 形态出现在上涨趋势后

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
- **输出**：形态识别数组（-100表示形态，0表示无形态）

## 含义
暮星表明：
- **看跌反转**：强向下反转信号
- **顶部形成**：经常标记市场顶部
- **动量转换**：从看涨到看跌动量的清晰转换
- **高可靠性**：最可靠的反转形态之一

## 使用方法
1. **反转信号**：在形态完成后进入空头头寸
2. **阻力位**：在关键阻力位最强大
3. **成交量确认**：第三根K线的高成交量强化信号
4. **止损**：设置在形态高点上方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLEVENINGSTAR
    TA_RetCode ret = TA_CDLEVENINGSTAR(
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
            if (pattern[i] == -100) {
                // 检测到暮星形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态完成时进入空头
2. **趋势变化**：退出多头头寸
3. **阻力交易**：结合阻力分析
4. **仓位大小**：鉴于形态可靠性增加仓位大小

## 优势
- 高度可靠的反转形态
- 清晰的视觉识别
- 适用于所有时间框架
- 强劲的历史记录

## 局限性
- 相对罕见的形态
- 需要三根K线完成
- 没有确认可能有虚假信号
- 在重要阻力位最有效

## 相关函数
- `CDLMORNINGSTAR` - 晨星
- `CDLEVENINGDOJISTAR` - 暮星十字星
- `CDL3BLACKCROWS` - 三只乌鸦
- `CDLDARKCLOUDCOVER` - 乌云盖顶

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
