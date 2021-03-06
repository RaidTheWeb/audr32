#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdint.h>

enum {
    TOK_EOF                     =              -1,
    TOK_NEWLINE                 =               0,
    TOK_NUMBER                  =               1,
    TOK_REGISTER                =               2,
    TOK_STRING                  =               3,
    TOK_CHAR                    =               4,
    TOK_COLON                   =               5,
    TOK_LSQUARE                 =               6,
    TOK_RSQUARE                 =               7,
    TOK_LBRACKET                =               8,
    TOK_RBRACKET                =               9,
    TOK_HASHTAG                 =               10,
    TOK_PERIOD                  =               11,
    TOK_DOLLAR                  =               12,

    TOK_LABEL                   =               101,

    TOK_NOP                     =               102,
    TOK_HLT                     =               103,
    TOK_MOV                     =               104,
    TOK_INT                     =               105,
    TOK_JMP                     =               106,
    TOK_JNZ                     =               107,
    TOK_JZ                      =               108,
    TOK_JNE                     =               109,
    TOK_JE                      =               110,
    TOK_JG                      =               111,
    TOK_JGE                     =               112,
    TOK_JL                      =               113,
    TOK_JLE                     =               114,
    TOK_CALL                    =               115,
    TOK_RET                     =               116,
    TOK_INX                     =               117,
    TOK_OUTX                    =               118,
    TOK_POP                     =               119,
    TOK_PUSH                    =               120,
    TOK_ADD                     =               121,
    TOK_SUB                     =               122,
    TOK_DIV                     =               123,
    TOK_IDIV                    =               124,
    TOK_MUL                     =               125,
    TOK_CMP                     =               126,
    TOK_AND                     =               127,
    TOK_SHL                     =               128,
    TOK_SHR                     =               129,
    TOK_XOR                     =               130,
    TOK_OR                      =               131,
    TOK_NOT                     =               132,
    TOK_SETEQ                   =               133,
    TOK_SETNE                   =               134,
    TOK_SETLT                   =               135,
    TOK_SETGT                   =               136,
    TOK_SETLE                   =               137,
    TOK_SETGE                   =               138,
    TOK_LEA                     =               139,
    TOK_NEG                     =               140,
    TOK_TEST                    =               141,
    TOK_SYSCALL                 =               142,

    TOK_PLUS                    =               201,
    TOK_MINUS                   =               202,
    TOK_ASTERISK                =               203,
    TOK_SLASH                   =               204,
    TOK_COMMA                   =               205,
    TOK_LSHIFT                  =               206,
    TOK_RSHIFT                  =               207,
    TOK_BOR                     =               208,
    TOK_BAND                    =               209
};

struct Lexer {
    char *source;
    char current;
    uint64_t pos;

    uint64_t line; // current line
    uint64_t charpos; // current pos on line
};

struct Token {
    char text[128];
    int type;
};


void inittoken(struct Token *token, char *text, int type);
void inittokenc(struct Token *token, char text, int type);
int checkifkeyword(char *text, struct Lexer *lexer, int startofline);
void nextchar(struct Lexer *lexer, int whitespace);
void initlexer(struct Lexer *lexer, char *source);
char peek(struct Lexer *lexer);
void skipwhitespace(struct Lexer *lexer);
void skipcomment(struct Lexer *lexer);
void lexerabort(struct Lexer *lexer, char *message);
struct Token gettoken(struct Lexer *lexer);

#endif
