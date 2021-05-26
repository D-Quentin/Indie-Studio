del bomberman.exe
rmdir "_build/Debug"
mkdir _build
cmake -H. -B_build
cd _build
cmake --build .
cd ..
@REM copy "Debug\bomberman.exe" "_build\Debug\bomberman.exe"
@REM copy "Debug\bomberman.pdb" "_build\Debug\bomberman.pdb"
@REM del "Debug\bomberman.exe"
@REM del "Debug\bomberman.pdb"
@REM rmdir "Debug"
copy "_build\Debug\bomberman.exe" "."