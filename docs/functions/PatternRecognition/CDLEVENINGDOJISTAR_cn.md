# CDLEVENINGDOJISTAR - 暮星十字星

## 概述
暮星十字星（CDLEVENINGDOJISTAR）是一种三根K线的看跌反转形态，类似于暮星，但中间K线是十字星。这种形态被认为比常规暮星更可靠。

## 分类
形态识别

## 计算方法
CDLEVENINGDOJISTAR 函数识别暮星十字星形态：

### 暮星十字星判断标准
- 第一根K线：大的看涨K线
- 第二根K线：向上跳空的十字星
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
暮星十字星表明：
- **强看跌反转**：非常强的向下反转信号
- **市场犹豫**：十字星显示反转前的平衡
- **顶部形成**：经常标记重要的市场顶部
- **非常高可靠性**：比常规暮星更可靠

## 使用方法
1. **反转信号**：在形态完成后进入空头头寸
2. **阻力位**：在关键阻力位最强大
3. **成交量**：更高的成交量强化信号
4. **止损**：设置在形态高点上方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLEVENINGDOJISTAR
    TA_RetCode ret = TA_CDLEVENINGDOJISTAR(
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
                // 暮星十字星形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在完成时进入空头
2. **高确信度**：鉴于可靠性增加仓位大小
3. **阻力交易**：结合阻力分析
4. **风险管理**：在形态高点上方设置紧密止损

## 优势
- 非常高的可靠性
- 清晰的犹豫信号（十字星）
- 强反转指标
- 适用于所有时间框架

## 局限性
- 罕见的形态
- 需要确认
- 需要三根K线
- 在关键阻力位最有效

## 相关函数
- `CDLEVENINGSTAR` - 暮星
- `CDLMORNINGDOJISTAR` - 晨星十字星
- `CDLDOJI` - 十字星
- `CDLDARKCLOUDCOVER` - 乌云盖顶

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
