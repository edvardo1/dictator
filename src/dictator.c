#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YACSL_IMPLEMENTATION
#include "yacsl.h"

typedef enum {
	dictator_TokenKind_Identifier,
	dictator_TokenKind_String,
	dictator_TokenKind_SmallInteger,

	dictator_TokenKind_Ampersand,
	dictator_TokenKind_AmpersandAmpersand,
	dictator_TokenKind_ArrowRight,
	dictator_TokenKind_Asterisk,
	dictator_TokenKind_AsteriskEquals,
	dictator_TokenKind_Colon,
	dictator_TokenKind_Comma,
	dictator_TokenKind_CurlyBracket_Close,
	dictator_TokenKind_CurlyBracket_Open,
	dictator_TokenKind_Dot,
	dictator_TokenKind_Equals,
	dictator_TokenKind_EqualsEquals,
	dictator_TokenKind_ExclamationMark,
	dictator_TokenKind_ExclamationMarkEquals,
	dictator_TokenKind_Hat,
	dictator_TokenKind_HatEquals,
	dictator_TokenKind_LeftArrow,
	dictator_TokenKind_LeftArrowEquals,
	dictator_TokenKind_LeftArrowLeftArrow,
	dictator_TokenKind_LeftArrowLeftArrowEquals,
	dictator_TokenKind_Minus,
	dictator_TokenKind_MinusEquals,
	dictator_TokenKind_Parenthesis_Close,
	dictator_TokenKind_Parenthesis_Open,
	dictator_TokenKind_Percent,
	dictator_TokenKind_PercentEquals,
	dictator_TokenKind_Pipe,
	dictator_TokenKind_PipePipe,
	dictator_TokenKind_Plus,
	dictator_TokenKind_PlusEquals,
	dictator_TokenKind_QuestionMark,
	dictator_TokenKind_RightArrow,
	dictator_TokenKind_RightArrowEquals,
	dictator_TokenKind_RightArrowRightArrow,
	dictator_TokenKind_RightArrowRightArrowEquals,
	dictator_TokenKind_Semicolon,
	dictator_TokenKind_Slash,
	dictator_TokenKind_SlashEquals,
	dictator_TokenKind_SquareBracket_Close,
	dictator_TokenKind_SquareBracket_Open,
	dictator_TokenKind_Tilde,
	dictator_TokenKind_Assert,
	dictator_TokenKind_Break,
	dictator_TokenKind_Case,
	dictator_TokenKind_Default,
	dictator_TokenKind_Else,
	dictator_TokenKind_Enum,
	dictator_TokenKind_Fn,
	dictator_TokenKind_For,
	dictator_TokenKind_If,
	dictator_TokenKind_Panic,
	dictator_TokenKind_Return,
	dictator_TokenKind_Rule,
	dictator_TokenKind_Struct,
	dictator_TokenKind_Union,
	dictator_TokenKind_Var,
	dictator_TokenKind_When,
	dictator_TokenKind_While,

	dictator_TokenKind_COUNT
} dictator_TokenKind;

typedef enum {
	dictator_TokenizerCode_Ok,
	dictator_TokenizerCode_Over,
	dictator_TokenizerCode_Error
} dictator_TokenizerCode;

#include "dictator.h"
#define func

struct dictator_Token {
	dictator_TokenKind kind;
	union {
		struct {
			String8 string;
		} identifier;
		struct {
			String8 string;
		} string;
		Long smallInteger;
	} as;
};

func Bool dictator_token_eq(dictator_Token *a, dictator_Token *b) {
	if (a == b) {
		return true;
	}
	if (a == NULL || b == NULL || a->kind != b->kind) {
		return false;
	}

	switch (a->kind) {
	case dictator_TokenKind_Identifier: {
		return strEq(a->as.identifier.string, b->as.identifier.string);
	} break;
	case dictator_TokenKind_String: {
		return strEq(a->as.string.string, b->as.string.string);
	} break;
	default: {
		if (0 <= a->kind && a->kind < dictator_TokenKind_COUNT) {
			return true;
		} else {
			assert(0);
		}
	} break;
	}
}

