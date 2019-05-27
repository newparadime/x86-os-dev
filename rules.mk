%.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

