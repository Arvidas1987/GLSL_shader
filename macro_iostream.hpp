#pragma once
#ifndef _MACRO_IOSTREAM_HPP_
#   define _MACRO_IOSTREAM_HPP_
#
#   include <iostream>
#
#   define CAPTION(x) std::cout << x;
#   define WRITELN(x) std::cout << x << '\n';
#   define NEWLN()    std::cout << '\n';
#
#   define ERRORLN(x) std::cerr << x << '\n';
#   define ERROR(x)   std::cerr << x;
#
#   define NAMESPACE_BEGIN(x) namespace x {
#   define NAMESPACE_END(x) }
#
#endif // _MACRO_IOSTREAM_HPP_
