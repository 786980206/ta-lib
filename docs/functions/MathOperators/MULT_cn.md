# MULT - 向量算术乘法

向量算术乘法（MULT）函数对两个输入数组执行逐元素乘法运算。这是一个基本的数学运算，将两个输入向量中对应的元素相乘并返回结果。

## 函数签名

```c
TA_RetCode TA_MULT(
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
- **inReal0[]**: 第一个输入数组
- **inReal1[]**: 第二个输入数组
- **outBegIdx**: 输出起始索引的指针
- **outNBElement**: 输出元素数量的指针
- **outReal[]**: 包含乘法结果的输出数组

## 计算

对于范围 [startIdx, endIdx] 内的每个元素 i：

```
outReal[i] = inReal0[i] * inReal1[i]
```

## 用法

MULT 常用于：
- **价格计算**: 价格乘以成交量进行成交量加权计算
- **指标组合**: 通过乘法组合多个指标
- **数学运算**: 基本向量算术运算
- **自定义指标**: 构建自定义技术指标

## 示例

```python
import talib
import numpy as np

# 示例数据
price = np.array([10.0, 11.0, 12.0, 13.0, 14.0])
volume = np.array([1000, 1100, 1200, 1300, 1400])

# 计算价格 * 成交量
result = talib.MULT(price, volume)
print(result)  # [10000.0, 12100.0, 14400.0, 16900.0, 19600.0]
```

## 特性

### 优点
1. **简单运算**: 基本数学乘法
2. **逐元素**: 对对应元素进行操作
3. **高效**: 快速计算
4. **通用**: 可用于各种上下文

### 局限性
1. **无验证**: 不检查除零或无效输入
2. **基本功能**: 仅限于简单乘法
3. **无平滑**: 无内置平滑或滤波

## 数学性质

- **交换律**: `MULT(A, B) = MULT(B, A)`
- **结合律**: `MULT(A, MULT(B, C)) = MULT(MULT(A, B), C)`
- **分配律**: `MULT(A, ADD(B, C)) = ADD(MULT(A, B), MULT(A, C))`

## 相关函数

- **ADD**: 向量算术加法
- **SUB**: 向量算术减法
- **DIV**: 向量算术除法
- **MAX**: 两个数组之间的最大值
- **MIN**: 两个数组之间的最小值

## 参考文献

- [TA-Lib 源代码: ta_MULT.c](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_MULT.c)
- [技术分析中的数学运算](https://en.wikipedia.org/wiki/Technical_analysis)
- [向量算术运算](https://en.wikipedia.org/wiki/Vector_space)

---

*此函数是 TA-Lib 中数学运算符组的一部分。*