func Void dictator_token_print(dictator_Token *token) {
	if (token == NULL) {
		printf("NULL\n");
		return;
	}
	switch (token->kind) {
	case dictator_TokenKind_Identifier: {
		printf("Identifier \"%.*s\"\n", Slens(token->as.identifier.string));
	} break;
	case dictator_TokenKind_String: {
		printf("String \"%.*s\"\n", Slens(token->as.string.string));
	} break;
	case dictator_TokenKind_SmallInteger: {
		printf("SmallInteger\n");
	} break;
	case dictator_TokenKind_Parenthesis_Open: {
		printf("Parenthesis_Open\n");
	} break;
	case dictator_TokenKind_Parenthesis_Close: {
		printf("Parenthesis_Close\n");
	} break;
	case dictator_TokenKind_SquareBracket_Open: {
		printf("SquareBracket_Open\n");
	} break;
	case dictator_TokenKind_SquareBracket_Close: {
		printf("SquareBracket_Close\n");
	} break;
	case dictator_TokenKind_CurlyBracket_Open: {
		printf("CurlyBracket_Open\n");
	} break;
	case dictator_TokenKind_CurlyBracket_Close: {
		printf("CurlyBracket_Close\n");
	} break;
	case dictator_TokenKind_Semicolon: {
		printf("Semicolon\n");
	} break;
	case dictator_TokenKind_Slash: {
		printf("Slash\n");
	} break;
	case dictator_TokenKind_SlashEquals: {
		printf("SlashEquals\n");
	} break;
	case dictator_TokenKind_Colon: {
		printf("Colon\n");
	} break;
	case dictator_TokenKind_Dot: {
		printf("Dot\n");
	} break;
	case dictator_TokenKind_Comma: {
		printf("Comma\n");
	} break;
	case dictator_TokenKind_Ampersand: {
		printf("Ampersand\n");
	} break;
	case dictator_TokenKind_AmpersandAmpersand: {
		printf("AmpersandAmpersand\n");
	} break;
	case dictator_TokenKind_ArrowRight: {
		printf("ArrowRight\n");
	} break;
	case dictator_TokenKind_Pipe: {
		printf("Pipe\n");
	} break;
	case dictator_TokenKind_PipePipe: {
		printf("PipePipe\n");
	} break;
	case dictator_TokenKind_LeftArrow: {
		printf("LeftArrow\n");
	} break;
	case dictator_TokenKind_LeftArrowLeftArrow: {
		printf("LeftArrowLeftArrow\n");
	} break;
	case dictator_TokenKind_RightArrow: {
		printf("RightArrow\n");
	} break;
	case dictator_TokenKind_RightArrowRightArrow: {
		printf("RightArrowRightArrow\n");
	} break;
	case dictator_TokenKind_Assert: {
		printf("Assert\n");
	} break;
	case dictator_TokenKind_Break: {
		printf("Break\n");
	} break;
	case dictator_TokenKind_Case: {
		printf("Case\n");
	} break;
	case dictator_TokenKind_Default: {
		printf("Default\n");
	} break;
	case dictator_TokenKind_Else: {
		printf("Else\n");
	} break;
	case dictator_TokenKind_Enum: {
		printf("Enum\n");
	} break;
	case dictator_TokenKind_Fn: {
		printf("Fn\n");
	} break;
	case dictator_TokenKind_For: {
		printf("For\n");
	} break;
	case dictator_TokenKind_If: {
		printf("If\n");
	} break;
	case dictator_TokenKind_Panic: {
		printf("Panic\n");
	} break;
	case dictator_TokenKind_Return: {
		printf("Return\n");
	} break;
	case dictator_TokenKind_Rule: {
		printf("Rule\n");
	} break;
	case dictator_TokenKind_Struct: {
		printf("Struct\n");
	} break;
	case dictator_TokenKind_Union: {
		printf("Union\n");
	} break;
	case dictator_TokenKind_Var: {
		printf("Var\n");
	} break;
	case dictator_TokenKind_When: {
		printf("When\n");
	} break;
	case dictator_TokenKind_While: {
		printf("While\n");
	} break;
	default: {
		printf("Unknown Token\n");
	} break;
	}
}

