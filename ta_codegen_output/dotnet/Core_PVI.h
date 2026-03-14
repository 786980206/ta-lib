         static int PviLookback( void );

#if defined( _MANAGED ) && defined( USE_SUBARRAY )
         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        SubArray<double>^ inClose,
                                        SubArray<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        SubArray<double>^  outReal );

         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        SubArray<float>^ inClose,
                                        SubArray<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        SubArray<double>^  outReal );

         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inClose,
                                        cli::array<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal )
         { return Pvi( startIdx, endIdx,
                         gcnew SubArrayFrom1D<double>(inClose,0),
                         gcnew SubArrayFrom1D<double>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inClose,
                                        cli::array<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal )
         { return Pvi( startIdx, endIdx,
                         gcnew SubArrayFrom1D<float>(inClose,0),
                         gcnew SubArrayFrom1D<float>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
#elif defined( _MANAGED )
         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inClose,
                                        cli::array<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Pvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inClose,
                                        cli::array<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal );
#endif

#if defined( _MANAGED ) && defined( USE_SUBARRAY )
         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             SubArray<double>^ inClose,
                                             SubArray<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             SubArray<double>^  outReal );

         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             SubArray<float>^ inClose,
                                             SubArray<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             SubArray<double>^  outReal );

         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inClose,
                                             cli::array<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal )
         { return PviLogic( startIdx, endIdx,
                         gcnew SubArrayFrom1D<double>(inClose,0),
                         gcnew SubArrayFrom1D<double>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inClose,
                                             cli::array<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal )
         { return PviLogic( startIdx, endIdx,
                         gcnew SubArrayFrom1D<float>(inClose,0),
                         gcnew SubArrayFrom1D<float>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
#elif defined( _MANAGED )
         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inClose,
                                             cli::array<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode PviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inClose,
                                             cli::array<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal );
#endif

         #define TA_PVI Core::Pvi
         #define TA_PVI_Lookback Core::PviLookback
         #define TA_PVI_Logic Core::PviLogic
         #define TA_INT_PVI Core::PviLogic
