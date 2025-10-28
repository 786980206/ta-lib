# CDL2CROWS - 两只乌鸦

## 概述
两只乌鸦形态（CDL2CROWS）是一种三根K线的看跌反转形态，出现在上涨趋势的顶部。它预示着从看涨到看跌的潜在趋势反转。

## 分类
形态识别

## 计算方法
CDL2CROWS 函数识别两只乌鸦形态：

### 两只乌鸦判断标准
- 第一根K线：强看涨K线（白/绿）
- 第二根K线：看跌K线，向上跳空但收盘价在第一根K线实体内
- 第三根K线：看跌K线，开盘价在第二根K线实体内，收盘价在第一根K线实体内
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
- **输出**：形态识别数组（-100表示形态，0表示无形态）

## 含义
两只乌鸦形态表明：
- **看跌反转**：上涨趋势后潜在的向下反转
- **多头疲软**：尽管向上跳空，但空头控制了局面
- **顶部形成**：经常标记市场顶部
- **需要确认**：应通过其他指标确认

## 使用方法
1. **反转信号**：在趋势顶部寻找两只乌鸦
2. **成交量确认**：通过增加的成交量确认
3. **阻力位**：在关键阻力位使用
4. **风险管理**：在形态高点上方设置止损

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDL2CROWS
    TA_RetCode ret = TA_CDL2CROWS(
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
            if (pattern[i] == -100) {
                // 检测到两只乌鸦形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态后进入空头头寸
2. **趋势变化**：退出多头头寸
3. **确认**：等待下一根K线确认
4. **止损**：设置在形态高点上方

## 优势
- 清晰的视觉形态
- 强反转信号
- 适用于所有时间框架
- 有据可查的形态

## 局限性
- 相对罕见的形态
- 需要确认
- 可能给出虚假信号
- 在重要阻力位最有效

## 相关函数
- `CDL3BLACKCROWS` - 三只乌鸦
- `CDLEVENINGSTAR` - 暮星
- `CDLDARKCLOUDCOVER` - 乌云盖顶
- `CDLENGULFING` - 吞没形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
