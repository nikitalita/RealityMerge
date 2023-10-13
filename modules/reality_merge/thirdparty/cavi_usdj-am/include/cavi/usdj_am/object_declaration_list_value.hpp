/**************************************************************************/
/* object_declaration_list_value.hpp                                      */
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

#ifndef CAVI_USDJ_AM_OBJECT_DECLARATION_LIST_VALUE_HPP
#define CAVI_USDJ_AM_OBJECT_DECLARATION_LIST_VALUE_HPP

// local
#include "node.hpp"
#include "number.hpp"
#include "value.hpp"

namespace cavi {
namespace usdj_am {

// export type USDA_ObjectDeclarationList<T extends USDA_ValueTypes> = {
//     type: 'objectDeclarationList',
//     values: {
//         index: number,
//         value: T
//     }[],
// };

/// \brief Represents an item within a "USDA_ObjectDeclarationList.values"
///        property in a syntax tree that was parsed out of a USDA document,
///        encoded as JSON and stored within an Automerge document.
class ObjectDeclarationListValue : public Node {
public:
    ObjectDeclarationListValue() = delete;

    /// \param document[in] A pointer to a borrowed Automerge document.
    /// \param map_object[in] A pointer to a borrowed Automerge map object.
    /// \pre \p document `!= nullptr`
    /// \pre \p map_object `!= nullptr`
    /// \pre `AMitemValType(` \p map_object `) == AM_VAL_TYPE_OBJ_TYPE`
    /// \pre `AMobjObjType(` \p document `, AMitemObjId(` \p map_object `)) == AM_OBJ_TYPE_MAP`
    /// \pre `AMobjSize(` \p document `, AMitemObjId(` \p map_object `)) == 2`
    /// \throws std::invalid_argument
    ObjectDeclarationListValue(AMdoc const* const document, AMitem const* const map_object);

    ObjectDeclarationListValue(ObjectDeclarationListValue const&) = delete;

    ObjectDeclarationListValue(ObjectDeclarationListValue&&) = default;

    ObjectDeclarationListValue& operator=(ObjectDeclarationListValue const&) = delete;

    ObjectDeclarationListValue& operator=(ObjectDeclarationListValue&&) = default;

    /// \brief Accepts a node visitor.
    ///
    /// \param[in] visitor A node visitor.
    void accept(Visitor& visitor) const;

    /// \brief Gets the `.index` property.
    ///
    /// \throws std::invalid_argument
    Number get_index() const;

    /// \brief Gets the `.value` property.
    ///
    /// \throws std::invalid_argument
    Value get_value() const;
};

}  // namespace usdj_am
}  // namespace cavi

#endif  // CAVI_USDJ_AM_OBJECT_DECLARATION_LIST_VALUE_HPP