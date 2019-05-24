%.o: %.c
	$(TARGET)-$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.cxx
	$(TARGET)-$(CXX) $(CXXFLAGS) -c $< -o $@
