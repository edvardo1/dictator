#if !defined(YACSL_DOT_H)
#define YACSL_DOT_H

#define TODO(msg) \
	( \
		fprintf( \
			stderr, \
			"\x1b[41m[TODO]\x1b[0m at %s:%d \x1b[35m\"%s\"\x1b[0m\n", \
			__FILE__, __LINE__, msg \
		), \
		fflush(stderr), \
		exit(1) \
	)
#define UNUSED(x) ((Void)(x))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CLAMP(n, lo, hi) MIN(MAX((n), (lo)), (hi))
#define CLAMPTOP(a, b) MIN(a, b)
#define CLAMPBOT(a, b) MAX(a, b)
#define IN_BOUNDS(n, lo, hi) ((lo <= n) && (n <= hi))
#define ABS(a) (((a) < 0) ? -(a) : (a))
#define SIGN(a) ((a) == 0 ? 0 : ((a) < 0 ? -1 : 1))
#define MAXABS(a, b) (ABS(a) > ABS(b) ? (a) : (b))
#define MINABS(a, b) (ABS(a) < ABS(b) ? (a) : (b))

#define S8(cstr) (string8FromCstr(cstr, sizeof(cstr) - 1))
#define S S8
#define S8lenbuf(str) (Int)(str).len, (str).buf
#define Slens S8lenbuf
#define string8 string8FromCstr
#define arena_pushArray(arena, type, len) \
	arena_push((arena), sizeof(type) * (len), sizeof(type))
#define arena_pushType(arena, type) \
	arena_push((arena), sizeof(type), sizeof(Usize))
#define arena_pushStruct(arena, type) \
	arena_push((arena), sizeof(type), sizeof(Usize))

#define PICO (10e-12)
#define NANO (10e-9)
#define MICRO (10e-6)
#define MILLI (10e-3)
#define KILO (10e3)
#define MEGA (10e6)
#define GIGA (10e9)
#define TERA (10e12)

#define KIBI (1024)
#define MIBI (KIBI * KIBI)
#define GIBI (KIBI * KIBI * KIBI)

#define HUNDRED (100)
#define THOUSAND (1000)
#define MILLION (THOUSAND * THOUSAND)
#define BILLION (THOUSAND * MILLION)
#define TRILLION (THOUSAND * BILLION)

#if defined(YACSL_USE_STDINT)
typedef int64_t I64;
typedef int32_t I32;
typedef int16_t I16;
typedef int8_t I8;
typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
#else
typedef signed long int I64;
typedef signed int I32;
typedef signed short I16;
typedef signed char I8;
typedef unsigned long int U64;
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;
#endif

#if __STDC_VERSION__ >= 199901L /* C99 or later */
typedef _Bool Bool;
#else
#if !defined(Bool)
typedef U8 Bool;
#endif /* !defined(Bool) */
#if !defined(false)
#define false ((Bool)0)
#endif /* !defined(false) */
#if !defined(true)
#define true ((Bool)1)
#endif /* !defined(true) */
#endif /* __STDC_VERSION__ >= 199901L */

typedef float F32;
typedef double F64;
typedef U8 B8;
typedef U16 B16;
typedef U32 B32;
typedef U64 B64;

typedef size_t Usize;
typedef float Float;
typedef double Double;
typedef unsigned long Ulong;
typedef long Long;
typedef unsigned int Uint;
typedef int Int;
typedef unsigned short Ushort;
typedef short Short;
typedef unsigned char Uchar;
typedef char Char;
typedef unsigned char Byte;
typedef void Void;
typedef Void *RawPtr;

typedef struct Allocator {
	Void *(*alloc)(Usize);
	Void (*free)(Void *);
} Allocator;

typedef struct String8 {
	Usize len;
	Char *buf;
} String8;

typedef struct Arena {
	Byte *memory;
	Usize size;
	Usize point;
} Arena;

