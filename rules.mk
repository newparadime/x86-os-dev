%.o: %.S
	$(AS) $< -o $@

