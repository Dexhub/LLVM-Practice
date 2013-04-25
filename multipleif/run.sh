rm -r temp_files
rm -r pdf
mkdir temp_files
mkdir pdf

clang -emit-llvm program.c -c -o ./temp_files/program.bc
cd temp_files
opt -insert-edge-profiling -f program.bc -o program.prof
#opt -insert-block-profiling -f $1 -o $1.prof
llc program.prof -o program.s
gcc program.s -lrt -L$LLVM_OBJ_DIR/Debug+Asserts/lib/ -lprofile_rt -lm -o program.exe $LIBS
./program.exe
echo Instrumented binary is ./$1.prof.exe

opt -profile-loader -load ~/llvm-liberty-objects/Debug+Asserts/lib/HKTailDuplication.so -HKtaildupl -debug program.bc -o prog.tail.bc

opt -dot-cfg-only program.bc

cd ..
dir=$(basename `pwd`)
echo \n\n\n-------Value of DIR is $dir
cd temp_files
dot -Tpdf cfg.main.dot -o ../pdf/$dir-program_main.pdf

opt -dot-cfg-only prog.tail.bc
dot -Tpdf cfg.main.dot -o ../pdf/$dir-tail_main.pdf


