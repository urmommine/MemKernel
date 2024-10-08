#ifndef MEMKERNEL_MEM_H
#define MEMKERNEL_MEM_H

#include <linux/kernel.h>
#include <linux/sched.h>

#define MAX_MEMOP_SIZE 4096 * 2

phys_addr_t translate_linear_address(struct mm_struct *mm, uintptr_t va);

bool read_physical_address(phys_addr_t pa, void *buffer, size_t size);

bool write_physical_address(phys_addr_t pa, void *buffer, size_t size);

bool read_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size);

bool write_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size);

#endif