# CDLMORNINGSTAR - 晨星

## 概述
晨星（CDLMORNINGSTAR）是一种三蜡烛看涨反转形态，出现在下跌趋势的底部。它由一根大看跌蜡烛、一根小实体蜡烛（"星"）和一根大看涨蜡烛组成。

## 分类
形态识别

## 计算方法
CDLMORNINGSTAR 函数识别晨星形态：

### 晨星判断标准
- 第一根蜡烛：大看跌蜡烛
- 第二根蜡烛：向下跳空的小实体（星）
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
晨星表明：
- **看涨反转**：强向上反转信号
- **底部形成**：经常标记市场底部
- **动量转换**：从看跌到看涨动量的清晰转换
- **高可靠性**：最可靠的反转形态之一

## 使用方法
1. **反转信号**：在形态完成后做多
2. **支撑位**：在关键支撑位最有效
3. **成交量确认**：第三根蜡烛的更高成交量强化信号
4. **止损**：设置在形态低点下方

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLMORNINGSTAR
    TA_RetCode ret = TA_CDLMORNINGSTAR(
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
                // 检测到晨星形态
            }
        }
    }
}
```

## 交易策略
1. **反转交易**：在形态完成时做多
2. **趋势变化**：退出空头头寸
3. **支撑交易**：结合支撑分析
4. **仓位大小**：由于形态可靠性可增加仓位大小

## 优势
- 高度可靠的反转形态
- 清晰的视觉识别
- 适用于所有时间框架
- 强历史记录

## 局限性
- 相对罕见形态
- 需要三根蜡烛完成
- 没有确认可能有虚假信号
- 在重要支撑位效果最好

## 相关函数
- `CDLEVENINGSTAR` - 暮星
- `CDLMORNINGDOJISTAR` - 晨星十字星
- `CDL3WHITESOLDIERS` - 三白兵
- `CDLPIERCING` - 刺透形态

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib