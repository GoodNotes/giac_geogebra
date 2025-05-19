#ifndef GIAC_BRIDGE_H
#define GIAC_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
  #define EXPORT_API __declspec(dllexport)
#else
  #define EXPORT_API __attribute__ ((visibility ("default")))
#endif

EXPORT_API void test(void);
EXPORT_API const char* getLastError(void);
EXPORT_API void clearLastError(void);
EXPORT_API void* Context_create(void);
EXPORT_API void Context_destroy(void* ctx);
EXPORT_API void* Gen_createFromString(void* ctx, const char* expression);
//EXPORT_API void* Gen_createFromInt(void* ctx, int value);
//EXPORT_API void* Gen_createFromDouble(void* ctx, double value);
EXPORT_API void Gen_destroy(void* gen);
EXPORT_API void Gen_selfEval(void* ctx, void* gen, int level);
EXPORT_API void* Gen_eval(void* ctx, void* gen, int level);
EXPORT_API const char* Gen_print(void* ctx, void* gen);
EXPORT_API int Gen_type(void* gen);
EXPORT_API int Gen_length(void* gen);
EXPORT_API int Gen_isNull(void* gen);
EXPORT_API int Gen_equalSign(void* a, void* b);
EXPORT_API int Gen_getListSize(void* gen);
EXPORT_API void* Gen_getListElement(void* ctx, void* gen, int index);
EXPORT_API const char* Gen_lname(void* gen);
EXPORT_API void* Gen_left(void* ctx, void* gen);
EXPORT_API void* Gen_right(void* ctx, void* gen);
EXPORT_API void* Gen_add(void* ctx, void* a, void* b);
EXPORT_API void* Gen_sub(void* ctx, void* a, void* b);
EXPORT_API void* Gen_mul(void* ctx, void* a, void* b);
EXPORT_API void* Gen_div(void* ctx, void* a, void* b);
EXPORT_API void* Gen_negate(void* ctx, void* gen);
EXPORT_API void* Gen_simplify(void* ctx, void* gen);
EXPORT_API void* Gen_canonicalForm(void* ctx, void* gen);
EXPORT_API void* Gen_regroup(void* ctx, void* gen);
EXPORT_API void Gen_resetTimeout(void* gen);

#ifdef __cplusplus
}
#endif

#endif // GIAC_BRIDGE_H
