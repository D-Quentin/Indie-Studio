rm -f bomberman.exe
rm -rf _build/Debug
mkdir _build
cmake -H. -B_build
cd _build
cmake --build .
cd ..
mv Debug _build
cp _build/Debug/bomberman.exe .