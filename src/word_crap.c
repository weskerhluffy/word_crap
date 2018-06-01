/*
 ============================================================================
 Name        : word_crap.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// XXX: http://www.spoj.com/problems/WORDCNT2/
// XXX: http://codeforces.com/blog/entry/48915
#include <stdio.h>
#include <stdlib.h>

#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO (char[1000] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)

typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;
typedef char byteme;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_NIMADRES
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

void caca_log_debug_func(const char *format, ...);

void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

void caca_comun_timestamp(char *stime) {
	time_t ltime;
	struct tm result;
	long ms;
#ifndef ONLINE_JUDGE
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%12d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (int i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

static char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(entero_largo_sin_signo *arreglo,
		entero_largo_sin_signo tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2llu",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	return NULL;
}
static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

static char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif
void caca_comun_strreplace(char s[], char chr, char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

static int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas,
		int *num_columnas, int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

static inline natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

static inline char caca_comun_letra_a_valor_minuscula(char letra) {
	return letra - 'a';
}

static inline natural caca_comun_max_natural(natural *nums, natural nums_tam) {
	natural max = 0;

	for (int i = 0; i < nums_tam; i++) {
		natural num_act = nums[i];
		if (num_act > max) {
			max = num_act;
		}
	}

	return max;
}

#endif
#endif

#if 1

#if 1

#define XXH_PUBLIC_API   /* do nothing */
#define FORCE_INLINE static
#define XXH_FORCE_NATIVE_FORMAT 0

#define XXH_rotl32(x,r) ((x << r) | (x >> (32 - r)))
#define XXH_rotl64(x,r) ((x << r) | (x >> (64 - r)))

typedef uint64_t U64;
typedef uint8_t BYTE;
typedef uint16_t U16;
typedef uint32_t U32;

static const U64 PRIME64_1 = 11400714785074694791ULL;
static const U64 PRIME64_2 = 14029467366897019727ULL;
static const U64 PRIME64_3 = 1609587929392839161ULL;
static const U64 PRIME64_4 = 9650029242287828579ULL;
static const U64 PRIME64_5 = 2870177450012600261ULL;

typedef enum {
	XXH_OK = 0, XXH_ERROR
} XXH_errorcode;

typedef enum {
	XXH_bigEndian = 0, XXH_littleEndian = 1
} XXH_endianess;

typedef struct XXH64_state_s {
	uint64_t total_len;
	uint64_t v1;
	uint64_t v2;
	uint64_t v3;
	uint64_t v4;
	uint64_t mem64[4];
	uint32_t memsize;
	uint32_t reserved[2]; /* never read nor write, might be removed in a future version */
} XXH64_state_t;
/* typedef'd to XXH64_state_t */

typedef enum {
	XXH_aligned, XXH_unaligned
} XXH_alignment;

static void* XXH_malloc(size_t s) {
	return malloc(s);
}
static void XXH_free(void* p) {
	free(p);
}
/*! and for memcpy() */
static void* XXH_memcpy(void* dest, const void* src, size_t size) {
	return memcpy(dest, src, size);
}

static int XXH_isLittleEndian(void) {
	const union {
		U32 u;
		BYTE c[4];
	} one = { 1 }; /* don't use static : performance detrimental  */
	return one.c[0];
}
#define XXH_CPU_LITTLE_ENDIAN   XXH_isLittleEndian()

XXH_PUBLIC_API XXH64_state_t* XXH64_createState(void) {
	return (XXH64_state_t*) XXH_malloc(sizeof(XXH64_state_t));
}

XXH_PUBLIC_API XXH_errorcode XXH64_reset(XXH64_state_t* statePtr,
		unsigned long long seed) {
	XXH64_state_t state; /* using a local state to memcpy() in order to avoid strict-aliasing warnings */
	memset(&state, 0, sizeof(state));
	state.v1 = seed + PRIME64_1 + PRIME64_2;
	state.v2 = seed + PRIME64_2;
	state.v3 = seed + 0;
	state.v4 = seed - PRIME64_1;
	/* do not write into reserved, planned to be removed in a future version */
	memcpy(statePtr, &state, sizeof(state) - sizeof(state.reserved));
	return XXH_OK;
}

static U64 XXH64_round(U64 acc, U64 input) {
	acc += input * PRIME64_2;
	acc = XXH_rotl64(acc, 31);
	acc *= PRIME64_1;
	return acc;
}

static U64 XXH_read64(const void* memPtr) {
	U64 val;
	memcpy(&val, memPtr, sizeof(val));
	return val;
}

static U64 XXH_swap64(U64 x) {
	return ((x << 56) & 0xff00000000000000ULL)
			| ((x << 40) & 0x00ff000000000000ULL)
			| ((x << 24) & 0x0000ff0000000000ULL)
			| ((x << 8) & 0x000000ff00000000ULL)
			| ((x >> 8) & 0x00000000ff000000ULL)
			| ((x >> 24) & 0x0000000000ff0000ULL)
			| ((x >> 40) & 0x000000000000ff00ULL)
			| ((x >> 56) & 0x00000000000000ffULL);
}

FORCE_INLINE U64 XXH_readLE64_align(const void* ptr, XXH_endianess endian,
		XXH_alignment align) {
	if (align == XXH_unaligned)
		return endian == XXH_littleEndian ?
				XXH_read64(ptr) : XXH_swap64(XXH_read64(ptr));
	else
		return endian == XXH_littleEndian ?
				*(const U64*) ptr : XXH_swap64(*(const U64*) ptr);
}

FORCE_INLINE U64 XXH_readLE64(const void* ptr, XXH_endianess endian) {
	return XXH_readLE64_align(ptr, endian, XXH_unaligned);
}

