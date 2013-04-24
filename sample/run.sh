if [ $1 = "d" ];then
opt -profile-loader -load ~/llvm-liberty-objects/Debug+Asserts/lib/HKTailDuplication.so -HKtaildupl -debug program.bc -o prog.tail.bc
fi
if [ $1 = "n" ];then
opt -profile-loader -load ~/llvm-liberty-objects/Debug+Asserts/lib/HKTailDuplication.so -HKtaildupl program.bc -o prog.tail.bc
fi



