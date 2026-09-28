#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YACSL_IO
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
	dictator_TokenKind_Define,
	dictator_TokenKind_Else,
	dictator_TokenKind_Enum,
	dictator_TokenKind_Fn,
	dictator_TokenKind_For,
	dictator_TokenKind_If,
	dictator_TokenKind_Or,
	dictator_TokenKind_Panic,
	dictator_TokenKind_Return,
	dictator_TokenKind_Rule,
	dictator_TokenKind_Struct,
	dictator_TokenKind_Union,
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
	case dictator_TokenKind_Define: {
		printf("Define\n");
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
	case dictator_TokenKind_Or: {
		printf("Or\n");
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
	Bool inComment = false;

	if (tokenizer->hasToken) {
		if (token != NULL) {
			*token = tokenizer->token;
		}
		tokenizer->hasToken = false;
		return 0;
	}

commentLabel:
	while (inComment) {
		err = dictator_tokenizer__popChar(tokenizer, &c);
		if (err) {
			return err;
		}
		if (c == '\n') {
			break;
		}
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
				} else if (c == '-') {
					inComment = true;
					goto commentLabel;
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
			Bool isSingleQuote = false;
			if (c == '"' || c == '\'') {
				if (c == '\'') {
					isSingleQuote = true;
				}
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
					if (err == 0 && ((c == '"' && !isSingleQuote) || (c == '\'' && isSingleQuote))) {
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
							} else if (strEq(tokenizer->token.as.identifier.string, S("define"))) {
								tokenizer->token.kind = dictator_TokenKind_Define;
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
							} else if (strEq(tokenizer->token.as.identifier.string, S("or"))) {
								tokenizer->token.kind = dictator_TokenKind_Or;
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
	dictator_PatternKind_String,
	dictator_PatternKind_Identifier,
	dictator_PatternKind_SmallInteger,
	dictator_PatternKind_Or,
	dictator_PatternKind_Concatenation,
	dictator_PatternKind_List
} dictator_PatternKind;

struct dictator_Pattern {
	dictator_PatternKind kind;
	Bool marked;
	union {
		String8 string;
		String8 identifier;
		I32 smallInteger;
		DynamicArray(dictator_Pattern) or;
		DynamicArray(dictator_Pattern) concatenation;
		DynamicArray(dictator_Pattern) list;
	} as;
};

func Void dictator_patternPrint(dictator_Pattern *atom) {
	Usize index = 0;
	if (atom->marked) {
		printf("$");
	}
	printf("(");
	switch (atom->kind) {
	case dictator_PatternKind_String: {
		printf("string %.*s", Slens(atom->as.string));
	} break;
	case dictator_PatternKind_Identifier: {
		printf("identifier %.*s", Slens(atom->as.identifier));
	} break;
	case dictator_PatternKind_SmallInteger: {
		printf("small_integer %d", atom->as.smallInteger);
	} break;
	case dictator_PatternKind_Or: {
		printf("or ");
		for (index = 0; index < atom->as.or.len; index += 1) {
			if (index != 0) {
				printf(" ");
			}
			dictator_patternPrint(&atom->as.or.items[index]);
		}
	} break;
	case dictator_PatternKind_List: {
		printf("list ");
		for (index = 0; index < atom->as.list.len; index += 1) {
			if (index != 0) {
				printf(" ");
			}
			dictator_patternPrint(&atom->as.list.items[index]);
		}
	} break;
	case dictator_PatternKind_Concatenation: {
		printf("concatenation ");
		for (index = 0; index < atom->as.concatenation.len; index += 1) {
			if (index != 0) {
				printf(" ");
			}
			dictator_patternPrint(&atom->as.concatenation.items[index]);
		}
	} break;
	}
	printf(")");
}

struct dictator_Parser {
	dictator_Tokenizer tokenizer;
};

struct dictator_Definition {
	String8 name;
	dictator_Pattern pattern;
};

struct dictator_Rule {
	dictator_Pattern before;
	dictator_Pattern after;
	dictator_Pattern when;
	Bool hasWhen;
};

struct dictator_Replacer {
	DynamicArray(dictator_Rule) rules;
	DynamicArray(dictator_Definition) definitions;
};

Int dictator_tryParsePatternPrimary(dictator_Parser *parser, dictator_Pattern *pattern) {
	dictator_Token token = {0};
	memZero(pattern, sizeof(*pattern));

	if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
		return 1;
	}

	if (token.kind == dictator_TokenKind_Identifier) {
		pattern->kind = dictator_PatternKind_Identifier;
		pattern->as.identifier = token.as.identifier.string;
	} else if (token.kind == dictator_TokenKind_String) {
		pattern->kind = dictator_PatternKind_String;
		pattern->as.string = token.as.string.string;
	} else if (token.kind == dictator_TokenKind_SmallInteger) {
		pattern->kind = dictator_PatternKind_SmallInteger;
		pattern->as.smallInteger = token.as.smallInteger;
	} else {
		return 1;
	}

	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);

	return 0;
}

Int dictator_tryParsePatternOr(dictator_Parser *parser, dictator_Pattern *pattern) {
	dictator_Token token = {0};
	memZero(pattern, sizeof(*pattern));
	dictator_Pattern individualPattern = {0};

	if (dictator_tryParsePatternPrimary(parser, &individualPattern) == 1) {
		return 1;
	}

	if (
		dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok ||
		token.kind != dictator_TokenKind_Or
	) {
		*pattern = individualPattern;
		return 0;
	}
	pattern->kind = dictator_PatternKind_Or;
	da_append(&pattern->as.or, individualPattern);
	for (;;) {
		if (token.kind != dictator_TokenKind_Or) {
			break;
		}
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		dictator_tryParsePatternPrimary(parser, &individualPattern);
		da_append(&pattern->as.or, individualPattern);
		if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
			break;
		}
	}

	return 0;
}

Int dictator_tryParsePatternConcat(dictator_Parser *parser, dictator_Pattern *pattern) {
	memZero(pattern, sizeof(*pattern));
	dictator_Pattern firstPattern = {0};
	dictator_Pattern individualPattern = {0};

	if (dictator_tryParsePatternOr(parser, &firstPattern) == 1) {
		return 1;
	}
	if (dictator_tryParsePatternOr(parser, &individualPattern) == 1) {
		*pattern = firstPattern;
		return 0;
	}

	pattern->kind = dictator_PatternKind_Concatenation;
	da_append(&pattern->as.concatenation, firstPattern);
	da_append(&pattern->as.concatenation, individualPattern);
	for (;;) {
		if (dictator_tryParsePatternOr(parser, &individualPattern) == 0) {
			da_append(&pattern->as.or, individualPattern);
		} else {
			return 0;
		}
	}
}

#define dictator_tryParsePattern dictator_tryParsePatternConcat

Int dictator_tryParseRule(dictator_Parser *parser, dictator_Rule *rule) {
	dictator_Token token = {0};
	memZero(rule, sizeof(*rule));
	if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
		return 1;
	}
	if (token.kind != dictator_TokenKind_Rule) {
		return 1;
	}
	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);

	assert(dictator_tryParsePattern(parser, &rule->before) == 0);
	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
	assert(token.kind == dictator_TokenKind_ArrowRight);
	assert(dictator_tryParsePattern(parser, &rule->after) == 0);

	if (
		dictator_tokenizer_peekToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok &&
		token.kind == dictator_TokenKind_When
	) {
		/* has when */
		rule->hasWhen = true;
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		assert(dictator_tryParsePattern(parser, &rule->when) == 0);
	}

	return 0;
}

