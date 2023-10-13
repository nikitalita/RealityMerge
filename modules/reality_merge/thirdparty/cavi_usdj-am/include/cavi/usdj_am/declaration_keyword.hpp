/**************************************************************************/
/* declaration_keyword.hpp                                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             RealityMerge                               */
/*                          https://cavi.au.dk/                           */
/**************************************************************************/
/* Copyright (c) 2023-present RealityMerge contributors (see AUTHORS.md). */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef CAVI_USDJ_AM_DECLARATION_KEYWORD_HPP
#define CAVI_USDJ_AM_DECLARATION_KEYWORD_HPP

#include <cstdint>
#include <iosfwd>

namespace cavi {
namespace usdj_am {

// export enum USDA_DeclarationKeyword {
//     Varying = 'varying',
//     Uniform = 'uniform',
//     Custom = 'custom',
//     Prepend = 'prepend',
//     Append = 'append',
//     Delete = 'delete',
//     Add = 'add',
// }

/// \brief An enum representing a "USDA_DeclarationKeyword" tag stored as a
///        string within an Automerge document.
enum class DeclarationKeyword : std::uint8_t {
    BEGIN_ = 1,
    VARYING = BEGIN_,
    UNIFORM,
    CUSTOM,
    PREPEND,
    APPEND,
    DELETE,
    ADD,
    END_,
    SIZE_ = END_ - BEGIN_
};

std::istream& operator>>(std::istream& is, cavi::usdj_am::DeclarationKeyword& out);

std::ostream& operator<<(std::ostream& os, cavi::usdj_am::DeclarationKeyword const& in);

}  // namespace usdj_am
}  // namespace cavi

#endif  // CAVI_USDJ_AM_DECLARATION_KEYWORD_HPP