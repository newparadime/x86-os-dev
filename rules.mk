%.o: %.S
	$(TARGET)-as $< -o $@