Int dictator_tryParseDefinition(dictator_Parser *parser, dictator_Definition *var) {
	dictator_Token token = {0};
	memZero(var, sizeof(*var));
	if (dictator_tokenizer_peekToken(&parser->tokenizer, &token) != dictator_TokenizerCode_Ok) {
		return 1;
	}
	if (token.kind != dictator_TokenKind_Define) {
		return 1;
	}
	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);

	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
	assert(token.kind == dictator_TokenKind_Identifier);
	var->name = token.as.identifier.string;

	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
	assert(token.kind == dictator_TokenKind_Equals);

	assert(dictator_tryParsePattern(parser, &var->pattern) == 0);

	return 0;
}

func Int dictator_tryParseReplacer(dictator_Parser *parser, dictator_Replacer *substituter) {
	dictator_Rule rule = {0};
	dictator_Definition definition = {0};

	for (;;) {
		if (dictator_tryParseRule(parser, &rule) == 0) {
			da_append(&substituter->rules, rule);
		} else if (dictator_tryParseDefinition(parser, &definition) == 0) {
			da_append(&substituter->definitions, definition);
		} else {
			break;
		}
	}
	
	return 0;
}

func Void test_parser(Void) {
	test_parser_0();
	/* test_parser_1(); */
	/* test_parser_2(); */
	/* test_parser_3(); */
}

