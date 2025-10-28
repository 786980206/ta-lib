# CDLSHORTLINE - 短线蜡烛

## 概述
短线蜡烛（CDLSHORTLINE）是一种单蜡烛形态，代表小价格移动，具有小实体和小影线，表明低波动性和犹豫不决。

## 分类
形态识别

## 计算方法
CDLSHORTLINE 函数识别短线蜡烛：

### 短线判断标准
- 相对于总范围的小实体
- 小上影线
- 小下影线
- 显示低波动性和犹豫不决

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
- **输出**：形态识别数组（100表示形态，0表示无形态）

## 含义
短线蜡烛表明：
- **低波动性**：最小价格移动
- **市场犹豫**：缺乏信念
- **整理**：可能发出整理阶段信号
- **潜在突破**：经常先于重大移动

## 使用方法
1. **整理信号**：寻找整理阶段
2. **突破准备**：为潜在突破做准备
3. **波动性评估**：用于波动性分析
4. **区间交易**：在区间内交易

## 使用示例
```c
#include "ta_libc.h"

int main() {
    // 计算CDLSHORTLINE
    TA_RetCode ret = TA_CDLSHORTLINE(
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
                // 检测到短线蜡烛
            }
        }
    }
}
```

## 交易策略
1. **整理交易**：在区间内交易
2. **突破准备**：为突破做准备
3. **波动性交易**：用于低波动性信号
4. **区间交易**：交易区间

## 优势
- 清晰的整理信号
- 易于识别
- 适合区间交易
- 对波动性分析有用

## 局限性
- 可能不提供清晰方向
- 在区间市场中效果最好
- 需要突破确认
- 在某些市场中可能有噪音

## 相关函数
- `CDLLONGLINE` - 长线蜡烛
- `CDLSPINNINGTOP` - 纺锤顶
- `CDLDOJI` - 十字星
- `CDLHIGHWAVE` - 高浪线

## 参考文献
- Nison, S. (1991). "日本K线图技术"
- TA-Lib 文档：https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib：https://deepwiki.com/TA-Lib/ta-lib
