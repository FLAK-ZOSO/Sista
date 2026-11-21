# ABI Tracker

Install `abi-tracker`, `abi-dumper`, `abi-compliance-checker`, `vtable-dumper`,
Universal Ctags, and optionally `gnuplot`.

```sh
scripts/run-abi-tracker.sh
```

The script builds the tagged releases with `-g -Og` and runs ABI Tracker in
`/tmp/sista-abi-analysis-og`. Pass a different work directory as the first argument if desired.

The HTML timeline is [`timeline/Sista/index.html`](file:///tmp/sista-abi-analysis-og/timeline/Sista/index.html) under that directory.

When Universal Ctags lacks `OldC++`, the script uses a local copy of ABI Dumper configured to use its available C++ parser.