func Void test_parser_0(Void) {
	dictator_Parser parser = {0};
	dictator_Pattern pattern = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("a \"p\" b"));
	TEST_EQ(dictator_tryParsePattern(&parser, &pattern), 0);
	TEST_EQ(pattern.kind, dictator_PatternKind_Concatenation);
	TEST_EQ(pattern.as.concatenation.len, 3);
	TEST_EQ(pattern.as.concatenation.items[0].kind, dictator_PatternKind_Identifier);
	TEST_EQ(strEq(pattern.as.concatenation.items[0].as.identifier, S("a")), true);
	TEST_EQ(pattern.as.concatenation.items[1].kind, dictator_PatternKind_String);
	TEST_EQ(strEq(pattern.as.concatenation.items[1].as.string, S("p")), true);
	TEST_EQ(pattern.as.concatenation.items[2].kind, dictator_PatternKind_Identifier);
	TEST_EQ(strEq(pattern.as.concatenation.items[2].as.identifier, S("b")), true);
}

func Void test_parser_1(Void) {
	dictator_Parser parser = {0};
	dictator_Rule rule = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("rule \"p\" -> \"b\""));
	TEST_EQ(dictator_tryParseRule(&parser, &rule), 0);
	TEST_EQ(rule.before.kind, dictator_PatternKind_String);
	TEST_EQ(strEq(rule.before.as.string, S("p")), true);
	TEST_EQ(rule.after.kind, dictator_PatternKind_String);
	TEST_EQ(strEq(rule.after.as.string, S("p")), true);
	TEST_EQ(rule.hasWhen, false);
}

func Void test_parser_2(Void) {
	dictator_Parser parser = {0};
	dictator_Rule rule = {0};
	dictator_tokenizer_init(&parser.tokenizer, S("rule \"p\" -> \"b\" when vowel _ consonant"));
	TEST_EQ(dictator_tryParseRule(&parser, &rule), 0);
	TEST_EQ(rule.before.kind, dictator_PatternKind_String);
	TEST_EQ(strEq(rule.before.as.string, S("p")), true);
	TEST_EQ(rule.after.kind, dictator_PatternKind_String);
	TEST_EQ(strEq(rule.after.as.string, S("p")), true);
	TEST_EQ(rule.hasWhen, true);
	TEST_EQ(rule.when.kind, dictator_PatternKind_Concatenation);
	TEST_EQ(rule.when.as.concatenation.len, 3);
	TEST_EQ(rule.when.as.concatenation.items[0].kind, dictator_PatternKind_Identifier);
	TEST_EQ(strEq(rule.when.as.concatenation.items[0].as.identifier, S("vowel")), true);
	TEST_EQ(rule.when.as.concatenation.items[1].kind, dictator_PatternKind_Identifier);
	TEST_EQ(strEq(rule.when.as.concatenation.items[1].as.identifier, S("_")), true);
	TEST_EQ(rule.when.as.concatenation.items[2].kind, dictator_PatternKind_Identifier);
	TEST_EQ(strEq(rule.when.as.concatenation.items[2].as.identifier, S("consonant")), true);
}

/* func Void test_parser_3_helper(dictator_TopNode *topNode, String8 before, String8 after) { */
/* 	TEST_EQ(topNode->kind, dictator_TopNodeKind_Rule); */
/* 	TEST_EQ(topNode->as.rule.before.len, 1); */
/* 	TEST_EQ(topNode->as.rule.before.items[0].kind, dictator_PatternKind_String); */
/* 	TEST_EQ(strEq(topNode->as.rule.before.items[0].as.string, before), true); */
/* 	TEST_EQ(topNode->as.rule.after.len, 1); */
/* 	TEST_EQ(topNode->as.rule.after.items[0].kind, dictator_PatternKind_String); */
/* 	TEST_EQ(strEq(topNode->as.rule.after.items[0].as.string, after), true); */
/* 	TEST_EQ(topNode->as.rule.when.items[0].kind, dictator_PatternKind_Identifier); */
/* 	TEST_EQ(strEq(topNode->as.rule.when.items[0].as.identifier, S("vowel")), true); */
/* 	TEST_EQ(topNode->as.rule.when.items[1].kind, dictator_PatternKind_Identifier); */
/* 	TEST_EQ(strEq(topNode->as.rule.when.items[1].as.identifier, S("_")), true); */
/* 	TEST_EQ(topNode->as.rule.when.items[2].kind, dictator_PatternKind_Identifier); */
/* 	TEST_EQ(strEq(topNode->as.rule.when.items[2].as.identifier, S("vowel")), true); */
/* } */