FORCE_INLINE
XXH_errorcode XXH64_update_endian(XXH64_state_t* state, const void* input,
		size_t len, XXH_endianess endian) {
	const BYTE* p = (const BYTE*) input;
	const BYTE* const bEnd = p + len;

	if (input == NULL)
#if defined(XXH_ACCEPT_NULL_INPUT_POINTER) && (XXH_ACCEPT_NULL_INPUT_POINTER>=1)
		return XXH_OK;
#else
		return XXH_ERROR;
#endif

	state->total_len += len;

	if (state->memsize + len < 32) { /* fill in tmp buffer */
		XXH_memcpy(((BYTE*) state->mem64) + state->memsize, input, len);
		state->memsize += (U32) len;
		return XXH_OK;
	}

	if (state->memsize) { /* tmp buffer is full */
		XXH_memcpy(((BYTE*) state->mem64) + state->memsize, input,
				32 - state->memsize);
		state->v1 = XXH64_round(state->v1,
				XXH_readLE64(state->mem64 + 0, endian));
		state->v2 = XXH64_round(state->v2,
				XXH_readLE64(state->mem64 + 1, endian));
		state->v3 = XXH64_round(state->v3,
				XXH_readLE64(state->mem64 + 2, endian));
		state->v4 = XXH64_round(state->v4,
				XXH_readLE64(state->mem64 + 3, endian));
		p += 32 - state->memsize;
		state->memsize = 0;
	}

	if (p + 32 <= bEnd) {
		const BYTE* const limit = bEnd - 32;
		U64 v1 = state->v1;
		U64 v2 = state->v2;
		U64 v3 = state->v3;
		U64 v4 = state->v4;

		do {
			v1 = XXH64_round(v1, XXH_readLE64(p, endian));
			p += 8;
			v2 = XXH64_round(v2, XXH_readLE64(p, endian));
			p += 8;
			v3 = XXH64_round(v3, XXH_readLE64(p, endian));
			p += 8;
			v4 = XXH64_round(v4, XXH_readLE64(p, endian));
			p += 8;
		} while (p <= limit);

		state->v1 = v1;
		state->v2 = v2;
		state->v3 = v3;
		state->v4 = v4;
	}

	if (p < bEnd) {
		XXH_memcpy(state->mem64, p, (size_t) (bEnd - p));
		state->memsize = (unsigned) (bEnd - p);
	}

	return XXH_OK;
}

XXH_PUBLIC_API XXH_errorcode XXH64_update(XXH64_state_t* state_in,
		const void* input, size_t len) {
	XXH_endianess endian_detected = (XXH_endianess) XXH_CPU_LITTLE_ENDIAN;

	if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
		return XXH64_update_endian(state_in, input, len, XXH_littleEndian);
	else
		return XXH64_update_endian(state_in, input, len, XXH_bigEndian);
}

static U64 XXH64_mergeRound(U64 acc, U64 val) {
	val = XXH64_round(0, val);
	acc ^= val;
	acc = acc * PRIME64_1 + PRIME64_4;
	return acc;
}

static U32 XXH_read32(const void* memPtr) {
	U32 val;
	memcpy(&val, memPtr, sizeof(val));
	return val;
}

static U32 XXH_swap32(U32 x) {
	return ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000)
			| ((x >> 8) & 0x0000ff00) | ((x >> 24) & 0x000000ff);
}

FORCE_INLINE U32 XXH_readLE32_align(const void* ptr, XXH_endianess endian,
		XXH_alignment align) {
	if (align == XXH_unaligned)
		return endian == XXH_littleEndian ?
				XXH_read32(ptr) : XXH_swap32(XXH_read32(ptr));
	else
		return endian == XXH_littleEndian ?
				*(const U32*) ptr : XXH_swap32(*(const U32*) ptr);
}

#define XXH_get32bits(p) XXH_readLE32_align(p, endian, align)

#define XXH_get64bits(p) XXH_readLE64_align(p, endian, align)

static U64 XXH64_avalanche(U64 h64) {
	h64 ^= h64 >> 33;
	h64 *= PRIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PRIME64_3;
	h64 ^= h64 >> 32;
	return h64;
}

static U64 XXH64_finalize(U64 h64, const void* ptr, size_t len,
		XXH_endianess endian, XXH_alignment align) {
	const BYTE* p = (const BYTE*) ptr;

#define PROCESS1_64          \
    h64 ^= (*p) * PRIME64_5; \
    p++;                     \
    h64 = XXH_rotl64(h64, 11) * PRIME64_1;

#define PROCESS4_64          \
    h64 ^= (U64)(XXH_get32bits(p)) * PRIME64_1; \
    p+=4;                    \
    h64 = XXH_rotl64(h64, 23) * PRIME64_2 + PRIME64_3;

#define PROCESS8_64 {        \
    U64 const k1 = XXH64_round(0, XXH_get64bits(p)); \
    p+=8;                    \
    h64 ^= k1;               \
    h64  = XXH_rotl64(h64,27) * PRIME64_1 + PRIME64_4; \
}

	switch (len & 31) {
	case 24:
		PROCESS8_64
		;
		/* fallthrough */
	case 16:
		PROCESS8_64
		;
		/* fallthrough */
	case 8:
		PROCESS8_64
		;
		return XXH64_avalanche(h64);

	case 28:
		PROCESS8_64
		;
		/* fallthrough */
	case 20:
		PROCESS8_64
		;
		/* fallthrough */
	case 12:
		PROCESS8_64
		;
		/* fallthrough */
	case 4:
		PROCESS4_64
		;
		return XXH64_avalanche(h64);

	case 25:
		PROCESS8_64
		;
		/* fallthrough */
	case 17:
		PROCESS8_64
		;
		/* fallthrough */
	case 9:
		PROCESS8_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 29:
		PROCESS8_64
		;
		/* fallthrough */
	case 21:
		PROCESS8_64
		;
		/* fallthrough */
	case 13:
		PROCESS8_64
		;
		/* fallthrough */
	case 5:
		PROCESS4_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 26:
		PROCESS8_64
		;
		/* fallthrough */
	case 18:
		PROCESS8_64
		;
		/* fallthrough */
	case 10:
		PROCESS8_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 30:
		PROCESS8_64
		;
		/* fallthrough */
	case 22:
		PROCESS8_64
		;
		/* fallthrough */
	case 14:
		PROCESS8_64
		;
		/* fallthrough */
	case 6:
		PROCESS4_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 27:
		PROCESS8_64
		;
		/* fallthrough */
	case 19:
		PROCESS8_64
		;
		/* fallthrough */
	case 11:
		PROCESS8_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 31:
		PROCESS8_64
		;
		/* fallthrough */
	case 23:
		PROCESS8_64
		;
		/* fallthrough */
	case 15:
		PROCESS8_64
		;
		/* fallthrough */
	case 7:
		PROCESS4_64
		;
		/* fallthrough */
	case 3:
		PROCESS1_64
		;
		/* fallthrough */
	case 2:
		PROCESS1_64
		;
		/* fallthrough */
	case 1:
		PROCESS1_64
		;
		/* fallthrough */
	case 0:
		return XXH64_avalanche(h64);
	}

	/* impossible to reach */
	assert(0);
	return 0; /* unreachable, but some compilers complain without it */
}

