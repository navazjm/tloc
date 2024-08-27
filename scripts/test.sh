#!/bin/bash

mkdir -p build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

# Needed for neovim clangd lsp
# Remove existing symlink if it exists
[ -L ../compile_commands.json ] && rm ../compile_commands.json
# Create symlink for neovim lspconfig clangd
ln -s build/compile_commands.json ../compile_commands.json

make tloc_test
cd ..
./build/tloc_test
