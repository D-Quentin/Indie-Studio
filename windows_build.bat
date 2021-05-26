del bomberman.exe
rmdir "_build/Debug"
mkdir _build
cmake -H. -B_build
cd _build
cmake --build .
cd ..
copy "Debug\bomberman.exe" "_build\Debug\bomberman.exe"
copy "Debug\bomberman.pdb" "_build\Debug\bomberman.pdb"
del "Debug\bomberman.exe"
del "Debug\bomberman.pdb"
rmdir "Debug"
copy "_build\Debug\bomberman.exe" "."