FORCE_INLINE U64 XXH64_digest_endian(const XXH64_state_t* state,
		XXH_endianess endian) {
	U64 h64;

	if (state->total_len >= 32) {
		U64 const v1 = state->v1;
		U64 const v2 = state->v2;
		U64 const v3 = state->v3;
		U64 const v4 = state->v4;

		h64 =
				XXH_rotl64(v1,
						1) + XXH_rotl64(v2, 7) + XXH_rotl64(v3, 12) + XXH_rotl64(v4, 18);
		h64 = XXH64_mergeRound(h64, v1);
		h64 = XXH64_mergeRound(h64, v2);
		h64 = XXH64_mergeRound(h64, v3);
		h64 = XXH64_mergeRound(h64, v4);
	} else {
		h64 = state->v3 /*seed*/+ PRIME64_5;
	}

	h64 += (U64) state->total_len;

	return XXH64_finalize(h64, state->mem64, (size_t) state->total_len, endian,
			XXH_aligned);
}

XXH_PUBLIC_API unsigned long long XXH64_digest(const XXH64_state_t* state_in) {
	XXH_endianess endian_detected = (XXH_endianess) XXH_CPU_LITTLE_ENDIAN;

	if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
		return XXH64_digest_endian(state_in, XXH_littleEndian);
	else
		return XXH64_digest_endian(state_in, XXH_bigEndian);
}

FORCE_INLINE U64 XXH64_endian_align(const void* input, size_t len, U64 seed,
		XXH_endianess endian, XXH_alignment align) {
	const BYTE* p = (const BYTE*) input;
	const BYTE* bEnd = p + len;
	U64 h64;

#if defined(XXH_ACCEPT_NULL_INPUT_POINTER) && (XXH_ACCEPT_NULL_INPUT_POINTER>=1)
	if (p==NULL) {
		len=0;
		bEnd=p=(const BYTE*)(size_t)32;
	}
#endif

	if (len >= 32) {
		const BYTE* const limit = bEnd - 32;
		U64 v1 = seed + PRIME64_1 + PRIME64_2;
		U64 v2 = seed + PRIME64_2;
		U64 v3 = seed + 0;
		U64 v4 = seed - PRIME64_1;

		do {
			v1 = XXH64_round(v1, XXH_get64bits(p));
			p += 8;
			v2 = XXH64_round(v2, XXH_get64bits(p));
			p += 8;
			v3 = XXH64_round(v3, XXH_get64bits(p));
			p += 8;
			v4 = XXH64_round(v4, XXH_get64bits(p));
			p += 8;
		} while (p <= limit);

		h64 =
				XXH_rotl64(v1,
						1) + XXH_rotl64(v2, 7) + XXH_rotl64(v3, 12) + XXH_rotl64(v4, 18);
		h64 = XXH64_mergeRound(h64, v1);
		h64 = XXH64_mergeRound(h64, v2);
		h64 = XXH64_mergeRound(h64, v3);
		h64 = XXH64_mergeRound(h64, v4);

	} else {
		h64 = seed + PRIME64_5;
	}

	h64 += (U64) len;

	return XXH64_finalize(h64, p, len, endian, align);
}

#define XXH_FORCE_ALIGN_CHECK 0
XXH_PUBLIC_API unsigned long long XXH64(const void* input, size_t len,
		unsigned long long seed) {
#if 0
	/* Simple version, good for code maintenance, but unfortunately slow for small inputs */
	XXH64_state_t state;
	XXH64_reset(&state, seed);
	XXH64_update(&state, input, len);
	return XXH64_digest(&state);
#else
	XXH_endianess endian_detected = (XXH_endianess) XXH_CPU_LITTLE_ENDIAN;

	if (XXH_FORCE_ALIGN_CHECK) {
		if ((((size_t) input) & 7) == 0) { /* Input is aligned, let's leverage the speed advantage */
			if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
				return XXH64_endian_align(input, len, seed, XXH_littleEndian,
						XXH_aligned);
			else
				return XXH64_endian_align(input, len, seed, XXH_bigEndian,
						XXH_aligned);
		}
	}

	if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
		return XXH64_endian_align(input, len, seed, XXH_littleEndian,
				XXH_unaligned);
	else
		return XXH64_endian_align(input, len, seed, XXH_bigEndian,
				XXH_unaligned);
#endif
}

#endif

