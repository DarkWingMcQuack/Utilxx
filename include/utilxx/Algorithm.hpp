#pragma once

namespace utilxx {

namespace {

template<class InputIterator,
         class OutputIterator,
         class UnaryOperation,
         class UnaryPredicate>
OutputIterator transform_if(InputIterator first,
                            InputIterator last,
                            OutputIterator result,
                            UnaryOperation op,
                            UnaryPredicate test)
{
    while(first != last) {
        if(test(*first))
            *result++ = op(*first);
        ++first;
    }
    return result;
}

}

} // namespace utilxx