/* func Void test_parser_3(Void) { */
/* 	dictator_Parser parser = {0}; */
/* 	dictator_BufferNode bufferNode = {0}; */
/* 	static Char buffer[] = */
/* 		"rule \"p\" -> \"b\" when vowel _ vowel\n" */
/* 		"rule \"t\" -> \"d\" when vowel _ vowel\n" */
/* 		"rule \"k\" -> \"g\" when vowel _ vowel" */
/* 		; */
/* 	dictator_tokenizer_init(&parser.tokenizer, S(buffer)); */
/* 	dictator_tryParseBuffer(&parser, &bufferNode); */
/* 	TEST_EQ(bufferNode.len, 3); */
/* 	test_parser_3_helper(&bufferNode.items[0], S("p"), S("b")); */
/* 	test_parser_3_helper(&bufferNode.items[1], S("t"), S("d")); */
/* 	test_parser_3_helper(&bufferNode.items[2], S("k"), S("g")); */
/* } */

/* Void getMatches(dictator_Pattern *pattern, String8 buffer, dictator_Slices *matches) { */
/* 	for */
/* } */

/* Void substitute(dictator_bufferNode *bnode, String8 buffer) { */
/* 	Usize ruleIndex = 0; */
/* 	for (ruleIndex = 0; ruleIndex < bnode->len; ruleIndex += 1) { */

/* 	} */
/* } */

struct dictator_Match {
	Usize index;
	Usize len;
};

func dictator_Match dictator_match(Usize index, Usize len) {
	struct dictator_Match match = {0};
	match.index = index;
	match.len = len;
	return match;
}

struct dictator_Matches {
	dictator_Match *items;
	Usize len;
	Usize capacity;
};

/* maybe change replacer to Environment */
func Bool dictator_doesMatch(const dictator_Replacer *replacer, const dictator_Pattern *pattern, const String8 buffer, Usize index, Usize *len) {
	switch (pattern->kind) {
	case dictator_PatternKind_String: {
		if (pattern->as.string.len <= buffer.len - index) {
			if (strEq(pattern->as.string, strSlice(buffer, index, pattern->as.string.len))) {
				*len = pattern->as.string.len;
				return true;
			}
		}
		return false;
	} break;
	case dictator_PatternKind_Identifier: {
		assert(0);
	} break;
	case dictator_PatternKind_SmallInteger: {
		assert(0);
	} break;
	case dictator_PatternKind_Or: {
		Usize orIndex = 0;
		for (orIndex = 0; orIndex < pattern->as.or.len; orIndex += 1) {
			if (dictator_doesMatch(replacer, &pattern->as.or.items[orIndex], buffer, index, len)) {
				return true;
			}
		}
		return false;
	} break;
	case dictator_PatternKind_Concatenation: {
		assert(0);
	} break;
	case dictator_PatternKind_List: {
		assert(0);
	} break;
	}
	assert(0);
}