typedef natural hm_iter;
#define HASH_MAP_VALOR_INVALIDO ((hm_iter)CACA_COMUN_VALOR_INVALIDO)
typedef struct hash_map_entry {
	const void *llave;
	natural llave_tam;
	entero_largo valor;
} hm_entry;
typedef struct hash_map_cubeta {
	uint64_t hash;
	hm_entry *entry;
} hm_cubeta;
typedef struct hash_map_robin_hood_back_shift {
	hm_cubeta *buckets_;
	uint64_t num_buckets_;
	uint64_t num_buckets_used_;
	uint64_t probing_min_;
	uint64_t probing_max_;
} hm_rr_bs_tabla;

static inline entero_largo_sin_signo hash_map_robin_hood_hashear(
		hm_rr_bs_tabla *ht, byteme *mierda, natural mierda_tam) {
	entero_largo_sin_signo ass = 0;

	ass = XXH64(mierda, mierda_tam, ass) % ht->num_buckets_;
	return ass;
}

int hash_map_robin_hood_back_shift_init(hm_rr_bs_tabla *ht, int num_cubetas) {
	ht->num_buckets_ = num_cubetas;
	ht->buckets_ = (hm_cubeta *) calloc(ht->num_buckets_, sizeof(hm_cubeta));
	ht->num_buckets_used_ = 0;
	ht->probing_max_ = num_cubetas;
	return 0;
}
int hash_map_robin_hood_back_shift_fini(hm_rr_bs_tabla *ht) {
	if (ht->buckets_ != NULL) {
		for (uint32_t i = 0; i < ht->num_buckets_; i++) {
			if (ht->buckets_[i].entry != NULL) {
				free(ht->buckets_[i].entry);
				ht->buckets_[i].entry = NULL;
			}
		}
		free(ht->buckets_);
	}
	return 0;
}
static inline int hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(
		hm_rr_bs_tabla *ht, uint64_t index_stored, uint64_t *distance) {
	hm_cubeta cubeta = ht->buckets_[index_stored];
	*distance = 0;
	if (cubeta.entry == NULL)
		return -1;
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t index_init = cubeta.hash % num_cubetas;
	if (index_init <= index_stored) {
		*distance = index_stored - index_init;
	} else {
		*distance = index_stored + (num_cubetas - index_init);
	}
	return 0;
}
hm_iter hash_map_robin_hood_back_shift_obten(hm_rr_bs_tabla *ht,
		const void *key, natural key_len, entero_largo *value) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	uint64_t probe_distance = 0;
	uint64_t index_current;
	bool found = falso;
	uint32_t i;
	*value = HASH_MAP_VALOR_INVALIDO;
	for (i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		hm_entry *entrada = ht->buckets_[index_current].entry;
		if (entrada == NULL) {
			break;
		}
		hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_current, &probe_distance);
		if (i > probe_distance) {
			break;
		}
		if (!memcmp(entrada->llave, key, entrada->llave_tam)) {
			*value = entrada->valor;
			found = verdadero;
			break;
		}
	}
	if (found)
		return index_current;
	return HASH_MAP_VALOR_INVALIDO;
}
hm_iter hash_map_robin_hood_back_shift_pon(hm_rr_bs_tabla *ht, const void *key,
		natural key_len, entero_largo value, bool *nuevo_entry) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_min_;
	hm_cubeta *cubetas = ht->buckets_;
	*nuevo_entry = verdadero;
	if (ht->num_buckets_used_ == num_cubetas) {
		*nuevo_entry = falso;
		return HASH_MAP_VALOR_INVALIDO;
	}
	ht->num_buckets_used_ += 1;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	hm_entry *entry = (hm_entry *) calloc(1, sizeof(hm_entry));
	entry->llave = key;
	entry->llave_tam = key_len;
	entry->valor = value;
	uint64_t index_current = index_init % num_cubetas;
	uint64_t probe_current = 0;
	uint64_t probe_distance;
	hm_entry *entry_temp;
	uint64_t hash_temp;
	uint64_t i;
	for (i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		hm_cubeta *cubeta = cubetas + index_current;
		if (cubeta->entry == NULL) {
			cubeta->entry = entry;
			cubeta->hash = hash;
			if (index_current > prob_max) {
				ht->probing_max_ = index_current;
			}
			if (index_current < prob_min) {
				ht->probing_min_ = index_current;
			}
			break;
		} else {
			if (!memcmp(cubeta->entry->llave, key, cubeta->entry->llave_tam)) {
				free(entry);
				*nuevo_entry = falso;
				break;
			}
			hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
					index_current, &probe_distance);
			if (probe_current > probe_distance) {
				// Swapping the current bucket with the one to insert
				entry_temp = cubeta->entry;
				hash_temp = cubeta->hash;
				cubeta->entry = entry;
				cubeta->hash = hash;
				entry = entry_temp;
				hash = hash_temp;
				probe_current = probe_distance;
			}
		}
		probe_current++;
	}
	return index_current;
}
int hash_map_robin_hood_back_shift_borra(hm_rr_bs_tabla *ht, const void *key,
		natural key_len) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_max_;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	bool found = falso;
	uint64_t index_current = 0;
	uint64_t probe_distance = 0;
	hm_entry *entrada = NULL;
	for (uint64_t i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		entrada = ht->buckets_[index_current].entry;
		hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_current, &probe_distance);
		if (entrada == NULL || i > probe_distance) {
			break;
		}
		if (!memcmp(entrada->llave, key, entrada->llave_tam)) {
			found = verdadero;
			break;
		}
	}
	if (found) {
		free(entrada);
		uint64_t i = 1;
		uint64_t index_previous = 0, index_swap = 0;
		for (i = 1; i < num_cubetas; i++) {
			index_previous = (index_current + i - 1) % num_cubetas;
			index_swap = (index_current + i) % num_cubetas;
			hm_cubeta *cubeta_swap = ht->buckets_ + index_swap;
			hm_cubeta *cubeta_previous = ht->buckets_ + index_previous;
			if (cubeta_swap->entry == NULL) {
				cubeta_previous->entry = NULL;
				break;
			}
			uint64_t distance;
			if (hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(
					ht, index_swap, &distance) != 0) {
				fprintf(stderr, "Error in FillDistanceToInitIndex()");
			}
			if (!distance) {
				cubeta_previous->entry = NULL;
				break;
			}
			cubeta_previous->entry = cubeta_swap->entry;
			cubeta_previous->hash = cubeta_swap->hash;
		}
		if (i < num_cubetas) {
			if (index_previous == prob_min) {
				prob_min++;
				if (prob_min >= num_cubetas) {
					prob_min = 0;
				} else {
					while (prob_min < num_cubetas
							&& ht->buckets_[prob_min].entry) {
						prob_min++;
					}
					if (prob_min >= num_cubetas) {
						prob_min = num_cubetas;
					}
				}
				ht->probing_min_ = prob_min;
			}
			if (index_previous == prob_max) {
				prob_max--;
				if (prob_max >= num_cubetas) {
					prob_max = num_cubetas;
				} else {
					while (((int64_t) prob_max) >= 0
							&& ht->buckets_[prob_max].entry) {
						prob_max--;
					}
					if (prob_max >= num_cubetas) {
						prob_max = 0;
					}
				}
				ht->probing_max_ = prob_max;
			}
		}
		ht->num_buckets_used_--;
		return 0;
	}
	return 1;
}
static inline int hash_map_robin_hood_back_shift_indice_inicio(
		hm_rr_bs_tabla *ht) {
	return ht->probing_min_;
}
static inline int hash_map_robin_hood_back_shift_indice_final(
		hm_rr_bs_tabla *ht) {
	return ht->probing_max_;
}
static inline bool hash_map_robin_hood_back_shift_indice_existe(
		hm_rr_bs_tabla *ht, hm_iter indice) {
	return !!ht->buckets_[indice].entry;
}
static inline const void *hash_map_robin_hood_back_shift_indice_obten_llave(
		hm_rr_bs_tabla *ht, hm_iter indice) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	hm_entry *entrada = ht->buckets_[indice].entry;
	assert_timeout(entrada);
	return entrada->llave;
}
static inline void hash_map_robin_hood_back_shift_indice_pon_valor(
		hm_rr_bs_tabla *ht, hm_iter indice, entero_largo valor) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	hm_entry *entrada = ht->buckets_[indice].entry;
	assert_timeout(entrada);
	entrada->valor = valor;
}
int hash_map_robin_hood_back_shift_indice_borra(hm_rr_bs_tabla *ht,
		hm_iter indice) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_max_;
	uint64_t index_current = indice;
	hm_entry *entrada = ht->buckets_[index_current].entry;
	assert_timeout(entrada);
	free(entrada);
	uint64_t i = 1;
	uint64_t index_previous = 0, index_swap = 0;
	for (i = 1; i < num_cubetas; i++) {
		index_previous = (index_current + i - 1) % num_cubetas;
		index_swap = (index_current + i) % num_cubetas;
		hm_cubeta *cubeta_swap = ht->buckets_ + index_swap;
		hm_cubeta *cubeta_previous = ht->buckets_ + index_previous;
		if (cubeta_swap->entry == NULL) {
			cubeta_previous->entry = NULL;
			break;
		}
		uint64_t distance;
		if (hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_swap, &distance) != 0) {
			fprintf(stderr, "Error in FillDistanceToInitIndex()");
		}
		if (!distance) {
			cubeta_previous->entry = NULL;
			break;
		}
		cubeta_previous->entry = cubeta_swap->entry;
		cubeta_previous->hash = cubeta_swap->hash;
	}
	if (i < num_cubetas) {
		if (index_previous == prob_min) {
			prob_min++;
			if (prob_min >= num_cubetas) {
				prob_min = 0;
			} else {
				while (prob_min < num_cubetas && ht->buckets_[prob_min].entry) {
					prob_min++;
				}
				if (prob_min >= num_cubetas) {
					prob_min = num_cubetas;
				}
			}
			ht->probing_min_ = prob_min;
		}
		if (index_previous == prob_max) {
			prob_max--;
			if (prob_max >= num_cubetas) {
				prob_max = num_cubetas;
			} else {
				while (((int64_t) prob_max) >= 0 && ht->buckets_[prob_max].entry) {
					prob_max--;
				}
				if (prob_max >= num_cubetas) {
					prob_max = 0;
				}
			}
			ht->probing_max_ = prob_max;
		}
	}
	ht->num_buckets_used_--;
	return 0;
}
static inline entero_largo hash_map_robin_hood_back_shift_indice_obten_valor(
		hm_rr_bs_tabla *ht, hm_iter indice) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	hm_entry *entrada = ht->buckets_[indice].entry;
	assert_timeout(entrada);
	return entrada->valor;
}
static inline bool hash_map_robin_hood_back_shift_esta_vacio(hm_rr_bs_tabla *ht) {
	assert_timeout(ht->num_buckets_used_ <= ht->num_buckets_);
	return !ht->num_buckets_used_;
}

