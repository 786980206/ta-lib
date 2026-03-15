/* TA-LIB Copyright (c) 1999-2025, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/// Return codes for TA-Lib function calls.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RetCode {
    /// Function completed successfully.
    Success,
    /// One or more parameters are invalid.
    BadParam,
    /// The start index is out of range.
    OutOfRangeStartIndex,
    /// The end index is out of range or less than start index.
    OutOfRangeEndIndex,
    /// Memory allocation failed.
    AllocErr,
    /// Internal error occurred.
    InternalError,
}

/// Compatibility mode for technical analysis calculations.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Compatibility {
    /// Default TA-Lib compatibility mode.
    Default,
    /// Metastock-compatible calculation mode.
    Metastock,
}

/// Identifies functions that have an unstable period.
///
/// Some technical analysis functions produce unreliable output during an
/// initial "unstable" period. This enum identifies each such function so
/// that a per-function unstable period can be configured.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum FuncUnstId {
    /// Average Directional Movement Index.
    Adx,
    /// Average Directional Movement Index Rating.
    Adxr,
    /// Average True Range.
    Atr,
    /// Chande Momentum Oscillator.
    Cmo,
    /// Directional Movement Index.
    Dx,
    /// Exponential Moving Average.
    Ema,
    /// Hilbert Transform - Dominant Cycle Period.
    HtDcPeriod,
    /// Hilbert Transform - Dominant Cycle Phase.
    HtDcPhase,
    /// Hilbert Transform - Phasor Components.
    HtPhasor,
    /// Hilbert Transform - SineWave.
    HtSine,
    /// Hilbert Transform - Instantaneous Trendline.
    HtTrendline,
    /// Hilbert Transform - Trend vs Cycle Mode.
    HtTrendMode,
    /// Intraday Momentum Index.
    Imi,
    /// Kaufman Adaptive Moving Average.
    Kama,
    /// MESA Adaptive Moving Average.
    Mama,
    /// Money Flow Index.
    Mfi,
    /// Minus Directional Indicator.
    MinusDI,
    /// Minus Directional Movement.
    MinusDM,
    /// Normalized Average True Range.
    Natr,
    /// Plus Directional Indicator.
    PlusDI,
    /// Plus Directional Movement.
    PlusDM,
    /// Relative Strength Index.
    Rsi,
    /// Stochastic Relative Strength Index.
    StochRsi,
    /// Triple Exponential Moving Average (T3).
    T3,
    /// Wildcard: set the unstable period for all functions at once.
    FuncUnstAll,
}

mod float;
pub use float::TaFloat;

/// Core struct providing access to all TA-Lib technical analysis functions.
///
/// Create an instance with [`Core::new()`] and call functions as methods.
/// Unstable period and compatibility mode can be configured per-instance.
///
/// # Example
///
/// ```
/// use ta_lib::ta_func::{Core, RetCode};
///
/// let core = Core::new();
/// let lookback = core.sma_lookback(30);
/// assert_eq!(lookback, 29);
/// ```
pub struct Core {
    /// Unstable period for each function identified by [`FuncUnstId`].
    pub unstable_period: [i32; FuncUnstId::FuncUnstAll as usize],
    /// Compatibility mode (default: [`Compatibility::Default`]).
    pub compatibility: Compatibility,
}

impl Core {
    /// Create a new Core instance with default settings.
    ///
    /// All unstable periods are initialized to 0 and compatibility
    /// mode is set to [`Compatibility::Default`].
    pub fn new() -> Self {
        Self {
            unstable_period: [0; FuncUnstId::FuncUnstAll as usize],
            compatibility: Compatibility::Default,
        }
    }

    /// Set the unstable period for a specific function.
    pub fn set_unstable_period(&mut self, id: FuncUnstId, period: i32) {
        self.unstable_period[id as usize] = period;
    }

    /// Get the unstable period for a specific function.
    pub fn get_unstable_period(&self, id: FuncUnstId) -> i32 {
        self.unstable_period[id as usize]
    }

    /// Set the compatibility mode.
    pub fn set_compatibility(&mut self, compat: Compatibility) {
        self.compatibility = compat;
    }

    /// Get the current compatibility mode.
    pub fn get_compatibility(&self) -> Compatibility {
        self.compatibility
    }
}

mod accbands;
mod acos;
mod ad;
mod add;
mod adosc;
mod adx;
mod adxr;
mod apo;
mod aroon;
mod aroonosc;
mod asin;
mod atan;
mod atr;
mod avgdev;
mod avgprice;
mod bbands;
mod beta;
mod bop;
mod cci;
mod cdl2crows;
mod cdl3blackcrows;
mod cdl3inside;
mod cdl3linestrike;
mod cdl3outside;
mod cdl3starsinsouth;
mod cdl3whitesoldiers;
mod cdlabandonedbaby;
mod cdladvanceblock;
mod cdlbelthold;
mod cdlbreakaway;
mod cdlclosingmarubozu;
mod cdlconcealbabyswall;
mod cdlcounterattack;
mod cdldarkcloudcover;
mod cdldoji;
mod cdldojistar;
mod cdldragonflydoji;
mod cdlengulfing;
mod cdleveningdojistar;
mod cdleveningstar;
mod cdlgapsidesidewhite;
mod cdlgravestonedoji;
mod cdlhammer;
mod cdlhangingman;
mod cdlharami;
mod cdlharamicross;
mod cdlhighwave;
mod cdlhikkake;
mod cdlhikkakemod;
mod cdlhomingpigeon;
mod cdlidentical3crows;
mod cdlinneck;
mod cdlinvertedhammer;
mod cdlkicking;
mod cdlkickingbylength;
mod cdlladderbottom;
mod cdllongleggeddoji;
mod cdllongline;
mod cdlmarubozu;
mod cdlmatchinglow;
mod cdlmathold;
mod cdlmorningdojistar;
mod cdlmorningstar;
mod cdlonneck;
mod cdlpiercing;
mod cdlrickshawman;
mod cdlrisefall3methods;
mod cdlseparatinglines;
mod cdlshootingstar;
mod cdlshortline;
mod cdlspinningtop;
mod cdlstalledpattern;
mod cdlsticksandwich;
mod cdltakuri;
mod cdltasukigap;
mod cdlthrusting;
mod cdltristar;
mod cdlunique3river;
mod cdlupsidegap2crows;
mod cdlxsidegap3methods;
mod ceil;
mod cmo;
mod correl;
mod cos;
mod cosh;
mod dema;
mod div;
mod dx;
mod ema;
mod exp;
mod floor;
mod ht_dcperiod;
mod ht_dcphase;
mod ht_phasor;
mod ht_sine;
mod ht_trendline;
mod ht_trendmode;
mod imi;
mod kama;
mod linearreg;
mod linearreg_angle;
mod linearreg_intercept;
mod linearreg_slope;
mod ln;
mod log10;
mod ma;
mod macd;
mod macdext;
mod macdfix;
mod mama;
mod mavp;
mod max;
mod maxindex;
mod medprice;
mod mfi;
mod midpoint;
mod midprice;
mod min;
mod minindex;
mod minmax;
mod minmaxindex;
mod minus_di;
mod minus_dm;
mod mom;
mod mult;
mod natr;
mod nvi;
mod obv;
mod plus_di;
mod plus_dm;
mod ppo;
mod pvi;
mod roc;
mod rocp;
mod rocr;
mod rocr100;
mod rsi;
mod sar;
mod sarext;
mod sin;
mod sinh;
mod sma;
mod sqrt;
mod stddev;
mod stoch;
mod stochf;
mod stochrsi;
mod sub;
mod sum;
mod t3;
mod tan;
mod tanh;
mod tema;
mod trange;
mod trima;
mod trix;
mod tsf;
mod typprice;
mod ultosc;
mod var;
mod wclprice;
mod willr;
mod wma;