#define PADDING(x, p) (((p) - ((x) % (p))) % (p))

#define CONCAT2__(a, b) a##b
#define CONCAT2_(a, b) CONCAT2__(a, b)
#define CONCAT2(a, b) CONCAT2_(a, b)

#define DynamicArray(type) \
	struct { \
		Usize len; \
		Usize capacity; \
		type *items; \
	}

#define Slice(type) \
	struct { \
		Usize len; \
		type *items; \
	}
#define slice_mem_eq(a, b) (_slice_mem_eq((a), (b)))
#define _slice_mem_eq(a, b) \
	a.len * sizeof(*a.items) == b.len * sizeof(*b.items) == b.len && \
	memEq((U8 *)a.items, (U8 *)b.items, a.len * sizeof(*a.items))

/*
#define da_at_(da, index) \
	((index < da->len) \
	 ? (da->items[index]) \
	 : (printError(S("out of bounds")), da->items[index]))
#define da_at(da, index) \
	da_at_((da), (index))

#define da_atPut_(da, index, value) \
	((index < da->len) \
	 ? (da->items[index] = value) \
	 : (printError(S("out of bounds")), da->items[index] = value))
#define da_atPut(da, index, value) \
	da_atPut_((da), (index), (value))

#define da_atFirst(da) \
	da_at((da), 0)

#define da_atFirstPut(da, value) \
	da_atPut((da), 0, (value))

#define da_atLast(da) \
	da_at((da), (da)->len - 1)

#define da_atLastPut(da, value) \
	da_atPut((da), (da)->len - 1, (value))
*/

Usize da_appendAEHelper(
	Void **items,
	Allocator allocator,
	Usize size,
	Usize copySize
);

#define da_appendAE_(da, value, allocator, err) \
	do { \
		if (da->len + 1 >= da->capacity) { \
			if (da->capacity == 0) { \
				da->capacity = 16; \
			} else { \
				da->capacity <<= 2; \
			} \
			*err = da_appendAEHelper( \
				(Void **)&da->items, \
				allocator, \
				da->capacity * sizeof(*da->items), \
				da->len * sizeof(*da->items) \
			); \
		} else { \
			*err = 0; \
		} \
		\
		if (!*err) { \
			da->items[da->len] = value; \
			da->len += 1; \
		} \
	} while(0)
#define da_appendAE(da, value, allocator, err) \
	da_appendAE_((da), (value), (allocator), (err))

#define da_appendAEZ_(da, allocator, err) \
	do { \
		if (da->len + 1 >= da->capacity) { \
			if (da->capacity == 0) { \
				da->capacity = 16; \
			} else { \
				da->capacity <<= 2; \
			} \
			*err = da_appendAEHelper( \
				(Void **)&da->items, \
				allocator, \
				da->capacity * sizeof(*da->items), \
				da->len * sizeof(*da->items) \
			); \
		} else { \
			*err = 0; \
		} \
		\
		if (!*err) { \
			memZero(&da->items[da->len], sizeof(*da->items)); \
			da->len += 1; \
		} \
	} while(0)
#define da_appendAEZ(da, allocator, err) \
	da_appendAEZ_((da), (allocator), (err))


#define da_appendA_(da, value, allocator) \
	do { \
		if (da->len + 1 >= da->capacity) { \
			if (da->capacity == 0) { \
				da->capacity = 16; \
			} else { \
				da->capacity <<= 2; \
			} \
			if (da_appendAEHelper( \
				(Void **)&da->items, \
				allocator, \
				da->capacity * sizeof(*da->items), \
				da->len * sizeof(*da->items) \
			)) { \
				printError(S("error during da_appendA_")); \
			} \
		} \
		\
		da->items[da->len] = value; \
		da->len += 1; \
	} while(0)
#define da_appendA(da, value, allocator) da_appendA_((da), (value), (allocator))

#define da_append(da, value) da_appendA((da), (value), (stdAllocator))