static inline void hash_map_robin_hood_back_shift_reemplazar(hm_rr_bs_tabla *ht,
		entero_largo llave, entero_largo valor) {
	hm_iter iter = 0;
	entero_largo *valor_int = &(entero_largo ) { 0 };

	iter = hash_map_robin_hood_back_shift_obten(ht, llave, valor_int);
	/*
	 if (llave == 99492) {
	 printf("llave %lu tiene orig valor %lu despues %lu\n", llave, valor_int,
	 valor);
	 assert_timeout(valor != 99480);
	 }
	 */

	assert_timeout(iter!=HASH_MAP_VALOR_INVALIDO);

	hash_map_robin_hood_back_shift_indice_pon_valor(ht, iter, valor);
}

static inline void hash_map_robin_hood_back_shift_insertar_nuevo(
		hm_rr_bs_tabla *ht, entero_largo llave, entero_largo valor) {
	hm_iter iter = 0;
	bool nuevo = falso;
	iter = hash_map_robin_hood_back_shift_pon(ht, llave, valor, &nuevo);

	assert_timeout(iter!=HASH_MAP_VALOR_INVALIDO);
	assert_timeout(nuevo);
}

#endif

#if 1

//http://www.thelearningpoint.net/computer-science/data-structures-heaps-with-c-program-source-code
#define HEAP_SHIT_MAX_NODOS (300002)
#define HEAP_SHIT_MAX_LLAVES HUARONVERGA_MAX_LLAVE
#define HEAP_SHIT_VALOR_INVALIDO ((entero_largo_sin_signo)(((entero_largo_sin_signo)CACA_COMUN_VALOR_INVALIDO)<<32 | CACA_COMUN_VALOR_INVALIDO))

