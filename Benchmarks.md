# Benchmark results for the current version of the library

The following benchmarks were run on...

- HP ProBook 430 G8 Notebook PC
- Intel Core `i5-1135G7` CPU `2.40GHz`
- `8GB` RAM
- Windows 11 Pro `22H2`
- 64-bit OS, x64-based processor

## v`0.1.0`

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50 x 50` = `2500` iterations
- `1` `Pawn` instance
- `20 milliseconds` per frame (`50 FPS`)

...and the following numeric results were obtained...

- `1'30"` (90 seconds) elapsed time
- `2500 x 0.020` = `50"` slept time
- `2500 x 2500 / 90` = `27778` cells per second
- sista.exe max memory usage: `0.3MBytes`
- sista.exe max CPU usage: `0.1%`

...along with the following qualitative results...

- The refresh is smooth
- Almost no blinking or flickering
- `Pawn` movement is snappy