struct dictator_Tokenizer {
	String8 string;
	Uint index;
	Bool hasToken;
	dictator_Token token;
};

func Void dictator_tokenizer_init(dictator_Tokenizer *tokenizer, String8 string) {
	tokenizer->string = string;
	tokenizer->index = 0;
	tokenizer->hasToken = false;
}

func Bool dictator_tokenizer__peekChar(dictator_Tokenizer *tokenizer, Char *c) {
	if (tokenizer->index < tokenizer->string.len) {
		*c = tokenizer->string.buf[tokenizer->index];
		return 0;
	} else {
		return 1;
	}
}

func Bool dictator_tokenizer__popChar(dictator_Tokenizer *tokenizer, Char *c) {
	Int err = dictator_tokenizer__peekChar(tokenizer, c);
	if (err == 0) {
		tokenizer->index += 1;
	}
	return err;
}

func Bool dictator_tokenizer__advanceChar(dictator_Tokenizer *tokenizer) {
	if (tokenizer->index < tokenizer->string.len) {
		tokenizer->index += 1;
		return 0;
	} else {
		return 1;
	}
}

func Bool charIsWhitespace(Char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

func Bool charIsDigit(Char c) {
	return '0' <= c && c <= '9';
}

func Bool charIsAlphaLower(Char c) {
	return 'a' <= c && c <= 'z';
}

func Bool charIsAlphaUpper(Char c) {
	return 'A' <= c && c <= 'Z';
}

func Bool charIsAlpha(Char c) {
	return charIsAlphaLower(c) || charIsAlphaUpper(c);
}

func Bool charIsAlphanumeric(Char c) {
	return charIsAlpha(c) || charIsDigit(c);
}

func Bool charIsIdentifierStart(Char c) {
	return charIsAlpha(c) || c == '_';
}

func Bool charIsIdentifierAfterStart(Char c) {
	return charIsAlpha(c) || c == '_' || charIsDigit(c);
}

func dictator_TokenizerCode dictator_tokenizer_popToken(dictator_Tokenizer *tokenizer, dictator_Token *token) {
	Char c = 0;
	Int err = 0;
	Uint initialIndex = 0, stringLen = 0;
	Bool isString = false;

	if (tokenizer->hasToken) {
		if (token != NULL) {
			*token = tokenizer->token;
		}
		tokenizer->hasToken = false;
		return 0;
	}

	err = dictator_tokenizer__peekChar(tokenizer, &c);
	while (err == 0 && charIsWhitespace(c)) {
		assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
		err = dictator_tokenizer__peekChar(tokenizer, &c);
	}

	if (err != 0) {
		return err;
	}

	err = dictator_tokenizer__peekChar(tokenizer, &c);
	if (err == 0) {
		if (c == '&') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Ampersand;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_AmpersandAmpersand;
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '*') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Asterisk;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_AsteriskEquals;
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == ':') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Colon;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == ',') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Comma;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '}') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_CurlyBracket_Close;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '{') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_CurlyBracket_Open;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '.') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Dot;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '=') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Equals;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_EqualsEquals;
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '!') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_ExclamationMark;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_ExclamationMarkEquals;
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '^') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Hat;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_HatEquals;
				assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '<') {
			assert(0);
		} else if (c == '-') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Minus;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0) {
				if (c == '=') {
					tokenizer->token.kind = dictator_TokenKind_MinusEquals;
					assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
				} else if (c == '>') {
					tokenizer->token.kind = dictator_TokenKind_ArrowRight;
					assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
				}
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == ')') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Parenthesis_Close;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '(') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Parenthesis_Open;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '%') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Percent;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_PercentEquals;
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '|') {
			assert(0);
		} else if (c == '+') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Plus;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_PlusEquals;
				assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '?') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_QuestionMark;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '<') {
			assert(0);
		} else if (c == '>') {
			assert(0);
		} else if (c == ';') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Semicolon;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '/') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Slash;
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0 && c == '=') {
				tokenizer->token.kind = dictator_TokenKind_SlashEquals;
				assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			}
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == ']') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_SquareBracket_Close;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '[') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_SquareBracket_Open;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '~') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Tilde;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else {
			if (c == '"') {
				isString = true;
				assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
				assert(dictator_tokenizer__peekChar(tokenizer, &c) == 0);
			}
			stringLen = 0;
			initialIndex = tokenizer->index;
			Bool areAllDigits = charIsDigit(c);
			for (;;) {
				if (isString) {
					if (err != 0) {
						assert(0);
					}
					if (err == 0 && c == '"') {
						assert(dictator_tokenizer__popChar(tokenizer, &c) == err);
						tokenizer->token.kind = dictator_TokenKind_String;
						tokenizer->token.as.string.string.buf = &tokenizer->string.buf[initialIndex];
						tokenizer->token.as.string.string.len = stringLen;
						if (token != NULL) {
							*token = tokenizer->token;
						}
						return 0;
					}
					assert(dictator_tokenizer__popChar(tokenizer, &c) == err);
					stringLen += 1;
				} else {
					Bool isStart = tokenizer->index == initialIndex;
					if (
						err == 0 &&
						((isStart && charIsIdentifierStart(c)) ||
						 (!isStart && charIsIdentifierAfterStart(c)))
						) {
						areAllDigits = areAllDigits && charIsDigit(c);
						assert(dictator_tokenizer__popChar(tokenizer, &c) == err);
						stringLen += 1;
					} else if (stringLen == 0) {
						return dictator_TokenizerCode_Error;
					} else {
						if (areAllDigits) {
							tokenizer->token.kind = dictator_TokenKind_SmallInteger;
							tokenizer->token.as.smallInteger =
								strtol(&tokenizer->string.buf[initialIndex], NULL, 0);
						} else {
							tokenizer->token.kind = dictator_TokenKind_Identifier;
							tokenizer->token.as.identifier.string.buf =
								&tokenizer->string.buf[initialIndex];
							tokenizer->token.as.identifier.string.len = stringLen;

							if (strEq(tokenizer->token.as.identifier.string, S("assert"))) {
								tokenizer->token.kind = dictator_TokenKind_Assert;
							} else if (strEq(tokenizer->token.as.identifier.string, S("break"))) {
								tokenizer->token.kind = dictator_TokenKind_Break;
							} else if (strEq(tokenizer->token.as.identifier.string, S("case"))) {
								tokenizer->token.kind = dictator_TokenKind_Case;
							} else if (strEq(tokenizer->token.as.identifier.string, S("default"))) {
								tokenizer->token.kind = dictator_TokenKind_Default;
							} else if (strEq(tokenizer->token.as.identifier.string, S("else"))) {
								tokenizer->token.kind = dictator_TokenKind_Else;
							} else if (strEq(tokenizer->token.as.identifier.string, S("enum"))) {
								tokenizer->token.kind = dictator_TokenKind_Enum;
							} else if (strEq(tokenizer->token.as.identifier.string, S("fn"))) {
								tokenizer->token.kind = dictator_TokenKind_Fn;
							} else if (strEq(tokenizer->token.as.identifier.string, S("for"))) {
								tokenizer->token.kind = dictator_TokenKind_For;
							} else if (strEq(tokenizer->token.as.identifier.string, S("if"))) {
								tokenizer->token.kind = dictator_TokenKind_If;
							} else if (strEq(tokenizer->token.as.identifier.string, S("panic"))) {
								tokenizer->token.kind = dictator_TokenKind_Panic;
							} else if (strEq(tokenizer->token.as.identifier.string, S("return"))) {
								tokenizer->token.kind = dictator_TokenKind_Return;
							} else if (strEq(tokenizer->token.as.identifier.string, S("rule"))) {
								tokenizer->token.kind = dictator_TokenKind_Rule;
							} else if (strEq(tokenizer->token.as.identifier.string, S("struct"))) {
								tokenizer->token.kind = dictator_TokenKind_Struct;
							} else if (strEq(tokenizer->token.as.identifier.string, S("union"))) {
								tokenizer->token.kind = dictator_TokenKind_Union;
							} else if (strEq(tokenizer->token.as.identifier.string, S("var"))) {
								tokenizer->token.kind = dictator_TokenKind_Var;
							} else if (strEq(tokenizer->token.as.identifier.string, S("while"))) {
								tokenizer->token.kind = dictator_TokenKind_While;
							} else if (strEq(tokenizer->token.as.identifier.string, S("when"))) {
								tokenizer->token.kind = dictator_TokenKind_When;
							}

							if (token != NULL) {
								*token = tokenizer->token;
							}
							return 0;
						}
						break;
					}
				}
				err = dictator_tokenizer__peekChar(tokenizer, &c);
			}
		}
	} else {
		return err;
	}
	return err;
}

