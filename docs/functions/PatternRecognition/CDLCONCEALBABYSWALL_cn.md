# CDLCONCEALBABYSWALL - 隐藏婴儿燕

## 概述
隐藏婴儿燕（CDLCONCEALBABYSWALL）是一种四根K线的看跌反转形态，出现在上涨趋势的顶部。它由四根具有特定特征的看跌K线组成。

## 分类
形态识别

## 计算方法
CDLCONCEALBABYSWALL 函数识别隐藏婴儿燕形态：

### 隐藏婴儿燕判断标准
- 第一根K线：黑光头光脚（很短的影线）
- 第二根K线：黑光头光脚（很短的影线）
- 第三根K线：黑K线，向下跳空开盘，上影线延伸到前期实体内
- 第四根K线：黑K线，完全包含第三根K线，包括影线
- 形态出现在下跌趋势中（看涨反转）

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
隐藏婴儿燕表明：
- **看跌反转**：上涨趋势后的强向下反转
- **顶部形成**：经常标记市场顶部
- **动量转换**：从看涨到看跌动量的清晰转换
- **高可靠性**：强反转信号

## 使用方法
1. **反转信号**：在形态完成后进入空头头寸
2. **阻力位**：在关键阻力位最强大
3. **成交量确认**：更高的成交量强化信号
4. **止损**：设置在形态高点上方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLCONCEALBABYSWALL
    TA_RetCode ret = TA_CDLCONCEALBABYSWALL(
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
                // 隐藏婴儿燕形态
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
- 需要四根K线完成
- 没有确认可能有虚假信号
- 在重要阻力位最有效

## 相关函数
- `CDLEVENINGSTAR` - 暮星
- `CDL3BLACKCROWS` - 三只乌鸦
- `CDLDARKCLOUDCOVER` - 乌云盖顶
- `CDLENGULFING` - 吞没形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
