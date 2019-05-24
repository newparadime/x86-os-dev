%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@
