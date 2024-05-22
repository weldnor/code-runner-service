cmake -S . -B ./build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE
cmake --build ./build --config Release -j8
