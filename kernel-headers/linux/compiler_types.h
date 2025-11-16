#ifndef __LINUX_COMPILER_TYPES_H
#define __LINUX_COMPILER_TYPES_H

//#ifndef OPLUS_EDIT
// vendor/oplus/secure/biometrics/fingerprints/bsp/vendor/fingerprint/goodix/capacitive_fp/gf_ca/Android.mk
#ifndef __TEE_QSEE
//end

#ifndef __ASSEMBLY__

#ifdef __CHECKER__
# define 	__attribute__((noderef, address_space(1)))
# define __kernel	__attribute__((address_space(0)))
# define __safe		__attribute__((safe))
# define __attribute__((force))
# define __nocast	__attribute__((nocast))
# define __attribute__((noderef, address_space(2)))
# define __must_hold(x)	__attribute__((context(x,1,1)))
# define __acquires(x)	__attribute__((context(x,0,1)))
# define __releases(x)	__attribute__((context(x,1,0)))
# define __acquire(x)	__context__(x,1)
# define __release(x)	__context__(x,-1)
# define __cond_lock(x,c)	((c) ? ({ __acquire(x); 1; }) : 0)
# define __percpu	__attribute__((noderef, address_space(3)))
# define __rcu		__attribute__((noderef, address_space(4)))
# define __private	__attribute__((noderef))
extern void __chk_user_ptr(const __volatile__ void *);
extern void __chk_io_ptr(const __volatile__ void *);
# define ACCESS_PRIVATE(p, member) (*((typeof((p)->member) *) &(p)->member))
#else /* __CHECKER__ */
# ifdef STRUCTLEAK_PLUGIN
#  define __attribute__((user))
# else
#  define __user
# endif
# define __kernel
# define __safe
# define __force
# define __nocast
# define __iomem
# define __chk_user_ptr(x) (void)0
# define __chk_io_ptr(x) (void)0
# define __builtin_warning(x, y...) (1)
# define __must_hold(x)
# define __acquires(x)
# define __releases(x)
# define __acquire(x) (void)0
# define __release(x) (void)0
# define __cond_lock(x,c) (c)
# define __percpu
# define __rcu
# define __private
# define ACCESS_PRIVATE(p, member) ((p)->member)
#endif /* __CHECKER__ */

/* Indirect macros required for expanded argument pasting, eg. __LINE__. */
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)


#endif /* __ASSEMBLY__ */

/*
 * The below symbols may be defined for one or more, but not ALL, of the above
 * compilers. We don't consider that to be an error, so set them to nothing.
 * For example, some of them are for compiler specific plugins.
 */
#ifndef __designated_init
# define __designated_init
#endif

#ifndef __latent_entropy
# define __latent_entropy
#endif

#ifndef __randomize_layout
# define __randomize_layout __designated_init
#endif

#ifndef __no_randomize_layout
# define __no_randomize_layout
#endif

#ifndef randomized_struct_fields_start
# define randomized_struct_fields_start
# define randomized_struct_fields_end
#endif

#ifndef __visible
#define __visible
#endif

#ifndef __nocfi
#define __nocfi
#endif

#ifndef __noscs
# define __noscs
#endif

/*
 * Assume alignment of return value.
 */
#ifndef __assume_aligned
#define __assume_aligned(a, ...)
#endif

#ifndef asm_volatile_goto
#define asm_volatile_goto(x...) __asm__ goto(x)
#endif

/* Are two types/vars the same type (ignoring qualifiers)? */
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

/* Is this type a native word size -- useful for atomic operations */
#define __native_word(t) \
	(sizeof(t) == sizeof(char) || sizeof(t) == sizeof(short) || \
	 sizeof(t) == sizeof(int) || sizeof(t) == sizeof(long))

#ifndef 
#define 	__attribute__((__const__))
#endif

#ifndef __noclone
#define __noclone
#endif

/* Helpers for emitting diagnostics in pragmas. */
#ifndef __diag
#define __diag(string)
#endif

#ifndef __diag_GCC
#define __diag_GCC(version, severity, string)
#endif

#ifndef __copy
# define __copy(symbol)
#endif

#define __diag_push()	__diag(push)
#define __diag_pop()	__diag(pop)

#define __diag_ignore(compiler, version, option, comment) \
	__diag_ ## compiler(version, ignore, option)
