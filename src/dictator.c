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

	dictator_TokenKind_ArrowRight,
	dictator_TokenKind_Comma,
	dictator_TokenKind_CurlyBracket_Close,
	dictator_TokenKind_CurlyBracket_Open,
	dictator_TokenKind_Equals,
	dictator_TokenKind_Parenthesis_Close,
	dictator_TokenKind_Parenthesis_Open,
	dictator_TokenKind_SquareBracket_Close,
	dictator_TokenKind_SquareBracket_Open,
	dictator_TokenKind_Define,
	dictator_TokenKind_Or,
	dictator_TokenKind_Rule,
	dictator_TokenKind_When,

	dictator_TokenKind_COUNT
} dictator_TokenKind;

typedef enum {
	dictator_TokenizerCode_Ok,
	dictator_TokenizerCode_Over,
	dictator_TokenizerCode_Error
} dictator_TokenizerCode;

#include "dictator.h"
#define func

struct StringBuilder {
	String8 *items;
	Usize len;
	Usize capacity;
};

func Void stringBuilder_build(StringBuilder *sb, String8 *out) {
	Usize totalLen = 0, i = 0;
	for (i = 0; i < sb->len; i += 1) {
		totalLen += sb->items[i].len;
	}
	out->buf = malloc(totalLen);
	out->len = 0;
	i = 0;
	while (out->len < totalLen) {
		memcpy(&out->buf[out->len], sb->items[i].buf, sb->items[i].len);
		assert(i < sb->len);
		out->len += sb->items[i].len;
		i += 1;
	}
	assert(out->len == totalLen);
}

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
	case dictator_TokenKind_Comma: {
		printf("Comma\n");
	} break;
	case dictator_TokenKind_ArrowRight: {
		printf("ArrowRight\n");
	} break;
	case dictator_TokenKind_Define: {
		printf("Define\n");
	} break;
	case dictator_TokenKind_Or: {
		printf("Or\n");
	} break;
	case dictator_TokenKind_Rule: {
		printf("Rule\n");
	} break;
	case dictator_TokenKind_When: {
		printf("When\n");
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
	return charIsAlpha(c) || c == '_' || c == '#';
}