typedef struct heap_shit_nodo {
	void *valor;
} heap_shit_nodo;
typedef struct heap_shit heap_shit;

typedef int (*heap_shit_compara_prioridad)(void *a, void *b);
typedef int (*heap_shit_compara_llave)(void *valor);
typedef entero_largo (*heap_shit_obten_llave)(void *valor);

struct heap_shit {
	bool min;
	natural heap_size;
	heap_shit_nodo heap[HEAP_SHIT_MAX_NODOS];
	hm_rr_bs_tabla *tablon_llave_a_idx_heap;
	heap_shit_compara_llave compara_llave_fn;
	heap_shit_compara_prioridad compara_prioridad_fn;
	heap_shit_obten_llave obten_llave_fn;
};

/*Initialize Heap*/
static inline heap_shit *heap_shit_init(bool es_min,
		heap_shit_compara_llave compara_llave_fn,
		heap_shit_compara_prioridad compara_prioridad_fn,
		heap_shit_obten_llave obten_llave_fn) {
	heap_shit *heap = calloc(1, sizeof(heap_shit));
	assert_timeout(heap);
	heap->heap_size = 0;
	heap->min = es_min;
	heap->compara_llave_fn = compara_llave_fn;
	heap->compara_prioridad_fn = compara_prioridad_fn;
	heap->obten_llave_fn = obten_llave_fn;
	memset(heap->heap, HEAP_SHIT_VALOR_INVALIDO, sizeof(heap->heap));
	heap->tablon_llave_a_idx_heap = calloc(1, sizeof(hm_rr_bs_tabla));
	assert_timeout(heap->tablon_llave_a_idx_heap);
	hash_map_robin_hood_back_shift_init(heap->tablon_llave_a_idx_heap,
	HEAP_SHIT_MAX_NODOS);
	return heap;
}

void heap_shit_fini(heap_shit *heap_ctx) {
	hash_map_robin_hood_back_shift_fini(heap_ctx->tablon_llave_a_idx_heap);
	free(heap_ctx->tablon_llave_a_idx_heap);
	free(heap_ctx);
}

static inline bool heap_shit_nodo_valido(heap_shit_nodo *nodo) {
	return nodo->valor != (void *) HEAP_SHIT_VALOR_INVALIDO;
}

static inline void heap_shit_valida_nodos(heap_shit *heap_ctx) {
	for (int i = 1; i <= heap_ctx->heap_size; i++) {
		assert_timeout(heap_shit_nodo_valido(heap_ctx->heap + i));
	}
}

static inline natural heap_shit_idx_padre(natural idx_nodo) {
	return idx_nodo >> 1;
}

static inline natural heap_shit_idx_hijo_izq(natural idx_nodo) {
	return idx_nodo << 1;
}

/*Insert an element into the heap */
static inline void heap_shit_insert(heap_shit *heap_ctx,
		heap_shit_nodo *nodo_nuevo) {
	natural heap_size = heap_ctx->heap_size;
	heap_shit_nodo *heap = NULL;
	hm_rr_bs_tabla *mapeo_inv = heap_ctx->tablon_llave_a_idx_heap;
	bool nuevo;

	heap = heap_ctx->heap;

	heap_size++;
	heap[heap_size] = *nodo_nuevo; /*Insert in the last place*/
	/*Adjust its position*/
	natural now = heap_size;

	while (heap_shit_nodo_valido(heap + heap_shit_idx_padre(now))
			&& ((heap_ctx->min
					&& heap_ctx->compara_prioridad_fn(
							heap[heap_shit_idx_padre(now)].valor,
							nodo_nuevo->valor) > 0)

					|| (!heap_ctx->min
							&& heap_ctx->compara_prioridad_fn(
									heap[heap_shit_idx_padre(now)].valor,
									nodo_nuevo->valor) < 0

					))) {
//printf("caca now %u de heap %u elem %u\n",now,heap[now],element);
		natural idx_padre = heap_shit_idx_padre(now);
		entero_largo llave_padre = heap_ctx->obten_llave_fn(
				heap[idx_padre].valor);
		assert_timeout(llave_padre!= HEAP_SHIT_VALOR_INVALIDO);

		heap[now] = heap[idx_padre];
		hash_map_robin_hood_back_shift_reemplazar(mapeo_inv, llave_padre, now);
		caca_log_debug("llave %d tiene valor %u ", llave_padre, now);

		now = idx_padre;
	}
//printf("raise now %u con heap %u y elem %u res %u\n",now,heap[now / 2],element, (unsigned int)heap[now / 2]>(unsigned int)element);

	heap[now] = *nodo_nuevo;
	hash_map_robin_hood_back_shift_insertar_nuevo(mapeo_inv,
			heap_ctx->obten_llave_fn(nodo_nuevo->valor), now);

	heap_ctx->heap_size = heap_size;
	assert_timeout(heap_size >= now);
//	heap_shit_valida_nodos(heap_ctx);
}

/*
 tipo_dato prioridad;
 tipo_dato llave;
 void *valor;
 */
