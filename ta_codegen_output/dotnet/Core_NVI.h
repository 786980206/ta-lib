         static int NviLookback( void );

#if defined( _MANAGED ) && defined( USE_SUBARRAY )
         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        SubArray<double>^ inClose,
                                        SubArray<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        SubArray<double>^  outReal );

         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        SubArray<float>^ inClose,
                                        SubArray<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        SubArray<double>^  outReal );

         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inClose,
                                        cli::array<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal )
         { return Nvi( startIdx, endIdx,
                         gcnew SubArrayFrom1D<double>(inClose,0),
                         gcnew SubArrayFrom1D<double>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inClose,
                                        cli::array<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal )
         { return Nvi( startIdx, endIdx,
                         gcnew SubArrayFrom1D<float>(inClose,0),
                         gcnew SubArrayFrom1D<float>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
#elif defined( _MANAGED )
         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inClose,
                                        cli::array<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Nvi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inClose,
                                        cli::array<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNBElement,
                                        cli::array<double>^  outReal );
#endif

#if defined( _MANAGED ) && defined( USE_SUBARRAY )
         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             SubArray<double>^ inClose,
                                             SubArray<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             SubArray<double>^  outReal );

         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             SubArray<float>^ inClose,
                                             SubArray<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             SubArray<double>^  outReal );

         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inClose,
                                             cli::array<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal )
         { return NviLogic( startIdx, endIdx,
                         gcnew SubArrayFrom1D<double>(inClose,0),
                         gcnew SubArrayFrom1D<double>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inClose,
                                             cli::array<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal )
         { return NviLogic( startIdx, endIdx,
                         gcnew SubArrayFrom1D<float>(inClose,0),
                         gcnew SubArrayFrom1D<float>(inVolume,0),
             outBegIdx,
             outNBElement,
               gcnew SubArrayFrom1D<double>(outReal,0) );
         }
#elif defined( _MANAGED )
         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inClose,
                                             cli::array<double>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode NviLogic( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inClose,
                                             cli::array<float>^ inVolume,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNBElement,
                                             cli::array<double>^  outReal );
#endif

         #define TA_NVI Core::Nvi
         #define TA_NVI_Lookback Core::NviLookback
         #define TA_NVI_Logic Core::NviLogic
         #define TA_INT_NVI Core::NviLogic
