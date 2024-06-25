#!/bin/bash

for asm_file in ./asm/nasm/*.asm; do
    sed -i '/align=/d' "$asm_file"
    sed -i '/execute/d' "$asm_file"
    sed -i '/noexecute/d' "$asm_file"
    sed -i '/default rel/d' "$asm_file"
    sed -i 's/: function//g' "$asm_file"
done