func Void dictator_getMatches(const dictator_Replacer *replacer, const dictator_Rule *rule, const String8 buffer, dictator_Matches *matches) {
	/* this probably kinda sucks */
	Usize index = 0, len = 0;
	memZero(matches, sizeof(*matches));
	for (index = 0; index < buffer.len; index += 1) {
		len = 0;
		if (rule->hasWhen) {
			Usize whenIndex = 0;
			Usize totalLen = 0;
			Usize currentLen = 0;
			Usize added = 0;
			assert(rule->when.kind == dictator_PatternKind_Concatenation);
			for (whenIndex = 0; whenIndex < rule->when.as.concatenation.len; whenIndex += 1) {
				const dictator_Pattern *pattern = &rule->when.as.concatenation.items[whenIndex];
				Bool isMain = false;
				if (
					pattern->kind == dictator_PatternKind_Identifier &&
					strEq(pattern->as.identifier, S("_"))
				) {
					isMain = true;
					pattern = &rule->before;
				}

				if (dictator_doesMatch(replacer, pattern, buffer, index + totalLen, &currentLen)) {
					if (isMain) {
						added += 1;
						da_append(matches, dictator_match(index + totalLen, currentLen));
					}
					totalLen += currentLen;
				} else {
					/* THIS IS VERY IMPORTANT!!! */
					/* we add the main matches even though we're not sure they're actually there
					   we remove them later with in the next line, make sure it never exits the
					   loop in any other way than the break in this body and the while condition
					   not being satisfied in the inner for statement */
					matches->len -= added;
					break;
				}
			}
		} else {
			if (dictator_doesMatch(replacer, &rule->before, buffer, index, &len)) {
				da_append(matches, dictator_match(index, len));
			}
		}
	}
}

func Void dictator_applyRule(const dictator_Replacer *replacer, const dictator_Rule *rule, const String8 buffer, String8 *newBuffer) {
	dictator_Matches matches = {0};
	Usize matchIndex = 0;
	Usize newIndex = 0, newLen = buffer.len;
	Usize oldIndex = 0, oldLen = buffer.len;

	dictator_getMatches(replacer, rule, buffer, &matches);
	assert(rule->after.kind == dictator_PatternKind_String);
	for (matchIndex = 0; matchIndex < matches.len; matchIndex += 1) {
		newLen -= matches.items[matchIndex].len;
		newLen += rule->after.as.string.len;
	}

	if (matches.len == 0) {
		newBuffer->buf = strdup(buffer.buf);
		newBuffer->len = buffer.len;
		return;
	}

	newBuffer->buf = malloc(newLen);
	newBuffer->len = newLen;

	for (matchIndex = 0; matchIndex < matches.len; matchIndex += 1) {
		/* append to buffer */
		Usize copyLen = matches.items[matchIndex].index - oldIndex;
		assert(matches.items[matchIndex].index >= oldIndex);
		if (copyLen > 0) {
			memcpy(&newBuffer->buf[newIndex], &buffer.buf[oldIndex], copyLen);
			newIndex += copyLen;
			oldIndex += copyLen;
		}
		oldIndex += matches.items[matchIndex].len;
		memcpy(&newBuffer->buf[newIndex], rule->after.as.string.buf, rule->after.as.string.len);
		newIndex += rule->after.as.string.len;
	}
	/* last one */
	if (newIndex != newLen) {
		Usize copyLen = oldLen - oldIndex;
		assert(oldLen > oldIndex);
		assert(copyLen > 0);
		memcpy(&newBuffer->buf[newIndex], &buffer.buf[oldIndex], copyLen);
		newIndex += copyLen;
		oldIndex += copyLen;
	}

	da_free(&matches);
}

func Bool dictator_getDefinition(dictator_Replacer *replacer, String8 name, dictator_Pattern *pattern) {
	Usize definitionIndex = 0;
	for (definitionIndex = 0; definitionIndex < replacer->definitions.len; definitionIndex += 1) {
		if (strEq(replacer->definitions.items[definitionIndex].name, name)) {
			*pattern = replacer->definitions.items[definitionIndex].pattern;
			return true;
		}
	}
	return false;
}

func Bool dictator_preprocessPattern(dictator_Replacer *replacer, dictator_Pattern *pattern) {
	switch (pattern->kind) {
	case dictator_PatternKind_String: {
		return false;
	} break;
	case dictator_PatternKind_Identifier: {
		dictator_Pattern truePattern = {0};
		if (dictator_getDefinition(replacer, pattern->as.identifier, &truePattern)) {
			*pattern = truePattern;
			return true;
		} else {
			return false;
		}
	} break;
	case dictator_PatternKind_SmallInteger: {
		return false;
	} break;
	case dictator_PatternKind_Or: {
		Usize orIndex = 0;
		Bool changed = false;
		for (orIndex = 0; orIndex < pattern->as.or.len; orIndex += 1) {
			if (dictator_preprocessPattern(replacer, &pattern->as.or.items[orIndex])) {
				changed = true;
			}
		}
		return changed;
	} break;
	case dictator_PatternKind_Concatenation: {
		Usize concatenationIndex = 0;
		Bool changed = false;
		for (concatenationIndex = 0; concatenationIndex < pattern->as.concatenation.len; concatenationIndex += 1) {
			if (dictator_preprocessPattern(replacer, &pattern->as.concatenation.items[concatenationIndex])) {
				changed = true;
			}
		}
		return changed;
	} break;
	case dictator_PatternKind_List: {
		Usize listIndex = 0;
		Bool changed = false;
		for (listIndex = 0; listIndex < pattern->as.list.len; listIndex += 1) {
			if (dictator_preprocessPattern(replacer, &pattern->as.list.items[listIndex])) {
				changed = true;
			}
		}
		return changed;
	} break;
	}
	assert(0);
}

