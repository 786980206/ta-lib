# 蜡烛图形态识别 - 技术概述

## 简介

TA-Lib 实现了一个基于传统日本蜡烛图分析的复杂蜡烛图形态识别系统。本文档解释了适用于所有蜡烛图形态函数（CDL* 函数）的技术实现细节。

## 自适应阈值系统

### 概述

与简单的固定比例形态识别不同，TA-Lib 使用**自适应阈值系统**，该系统根据最近的市场条件调整形态标准。这使得形态识别在不同证券和市场环境中更加稳健。

### 工作原理

当文档描述形态标准时，如：
- "长实体"
- "短实体"
- "小实体"
- "十字星（开盘价 ≈ 收盘价）"
- "长影线"
- "向上/向下跳空"

实际实现将当前蜡烛特征与**最近历史平均值**进行比较，而不是固定百分比。

### 自适应计算

对于每个蜡烛特征（例如，实体长度），TA-Lib：

1. **计算该特征的滚动平均值**，基于最近的蜡烛
2. **将当前值与这个自适应阈值进行比较**
3. **自动调整市场波动性**

#### 示例：十字星形态

**概念描述：**
```
当 |收盘价 - 开盘价| 相对于价格区间非常小时，出现十字星
```

**实际实现：**
```c
if( TA_REALBODY(i) <= TA_CANDLEAVERAGE(BodyDoji, BodyDojiPeriodTotal, i) )
    // 这是一个十字星
```

其中：
- `TA_REALBODY(i)` = 蜡烛 i 的 |收盘价 - 开盘价|
- `TA_CANDLEAVERAGE(BodyDoji, ...)` = 基于最近蜡烛的自适应阈值
- 阈值自动适应市场条件

### 阈值类型

TA-Lib 定义了多种蜡烛特征类型：

| 类型 | 描述 | 用于 |
|------|------|------|
| `BodyDoji` | 非常小的实体 | 十字星形态 |
| `BodyShort` | 短实体 | 星形形态，小蜡烛 |
| `BodyLong` | 长实体 | 强方向性蜡烛 |
| `ShadowShort` | 短影线 | 有限的上影线 |
| `ShadowLong` | 长影线 | 延长的影线 |
| `ShadowVeryShort` | 非常短的影线 | 类似光头光脚 |
| `ShadowVeryLong` | 非常长的影线 | 锤子，流星 |
| `Near` | 接近 | 跳空分析 |
| `Far` | 显著分离 | 跳空分析 |
| `Equal` | 大约相等 | 水平比较 |

## 可配置设置

### TA_SetCandleSettings 函数

用户可以使用以下方式自定义形态识别阈值：

```c
TA_RetCode TA_SetCandleSettings(
    TA_CandleSettingType settingType,    // 要调整的特征
    TA_RangeType rangeType,              // 如何计算范围
    int avgPeriod,                       // 平均值的回望周期
    double factor                        // 阈值的乘数
);
```

### 参数

**settingType**: 要调整的蜡烛特征（BodyLong、ShadowShort 等）

**rangeType**: 如何测量特征：
- `RealBody` - 使用 |收盘价 - 开盘价|
- `HighLow` - 使用 最高价 - 最低价
- `Shadows` - 使用影线长度

**avgPeriod**: 滚动平均的蜡烛数量（0 = 使用默认值）

**factor**: 阈值乘数（默认值因设置而异）

### 默认设置

TA-Lib 使用基于广泛测试精心校准的默认值：

```c
// 示例默认值（简化）
BodyDoji:      avgPeriod=10, factor=0.1   // 实体 ≤ 最近平均范围的 10%
BodyShort:     avgPeriod=10, factor=0.3   // 实体 ≤ 最近平均实体的 30%
BodyLong:      avgPeriod=10, factor=1.0   // 实体 ≥ 最近平均实体的 100%
ShadowLong:    avgPeriod=10, factor=1.0   // 影线 ≥ 最近平均的 100%
```

### 恢复默认值

```c
TA_RetCode TA_RestoreCandleDefaultSettings(TA_CandleSettingType settingType);
```

将 `settingType` 设置为 `TA_AllCandleSettings` 以恢复所有默认值。

## 形态识别输出

### 输出值

蜡烛图形态函数返回整数值：

| 值 | 含义 |
|----|------|
| `100` | 检测到看涨形态（强） |
| `1-99` | 检测到看涨形态（较弱信心） |
| `0` | 未检测到形态 |
| `-1 到 -99` | 检测到看跌形态（较弱信心） |
| `-100` | 检测到看跌形态（强） |

### 强度评分