#define da_appendAZ_(da, allocator) \
	do { \
		if (da->len + 1 >= da->capacity) { \
			if (da->capacity == 0) { \
				da->capacity = 16; \
			} else { \
				da->capacity <<= 2; \
			} \
			if (da_appendAEHelper( \
				(Void **)&da->items, \
				allocator, \
				da->capacity * sizeof(*da->items), \
				da->len * sizeof(*da->items) \
			)) { \
				printError(S("error during da_appendA_")); \
			} \
		} \
		\
		memZero(&da->items[da->len], sizeof(*da->items)); \
		da->len += 1; \
	} while(0)
#define da_appendAZ(da, allocator) da_appendAZ_((da), (allocator))

#define da_appendZ(da) da_appendAZ((da), (stdAllocator))

#define da_at_(da, index) (assert(index < da->len), da->items[index])
#define da_at(da, index) (da_at_((da), ((Usize)(index))))
#define da_first(da) (da_at((da), 0))
#define da_last(da) (da_at((da), ((da)->len) - 1))

#define da_freeA(da, allocator) \
	do { \
		if ((da)->items != NULL) { \
			(allocator).free((da)->items); \
			(da)->items = NULL; \
		} \
	} while(0)


#define da_free(da) da_freeA(da, stdAllocator)

/*
WOWHASHMAP
#define HashMap(key_type, value_type) \
	struct { \
		key_type *keys; \
		value_type *values; \
		Usize *hasValue; \
		Usize amount; \
		Usize capacity; \
	}

#define hmSet(hm, key, value) \
	_hmSet
#define hmGetR(hm)
#define hmGet(hm)
#define hmHas(hm)
#define hmNext(hm)
*/

String8 string8FromCstr(char *cstr, Usize len);
Bool memEq(const Void *a, const Void *b, Usize len);
Bool strEq(const String8 a, const String8 b);
String8 strSlice(String8 str, const Usize idx, const Usize len);
Void memZero(Void *ptr, Usize len);
Void memCopy(Void *dst, Void *src, Usize size);
Int arena_alloc(Arena *arena, Usize size, Allocator allocator);
Void arena_free(Arena *arena, Allocator allocator);
Void arena_zero(Arena *arena);
Void arena_reset(Arena *arena);
Void *arena_push(Arena *arena, Usize size, Usize align);
Ulong djb2(const Void *ptr, Usize len);
Void printError(String8 str);

#if defined(YACSL_IO)
Void readWholeFile(FILE *fp, U8 **buf, Usize *size);
#endif /* defined(YACSL_IO) */

extern Allocator stdAllocator;

#endif /* !defined(YACSL_DOT_H) */

#if defined(YACSL_IMPLEMENTATION)

Allocator stdAllocator = {malloc, free};

Usize da_appendAEHelper(
	Void **items,
	Allocator allocator,
	Usize size,
	Usize copySize
) {
	Void *newPtr = allocator.alloc(size);
	Void *oldPtr = *items;

	if (newPtr == NULL) {
		return 1;
	}

	if (oldPtr != NULL) {
		memCopy(newPtr, oldPtr, copySize);
		allocator.free(oldPtr);
	}

	*items = newPtr;
	return 0;
}

String8 string8FromCstr(char *cstr, Usize len) {
	String8 str8 = {0};
	str8.len = len;
	str8.buf = cstr;
	return str8;
}

Bool memEq(const Void *a, const Void *b, Usize len) {
	Usize i = 0;
	const Byte *ba = (const Byte *)a;
	const Byte *bb = (const Byte *)b;
	for (; i < len; i++) {
		if (ba[i] != bb[i]) {
			return 0;
		}
	}
	return 1;
}

Bool strEq(const String8 a, const String8 b) {
	if (a.len == b.len) {
		return memEq(a.buf, b.buf, a.len);
	}
	return 0;
}

