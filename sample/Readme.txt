>This Pass performs Tail-Duplication

Steps:

Run :

>>>>>>>>sample/prof-script.sh program.bc
-Program.c ->Program.bc that contains Edge profiling - program.bc.prof
-Instrumented binary generated: program.bc
-llvmprof.out


>>>>>>>>>opt -profile-loader -load ~/llvm-liberty-objects/Debug+Asserts/lib/HKTailDuplication.so -HKtaildupl -debug program.bc -o prog.tail.bc

>>>>>>>>>>opt -dot-cfg-only file_name(prog.tail.bc)
dot -Tpdf cfg.main.dot -o main.pdf




