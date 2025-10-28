# CDLSHOOTINGSTAR - 流星线

## 概述
流星线（CDLSHOOTINGSTAR）是一种看跌反转K线形态，在上涨趋势后形成。它在底部有一个小实体，长上影线，很少或没有下影线。

## 分类
形态识别

## 计算方法
CDLSHOOTINGSTAR 函数识别流星线形态：

### 流星线判断标准
- 蜡烛底部附近的小实体
- 长上影线（明显长于实体 - 自适应阈值）
- 很少或无下影线
- 出现在上涨趋势后
- 实体可以是看涨或看跌的

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
流星线表明：
- **看跌反转**：上涨趋势后潜在的向下反转
- **拒绝**：显示对更高价格的拒绝
- **动量转换**：表明潜在的动量转换
- **需要确认**：需要下一根K线确认

## 使用方法
1. **反转信号**：在上涨趋势顶部寻找流星线
2. **确认**：等待看跌K线确认
3. **阻力位**：在关键阻力位最有效
4. **成交量**：更高的成交量强化信号

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLSHOOTINGSTAR
    TA_RetCode ret = TA_CDLSHOOTINGSTAR(
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
                // 检测到流星线形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态确认后进入空头
2. **止损**：设置在形态高点上方
3. **阻力交易**：结合阻力位分析
4. **确认**：等待看跌跟进

## 优势
- 清晰的视觉形态
- 顶部的强反转信号
- 适用于所有时间框架
- 有据可查的形态

## 局限性
- 需要确认
- 没有确认可能给出虚假信号
- 在重要阻力位最有效
- 在震荡市场中可靠性较低

## 相关函数
- `CDLINVERTEDHAMMER` - 倒锤子线
- `CDLHANGINGMAN` - 上吊线
- `CDLDOJI` - 十字星
- `CDLGRAVESTONEDOJI` - 墓碑十字星

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
