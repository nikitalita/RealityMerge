/**************************************************************************/
/* document.cpp                                                           */
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

#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include <vector>

// third-party
extern "C" {

#include <automerge-c/automerge.h>
#include <automerge-c/utils/enum_string.h>
}

// local
#include "utils/bytes.hpp"
#include "utils/document.hpp"

namespace cavi {
namespace usdj_am {
namespace utils {

Document Document::load(std::filesystem::path const& path) {
    ResultPtr result{nullptr, AMresultFree};
    std::ostringstream arguments;
    std::basic_ifstream<std::uint8_t> file(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (file) {
        std::vector<std::uint8_t> buffer(file.tellg());
        file.seekg(0, std::ios::beg);
        if (file.read(buffer.data(), buffer.size())) {
            result = ResultPtr{AMload(buffer.data(), buffer.size()), AMresultFree};
            if (AMresultStatus(result.get()) != AM_STATUS_OK) {
                arguments << "AMresultError(AMload(..., ...)) == \"" << from_bytes(AMresultError(result.get())) << "\"";
            }
        } else {
            arguments << typeid(decltype(file)).name() << "(" << path << ").read(..., ...) == " << std::boolalpha
                      << false;
        }
    } else {
        arguments << typeid(decltype(file)).name() << "(" << path << ").fail()";
    }
    if (!arguments.str().empty()) {
        std::ostringstream what;
        what << typeid(Document).name() << "::" << __func__ << "(" << arguments.str() << ")";
        throw std::invalid_argument(what.str());
    }
    return Document(std::move(result));
}

Document::Document(ResultPtr&& result) : m_document{nullptr}, m_result{std::move(result)} {
    std::ostringstream arguments;
    if (!m_result) {
        arguments << "result.get() == nullptr";
    } else {
        AMvalType const val_type = AMitemValType(AMresultItem(m_result.get()));
        if (val_type != AM_VAL_TYPE_DOC) {
            arguments << "AMitemValType(AMresultItem(result.get())) == " << AMvalTypeToString(val_type);
        } else if (!AMitemToDoc(AMresultItem(m_result.get()), &m_document)) {
            arguments << "AMitemToDoc(AMresultItem(result.get()), ...) == " << std::boolalpha << false;
        }
    }
    if (!arguments.str().empty()) {
        std::ostringstream what;
        what << typeid(*this).name() << "::" << __func__ << "(" << arguments.str() << ")";
        throw std::invalid_argument(what.str());
    }
}

}  // namespace utils
}  // namespace usdj_am
}  // namespace cavi