func dictator_TokenizerCode dictator_tokenizer_peekToken(dictator_Tokenizer *tokenizer, dictator_Token *token) {
	Int err = dictator_tokenizer_popToken(tokenizer, token);
	if (err == 0) {
		tokenizer->hasToken = true;
	}
	return err;
}

func Void test_tokenizer(Void) {
	test_tokenizer_0();
	test_tokenizer_1();
}

func Void test_tokenizer_0(Void) {
	dictator_Tokenizer tokenizer = {0};
	dictator_tokenizer_init(&tokenizer, S("fn swap(a: [&]Int, b: &Int) {;}"));
	dictator_Token token = {0};
#define TEST_EQ(a, b) \
do { \
	if ((a) != (b)) { \
		printf("FAILED EQ: <<%s>> != <<%s>>\n", #a, #b); \
		assert(a == b); \
	} \
} while (0)
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Fn);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("swap")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Parenthesis_Open);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("a")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Colon);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_SquareBracket_Open);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Ampersand);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_SquareBracket_Close);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("Int")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Comma);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("b")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Colon);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Ampersand);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("Int")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Parenthesis_Close);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_CurlyBracket_Open);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Semicolon);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_CurlyBracket_Close);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Over);
}

func Void test_tokenizer_1(Void) {
	dictator_Tokenizer tokenizer = {0};
	dictator_tokenizer_init(&tokenizer, S("rule \"p\" -> \"b\" when vowel _ vowel"));
	dictator_Token token = {0};
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Rule);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_String);
	TEST_EQ(strEq(token.as.string.string, S("p")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_ArrowRight);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_String);
	TEST_EQ(strEq(token.as.string.string, S("b")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_When);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("vowel")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("_")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Ok);
	TEST_EQ(token.kind, dictator_TokenKind_Identifier);
	TEST_EQ(strEq(token.as.identifier.string, S("vowel")), true);
	TEST_EQ(dictator_tokenizer_popToken(&tokenizer, &token), dictator_TokenizerCode_Over);
}

