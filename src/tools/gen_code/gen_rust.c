/** RUST functions that get injected hackily into the bottom gen_code.c **/

// Forward declarations
void rustCargoFix(void);
void rustCargoFormat(void);

/* Check if a function name is in the RUST_SUPPORTED_FUNCS comma-separated list.
 * Returns 1 if found (or if RUST_SUPPORTED_FUNCS is not defined), 0 if not found.
 */
#if defined(RUST_SUPPORTED_FUNCS)
static int isRustSupportedFunc(const char *funcName)
{
    char buf[500];
    char *token;
    strncpy(buf, RUST_SUPPORTED_FUNCS, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';
    token = strtok(buf, ",");
    while (token) {
        /* Skip leading whitespace */
        while (*token == ' ') token++;
        if (strcmp(funcName, token) == 0)
            return 1;
        token = strtok(NULL, ",");
    }
    return 0;
}
#endif

static void printRustFuncDoc(FILE *out,
                             const TA_FuncInfo *funcInfo,
                             int docType)
{
    TA_RetCode retCode;
    unsigned int paramNb;
    const TA_InputParameterInfo *inputParamInfo;
    const TA_OptInputParameterInfo *optInputParamInfo;
    const TA_OutputParameterInfo *outputParamInfo;
    char snakeName[500];

    toLowerSnakeCase(funcInfo->name, snakeName);

    if (docType == RUST_DOC_SINGLE)
    {
        /* Single precision: just a cross-reference */
        fprintf(out, "@RUSTDOC@Single-precision variant of [`Core::%s`].\n", snakeName);
        return;
    }

    if (docType == RUST_DOC_LOOKBACK)
    {
        /* Lookback: short doc with params */
        fprintf(out, "@RUSTDOC@Lookback period for [`Core::%s`].\n", snakeName);
    }
    else
    {
        /* Main function: full description */
        fprintf(out, "@RUSTDOC@%s\n", funcInfo->hint);
    }

    fprintf(out, "@RUSTDOC@\n");
    fprintf(out, "@RUSTDOC@# Arguments\n");
    fprintf(out, "@RUSTDOC@\n");

    if (docType == RUST_DOC_MAIN)
    {
        /* startIdx/endIdx for main function only */
        fprintf(out, "@RUSTDOC@* `startIdx` - Start index for calculation range\n");
        fprintf(out, "@RUSTDOC@* `endIdx` - End index for calculation range (inclusive)\n");

        /* Input parameters */
        for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
        {
            retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
            if (retCode != TA_SUCCESS) return;

            switch (inputParamInfo->type)
            {
            case TA_Input_Price:
                {
                    #define PRICE_DOC(upperParam, lowerParam, desc) \
                    if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                        fprintf(out, "@RUSTDOC@* `%s` - %s price series\n", lowerParam, desc);

                    PRICE_DOC(OPEN, "inOpen", "Open")
                    PRICE_DOC(HIGH, "inHigh", "High")
                    PRICE_DOC(LOW, "inLow", "Low")
                    PRICE_DOC(CLOSE, "inClose", "Close")
                    PRICE_DOC(VOLUME, "inVolume", "Volume")
                    PRICE_DOC(OPENINTEREST, "inOpenInterest", "Open interest")

                    #undef PRICE_DOC
                }
                break;
            case TA_Input_Real:
                fprintf(out, "@RUSTDOC@* `%s` - Input price series\n", inputParamInfo->paramName);
                break;
            case TA_Input_Integer:
                fprintf(out, "@RUSTDOC@* `%s` - Input integer series\n", inputParamInfo->paramName);
                break;
            }
        }
    }

    /* Optional input parameters (both lookback and main) */
    for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
    {
        retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
        if (retCode != TA_SUCCESS) return;

        switch (optInputParamInfo->type)
        {
        case TA_OptInput_IntegerRange:
            fprintf(out, "@RUSTDOC@* `%s` - %s (default: %d, range: %d..=%d)\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint,
                    (int)optInputParamInfo->defaultValue,
                    ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min,
                    ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max);
            break;
        case TA_OptInput_RealRange:
            fprintf(out, "@RUSTDOC@* `%s` - %s (default: %g)\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint,
                    optInputParamInfo->defaultValue);
            break;
        case TA_OptInput_IntegerList:
        case TA_OptInput_RealList:
            fprintf(out, "@RUSTDOC@* `%s` - %s\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint);
            break;
        }
    }

    if (docType == RUST_DOC_MAIN)
    {
        /* Output parameters */
        fprintf(out, "@RUSTDOC@* `outBegIdx` - First valid output index\n");
        fprintf(out, "@RUSTDOC@* `outNBElement` - Number of valid output elements\n");

        for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
        {
            retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
            if (retCode != TA_SUCCESS) return;

            fprintf(out, "@RUSTDOC@* `%s` - Output values\n", outputParamInfo->paramName);
        }

        /* Returns section */
        fprintf(out, "@RUSTDOC@\n");
        fprintf(out, "@RUSTDOC@# Returns\n");
        fprintf(out, "@RUSTDOC@\n");
        fprintf(out, "@RUSTDOC@[`RetCode::Success`] on success, or an error code on failure.\n");

        /* Example section */
        {
            char examplePath[1024];
            FILE *exampleFile;
            int arraySize;
            int defaultOptVal;
            char lowerName[500];

            /* Check for rich hand-written example */
            toLowerSnakeCase(funcInfo->name, lowerName);
            sprintf(examplePath, ".." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_abstract"
                    PATH_SEPARATOR "rust_examples" PATH_SEPARATOR "%s.txt", lowerName);
            exampleFile = fopen(examplePath, "r");

            fprintf(out, "@RUSTDOC@\n");
            fprintf(out, "@RUSTDOC@# Example\n");
            fprintf(out, "@RUSTDOC@\n");
            fprintf(out, "@RUSTDOC@```\n");
            fprintf(out, "@RUSTDOC@use ta_lib::ta_func::{Core, RetCode};\n");
            fprintf(out, "@RUSTDOC@\n");

            if (exampleFile)
            {
                /* Inject hand-written example */
                char line[1024];
                while (fgets(line, sizeof(line), exampleFile))
                {
                    /* Remove trailing newline */
                    int len = strlen(line);
                    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
                        line[--len] = '\0';

                    if (len == 0)
                        fprintf(out, "@RUSTDOC@\n");
                    else
                        fprintf(out, "@RUSTDOC@%s\n", line);
                }
                fclose(exampleFile);
            }
            else
            {
                /* Generate mechanical example */

                /* Calculate array size from largest optInput default + 20, min 50 */
                arraySize = 50;
                for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
                {
                    retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
                    if (retCode != TA_SUCCESS) continue;
                    defaultOptVal = (int)optInputParamInfo->defaultValue;
                    if (defaultOptVal + 20 > arraySize)
                        arraySize = defaultOptVal + 20;
                }

                /* Input arrays */
                for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
                {
                    retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (inputParamInfo->type)
                    {
                    case TA_Input_Price:
                        #define PRICE_EXAMPLE(upperParam, lowerParam) \
                        if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                            fprintf(out, "@RUSTDOC@let %s = [1.0_f64; %d];\n", lowerParam, arraySize);

                        PRICE_EXAMPLE(OPEN, "in_open")
                        PRICE_EXAMPLE(HIGH, "in_high")
                        PRICE_EXAMPLE(LOW, "in_low")
                        PRICE_EXAMPLE(CLOSE, "in_close")
                        PRICE_EXAMPLE(VOLUME, "in_volume")
                        PRICE_EXAMPLE(OPENINTEREST, "in_open_interest")

                        #undef PRICE_EXAMPLE
                        break;
                    case TA_Input_Real:
                        fprintf(out, "@RUSTDOC@let input = [1.0_f64; %d];\n", arraySize);
                        break;
                    case TA_Input_Integer:
                        fprintf(out, "@RUSTDOC@let input = [1_i32; %d];\n", arraySize);
                        break;
                    }
                }

                /* Output arrays */
                for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
                {
                    retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (outputParamInfo->type)
                    {
                    case TA_Output_Real:
                        if (funcInfo->nbOutput == 1)
                            fprintf(out, "@RUSTDOC@let mut out = [0.0_f64; %d];\n", arraySize);
                        else
                            fprintf(out, "@RUSTDOC@let mut %s = [0.0_f64; %d];\n",
                                    outputParamInfo->paramName, arraySize);
                        break;
                    case TA_Output_Integer:
                        if (funcInfo->nbOutput == 1)
                            fprintf(out, "@RUSTDOC@let mut out = [0_i32; %d];\n", arraySize);
                        else
                            fprintf(out, "@RUSTDOC@let mut %s = [0_i32; %d];\n",
                                    outputParamInfo->paramName, arraySize);
                        break;
                    }
                }

                fprintf(out, "@RUSTDOC@let mut out_beg_idx: usize = 0;\n");
                fprintf(out, "@RUSTDOC@let mut out_nb_element: usize = 0;\n");
                fprintf(out, "@RUSTDOC@\n");

                /* Function call */
                fprintf(out, "@RUSTDOC@let core = Core::new();\n");
                fprintf(out, "@RUSTDOC@let result = core.%s(\n", snakeName);
                fprintf(out, "@RUSTDOC@    0,\n");
                fprintf(out, "@RUSTDOC@    %d,\n", arraySize - 1);

                /* Input args */
                for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
                {
                    retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (inputParamInfo->type)
                    {
                    case TA_Input_Price:
                        #define PRICE_ARG(upperParam, lowerParam) \
                        if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                            fprintf(out, "@RUSTDOC@    &%s,\n", lowerParam);

                        PRICE_ARG(OPEN, "in_open")
                        PRICE_ARG(HIGH, "in_high")
                        PRICE_ARG(LOW, "in_low")
                        PRICE_ARG(CLOSE, "in_close")
                        PRICE_ARG(VOLUME, "in_volume")
                        PRICE_ARG(OPENINTEREST, "in_open_interest")

                        #undef PRICE_ARG
                        break;
                    case TA_Input_Real:
                        fprintf(out, "@RUSTDOC@    &input,\n");
                        break;
                    case TA_Input_Integer:
                        fprintf(out, "@RUSTDOC@    &input,\n");
                        break;
                    }
                }

                /* OptInput args */
                for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
                {
                    retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
                    if (retCode != TA_SUCCESS) continue;
                    fprintf(out, "@RUSTDOC@    %d, // %s\n",
                            (int)optInputParamInfo->defaultValue,
                            optInputParamInfo->paramName);
                }

                /* Output args */
                fprintf(out, "@RUSTDOC@    &mut out_beg_idx,\n");
                fprintf(out, "@RUSTDOC@    &mut out_nb_element,\n");

                for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
                {
                    retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    if (funcInfo->nbOutput == 1)
                        fprintf(out, "@RUSTDOC@    &mut out,\n");
                    else
                        fprintf(out, "@RUSTDOC@    &mut %s,\n", outputParamInfo->paramName);
                }

                fprintf(out, "@RUSTDOC@);\n");
                fprintf(out, "@RUSTDOC@\n");
                fprintf(out, "@RUSTDOC@assert_eq!(result, RetCode::Success);\n");
            }

            fprintf(out, "@RUSTDOC@```\n");
        }
    }
}

static void printRustLookbackFunctionSignature(FILE* out,
                                               const char* prefix, /* Can be NULL */
                                               const TA_FuncInfo* funcInfo)
{
    char funcNameBuffer[1024]; /* Not safe, but 1024 is realistic, */
    const TA_OptInputParameterInfo* optInputParamInfo;
    int i, indent;
    toLowerSnakeCase(funcInfo->name, funcNameBuffer);

    // print lookback function header
    sprintf(gTempBuf, "%spub fn %s_lookback(&self,\n",
            prefix? prefix:"",
            funcNameBuffer);

    print(out, gTempBuf);

    // Calculate indent for parameter alignment
    indent = (unsigned int)strlen(gTempBuf);

    // Print optional input parameters - only these are needed for lookback
    for (i = 0; i < funcInfo->nbOptInput; i++)
    {
        TA_GetOptInputParameterInfo(funcInfo->handle, i, &optInputParamInfo);

        if (i > 0)
        {
            fprintf(out, ",\n");
            printIndent(out, indent);
        }

        switch (optInputParamInfo->type)
        {
        case TA_OptInput_RealRange:
            fprintf(out, "mut %s: f64", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerRange:
            fprintf(out, "mut %s: i32", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerList:
            fprintf(out, "mut %s: i32", optInputParamInfo->paramName);
            break;
        case TA_OptInput_RealList:
            fprintf(out, "mut %s: f64", optInputParamInfo->paramName);
            break;
        default:
            printf("Unknown optional input type for %s\n", funcInfo->name);
            break;
        }
    }

    // Close function and add return type
    fprintf(out, ") -> i32\n");
}

static void printRustDoublePrecisionFunctionSignature(FILE* out,
                                                      const char* prefix, /* Can be NULL */
                                                      const TA_FuncInfo* funcInfo)
{
    char funcNameBuffer[1024]; /* Not safe, but 1024 is realistic, */
    const TA_OptInputParameterInfo* optInputParamInfo;
    const TA_OutputParameterInfo* outputParamInfo;
    const TA_InputParameterInfo* inputParamInfo;
    toLowerSnakeCase(funcInfo->name, funcNameBuffer);
    int indent, i;

    // Print function header with idiomatic Rust signature
    sprintf(gTempBuf, "%spub fn %s(&self, ",
            prefix? prefix:"",
            funcNameBuffer);

    print(out, gTempBuf);

    // Calculate indent for parameter alignment
    indent = (unsigned int)strlen(gTempBuf);

    // Start with startIdx and endIdx parameters
    fprintf(out, "mut startIdx: usize,\n");
    printIndent(out, indent);
    fprintf(out, "endIdx: usize,\n");

    // Print input parameters with proper Rust types
    for (i = 0; i < funcInfo->nbInput; i++)
    {
        TA_GetInputParameterInfo(funcInfo->handle, i, &inputParamInfo);

        printIndent(out, indent);

        switch (inputParamInfo->type)
        {
        case TA_Input_Real:
            fprintf(out, "%s: &[f64],\n", inputParamInfo->paramName);
            break;
        case TA_Input_Integer:
            fprintf(out, "%s: &[i32],\n", inputParamInfo->paramName);
            break;
        case TA_Input_Price:
            // Handle complex price inputs - can have multiple components
            switch (inputParamInfo->flags)
            {
            case TA_IN_PRICE_OPEN:
                fprintf(out, "%s: &[f64],\n", "inOpen");
                break;
            case TA_IN_PRICE_HIGH:
                fprintf(out, "%s: &[f64],\n", "inHigh");
                break;
            case TA_IN_PRICE_LOW:
                fprintf(out, "%s: &[f64],\n", "inLow");
                break;
            case TA_IN_PRICE_CLOSE:
                fprintf(out, "%s: &[f64],\n", "inClose");
                break;
            case TA_IN_PRICE_VOLUME:
                fprintf(out, "%s: &[f64],\n", "inVolume");
                break;
            default:
                printf("Unsupported price input for %s\n", funcInfo->name);
                break;
            }
            break;
        default:
            printf("Unknown input type for %s\n", funcInfo->name);
            break;
        }
    }

    // Print optional input parameters (mut because validation may assign defaults)
    for (i = 0; i < funcInfo->nbOptInput; i++)
    {
        TA_GetOptInputParameterInfo(funcInfo->handle, i, &optInputParamInfo);

        printIndent(out, indent);

        switch (optInputParamInfo->type)
        {
        case TA_OptInput_RealRange:
            fprintf(out, "mut %s: f64,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerRange:
            fprintf(out, "mut %s: i32,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerList:
            fprintf(out, "mut %s: i32,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_RealList:
            fprintf(out, "mut %s: f64,\n", optInputParamInfo->paramName);
            break;
        default:
            printf("Unknown optional input type for %s\n", funcInfo->name);
            break;
        }
    }

    // Print output parameters with proper Rust mutable references
    printIndent(out, indent);
    fprintf(out, "outBegIdx: &mut usize,\n");
    printIndent(out, indent);
    fprintf(out, "outNBElement: &mut usize,\n");

    for (i = 0; i < funcInfo->nbOutput; i++)
    {
        TA_GetOutputParameterInfo(funcInfo->handle, i, &outputParamInfo);
        printIndent(out, indent);

        switch (outputParamInfo->type)
        {
        case TA_Output_Real:
            fprintf(out, "%s: &mut [f64]", outputParamInfo->paramName);
            break;
        case TA_Output_Integer:
            fprintf(out, "%s: &mut [i32]", outputParamInfo->paramName);
            break;
        default:
            printf("Unknown output type for %s\n", funcInfo->name);
            break;
        }

        // Add comma except for the last parameter
        if (i < funcInfo->nbOutput - 1)
        {
            fprintf(out, ",\n");
        }
    }

    // Close parameters and add return type
    fprintf(out, ") -> RetCode\n");
}

static void printRustSinglePrecisionFunctionSignature(FILE* out,
                                                      const char* prefix, /* Can be NULL */
                                                      const TA_FuncInfo* funcInfo)
{
    char funcNameBuffer[1024]; /* Not safe, but 1024 is realistic, */
    const TA_OptInputParameterInfo* optInputParamInfo;
    const TA_OutputParameterInfo* outputParamInfo;
    const TA_InputParameterInfo* inputParamInfo;
    toLowerSnakeCase(funcInfo->name, funcNameBuffer);
    int indent, i;

    // Print function header with idiomatic Rust signature for single precision
    sprintf(gTempBuf, "%spub fn %s_s(&self, ",
            prefix? prefix:"",
            funcNameBuffer);

    print(out, gTempBuf);

    // Calculate indent for parameter alignment
    indent = (unsigned int)strlen(gTempBuf);

    // Start with startIdx and endIdx parameters
    fprintf(out, "mut startIdx: usize,\n");
    printIndent(out, indent);
    fprintf(out, "endIdx: usize,\n");

    // Print input parameters with proper Rust types (f32 for single precision)
    for (i = 0; i < funcInfo->nbInput; i++)
    {
        TA_GetInputParameterInfo(funcInfo->handle, i, &inputParamInfo);

        printIndent(out, indent);

        switch (inputParamInfo->type)
        {
        case TA_Input_Real:
            fprintf(out, "%s: &[f32],\n", inputParamInfo->paramName);
            break;
        case TA_Input_Integer:
            fprintf(out, "%s: &[i32],\n", inputParamInfo->paramName);
            break;
        case TA_Input_Price:
            // Handle complex price inputs - can have multiple components
            switch (inputParamInfo->flags)
            {
            case TA_IN_PRICE_OPEN:
                fprintf(out, "%s: &[f32],\n", "inOpen");
                break;
            case TA_IN_PRICE_HIGH:
                fprintf(out, "%s: &[f32],\n", "inHigh");
                break;
            case TA_IN_PRICE_LOW:
                fprintf(out, "%s: &[f32],\n", "inLow");
                break;
            case TA_IN_PRICE_CLOSE:
                fprintf(out, "%s: &[f32],\n", "inClose");
                break;
            case TA_IN_PRICE_VOLUME:
                fprintf(out, "%s: &[f32],\n", "inVolume");
                break;
            default:
                printf("Unsupported price input for %s\n", funcInfo->name);
                break;
            }
            break;
        default:
            printf("Unknown input type for %s\n", funcInfo->name);
            break;
        }
    }

    // Print optional input parameters (mut because validation may assign defaults)
    for (i = 0; i < funcInfo->nbOptInput; i++)
    {
        TA_GetOptInputParameterInfo(funcInfo->handle, i, &optInputParamInfo);

        printIndent(out, indent);

        switch (optInputParamInfo->type)
        {
        case TA_OptInput_RealRange:
            fprintf(out, "mut %s: f32,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerRange:
            fprintf(out, "mut %s: i32,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_IntegerList:
            fprintf(out, "mut %s: i32,\n", optInputParamInfo->paramName);
            break;
        case TA_OptInput_RealList:
            fprintf(out, "mut %s: f32,\n", optInputParamInfo->paramName);
            break;
        default:
            printf("Unknown optional input type for %s\n", funcInfo->name);
            break;
        }
    }

    // Print output parameters with proper Rust mutable references
    // Note: outputs still use f64 even for single precision functions
    printIndent(out, indent);
    fprintf(out, "outBegIdx: &mut usize,\n");
    printIndent(out, indent);
    fprintf(out, "outNBElement: &mut usize,\n");

    for (i = 0; i < funcInfo->nbOutput; i++)
    {
        TA_GetOutputParameterInfo(funcInfo->handle, i, &outputParamInfo);
        printIndent(out, indent);

        switch (outputParamInfo->type)
        {
        case TA_Output_Real:
            fprintf(out, "%s: &mut [f64]", outputParamInfo->paramName);
            break;
        case TA_Output_Integer:
            fprintf(out, "%s: &mut [i32]", outputParamInfo->paramName);
            break;
        default:
            printf("Unknown output type for %s\n", funcInfo->name);
            break;
        }

        // Add comma except for the last parameter
        if (i < funcInfo->nbOutput - 1)
        {
            fprintf(out, ",\n");
        }
    }

    // Close parameters and add return type
    fprintf(out, ") -> RetCode\n");
}

void writeRustModLines(const TA_FuncInfo* funcInfo, void* opaque)
{
    struct WriteRustModLinesParams* params = (struct WriteRustModLinesParams*)opaque;
    FileHandle* out = params->out;
    char buffer[500];

#if defined(RUST_SUPPORTED_FUNCS)
    if (!isRustSupportedFunc(funcInfo->name))
        return;
#endif

    // Convert filename to lowercase into buffer.
    int i = 0;
    while (funcInfo->name[i])
    {
        buffer[i] = tolower(funcInfo->name[i]);
        i++;
    }
    buffer[i] = '\0';

    if (params->writePubUse == 1)
        fprintf(out->file, "pub use self::%s::*;\n", buffer);
    else
        fprintf(out->file, "/// %s implementation.\npub mod %s;\n", funcInfo->hint, buffer);
}

void writeRustMod(void)
{
    // Update the rust/src/ta_func/mod.rs file.
    struct WriteRustModLinesParams params;
    char buffer[500];
    FileHandle* out;

    if (!gmcpp_installed)
        return;

    // Add rs file to ta_func/mod.rs
    // A common header/footer is provided by the template file.
#define FILE_RUST_MOD ".." PATH_SEPARATOR "rust" PATH_SEPARATOR "src" PATH_SEPARATOR "ta_func" PATH_SEPARATOR "mod.rs"
#define FILE_RUST_MOD_TEMPLATE ".." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_abstract" PATH_SEPARATOR "templates" PATH_SEPARATOR "ta_func_mod.rs.template"

    out = fileOpen(FILE_RUST_MOD,
                   FILE_RUST_MOD_TEMPLATE,
                   FILE_WRITE | WRITE_ON_CHANGE_ONLY);


    params.out = out;
    params.writePubUse = 1;
    TA_ForEachFunc(writeRustModLines, &params);
    params.writePubUse = 0;
    TA_ForEachFunc(writeRustModLines, &params);

    fileClose(out);
    
    // Run cargo commands to clean up generated Rust code
    rustCargoFix();
    rustCargoFormat();
}

void genRustCodePhase2(const TA_FuncInfo* funcInfo)
{
    // Each TA function get its own .rs file generated.
    // A common header/footer is provided by the template file.
    FILE* logicTmp;
    char buffer[500];
    int idx, again;
    static int firstTime = 1;
    int ret;

#if defined(RUST_SUPPORTED_FUNCS)
    if (!isRustSupportedFunc(funcInfo->name))
        return;
#endif

    if (!gmcpp_installed)
        return;


    // Convert filename to lowercase into buffer.
    int i = 0;
    while (funcInfo->name[i])
    {
        buffer[i] = tolower(funcInfo->name[i]);
        i++;
    }
    buffer[i] = '\0';
    strcat(buffer, ".rs");
#define FILE_RUST_FUNC_TEMPLATE ".." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_abstract" PATH_SEPARATOR "templates" PATH_SEPARATOR "ta_x.rs.template"

    FileHandle* out = fileOpen(ta_fs_path(5, "..", "rust", "src", "ta_func", buffer),
                               FILE_RUST_FUNC_TEMPLATE,
                               FILE_WRITE | WRITE_ON_CHANGE_ONLY);


    /* Clean-up just in case. */
    fileDelete(ta_fs_path(3, "..", "temp", "rust_logic.tmp"));

#ifdef _MSC_VER
     sprintf( buffer, "%s -c -+ -z -P -I.." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_common -I.." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_abstract -I.." PATH_SEPARATOR "include -D _RUST .." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_func" PATH_SEPARATOR "TA_%s.c >>.." PATH_SEPARATOR "temp" PATH_SEPARATOR "rust_logic.tmp ", gmcpp_exec, funcInfo->name);
     ret = system( buffer );
#else
    sprintf(buffer,
            "%s -@compat -+ -z -P -I.." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_common -I.." PATH_SEPARATOR "src"
            PATH_SEPARATOR "ta_abstract -I.." PATH_SEPARATOR "include -D _RUST .." PATH_SEPARATOR "src" PATH_SEPARATOR
            "ta_func" PATH_SEPARATOR "ta_%s.c | sed '/^#include/d' >> .." PATH_SEPARATOR "temp" PATH_SEPARATOR
            "rust_logic.tmp ", gmcpp_exec, funcInfo->name);
    ret = system(buffer);
#endif

    /* Write the output of the C pre-processor to the rust file. */
    init_gToOpen(ta_fs_path(3, "..", "temp", "rust_logic.tmp"), NULL);
    logicTmp = fopen(gToOpen, "r");
    if (!logicTmp)
    {
        printf("Cannot open temp/rust_logic.tmp\n");
        return;
    }
    while (fgets(gTempBuf,BUFFER_SIZE, logicTmp))
    {
        /* Convert @RUSTDOC@ markers to /// doc comments */
        {
            char *marker;
            while ((marker = strstr(gTempBuf, "@RUSTDOC@")) != NULL)
            {
                /* Replace @RUSTDOC@ (9 chars) with "    /// " (8 chars) */
                /* Shift content left by 1 char, then overwrite */
                int markerPos = (int)(marker - gTempBuf);
                int tailLen = (int)strlen(marker + 9);
                memmove(marker + 8, marker + 9, tailLen + 1); /* +1 for null */
                memcpy(marker, "    /// ", 8);
            }
        }

        /* Remove empty lines and lines with only a ';' */
        idx = 0;
        again = 1;
        while (again && gTempBuf[idx] != '\0')
        {
            if (!isspace(gTempBuf[idx]) && !(gTempBuf[idx] == ';'))
                again = 0;
            idx++;
        }
        if ((again == 0) && (idx > 0))
            fputs(gTempBuf, out->file);
    }

    /* Clean-up */
    fclose(logicTmp);
    print(out->file, "\n");
    fileDelete(ta_fs_path(3, "..", "temp", "rust_logic.tmp"));

    // Upon closing, will touch the target file only if there was a change...
    fileClose(out);
}

static int tryCargoCommand(const char* command)
{
    char fullCommand[1024];
    int result;
    
    // Try 1: Use PATH (standard installation)
    snprintf(fullCommand, sizeof(fullCommand), "cd " ".." PATH_SEPARATOR "rust" " && cargo %s 2>/dev/null", command);
    result = system(fullCommand);
    if (result == 0) return 0;
    
    // Try 2: Common user installation location
    snprintf(fullCommand, sizeof(fullCommand), "cd " ".." PATH_SEPARATOR "rust" " && ~/.cargo/bin/cargo %s 2>/dev/null", command);
    result = system(fullCommand);
    if (result == 0) return 0;
    
    // Try 3: System-wide installation (Linux/macOS)
    snprintf(fullCommand, sizeof(fullCommand), "cd " ".." PATH_SEPARATOR "rust" " && /usr/local/bin/cargo %s 2>/dev/null", command);
    result = system(fullCommand);
    if (result == 0) return 0;
    
    // Try 4: Check if CARGO_HOME is set
    const char* cargoHome = getenv("CARGO_HOME");
    if (cargoHome) {
        snprintf(fullCommand, sizeof(fullCommand), "cd " ".." PATH_SEPARATOR "rust" " && %s/bin/cargo %s 2>/dev/null", cargoHome, command);
        result = system(fullCommand);
        if (result == 0) return 0;
    }
    
    return -1; // All attempts failed
}

void rustCargoFix(void)
{
    printf("Running cargo fix on generated Rust code...\n");
    
    if (tryCargoCommand("fix --lib -p ta-lib --allow-dirty") != 0) {
        printf("Warning: cargo fix failed (cargo not found or command failed)\n");
        printf("  To enable automatic cargo fix, ensure 'cargo' is in your PATH\n");
    }
}

void rustCargoFormat(void)
{
    printf("Running cargo fmt on generated Rust code...\n");
    
    if (tryCargoCommand("fmt") != 0) {
        printf("Warning: cargo fmt failed (cargo not found or command failed)\n");
        printf("  To enable automatic cargo fmt, ensure 'cargo' is in your PATH\n");
    }
}
