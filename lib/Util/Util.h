/**
 * @file Util.h
 * @author Shivam Veerabudren
 * @brief Header containing some utility functions and defines
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef UTIL_H
#define UTIL_H

#include <iostream>

/**
 * @brief Macro for easier standard output to console
 *
 */
#define LOG( message ) ( std::cout << message << std::endl )

/**
 * @brief Alias for C++ unsigned int type.
 * Introduced to reduce verbosity while preserving portability
 */
typedef unsigned int u_32;

#endif // UTIL_H