func Bool charIsIdentifierAfterStart(Char c) {
	return charIsAlpha(c) || c == '_' || c == '#' || charIsDigit(c);
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
		if (c == ',') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Comma;
			if (token != NULL) {
				*token = tokenizer->token;
			}
			return 0;
		} else if (c == '-') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			if (dictator_tokenizer__peekChar(tokenizer, &c) == 0) {
				if (c == '>') {
					tokenizer->token.kind = dictator_TokenKind_ArrowRight;
					assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
				} else if (c == '-') {
					inComment = true;
					goto commentLabel;
				} else {
					assert(0);
				}
			}
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
		} else if (c == '=') {
			assert(dictator_tokenizer__advanceChar(tokenizer) == 0);
			tokenizer->token.kind = dictator_TokenKind_Equals;
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
		} else if (charIsDigit(c)) {
			Int number = 0;
			Usize totalLen = 0;
			for (;;) {
				err = dictator_tokenizer__peekChar(tokenizer, &c);
				if (charIsDigit(c)) {
					number = number * 10 + (c - '0');
					totalLen += 1;
					assert(err == dictator_tokenizer__popChar(tokenizer, &c));
				} else {
					tokenizer->token.kind = dictator_TokenKind_SmallInteger;
					tokenizer->token.as.smallInteger = number;
					if (token != NULL) {
						*token = tokenizer->token;
					}
					return 0;
				}
			}
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

							if (strEq(tokenizer->token.as.identifier.string, S("define"))) {
								tokenizer->token.kind = dictator_TokenKind_Define;
							} else if (strEq(tokenizer->token.as.identifier.string, S("or"))) {
								tokenizer->token.kind = dictator_TokenKind_Or;
							} else if (strEq(tokenizer->token.as.identifier.string, S("rule"))) {
								tokenizer->token.kind = dictator_TokenKind_Rule;
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

func Void dictator_patternPrint(const dictator_Pattern *atom) {
	Usize index = 0;
	if (atom->marked) {
		fprintf(stderr, "$");
	}
	fprintf(stderr, "(");
	switch (atom->kind) {
	case dictator_PatternKind_String: {
		fprintf(stderr, "string %.*s", Slens(atom->as.string));
	} break;
	case dictator_PatternKind_Identifier: {
		fprintf(stderr, "identifier %.*s", Slens(atom->as.identifier));
	} break;
	case dictator_PatternKind_SmallInteger: {
		fprintf(stderr, "small_integer %d", atom->as.smallInteger);
	} break;
	case dictator_PatternKind_Or: {
		fprintf(stderr, "or ");
		for (index = 0; index < atom->as.or.len; index += 1) {
			if (index != 0) {
				fprintf(stderr, " ");
			}
			dictator_patternPrint(&atom->as.or.items[index]);
		}
	} break;
	case dictator_PatternKind_List: {
		fprintf(stderr, "list ");
		for (index = 0; index < atom->as.list.len; index += 1) {
			if (index != 0) {
				fprintf(stderr, " ");
			}
			dictator_patternPrint(&atom->as.list.items[index]);
		}
	} break;
	case dictator_PatternKind_Concatenation: {
		fprintf(stderr, "concatenation ");
		for (index = 0; index < atom->as.concatenation.len; index += 1) {
			if (index != 0) {
				fprintf(stderr, " ");
			}
			dictator_patternPrint(&atom->as.concatenation.items[index]);
		}
	} break;
	}
	fprintf(stderr, ")");
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

func Int dictator_tryParsePatternPrimary(dictator_Parser *parser, dictator_Pattern *pattern) {
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
	} else if (token.kind == dictator_TokenKind_Parenthesis_Open) {
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		dictator_tryParsePattern(parser, pattern);
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		assert(token.kind == dictator_TokenKind_Parenthesis_Close);
		return 0;
	} else if (token.kind == dictator_TokenKind_SquareBracket_Open) {
		dictator_Pattern item = {0};
		Bool needComma = false;
		pattern->kind = dictator_PatternKind_List;
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);

		for (;;) {
			assert(dictator_tokenizer_peekToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
			if (token.kind == dictator_TokenKind_SquareBracket_Close) {
				assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
				break;
			} else if (token.kind == dictator_TokenKind_Comma) {
				needComma = false;
				assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
			} else if (!needComma && dictator_tryParsePattern(parser, &item) == 0) {
				da_append(&pattern->as.list, item);
				needComma = true;
			} else {
				assert(0);
			}
		}

		return 0;
	} else if (token.kind == dictator_TokenKind_CurlyBracket_Open) {
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		dictator_tryParsePattern(parser, pattern);
		assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);
		pattern->marked = true;
		assert(token.kind == dictator_TokenKind_CurlyBracket_Close);
		return 0;
	} else {
		return 1;
	}

	assert(dictator_tokenizer_popToken(&parser->tokenizer, &token) == dictator_TokenizerCode_Ok);

	return 0;
}

func Int dictator_tryParsePatternOr(dictator_Parser *parser, dictator_Pattern *pattern) {
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

func Int dictator_tryParsePatternConcat(dictator_Parser *parser, dictator_Pattern *pattern) {
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

func Int dictator_tryParsePattern(dictator_Parser *parser, dictator_Pattern *pattern) {
	return dictator_tryParsePatternConcat(parser, pattern);
}

func Int dictator_tryParseRule(dictator_Parser *parser, dictator_Rule *rule) {
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

func Int dictator_tryParseDefinition(dictator_Parser *parser, dictator_Definition *var) {
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
			if (parser->tokenizer.index < parser->tokenizer.string.len) {
				printf("error at index: %d\n", parser->tokenizer.index);
				exit(1);
			}
			break;
		}
	}
	
	return 0;
}

struct dictator_Match {
	Usize index;
	Usize len;
	DynamicArray(I32) listIndices;
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

	DynamicArray(I32) markedIndices;
};

/* maybe change replacer to Environment */
func Bool dictator_getMatch(const dictator_Replacer *replacer, const dictator_Pattern *pattern, const String8 buffer, const Usize index, Usize *len, dictator_Match *match) {
	assert(match != NULL);
	switch (pattern->kind) {
	case dictator_PatternKind_String: {
		if (pattern->as.string.len <= buffer.len - index) {
			if (strEq(pattern->as.string, strSlice(buffer, index, pattern->as.string.len))) {
				*len = pattern->as.string.len;
				if (match != NULL) {
					match->index = index;
					match->len = *len;
				}
				return true;
			}
		}
		return false;
	} break;
	case dictator_PatternKind_Identifier: {
		if (strEq(pattern->as.identifier, S("#"))) {
			if (index == 0) {
				*len = 0;
				if (match != NULL) {
					match->index = index;
					match->len = *len;
				}
				return true;
			} else if (charIsWhitespace(buffer.buf[index])) {
				*len = 1;
				if (match != NULL) {
					match->index = index;
					match->len = *len;
				}
				return true;
			} else {
				return false;
			}
		}
		printf("error: unknown identiifer \"%.*s\"\n", Slens(pattern->as.identifier));
		exit(1);
	} break;
	case dictator_PatternKind_SmallInteger: {
		assert(0);
	} break;
	case dictator_PatternKind_Or: {
		Usize orIndex = 0;
		for (orIndex = 0; orIndex < pattern->as.or.len; orIndex += 1) {
			if (dictator_getMatch(replacer, &pattern->as.or.items[orIndex], buffer, index, len, match)) {
				if (match != NULL) {
					match->index = index;
					match->len = *len;
				}
				return true;
			}
		}
		return false;
	} break;
	case dictator_PatternKind_Concatenation: {
		Usize concatenationIndex = 0;
		Usize currentIndex = index;
		*len = 0;
		for (
			concatenationIndex = 0;
			concatenationIndex < pattern->as.concatenation.len;
			concatenationIndex += 1
		) {
			Usize currentLen = 0;
			if (
				!dictator_getMatch(
					replacer,
					&pattern->as.concatenation.items[concatenationIndex],
					buffer,
					currentIndex,
					&currentLen,
					match
				)
			) {
				return false;
			}
			currentIndex += currentLen;
		}
		*len = currentIndex - index;
		if (pattern->marked && match != NULL) {
			dictator_Mark mark = {index, *len};
			da_append(&match->marks, mark);
		}
		if (match != NULL) {
			match->index = index;
			match->len = *len;
		}
		return true;
	} break;
	case dictator_PatternKind_List: {
		Usize listIndex = 0;
		assert(match != NULL);
		for (listIndex = 0; listIndex < pattern->as.or.len; listIndex += 1) {
			Usize listIndicesLen = match->listIndices.len;
			if (dictator_getMatch(replacer, &pattern->as.list.items[listIndex], buffer, index, len, match)) {
				match->index = index;
				match->len = *len;
				da_appendZ(&match->listIndices);
				memmove(&match->listIndices.items[listIndicesLen + 1], &match->listIndices.items[listIndicesLen], (match->listIndices.len - listIndicesLen) * sizeof(*match->listIndices.items));
				match->listIndices.items[listIndicesLen] = listIndex;
				/* replace with da_insert later */
				return true;
			}
		}
		return false;
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
				dictator_Match match = {0};
				Bool isMain = false;
				if (
					pattern->kind == dictator_PatternKind_Identifier &&
					strEq(pattern->as.identifier, S("_"))
				) {
					isMain = true;
					pattern = &rule->before;
				}

				if (dictator_getMatch(replacer, pattern, buffer, index + totalLen, &currentLen, &match)) {
					if (isMain) {
						added += 1;
						da_append(matches, match);
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
			dictator_Match match = {0};
			if (dictator_getMatch(replacer, &rule->before, buffer, index, &len, &match)) {
				if (len > 0) {
					da_append(matches, match);
				}
			}
		}
	}
}

func Void dictator_addPatternToStringBuilder(const dictator_Match *match, Usize *listIndicesIndex, const dictator_Pattern *pattern, StringBuilder *sb) {
	if (pattern->kind == dictator_PatternKind_String) {
		da_append(sb, pattern->as.string);
	} else if (pattern->kind == dictator_PatternKind_SmallInteger) {
		assert(0);
	} else if (pattern->kind == dictator_PatternKind_List) {
		Usize listIndex = 0;
		assert(*listIndicesIndex < match->listIndices.len);
		listIndex = match->listIndices.items[*listIndicesIndex];
		*listIndicesIndex += 1;
		assert(listIndex < pattern->as.list.len);
		dictator_addPatternToStringBuilder(
			match,
			listIndicesIndex,
			&pattern->as.list.items[listIndex],
			sb
		);
	}
}

func Void dictator_getReplacementString(const dictator_Matches *matches, Usize index, const dictator_Rule *rule, String8 *replacementString) {
	StringBuilder rbuf = {0};
	const dictator_Pattern *plist = NULL;
	Usize len = 0, i = 0, listIndicesIndex = 0;
	const dictator_Match *match = &matches->items[index];

	if (rule->after.kind == dictator_PatternKind_Concatenation) {
		plist = rule->after.as.concatenation.items;
		len   = rule->after.as.concatenation.len;
	} else {
		plist = &rule->after;
		len = 1;
	}

	for (i = 0; i < len; i += 1) {
		dictator_addPatternToStringBuilder(match, &listIndicesIndex, &plist[i], &rbuf);
	}

	stringBuilder_build(&rbuf, replacementString);
}

func Void dictator_applyRule(const dictator_Replacer *replacer, const dictator_Rule *rule, const String8 buffer, String8 *newBuffer) {
	dictator_Matches matches = {0};
	DynamicArray(String8) builder = {0};
	String8 replacementString = {0};
	Usize matchIndex = 0, builderIndex = 0;
	Usize newIndex = 0, newLen = 0;
	Usize oldIndex = 0, oldLen = buffer.len;

	dictator_getMatches(replacer, rule, buffer, &matches);

	if (matches.len == 0) {
		newBuffer->buf = strdup(buffer.buf);
		newBuffer->len = buffer.len;
		return;
	}

	for (matchIndex = 0; matchIndex < matches.len; matchIndex += 1) {
		/* append to buffer */
		Usize copyLen = matches.items[matchIndex].index - oldIndex;
		assert(matches.items[matchIndex].index >= oldIndex);
		if (copyLen > 0) {
			da_append(&builder, strSlice(buffer, oldIndex, copyLen));
			newIndex += copyLen;
			oldIndex += copyLen;
		}
		oldIndex += matches.items[matchIndex].len;
		dictator_getReplacementString(&matches, matchIndex, rule, &replacementString);
		da_append(&builder, replacementString);
		newIndex += replacementString.len;
	}

	/* last one */
	if (oldIndex != oldLen) {
		Usize copyLen = oldLen - oldIndex;
		assert(oldLen > oldIndex);
		assert(copyLen > 0);
		da_append(&builder, strSlice(buffer, oldIndex, copyLen));
		newIndex += copyLen;
		oldIndex += copyLen;
	}

	for (builderIndex = 0; builderIndex < builder.len; builderIndex += 1) {
		newLen += builder.items[builderIndex].len;
	}
	newBuffer->buf = malloc(newLen);
	newBuffer->len = 0;
	for (builderIndex = 0; builderIndex < builder.len; builderIndex += 1) {
		memcpy(
			&newBuffer->buf[newBuffer->len],
			builder.items[builderIndex].buf,
			builder.items[builderIndex].len
		);
		newBuffer->len += builder.items[builderIndex].len;
	}
	assert(newBuffer->len == newLen);

	da_free(&matches);
	da_free(&builder);
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
		for (
			concatenationIndex = 0;
			concatenationIndex < pattern->as.concatenation.len;
			concatenationIndex += 1
		) {
			if (
				dictator_preprocessPattern(
					replacer,
					&pattern->as.concatenation.items[concatenationIndex]
				)
			) {
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

func Void showFormat() {
	printf("format:\n");
	printf("  dictator -r rules.dictator -t text.txt\n");
}

func Int main(Int argc, Char **argv) {
	dictator_Parser parser = {0};
	dictator_Replacer replacer = {0};
	String8 rulesSource = {0}, textSource = {0};
	String8 rulesBuffer = {0}, textBuffer = {0};
	Bool providedRules = false, providedText = false;

	argc -= 1;
	argv += 1;
	while (argc > 0) {
		if (strcmp(*argv, "-r") == 0) {
			if (providedRules) {
				printf("error: tried to provide more than 1 rule file\n");
				showFormat();
				return 1;
			}
			if (argc <= 0) {
				printf("error: missing rule file argument\n");
				showFormat();
				return 1;
			}
			argc -= 1;
			argv += 1;
			rulesSource = string8FromCstr(*argv, strlen(*argv));
			providedRules = true;
		} else if (strcmp(*argv, "-t") == 0) {
			if (providedText) {
				printf("error: tried to provide more than 1 text file\n");
				showFormat();
				return 1;
			}
			if (argc <= 0) {
				printf("error: missing text file argument\n");
				showFormat();
				return 1;
			}
			argc -= 1;
			argv += 1;
			textSource = string8FromCstr(*argv, strlen(*argv));
			providedText = true;
		}
		argc -= 1;
		argv += 1;
	}

	if (!providedRules) {
		printf("error: no rules file provided\n");
		showFormat();
		return 1;
	}

	if (!providedText) {
		printf("error: no text file provided\n");
		showFormat();
		return 1;
	}

	assert(rulesSource.len != 0);
	assert(textSource.len != 0);

	slurpFile(rulesSource, &rulesBuffer);
	slurpFile(textSource, &textBuffer);

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
		printf("%.*s", Slens(buffer));
	}

	return 0;
}
