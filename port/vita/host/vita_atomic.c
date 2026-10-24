/*
 * Tiny VitaSDK fallback for GCC/Clang out-of-line integer atomics.
 *
 * The VitaSDK 2026.08 container ships an ARM GCC without libatomic.a.
 * Clang emits these runtime calls for shared 16/32-bit values, although
 * the Cortex-A9 can perform the operations with ARM exclusive accesses.
 *
 * Use GCC's legacy __sync builtins, which the Cortex-A9 toolchain expands
 * to hardware-exclusive instructions, and give all calls full-barrier
 * semantics (stronger than the requested C11 ordering).
 *
 * Function identifiers avoid the __atomic_* builtin spelling; the asm
 * aliases provide the exact external libatomic ABI symbols.
 */
#include <stdint.h>
#include <stdbool.h>

uint16_t vita_atomic_load_2(const volatile uint16_t *ptr, int order) __asm__("__atomic_load_2");
uint32_t vita_atomic_load_4(const volatile uint32_t *ptr, int order) __asm__("__atomic_load_4");
void vita_atomic_store_4(volatile uint32_t *ptr, uint32_t value, int order) __asm__("__atomic_store_4");
uint32_t vita_atomic_exchange_4(volatile uint32_t *ptr, uint32_t value, int order) __asm__("__atomic_exchange_4");
bool vita_atomic_compare_exchange_4(volatile uint32_t *ptr, uint32_t *expected, uint32_t desired,
	int success_order, int failure_order) __asm__("__atomic_compare_exchange_4");
uint16_t vita_atomic_fetch_and_2(volatile uint16_t *ptr, uint16_t mask, int order) __asm__("__atomic_fetch_and_2");
uint16_t vita_atomic_fetch_or_2(volatile uint16_t *ptr, uint16_t mask, int order) __asm__("__atomic_fetch_or_2");

uint16_t vita_atomic_load_2(const volatile uint16_t *ptr, int order)
{
	uint16_t value;
	(void)order;
	__sync_synchronize();
	value = *ptr;
	__sync_synchronize();
	return value;
}

uint32_t vita_atomic_load_4(const volatile uint32_t *ptr, int order)
{
	uint32_t value;
	(void)order;
	__sync_synchronize();
	value = *ptr;
	__sync_synchronize();
	return value;
}

void vita_atomic_store_4(volatile uint32_t *ptr, uint32_t value, int order)
{
	(void)order;
	__sync_synchronize();
	*ptr = value;
	__sync_synchronize();
}

uint32_t vita_atomic_exchange_4(volatile uint32_t *ptr, uint32_t value, int order)
{
	uint32_t old;
	(void)order;
	__sync_synchronize();
	old = __sync_lock_test_and_set(ptr, value);
	__sync_synchronize();
	return old;
}

bool vita_atomic_compare_exchange_4(volatile uint32_t *ptr, uint32_t *expected, uint32_t desired,
	int success_order, int failure_order)
{
	uint32_t old;
	(void)success_order;
	(void)failure_order;
	old = __sync_val_compare_and_swap(ptr, *expected, desired);
	if (old == *expected)
		return true;
	*expected = old;
	return false;
}

uint16_t vita_atomic_fetch_and_2(volatile uint16_t *ptr, uint16_t mask, int order)
{
	(void)order;
	return __sync_fetch_and_and(ptr, mask);
}

uint16_t vita_atomic_fetch_or_2(volatile uint16_t *ptr, uint16_t mask, int order)
{
	(void)order;
	return __sync_fetch_and_or(ptr, mask);
}
