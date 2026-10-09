param(
    [Parameter(Mandatory = $true)][string]$Man3Dir,
    [Parameter(Mandatory = $true)][string]$Specs
)

$ErrorActionPreference = 'Stop'

foreach ($spec in ($Specs -split '\s+')) {
    if (-not $spec) { continue }
    $parts = $spec -split '=', 2
    if ($parts.Count -ne 2 -or -not $parts[0] -or -not $parts[1]) {
        throw "Invalid man-page alias specification: $spec"
    }

    $source = Join-Path $Man3Dir $parts[1]
    $destination = Join-Path $Man3Dir ($parts[0] + '.3')
    try {
        Copy-Item -LiteralPath $source -Destination $destination -Force -ErrorAction Stop
    } catch {
        throw "Could not install man-page alias $($parts[0]) from $($parts[1]): $_"
    }
}