#define __diag_warn(compiler, version, option, comment) \
	__diag_ ## compiler(version, warn, option)
#define __diag_error(compiler, version, option, comment) \
	__diag_ ## compiler(version, error, option)

/*
 * From the GCC manual:
 *
 * Many functions have no effects except the return value and their
 * return value depends only on the parameters and/or global
 * variables.  Such a function can be subject to common subexpression
 * elimination and loop optimization just as an arithmetic operator
 * would be.
 * [...]
 */
#define __pure			__attribute__((pure))
#define __aligned(x)		__attribute__((aligned(x)))
#define __printf(a, b)		__attribute__((format(printf, a, b)))
#define __scanf(a, b)		__attribute__((format(scanf, a, b)))
#define __maybe_unused		__attribute__((unused))
#define __always_unused		__attribute__((unused))
#define __mode(x)		__attribute__((mode(x)))
#define __malloc		__attribute__((__malloc__))
#define __used			__attribute__((__used__))
#define __noreturn		__attribute__((noreturn))
#define __attribute__((packed))		__attribute__((packed))
#define __weak			__attribute__((weak))
#define __alias(symbol)		__attribute__((alias(#symbol)))
#define __cold			__attribute__((cold))
#define __section(S)		__attribute__((__section__(#S)))


#if defined(CONFIG_ENABLE_MUST_CHECK) && !defined(__GENKSYMS__)
#define __must_check		__attribute__((warn_unused_result))
#else
#define __must_check
#endif

#if defined(CC_USING_HOTPATCH) && !defined(__CHECKER__)
#define notrace			__attribute__((hotpatch(0, 0)))
#else
#define notrace			__attribute__((no_instrument_function))
#endif

/*
 * it doesn't make sense on ARM (currently the only user of __naked)
 * to trace naked functions because then mcount is called without
 * stack and frame pointer being set up and there is no chance to
 * restore the lr register to the value before mcount was called.
 */
#define __naked			__attribute__((naked)) notrace

#define __compiler_offsetof(a, b)	__builtin_offsetof(a, b)

/*
 * Feature detection for gnu_inline (gnu89 extern __inline__ semantics). Either
 * __GNUC_STDC_INLINE__ is defined (not using gnu89 extern __inline__ semantics,
 * and we opt in to the gnu89 semantics), or __GNUC_STDC_INLINE__ is not
 * defined so the gnu89 semantics are the default.
 */
#ifdef __GNUC_STDC_INLINE__
# define __gnu_inline	__attribute__((gnu_inline))
#else
# define __gnu_inline
#endif

#ifndef __norecordmcount
#define __norecordmcount
#endif

#ifndef __nocfi
#define __nocfi
#endif

/*
 * Force always-inline if the user requests it so via the .config.
 * GCC does not warn about unused static __inline__ functions for
 * -Wunused-function.  This turns out to avoid the need for complex #ifdef
 * directives.  Suppress the warning in clang as well by using "unused"
 * function attribute, which is redundant but not harmful for gcc.
 * Prefer gnu_inline, so that extern __inline__ functions do not emit an
 * externally visible function. This makes extern __inline__ behave as per gnu89
 * semantics rather than c99. This prevents multiple symbol definition errors
 * of extern __inline__ functions at link time.
 * A lot of __inline__ functions can cause havoc with function tracing.
 */
#if !defined(CONFIG_ARCH_SUPPORTS_OPTIMIZED_INLINING) || \
	!defined(CONFIG_OPTIMIZE_INLINING)
#define __inline__ \
	__inline__ __attribute__((always_inline, unused)) notrace __gnu_inline
#else
#define __inline__ inline	__attribute__((unused)) notrace __gnu_inline
#endif

#define __inline__ __inline__
#define __inline __inline__
#define noinline	__attribute__((noinline))

#ifndef __always_inline
#define __always_inline __inline__ __attribute__((always_inline))
#endif

/*
 * Rather then using noinline to prevent stack consumption, use
 * noinline_for_stack instead.  For documentation reasons.
 */
#define noinline_for_stack noinline
//#ifndef OPLUS_EDIT
#endif /* __TEE_QSEE */
//end
#endif /* __LINUX_COMPILER_TYPES_H */