#define heap_shit_insertar(heap_ctx,valor_in) heap_shit_insert(heap_ctx,&(heap_shit_nodo) {.valor=valor_in})
#define heap_shit_insertar_valor_unico(heap_ctx,valor) heap_shit_insertar(heap_ctx,valor,valor,(void *)((entero_largo)valor))

static inline void *heap_shit_delete(heap_shit *heap_ctx, natural idx_a_borrar) {
	natural heap_size = heap_ctx->heap_size;
	natural child, now;
	heap_shit_nodo minElement = { 0 };
	heap_shit_nodo lastElement = { 0 };
	heap_shit_nodo *heap;
	hm_rr_bs_tabla *mapeo_inv = heap_ctx->tablon_llave_a_idx_heap;
	void *resultado;
	bool nuevo;

	heap = heap_ctx->heap;

	assert_timeout(heap_size >= idx_a_borrar);
	assert_timeout(idx_a_borrar);

	/* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.
	 Now heap[1] has to be filled. We put the last element in its place and see if it fits.
	 If it does not fit, take minimum element among both its children and replaces parent with it.
	 Again See if the last element fits in that place.*/
	minElement = heap[idx_a_borrar];
	resultado = minElement.valor;
	lastElement = heap[heap_size--];

	now = idx_a_borrar;
	if (idx_a_borrar != heap_size + 1) {
		if (heap_shit_nodo_valido(heap + heap_shit_idx_padre(now))
				&& ((heap_ctx->min
						&& heap_ctx->compara_prioridad_fn(
								heap[heap_shit_idx_padre(now)].valor,
								lastElement.valor) > 0)
						|| (!heap_ctx->min
								&& (heap_ctx->compara_prioridad_fn(
										heap[heap_shit_idx_padre(now)].valor,
										lastElement.valor))))) {

			while (heap_shit_nodo_valido(heap + heap_shit_idx_padre(now))
					&& ((heap_ctx->min
							&& heap_ctx->compara_prioridad_fn(
									heap[heap_shit_idx_padre(now)].valor,
									lastElement.valor) > 0)
							|| (!heap_ctx->min
									&& (heap_ctx->compara_prioridad_fn(
											heap[heap_shit_idx_padre(now)].valor,
											lastElement.valor) < 0)))) {
				assert_timeout(now <= heap_size);
				natural idx_padre = heap_shit_idx_padre(now);
				entero_largo llave_padre = heap_ctx->obten_llave_fn(
						heap[idx_padre].valor);

				assert_timeout(llave_padre != HEAP_SHIT_VALOR_INVALIDO);

				heap[now] = heap[idx_padre];

				hash_map_robin_hood_back_shift_reemplazar(mapeo_inv,
						llave_padre, now);

				caca_log_debug("llave %d tiene valor %u", llave_padre, now);

				now = idx_padre;
			}
		} else {

			/* now refers to the index at which we are now */
			for (now = idx_a_borrar; heap_shit_idx_hijo_izq(now) <= heap_size;
					now = child) {
				/* child is the index of the element which is minimum among both the children */
				/* Indexes of children are i*2 and i*2 + 1*/
				child = heap_shit_idx_hijo_izq(now);
				assert_timeout(child <= heap_size);
				/*child!=heap_size beacuse heap[heap_size+1] does not exist, which means it has only one
				 child */
				if (child != heap_size
						&& ((heap_ctx->min
								&& heap_ctx->compara_prioridad_fn(
										heap[child + 1].valor,
										heap[child].valor) < 0)
								|| (!heap_ctx->min
										&& heap_ctx->compara_prioridad_fn(
												heap[child + 1].valor,
												heap[child].valor) > 0))) {
					child++;
				}
				assert_timeout(child <= heap_size);
				/* To check if the last element fits ot not it suffices to check if the last element
				 is less than the minimum element among both the children*/
				//printf("last %u heap %u\n",lastElement,heap[child]);
				if ((heap_ctx->min
						&& heap_ctx->compara_prioridad_fn(lastElement.valor,
								heap[child].valor) > 0)
						|| (!heap_ctx->min
								&& heap_ctx->compara_prioridad_fn(
										lastElement.valor, heap[child].valor))) {
					heap[now] = heap[child];

					hash_map_robin_hood_back_shift_reemplazar(mapeo_inv,
							heap_ctx->obten_llave_fn(heap[child].valor), now);
					caca_log_debug("llave %d tiene valor %u",
							heap_ctx->obten_llave_fn(heap[child].valor), now);
				} else /* It fits there */
				{
					break;
				}
			}
		}
	}

	hash_map_robin_hood_back_shift_borra(mapeo_inv,
			heap_ctx->obten_llave_fn(minElement.valor));
	caca_log_debug("borrada llave %d",
			heap_ctx->obten_llave_fn( minElement.valor));
	if (heap_size && idx_a_borrar != heap_size + 1) {
		assert_timeout(now <= heap_size);
		heap[now] = lastElement;
		hash_map_robin_hood_back_shift_reemplazar(mapeo_inv,
				heap_ctx->obten_llave_fn(lastElement.valor), now);
		caca_log_debug("llave %d tiene valor %u ",
				heap_ctx->obten_llave_fn(lastElement.valor), now);
	}
	heap_ctx->heap_size = heap_size;
	//heap_shit_valida_nodos(heap_ctx);
	return resultado;
}

static inline void *heap_shit_borrar_directo(heap_shit *heap_ctx,
		tipo_dato llave) {
	natural heap_size = heap_ctx->heap_size;
	hm_rr_bs_tabla *indices_valores = heap_ctx->tablon_llave_a_idx_heap;
	entero_largo idx_a_borrar;

	assert_timeout(heap_size);

	natural idx_hm = hash_map_robin_hood_back_shift_obten(indices_valores,
			llave, &idx_a_borrar);
	assert_timeout(idx_a_borrar <= heap_size);
	caca_log_debug("borrando llave %d en idx %u en idx hm %u con heap size %u",
			llave, idx_a_borrar, idx_hm, heap_size);
	assert_timeout(idx_hm!=HASH_MAP_VALOR_INVALIDO);
	assert_timeout(idx_a_borrar != HEAP_SHIT_VALOR_INVALIDO);

	return heap_shit_delete(heap_ctx, idx_a_borrar);
}

