#ifndef COLORS_H
#define COLORS_H

// ============================================
// ZENITHOS COLOR SYSTEM - ANSI Escape Codes
// ============================================

// Reset
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"

// ============================================
// FOREGROUND COLORS
// ============================================
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Bright Foreground
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// ============================================
// BACKGROUND COLORS
// ============================================
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// ============================================
// ZENITHOS THEME COLORS
// ============================================
#define ZENITH_PRIMARY BRIGHT_CYAN
#define ZENITH_SECONDARY BRIGHT_BLUE
#define ZENITH_SUCCESS BRIGHT_GREEN
#define ZENITH_WARNING BRIGHT_YELLOW
#define ZENITH_ERROR BRIGHT_RED
#define ZENITH_INFO BRIGHT_WHITE
#define ZENITH_ACCENT BRIGHT_MAGENTA
#define ZENITH_DIM BRIGHT_BLACK

// Box Drawing Characters
#define BOX_TL "╔"
#define BOX_TR "╗"
#define BOX_BL "╚"
#define BOX_BR "╝"
#define BOX_H "═"
#define BOX_V "║"
#define BOX_L "╠"
#define BOX_R "╣"
#define BOX_T "╦"
#define BOX_B "╩"
#define BOX_X "╬"

#endif