typedef enum {
	dictator_PatternAtomNodeKind_String,
	dictator_PatternAtomNodeKind_Identifier,
	dictator_PatternAtomNodeKind_SmallInteger
} dictator_PatternAtomNodeKind;

struct dictator_PatternAtomNode {
	dictator_PatternAtomNodeKind kind;
	union {
		String8 string;
		String8 identifier;
		I32 smallInteger;
	} as;
};

struct dictator_PatternNode {
	dictator_PatternAtomNode *items;
	Usize len;
	Usize capacity;
};

func Void dictator_patternAtomPrint(dictator_PatternAtomNode *atom) {
	printf("(");
	switch (atom->kind) {
	case dictator_PatternAtomNodeKind_String: {
		printf("String %.*s", Slens(atom->as.string));
	} break;
	case dictator_PatternAtomNodeKind_Identifier: {
		printf("Identifier %.*s", Slens(atom->as.identifier));
	} break;
	case dictator_PatternAtomNodeKind_SmallInteger: {
		printf("Identifier %d", atom->as.smallInteger);
	} break;
	}
	printf(")");
}

func Void dictator_patternPrint(dictator_PatternNode *pattern) {
	Usize index = 0;
	printf("[Pattern ");
	for (index = 0; index < pattern->len; index += 1) {
		if (index != 0) {
			printf(" ");
		}
		dictator_patternAtomPrint(&pattern->items[index]);
	}
	printf("]\n");
}

