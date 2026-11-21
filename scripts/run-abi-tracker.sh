#!/bin/sh
# Build tagged shared libraries with debug information in an isolated directory.
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
work=${1:-/tmp/sista-abi-analysis-og}
mkdir -p "$work"
work=$(CDPATH= cd -- "$work" && pwd)
for version in 3.0.2 3.0.3 3.1.0; do
    src="$work/src/$version"
    install="$work/installed/$version"
    mkdir -p "$src" "$install/lib" "$install/include"
    git -C "$repo" archive "v$version" | tar -x -C "$src"
    cd "$src"
    files='ansi border coordinates cursor field pawn'
    objects=''
    for file in $files; do
        g++ -std=c++17 -g -Og -fPIC -Iinclude -c "include/sista/$file.cpp" -o "$file.o"
        objects="$objects $file.o"
    done
    g++ -shared -Wl,-soname,libSista.so.3 -o "$install/lib/libSista.so.$version" $objects
    g++ -std=c++17 -g -Og -fPIC -Iinclude -c include/sista/api.cpp -o api.o
    g++ -shared -Wl,-soname,libSista_api.so.3 -o "$install/lib/libSista_api.so.$version" api.o "$install/lib/libSista.so.$version"
    cp -R include/sista "$install/include/"
done
cd "$work"
# ABI Dumper 1.4 still requests the OldC++ parser, removed in newer
# Universal Ctags. Use a local copy with the supported parser only.
if ! ctags --list-languages | grep -Fxq 'OldC++'; then
    dumper=$(command -v abi-dumper)
    mkdir -p "$work/tools"
    if ! grep -Fq '@Langs = ("C++", "OldC++");' "$dumper"; then
        echo "Unsupported abi-dumper: cannot adapt its OldC++ parser selection" >&2
        exit 1
    fi
    sed 's/@Langs = ("C++", "OldC++");/@Langs = ("C++");/' "$dumper" > "$work/tools/abi-dumper"
    chmod +x "$work/tools/abi-dumper"
    PATH="$work/tools:$PATH"
    export PATH
fi
abi-tracker -rebuild -regen-dump "$repo/scripts/abi-tracker.json"
printf '\nReport: %s/timeline/Sista/index.html\n' "$work"
