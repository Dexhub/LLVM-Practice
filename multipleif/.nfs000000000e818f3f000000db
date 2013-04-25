# Commands to perform Profiling and generate Prof.out
#Work in Progress
clang -emit-llvm program.c -c -o program.bc
opt -insert-edge-profiling -f $1 -o $1.prof
#opt -insert-block-profiling -f $1 -o $1.prof
llc $1.prof -o $1.prof.s
gcc $1.prof.s -lrt -L$LLVM_OBJ_DIR/Debug+Asserts/lib/ -lprofile_rt -lm -o $1.prof.exe $LIBS
./$1.prof.exe
echo Instrumented binary is ./$1.prof.exe


#opt -insert-edge-profiling -o program.edge.bc program.bc
#lli -load ~/llvm-workspace/llvm-objects/Debug+Asserts/lib/libprofile_rt.so program.edge.so
#llvm-prof -annotated-llvm program.edge.so
#llc program.edge.bc -o program.edge.S
#gcc -o program.edge.bc program.edge.S ~/llvm-workspace/llvm-objects/Debug+Asserts/lib/libprofile_rt.so
#./program.exe