typedef enum {
	dictator_TopNodeKind_Var,
	dictator_TopNodeKind_Rule
} dictator_TopNodeKind;

struct dictator_TopNode {
	dictator_TopNodeKind kind;
	union {
		struct {
			dictator_PatternNode before;
			dictator_PatternNode after;
			dictator_PatternNode when;
		} rule;
		struct {
			String8 name;
			dictator_PatternNode value;
		} var;
	} as;
};

struct dictator_BufferNode {
	dictator_TopNode *items;
	Usize len;
	Usize capacity;
};

struct dictator_Parser {
	dictator_Tokenizer tokenizer;
};

Int dictator_tryParsePattern(dictator_Parser *parser, dictator_PatternNode *pattern) {
	dictator_Token token = {0};
	dictator_PatternAtomNode atomNode = {0};
	Usize count = 0;
	memZero(pattern, sizeof(*pattern));
	for (;; count += 1) {
		if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
			if (count > 0) {
				return 0;
			} else {
				return 1;
			}
		}

		if (token.kind == dictator_TokenKind_Identifier) {
			atomNode.kind = dictator_PatternAtomNodeKind_Identifier;
			atomNode.as.identifier = token.as.identifier.string;
		} else if (token.kind == dictator_TokenKind_String) {
			atomNode.kind = dictator_PatternAtomNodeKind_String;
			atomNode.as.string = token.as.string.string;
		} else if (token.kind == dictator_TokenKind_SmallInteger) {
			atomNode.kind = dictator_PatternAtomNodeKind_SmallInteger;
			atomNode.as.smallInteger = token.as.smallInteger;
		} else {
			if (count > 0) {
				return 0;
			} else {
				return 1;
			}
		}

		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		da_append(pattern, atomNode);
	}
	return 0;
}

Int dictator_tryParseRule(dictator_Parser *parser, dictator_TopNode *node) {
	dictator_Token token = {0};
	memZero(node, sizeof(*node));
	if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
		return 1;
	}
	if (token.kind != dictator_TokenKind_Rule) {
		return 1;
	}
	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
	node->kind = dictator_TopNodeKind_Rule;

	assert(dictator_tryParsePattern(parser, &node->as.rule.before) == 0);
	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
	assert(token.kind == dictator_TokenKind_ArrowRight);
	assert(dictator_tryParsePattern(parser, &node->as.rule.after) == 0);

	if (
		dictator_tokenizer_peekToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok &&
		token.kind == dictator_TokenKind_When
	) {
		/* has when */
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		assert(dictator_tryParsePattern(parser, &node->as.rule.when) == 0);
	}

	return 0;
}

Void dictator_tryParseBuffer(dictator_Parser *parser, dictator_BufferNode *bufferNode) {
	dictator_TopNode topNode = {0};
	for (;;) {
		if (dictator_tryParseRule(parser, &topNode) == 0) {
			da_append(bufferNode, topNode);
		} else {
			break;
		}
	}
}

func Void test_parser(Void) {
	test_parser_0();
	test_parser_1();
	test_parser_2();
	test_parser_3();
}

func Void test_parser_0(Void) {
	dictator_Parser parser = {0};
	dictator_PatternNode pattern = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("a \"p\" b"));
	TEST_EQ(dictator_tryParsePattern(&parser, &pattern), 0);
	TEST_EQ(pattern.len, 3);
	TEST_EQ(pattern.items[0].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(pattern.items[0].as.identifier, S("a")), true);
	TEST_EQ(pattern.items[1].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(pattern.items[1].as.string, S("p")), true);
	TEST_EQ(pattern.items[2].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(pattern.items[2].as.identifier, S("b")), true);
}

func Void test_parser_1(Void) {
	dictator_Parser parser = {0};
	dictator_TopNode topNode = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("rule \"p\" -> \"b\""));
	TEST_EQ(dictator_tryParseRule(&parser, &topNode), 0);
	TEST_EQ(topNode.kind, dictator_TopNodeKind_Rule);
	TEST_EQ(topNode.as.rule.before.len, 1);
	TEST_EQ(topNode.as.rule.before.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode.as.rule.before.items[0].as.string, S("p")), true);
	TEST_EQ(topNode.as.rule.after.len, 1);
	TEST_EQ(topNode.as.rule.after.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode.as.rule.after.items[0].as.string, S("b")), true);
	TEST_EQ(topNode.as.rule.when.len, 0);
}

