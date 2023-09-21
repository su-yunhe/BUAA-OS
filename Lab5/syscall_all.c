
/* Overview:
 *  This function is used to write data at 'va' with length 'len' to a device physical address
 *  'pa'. Remember to check the validity of 'va' and 'pa' (see Hint below);
 *
 *  'va' is the starting address of source data, 'len' is the
 *  length of data (in bytes), 'pa' is the physical address of
 *  the device (maybe with a offset).
 *
 * Post-Condition:
 *  Data within [va, va+len) is copied to the physical address 'pa'.
 *  Return 0 on success.
 *  Return -E_INVAL on bad address.
 *
 * Hint: Use the unmapped and uncached segment in kernel address space (KSEG1) to perform MMIO.
 * Hint: You can use 'is_illegal_va_range' to validate 'va'.
 * Hint: You MUST use 'memcpy' to copy data after checking the validity.
 *
 *  All valid device and their physical address ranges:
 *	* ---------------------------------*
 *	|   device   | start addr | length |
 *	* -----------+------------+--------*
 *	|  console   | 0x10000000 | 0x20   | (dev_cons.h)
 *	|  IDE disk  | 0x13000000 | 0x4200 | (dev_disk.h)
 *	|    rtc     | 0x15000000 | 0x200  | (dev_rtc.h)
 *	* ---------------------------------*
 */
int sys_write_dev(u_int va, u_int pa, u_int len) {
	/* Exercise 5.1: Your code here. (1/2) */
	if (is_illegal_va_range(va, len)) {
		return -E_INVAL;
	}
	
	if (!((va >= 0x10000000 && len <= 0x20) || (va >= 0x13000000 && len <= 0x4200) || (va >= 0x15000000 && len <= 0x200))) {
		return -E_INVAL;
	}

	memcpy((void *)(KSEG1 | pa), (void *)va, len);

	return 0;
}

/* Overview:
 *  This function is used to read data from a device physical address.
 *  Remember to check the validity of addresses (same as in 'sys_write_dev').
 *
 * Post-Condition:
 *  Data at 'pa' is copied from device to [va, va+len).
 *  Return 0 on success.
 *  Return -E_INVAL on bad address.
 *
 * Hint: You MUST use 'memcpy' to copy data after checking the validity.
 */
int sys_read_dev(u_int va, u_int pa, u_int len) {
	/* Exercise 5.1: Your code here. (2/2) */
	if (is_illegal_va_range(va, len)) {
		return -E_INVAL;
	}
	
	if (!((va >= 0x10000000 && len <= 0x20) || (va >= 0x13000000 && len <= 0x4200) || (va >= 0x15000000 && len <= 0x200))) {
		return -E_INVAL;
	}

	memcpy((void *)va, (void *)(KSEG1 | pa), len);
	return 0;
}


//================================================================================================================
int syscall_write_dev(void *va, u_int dev, u_int len) {
	/* Exercise 5.2: Your code here. (1/2) */
	return msyscall(SYS_write_dev, va, dev, len);

}

int syscall_read_dev(void *va, u_int dev, u_int len) {
	/* Exercise 5.2: Your code here. (2/2) */
	return msyscall(SYS_read_dev, va, dev, len);
}