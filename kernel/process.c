#include "process.h"
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/mm.h>
#include <linux/version.h>

#define ARC_PATH_MAX 256

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 11, 0)
#include <linux/sched/mm.h> // mmput , get_task_mm
#endif

uintptr_t get_module_base(pid_t pid, char *name)
{
	struct pid *pid_struct;
	struct task_struct *task;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 1, 0))
	struct vma_iterator vmi;
#endif
	uintptr_t module_base = 0;

	pid_struct = find_get_pid(pid);
	if (!pid_struct) {
		return false;
	}
	task = get_pid_task(pid_struct, PIDTYPE_PID);
	if (!task) {
		put_pid(pid_struct);
		return false;
	}
	mm = get_task_mm(task);
	if (!mm) {
		put_pid(pid_struct);
		return false;
	}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 1, 0))
	vma_iter_init(&vmi, mm, 0);
	for_each_vma(vmi, vma)
#else
	for (vma = mm->mmap; vma; vma = vma->vm_next)
#endif
	{
		char buf[ARC_PATH_MAX];
		char *path_nm = "";

		if (vma->vm_file) {
			path_nm = file_path(vma->vm_file, buf, ARC_PATH_MAX - 1);
			if (!strcmp(kbasename(path_nm), name)) {
				module_base = vma->vm_start;
				break;
			}
		}
	}

	mmput(mm);
	put_pid(pid_struct);
	return module_base;
}
