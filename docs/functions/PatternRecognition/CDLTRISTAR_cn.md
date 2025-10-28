# CDLTRISTAR - 三星形态

## 概述
三星形态（CDLTRISTAR）是一种三蜡烛反转形态，由三根十字星蜡烛组成，表明极端的市场犹豫不决和潜在反转。

## 分类
形态识别

## 计算方法
CDLTRISTAR 函数识别三星形态：

### 三星判断标准
- 第一根蜡烛：十字星
- 第二根蜡烛：与第一根跳空的十字星
- 第三根蜡烛：与第二根跳空的十字星
- 所有三根蜡烛都是十字星
- 显示极端犹豫不决

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
三星形态表明：
- **极端犹豫**：最大市场不确定性
- **潜在反转**：经常出现在主要转折点
- **市场衰竭**：可能发出趋势衰竭信号
- **高可靠性**：非常强的反转信号

## 使用方法
1. **主要反转信号**：在重要位置寻找
2. **成交量确认**：更高成交量强化信号
3. **背景分析**：考虑市场条件
4. **跟进**：等待下一根蜡烛方向

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLTRISTAR
    TA_RetCode ret = TA_CDLTRISTAR(
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
                // 看涨三星
            } else if (pattern[i] == -100) {
                // 看跌三星
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态后寻找反转
2. **突破交易**：交易从犹豫中的突破
3. **衰竭交易**：交易趋势衰竭
4. **重要位置**：在重要支撑/阻力位使用

## 优势
- 非常强的反转信号
- 清晰的犹豫形态
- 在重要位置有效
- 高可靠性

## 局限性
- 非常罕见的形态
- 需要强确认
- 可能不提供清晰方向
- 最好与其他指标一起使用

## 相关函数
- `CDLDOJI` - 十字星
- `CDLSTAR` - 星形形态
- `CDLMORNINGSTAR` - 晨星
- `CDLEVENINGSTAR` - 暮星

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