func Void test_parser_2(Void) {
	dictator_Parser parser = {0};
	dictator_TopNode topNode = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("rule \"p\" -> \"b\" when vowel _ consonant"));
	TEST_EQ(dictator_tryParseRule(&parser, &topNode), 0);
	TEST_EQ(topNode.kind, dictator_TopNodeKind_Rule);
	TEST_EQ(topNode.as.rule.before.len, 1);
	TEST_EQ(topNode.as.rule.before.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode.as.rule.before.items[0].as.string, S("p")), true);
	TEST_EQ(topNode.as.rule.after.len, 1);
	TEST_EQ(topNode.as.rule.after.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode.as.rule.after.items[0].as.string, S("b")), true);
	TEST_EQ(topNode.as.rule.when.items[0].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode.as.rule.when.items[0].as.identifier, S("vowel")), true);
	TEST_EQ(topNode.as.rule.when.items[1].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode.as.rule.when.items[1].as.identifier, S("_")), true);
	TEST_EQ(topNode.as.rule.when.items[2].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode.as.rule.when.items[2].as.identifier, S("consonant")), true);
}

func Void test_parser_3_helper(dictator_TopNode *topNode, String8 before, String8 after) {
	TEST_EQ(topNode->kind, dictator_TopNodeKind_Rule);
	TEST_EQ(topNode->as.rule.before.len, 1);
	TEST_EQ(topNode->as.rule.before.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode->as.rule.before.items[0].as.string, before), true);
	TEST_EQ(topNode->as.rule.after.len, 1);
	TEST_EQ(topNode->as.rule.after.items[0].kind, dictator_PatternAtomNodeKind_String);
	TEST_EQ(strEq(topNode->as.rule.after.items[0].as.string, after), true);
	TEST_EQ(topNode->as.rule.when.items[0].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode->as.rule.when.items[0].as.identifier, S("vowel")), true);
	TEST_EQ(topNode->as.rule.when.items[1].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode->as.rule.when.items[1].as.identifier, S("_")), true);
	TEST_EQ(topNode->as.rule.when.items[2].kind, dictator_PatternAtomNodeKind_Identifier);
	TEST_EQ(strEq(topNode->as.rule.when.items[2].as.identifier, S("vowel")), true);
}

func Void test_parser_3(Void) {
	dictator_Parser parser = {0};
	dictator_BufferNode bufferNode = {0};
	static Char buffer[] =
		"rule \"p\" -> \"b\" when vowel _ vowel\n"
		"rule \"t\" -> \"d\" when vowel _ vowel\n"
		"rule \"k\" -> \"g\" when vowel _ vowel"
		;
	dictator_tokenizer_init(&parser.tokenizer, S(buffer));
	dictator_tryParseBuffer(&parser, &bufferNode);
	TEST_EQ(bufferNode.len, 3);
	test_parser_3_helper(&bufferNode.items[0], S("p"), S("b"));
	test_parser_3_helper(&bufferNode.items[1], S("t"), S("d"));
	test_parser_3_helper(&bufferNode.items[2], S("k"), S("g"));
}

struct dictator_Slice {
	Usize index;
	Usize len;
};

struct dictator_Slices {
	dictator_Slice *items;
	Usize len;
	Usize capacity;
};

struct dictator_Substituter {
	DynamicArray(dictator_Rule) rules;
	DynamicArray(dictator_Variable) variables;
};

Void getMatches(dictator_PatternNode *pattern, String8 buffer, dictator_Slices *matches) {
	for
}

Void substitute(dictator_bufferNode *bnode, String8 buffer) {
	Usize ruleIndex = 0;
	for (ruleIndex = 0; ruleIndex < bnode->len; ruleIndex += 1) {

	}
}

func Int main() {
	test_tokenizer();
	test_parser();
	printf("    done :)\n");
	return 0;
}
