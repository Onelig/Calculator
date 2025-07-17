#pragma once
#include <QChar>
#include <QString>

inline constexpr QChar PLUS       = QChar('+');
inline constexpr QChar MINUS      = QChar(0x2212);
inline constexpr QChar MULTIPLY   = QChar(0x00D7);
inline constexpr QChar DIVIDE     = QChar(0x00F7);
inline constexpr QChar ROOT       = QChar(0x221A);
inline constexpr QChar PERCENT    = QChar('%');
inline constexpr QChar LPAREN     = QChar('(');
inline constexpr QChar RPAREN     = QChar(')');
inline constexpr QChar DOT        = QChar('.');

inline const QString csymbols                = QStringLiteral("\u2212\u00D7\u00F7\u221A%+().");
inline const QString nonBOperatorFollowChars = QStringLiteral("+\u2212\u221A\u00D7\u00F7(.");
inline const QString NneedSignClarif         = QStringLiteral("\u00D7\u00F7\u221A("); // symbols we might miss, just remove the "-" and don't add the "+"

inline bool isSymbol(const QChar& element)
{
    return csymbols.indexOf(element) != -1;
}
