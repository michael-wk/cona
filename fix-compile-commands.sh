#!/bin/bash
# fix-compile-commands.sh
sed -E \
  -e 's/[Cc]:\\\\/\/mnt\/c\//g' \
  -e 's/[Cc]:\//\/mnt\/c\//g' \
  -e 's/\\\\/\//g' \
  build/compile_commands.json > compile_commands.json