String8 strSlice(String8 str, const Usize idx, const Usize len) {
	String8 out = {0};
	out.buf = &str.buf[idx];
	out.len = len;
	return out;
}

Void memZero(Void *ptr, Usize len) {
	memset(ptr, 0, len);
}

Void memCopy(Void *dst, Void *src, Usize size) {
	Byte *bdst = (Byte *)dst;
	Byte *bsrc = (Byte *)src;
	Usize i = 0;
	for (; i < size; i++) {
		bdst[i] = bsrc[i];
	}
}

/* @todo make allocator a pointer */
Int arena_alloc(Arena *arena, Usize size, Allocator allocator) {
	if (arena->memory != NULL) {
		arena_free(arena, allocator);
	}

	arena->memory = (Byte *)allocator.alloc(size);
	if (arena->memory == NULL) {
		return 1;
	}
	/* memZero(arena->memory, size); */
	arena->point = 0;
	arena->size = size;

	return 0;
}

Void arena_free(Arena *arena, Allocator allocator) {
	if (arena->memory != NULL) {
		allocator.free(arena->memory);
		arena->memory = NULL;
	}
}

Void arena_zero(Arena *arena) {
	Usize i = 0;
	for (; i < arena->size; i++) {
		arena->memory[i] = 0;
	}
}

Void arena_reset(Arena *arena) {
	arena->point = 0;
}

Void *arena_push(Arena *arena, Usize size, Usize align) {
	Void *out = NULL;
	const Usize padding = (-arena->point) & (align - 1);
	if (arena->point + size + padding > arena->size) {
		return NULL;
	} else {
		out = &arena->memory[arena->point + padding];
		arena->point += size + padding;
		return out;
	}
}

Usize djb2(const Void *ptr, Usize len) {
	const Byte *buf = (const Byte *)ptr;
	Usize ret = 5381;
	Usize i = 0;
	for (; i < len; i++) {
		ret = ((ret << 5) + ret) + buf[i];
	}
	return ret;
}

Void printError(String8 str) {
	fprintf(stderr, "ERROR: \"%*s\"\n", (int)str.len, str.buf);
	fprintf(stderr, "segfaulting now...\n");
	fflush(stderr);
	assert(0);
}

#if defined(YACSL_IO)

/*
Int readWholeFile(const Char *filename, U8 **buf, Usize *size) {
	FILE *fp = NULL;
	U8 *internalBuf = NULL;
	Int err = 0;
	Usize freadSize, ftellSize;

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		goto err;
	}

	err = fseek(fp, 0, SEEK_END);
	if (err) {
		goto err;
	}
	ftellSize = ftell(fp);
	if (size != NULL) {
		*size = ftellSize;
	}

	err = fseek(fp, 0, SEEK_SET);
	if (err) {
		goto err;
	}

	if (buf != NULL) {
		internalBuf = malloc(sizeof(U8) * ftellSize);
		if (internalBuf == NULL) {
			goto err;
		}

		freadSize = fread(internalBuf, 1, ftellSize, fp);
		if (freadSize != ftellSize) {
			goto err;
		}

		*buf = internalBuf;
	}

	fclose(fp);

	return 0;
err:
	if (fp != NULL) {
		fclose(fp);
	}
	if (internalBuf != NULL) {
		free(internalBuf);
	}

	return 1;
}
*/

Void readWholeFile(FILE *fp, U8 **buf, Usize *size) {
	if (buf == NULL) {assert(size != NULL);}

	if (buf == NULL && size != NULL) {
		assert(fseek(fp, 0, SEEK_END) == 0);
		*size = ftell(fp);
		assert(fseek(fp, 0, SEEK_SET) == 0);
	}

	if (buf != NULL && size != NULL) {
		assert(fread(*buf, 1, *size, fp) == *size);
	}
}

#endif /* defined(YACSL_IO) */

#endif /* defined(YACSL_IMPLEMENTATION) */
