#!/bin/bash
echo "==============================================================================================\n
Generating CFG graphs -> PDFs 1- with body and 2- no body Option Selected : $2 - File name : $1 \n
=============================================================================================="

if [ $2 = "1" ];then
opt -dot-cfg $1
dot -Tpdf cfg.main.dot -o main.pdf
#dot -Tpdf cfg.fib.dot -o fib.pdf
#dot -Tpdf cfg.fib2.dot -o fib2.pdf
fi

if [ $2 = "2" ];then
opt -dot-cfg-only $1
dot -Tpdf cfg.main.dot -o main.pdf
#dot -Tpdf cfg.fib.dot -o fib.pdf
#dot -Tpdf cfg.fib2.dot -o fib2.pdf
fi


