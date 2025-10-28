# SUB - 向量算术减法

向量算术减法（SUB）函数对两个输入数组执行逐元素减法运算。这是一个基本的数学运算，将两个输入向量中对应的元素相减并返回结果。

## 函数签名

```c
TA_RetCode TA_SUB(
    int    startIdx,
    int    endIdx,
    const double inReal0[],
    const double inReal1[],
    int          *outBegIdx,
    int          *outNBElement,
    double       outReal[]
);
```

## 参数

- **startIdx**: 计算的起始索引
- **endIdx**: 计算的结束索引
- **inReal0[]**: 第一个输入数组（被减数）
- **inReal1[]**: 第二个输入数组（减数）
- **outBegIdx**: 输出起始索引的指针
- **outNBElement**: 输出元素数量的指针
- **outReal[]**: 包含减法结果的输出数组

## 计算

对于范围 [startIdx, endIdx] 内的每个元素 i：

```
outReal[i] = inReal0[i] - inReal1[i]
```

## 用法

SUB 常用于：
- **价格差异**: 计算价格变化或价差
- **指标差异**: 寻找指标之间的差异
- **数学运算**: 基本向量算术运算
- **自定义指标**: 构建自定义技术指标
- **变化率**: 计算百分比变化

## 示例

```python
import talib
import numpy as np

# 示例数据
current_price = np.array([10.0, 11.0, 12.0, 13.0, 14.0])
previous_price = np.array([9.5, 10.5, 11.5, 12.5, 13.5])

# 计算价格差异
result = talib.SUB(current_price, previous_price)
print(result)  # [0.5, 0.5, 0.5, 0.5, 0.5]
```

## 特性

### 优点
1. **简单运算**: 基本数学减法
2. **逐元素**: 对对应元素进行操作
3. **高效**: 快速计算
4. **通用**: 可用于各种上下文
5. **方向性**: 显示变化方向

### 局限性
1. **无验证**: 不检查无效输入
2. **基本功能**: 仅限于简单减法
3. **无平滑**: 无内置平滑或滤波
4. **无标准化**: 结果取决于输入规模

## 数学性质

- **非交换律**: `SUB(A, B) ≠ SUB(B, A)`
- **非结合律**: `SUB(A, SUB(B, C)) ≠ SUB(SUB(A, B), C)`
- **单位元**: `SUB(A, 0) = A`
- **逆元**: `SUB(A, A) = 0`

## 常见应用

### 价格分析
- **价格变化**: 当前价格 - 前一价格
- **价差分析**: 买价 - 卖价
- **跳空分析**: 开盘价 - 前收盘价

### 技术指标
- **MACD**: EMA(12) - EMA(26)
- **价格振荡器**: 价格 - 移动平均
- **成交量分析**: 当前成交量 - 平均成交量

## 相关函数

- **ADD**: 向量算术加法
- **MULT**: 向量算术乘法
- **DIV**: 向量算术除法
- **MAX**: 两个数组之间的最大值
- **MIN**: 两个数组之间的最小值
- **ROC**: 变化率（百分比）

## 参考文献

- [TA-Lib 源代码: ta_SUB.c](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_SUB.c)
- [技术分析中的数学运算](https://en.wikipedia.org/wiki/Technical_analysis)
- [向量算术运算](https://en.wikipedia.org/wiki/Vector_space)

---

*此函数是 TA-Lib 中数学运算符组的一部分。*
