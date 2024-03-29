# Benchmark results for the current version of the library

The following benchmarks were run on...

- HP ProBook 430 G8 Notebook PC
- Intel Core `i5-1135G7` CPU `2.40GHz`
- `8GB` RAM
- Windows 11 Pro `22H2`
- 64-bit OS, x64-based processor

From version `1.0.0` the benchmarks were run on...

- Acer Aspire E5-573G
- Intel core `i7-5500U` CPU `3.00GHz`
- `8GB` RAM
- Ubuntu 22.04.3 LTS x86_64

## v`0.1.0`

### `sista.exe` I - 7/12/2022

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50 x 50` = `2500` iterations
- `1` `Pawn` instance
- `20 milliseconds` per frame (`50 FPS`)

...and the following numeric results were obtained...

- `1'30"` (90 seconds) elapsed time
- `2500 x 0.020` = `50"` slept time
- `2500 x 2500 / 90` = `69444` cells per second
- sista.exe max memory usage: `0.3MBytes`
- sista.exe max CPU usage: `0.9%`

...along with the following qualitative results...

- The refresh is smooth
- Almost no blinking or flickering
- `Pawn` movement is snappy

### `sista.exe` II - 8/12/2022

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50 x 50 / 2` = `1250` iterations
- `2` `Pawn` instances
- `20 milliseconds` per frame (`50 FPS`)

...and the following numeric results were obtained...

- `39"` (39 seconds) elapsed time
- `1250 x 0.020` = `25"` slept time
- `2500 x 1250 / 90` = `34722` cells per second
- sista.exe max memory usage: `0.4MBytes`
- sista.exe max CPU usage: `1.4%`

...along with the following qualitative results...

- The refresh is smooth
- Almost no blinking or flickering
- `Pawn`s movement is snappy

## v`0.4.0`

### `sista.exe` III - 25/12/2022

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50 x 50` = `2500` iterations
- `2` `Pawn` instances (allocated on heap with `new`)
- `20 milliseconds` per frame (`50 FPS`)

...and the following numeric results were obtained...

- `1'22"` (82 seconds) elapsed time
- `2500 x 0.020` = `50"` slept time
- `2500 x 2500 / 82` = `60976` cells per second
- sista.exe max memory usage: `0.5MBytes`
- sista.exe max CPU usage: `0%` (according to Task Manager)

...along with the following qualitative results...

- The refresh is smooth
- Almost no blinking or flickering
- Some `Pawn`s movement is snappy

## v`0.5.0`

### `sista.exe` IV - 27/12/2022

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50 x 50` = `2500` iterations
- `6` `Pawn` instances (allocated on heap with `new`)
- `10 milliseconds` per frame (`100 FPS`)

...and the following numeric results were obtained...

- `39"` (39 seconds) elapsed time
- `2500 x 0.010` = `25"` slept time
- `2500 x 2500 / 39` = `102564` cells per second
- sista.exe max memory usage: `0.5MBytes`
- sista.exe max CPU usage: `0%` (according to Task Manager)

...along with the following qualitative results...

- The refresh is smooth (actually there's no refresh)
- No flickering at all (there's no more refresh)
- Some `Pawn`s movement is snappy (mostly due to the `10ms` frame time)

## v`0.7.0`

### `sista.exe` V -  18/02/2023

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `1000` = `1000` iterations
- `6` `Pawn` instances (allocated on heap with `new`)
- `10 milliseconds` per frame (`100 FPS`)

...and the following numeric results were obtained...

- `11"` (11 seconds) elapsed time
- `1000 x 0.010` = `10"` slept time
- `1000 x 2500 / 11` = `227272` cells per second
- sista.exe max memory usage: `0.5MBytes`
- sista.exe max CPU usage: `0%` (according to Task Manager)

...along with the following qualitative results...

- The refresh is smooth (actually there's no refresh)
- No flickering at all (there's no more refresh)
- Not a single `Pawn` movement is snappy (due to the fact that they're at the same x coordinate)

## v`1.0.0`

### [`header-test`](https://github.com/FLAK-ZOSO/Sista/blob/main/demo/header-test.cpp) - 21/12/2023

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `50` `Pawn` instances (allocated on heap with `new`)
- `10 milliseconds` per frame (`100 FPS`)
- `1000` = `1000` iterations

...and the following numeric results were obtained...

- `11"` (11 seconds) elapsed time
- `1000 x 0.010` = `10"` slept time
- `1000 x 2500 / 11` = `227272` cells per second
- `header-test` max memory usage: `131KBytes`
- `header-test` max CPU usage: `2.17%` (according to System Monitor)

### `sista` VI - 21/12/2023

The following test was run with...

- `50 x 50` Field size (`2500` cells)
- `6` `Pawn` instances (allocated on heap with `new`)
- `10 milliseconds` per frame (`100 FPS`)
- `1000` = `1000` iterations

...and the following numeric results were obtained...

- `11"` (11 seconds) elapsed time
- `1000 x 0.010` = `10"` slept time
- `1000 x 2500 / 11` = `227272` cells per second
- `sista` max memory usage: `262KBytes`
- `sista` max CPU usage: `0.26%` (according to System Monitor)