Void dictator_preprocessDefinitions(dictator_Replacer *replacer) {
	Usize definitionIndex = 0;
	for (definitionIndex = 0; definitionIndex < replacer->definitions.len; definitionIndex += 1) {
		dictator_Definition *definition = &replacer->definitions.items[definitionIndex];
		dictator_preprocessPattern(replacer, &definition->pattern);
	}
}

Void dictator_preprocessRules(dictator_Replacer *replacer) {
	Usize ruleIndex = 0;
	for (ruleIndex = 0; ruleIndex < replacer->rules.len; ruleIndex += 1) {
		dictator_Rule *rule = &replacer->rules.items[ruleIndex];
		dictator_preprocessPattern(replacer, &rule->before);
		dictator_preprocessPattern(replacer, &rule->when);
	}
}

func Void dictator_preprocess(dictator_Replacer *replacer) {
	/* const Usize maxIter = 5000; */
	/* Usize iterCount = 0; */
	dictator_preprocessDefinitions(replacer);
	dictator_preprocessRules(replacer);
}

func Void slurpFile(String8 filepath, String8 *out) {
	if (strEq(filepath, S("-"))) {
		Usize size = 1024;
		out->buf = calloc(size, 1);
		for (;;) {
			Usize fsize = fread(&out->buf[size - 1024], 1, 1024, stdin);
			if (fsize < 1024) {
				break;
			}
			size += 1024;
			out->buf = realloc(out->buf, size);
			out->buf[size] = '\0';
		}
		out->len = strlen(out->buf);
	} else {
		FILE *fp = fopen(filepath.buf, "r");
		readWholeFile(fp, NULL, &out->len);
		out->buf = malloc(out->len);
		readWholeFile(fp, (U8 **)&out->buf, &out->len);
		fclose(fp);
	}
}

func Int main(Int argc, Char **argv) {
	dictator_Parser parser = {0};
	dictator_Replacer replacer = {0};
	String8 rulesSource = {0}, textSource = {0};
	String8 rulesBuffer = {0}, textBuffer = {0};

	test_tokenizer();
	test_parser();

	argc -= 1;
	argv += 1;
	while (argc > 0) {
		if (strcmp(*argv, "-r") == 0) {
			assert(argc > 1);
			argc -= 1;
			argv += 1;
			rulesSource = string8FromCstr(*argv, strlen(*argv));
		} else if (strcmp(*argv, "-t") == 0) {
			assert(argc != 0);
			argc -= 1;
			argv += 1;
			textSource = string8FromCstr(*argv, strlen(*argv));
		}
		argc -= 1;
		argv += 1;
	}

	assert(rulesSource.len != 0);
	assert(textSource.len != 0);

	slurpFile(rulesSource, &rulesBuffer);
	slurpFile(textSource, &textBuffer);

	printf("rules: %.*s\n", Slens(rulesBuffer));
	printf("text: %.*s\n", Slens(textBuffer));

	dictator_tokenizer_init(&parser.tokenizer, rulesBuffer);
	assert(dictator_tryParseReplacer(&parser, &replacer) == 0);
	dictator_preprocess(&replacer);
	{
		String8 buffer = textBuffer;
		String8 newBuffer = {0};
		Usize ruleIndex = 0;
		for (ruleIndex = 0; ruleIndex < replacer.rules.len; ruleIndex += 1) {
			dictator_applyRule(&replacer, &replacer.rules.items[ruleIndex], buffer, &newBuffer);
			buffer = newBuffer;
		}
		printf("%.*s\n", Slens(buffer));
	}

	return 0;
}