static inline void *heap_shit_borra_torpe(heap_shit *heap_ctx) {
	if (heap_ctx->heap_size) {
		return heap_shit_borrar_directo(heap_ctx,
				heap_ctx->obten_llave_fn(heap_ctx->heap[1].valor));
	} else {
		assert_timeout(!heap_ctx->heap[0].valor);
		return NULL;
	}
}

static inline void heap_shit_actualiza(heap_shit *ctx, void *valor) {
	entero_largo llave = ctx->obten_llave_fn(valor);
	heap_shit_borrar_directo(ctx, llave);
	heap_shit_insertar(ctx, valor);
}
#endif

#if 1

typedef struct my_struct {
	void *valor;
	struct my_struct* next;
} listilla_nodo;

typedef struct my_list {
	struct my_struct* head;
	struct my_struct* tail;
	natural elementos_cnt;
} listilla_fifo;

typedef struct listilla_iterador {
	listilla_fifo *ctx;
	listilla_nodo *nodo_act;
	bool primera_llamada;
	natural llamadas;
} listilla_iterador;

/* Will always return the pointer to my_list */
struct my_list* list_add_element(struct my_list* s, void *valor) {
	struct my_struct* p = malloc(1 * sizeof(*p));

	if ( NULL == p) {
		fprintf(stderr, "IN %s, %s: malloc() failed\n", __FILE__, "list_add");
		return s;
	}

	p->valor = valor;
	p->next = NULL;

	if ( NULL == s) {
		printf("Queue not initialized\n");
		free(p);
		return s;
	} else if ( NULL == s->head && NULL == s->tail) {
		/* printf("Empty list, adding p->num: %d\n\n", p->num);  */
		s->head = s->tail = p;
		return s;
	} else if ( NULL == s->head || NULL == s->tail) {
		fprintf(stderr,
				"There is something seriously wrong with your assignment of head/tail to the list\n");
		free(p);
		return NULL;
	} else {
		/* printf("List not empty, adding element to tail\n"); */
		s->tail->next = p;
		s->tail = p;
	}
	s->elementos_cnt++;

	return s;
}

/* This is a queue and it is FIFO, so we will always remove the first element */
static void *list_remove_element(struct my_list* s) {
	struct my_struct* h = NULL;
	struct my_struct* p = NULL;
	void *valor = NULL;

	if ( NULL == s) {
		printf("List is empty\n");
		return s;
	} else if ( NULL == s->head && NULL == s->tail) {
		printf("Well, List is empty\n");
		return s;
	} else if ( NULL == s->head || NULL == s->tail) {
		printf("There is something seriously wrong with your list\n");
		printf("One of the head/tail is empty while other is not \n");
		abort();
	}

	h = s->head;
	valor = h->valor;
	p = h->next;
	free(h);
	s->head = p;
	if ( NULL == s->head)
		s->tail = s->head; /* The element tail was pointing to is free(), so we need an update */

	s->elementos_cnt--;
	return valor;
}

/* ---------------------- small helper fucntions ---------------------------------- */
struct my_list* list_free(struct my_list* s) {
	while (s->head) {
		list_remove_element(s);
	}

	return s;
}

struct my_list* list_new(void) {
	struct my_list* p = malloc(1 * sizeof(*p));

	assert_timeout(p);

	p->head = p->tail = NULL;

	return p;
}

void list_print_element(const struct my_struct* p) {
	if (p) {
		printf("Num = %p\n", p->valor);
	} else {
		printf("Can not print NULL struct \n");
	}
}

void list_print(const struct my_list* ps) {
	struct my_struct* p = NULL;

	if (ps) {
		for (p = ps->head; p; p = p->next) {
			list_print_element(p);
		}
	}

	printf("------------------\n");
}

static bool list_empty(struct my_list *s) {
	return !s->head;
}

static void list_iterador_init(listilla_fifo *ctx, listilla_iterador *iter) {
	assert_timeout(!iter->ctx);
	assert_timeout(!iter->primera_llamada);
	assert_timeout(!iter->nodo_act);
	assert_timeout(!iter->llamadas);
	iter->ctx = ctx;
	iter->nodo_act = NULL;
	iter->primera_llamada = verdadero;
	iter->llamadas = 0;
}
static void list_iterador_fini(listilla_iterador *iter) {
	iter->ctx = NULL;
	iter->nodo_act = NULL;
	iter->primera_llamada = falso;
	iter->llamadas = 0;
}

static void *list_iterador_peekea_actual(listilla_iterador *iter) {
	return iter->nodo_act ? iter->nodo_act->valor : NULL;
}

static void *list_iterador_obten_siguiente(listilla_iterador *iter) {
	if (iter->nodo_act) {
		iter->nodo_act = iter->nodo_act->next;
	} else {
		if (iter->primera_llamada) {
			iter->primera_llamada = falso;
			iter->nodo_act = iter->ctx->head;
		}
	}
	if (iter->nodo_act) {
		iter->llamadas++;
	}
	return iter->nodo_act ? iter->nodo_act->valor : NULL;
}
static void *list_iterador_hay_siguiente(listilla_iterador *iter) {
	listilla_nodo *siguiente = NULL;
	if (!iter->nodo_act) {
		if (iter->primera_llamada) {
			siguiente = iter->ctx->head;
		}
	} else {
		siguiente = iter->nodo_act->next;
	}

	return siguiente ? siguiente->valor : NULL;
}

static bool list_iterador_esta_initializado(listilla_iterador *iter) {
	return !!iter->ctx;
}

#endif

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}