某些形态根据以下因素调整输出强度：
- **精确与近似匹配**（例如，完美/接近完美的吞没形态为 100 vs 80）
- **形态形成质量**（例如，更清晰的形态得分更高）
- **标准完整性**（满足所有条件 vs 满足大多数条件）

## 实现细节

### 宏系统

TA-Lib 使用 C 宏进行高效的形态检测：

```c
// 检查蜡烛颜色
TA_CANDLECOLOR(i)          // 返回 1（白色/看涨）或 -1（黑色/看跌）

// 测量蜡烛特征
TA_REALBODY(i)             // |收盘价 - 开盘价|
TA_UPPERSHADOW(i)          // 最高价 - max(开盘价, 收盘价)
TA_LOWERSHADOW(i)          // min(开盘价, 收盘价) - 最低价
TA_HIGHHIGHLOW(i)          // 最高价 - 最低价

// 与自适应平均值比较
TA_CANDLEAVERAGE(type, total, i)  // 自适应阈值

// 检测跳空
TA_REALBODYGAPUP(i, j)     // 实体向上跳空
TA_REALBODYGAPDOWN(i, j)   // 实体向下跳空
```

### 滚动平均计算

对于每次形态识别调用，TA-Lib：

1. **初始化每个使用的阈值类型的周期总计**
2. **在 avgPeriod 期间累积历史值**
3. **在处理每个新蜡烛时更新滚动总计**
4. **计算自适应阈值** = (periodTotal / avgPeriod) × factor

这种高效方法允许实时形态检测，无需从头重新计算。

## 形态文档解释

### 阅读形态标准

当形态的文档说明标准时，如：

**"第一根蜡烛：长白实体"**

这意味着：
```c
TA_CANDLECOLOR(i-2) == 1 &&  // 白色（看涨）
TA_REALBODY(i-2) > TA_CANDLEAVERAGE(BodyLong, BodyLongPeriodTotal, i-2)  // 长
```

**"第二根蜡烛：小实体"**

这意味着：
```c
TA_REALBODY(i-1) <= TA_CANDLEAVERAGE(BodyShort, BodyShortPeriodTotal, i-1)
```

**"蜡烛间向上跳空"**

这意味着：
```c
TA_REALBODYGAPUP(i, i-1)  // 当前实体在前一根实体上方跳空
```

### 固定 vs 自适应标准

某些形态标准是固定的（非自适应）：

✅ **自适应**（适应市场）：
- 实体大小分类（长/短/十字星）
- 影线长度分类
- 什么构成"跳空"

🔒 **固定**（始终相同）：
- 蜡烛颜色（看涨/看跌）
- 蜡烛序列和顺序
- 相对位置要求（例如，"在前一根实体内收盘"）
- 穿透百分比（当明确指定为参数时）

## 最佳实践

### 对于形态识别用户

1. **最初使用默认设置** - 它们适用于大多数市场
2. **为特定证券调整设置**（如果需要）（例如，加密货币 vs 股票）
3. **在历史数据上测试阈值变化**，然后再进行实盘交易
4. **与其他分析结合** - 蜡烛图形态是信号，不是确定性
5. **考虑市场背景** - 形态在支撑/阻力位更可靠

### 对于不同市场

**股票**：默认设置效果良好

**外汇**：可能需要稍微严格的阈值（较低的因子）

**加密货币**：由于波动性较高，可能需要更宽松的阈值

**低波动性**：考虑减少 avgPeriod 以更快适应

**高波动性**：考虑增加 avgPeriod 以获得更多稳定性

## 技术参考

### 关键函数

- `TA_SetCandleSettings()` - 自定义阈值
- `TA_RestoreCandleDefaultSettings()` - 重置为默认值
- 所有 `TA_CDL*()` 函数 - 形态识别函数

### 源代码

形态识别实现：`ta-lib/src/ta_func/ta_CDL*.c`

蜡烛图工具：`ta-lib/src/ta_func/ta_utility.h`

设置管理：`ta-lib/src/ta_common/ta_global.c`

## 总结

TA-Lib 的蜡烛图形态识别系统提供：

✅ **自适应阈值**，适应市场条件
✅ **可配置设置**，用于自定义
✅ **稳健检测**，适用于不同证券
✅ **高效计算**，通过滚动平均
✅ **传统形态**，现代实现

这种自适应方法使 TA-Lib 的形态识别比简单的固定比例系统更可靠，同时仍然遵循传统日本蜡烛图分析原则。

## 另请参阅

- 个别形态文档：`CDL*.md` 文件
- TA-Lib API 文档：特定语言的使用方法
- 传统蜡烛图分析文献，用于形态解释
