/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2022 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#pragma once

#include <miopen/miopen.h>

namespace miopen {

namespace fusion {
struct FusionOpInvokeParamBase;
} // namespace fusion

// FusionOpInvokeParamBase is incomplete here. Every member that can destroy a
// unique_ptr<FusionOpInvokeParamBase> is defined out of line in op_args.cpp,
// where the type is complete; inline definitions fail to compile once the
// vector/unique_ptr members are constexpr (C++23).
struct OperatorArgs : miopenOperatorArgs
{
    OperatorArgs();
    ~OperatorArgs();
    OperatorArgs(OperatorArgs&&) noexcept;
    OperatorArgs& operator=(OperatorArgs&&) noexcept;

    std::vector<std::unique_ptr<fusion::FusionOpInvokeParamBase>> params;
    friend std::ostream& operator<<(std::ostream& stream, const OperatorArgs& x);
    void SetArg(size_t idx, std::unique_ptr<fusion::FusionOpInvokeParamBase>&& arg);
};

} // namespace miopen
