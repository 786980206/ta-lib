# CDLMORNINGDOJISTAR - 晨星十字星

## 概述
晨星十字星（CDLMORNINGDOJISTAR）是一种三蜡烛看涨反转形态，类似于晨星，但中间蜡烛是十字星。这种形态被认为比普通晨星更可靠。

## 分类
形态识别

## 计算方法
CDLMORNINGDOJISTAR 函数识别晨星十字星形态：

### 晨星十字星判断标准
- 第一根蜡烛：大看跌蜡烛
- 第二根蜡烛：向下跳空的十字星
- 第三根蜡烛：大看涨蜡烛，收盘价深入第一根蜡烛的实体
- 形态出现在下跌趋势后

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
- **穿透度**：第三根蜡烛必须收盘深入第一根蜡烛的程度（默认：0.3 = 30%）
- **输出**：形态识别数组（100表示形态，0表示无形态）

## 含义
晨星十字星表明：
- **强看涨反转**：非常强的向上反转信号
- **市场犹豫**：十字星显示反转前的平衡
- **底部形成**：经常标记重要的市场底部
- **极高可靠性**：比普通晨星更可靠

## 使用方法
1. **反转信号**：在形态完成后做多
2. **支撑位**：在关键支撑位最有效
3. **成交量**：更高成交量强化信号
4. **止损**：设置在形态低点下方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLMORNINGDOJISTAR
    TA_RetCode ret = TA_CDLMORNINGDOJISTAR(
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
                // 晨星十字星形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在完成时做多
2. **高信心**：由于可靠性可增大仓位
3. **支撑交易**：结合支撑分析
4. **风险管理**：在形态低点下方设置紧密止损

## 优势
- 极高可靠性
- 清晰的犹豫信号（十字星）
- 强反转指标
- 适用于所有时间框架

## 局限性
- 罕见形态
- 需要确认
- 需要三根蜡烛
- 在关键支撑位效果最好

## 相关函数
- `CDLMORNINGSTAR` - 晨星
- `CDLEVENINGDOJISTAR` - 暮星十字星
- `CDLDOJI` - 十字星
- `CDLPIERCING` - 刺透形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
