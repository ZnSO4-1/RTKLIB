param(
    [Parameter(Mandatory = $true)][string]$Baseline,
    [Parameter(Mandatory = $true)][string]$Actual
)

$ErrorActionPreference = "Stop"

function Normalize-Lines {
    param([string]$Path)

    $text = [System.IO.File]::ReadAllText($Path)
    $text = $text -replace "`r`n", "`n"
    $text = $text -replace "\\", "/"
    return $text -split "`n"
}

function Get-DataLines {
    param([string[]]$Lines)

    return @(
        $Lines | Where-Object {
            $line = $_.Trim()
            $line.Length -gt 0 -and -not $line.StartsWith("%")
        }
    )
}

function Compare-Float {
    param(
        [double]$Expected,
        [double]$Actual,
        [double]$Tolerance
    )

    return [Math]::Abs($Expected - $Actual) -le $Tolerance
}

$expectedLines = Normalize-Lines -Path $Baseline
$actualLines = Normalize-Lines -Path $Actual

$expectedData = Get-DataLines -Lines $expectedLines
$actualData = Get-DataLines -Lines $actualLines

if ($expectedData.Count -ne $actualData.Count) {
    throw "data line count mismatch: expected $($expectedData.Count), actual $($actualData.Count)"
}

# Columns:
# week tow lat lon hgt Q ns sdn sde sdu sdne sdeu sdun age ratio
$tolerances = @(0.0, 1E-3, 1E-7, 1E-7, 0.05, 0.0, 0.0, 0.05, 0.05, 0.10, 0.05, 0.05, 0.05, 0.01, 1.0)

for ($i = 0; $i -lt $expectedData.Count; $i++) {
    $expectedCols = [regex]::Split($expectedData[$i].Trim(), "\s+") | Where-Object { $_ -ne "" }
    $actualCols = [regex]::Split($actualData[$i].Trim(), "\s+") | Where-Object { $_ -ne "" }

    if ($expectedCols.Count -ne $actualCols.Count) {
        throw "column count mismatch at data line $($i + 1): expected $($expectedCols.Count), actual $($actualCols.Count)"
    }
    if ($expectedCols.Count -ne $tolerances.Count) {
        throw "unexpected data column count at line $($i + 1): $($expectedCols.Count)"
    }

    for ($j = 0; $j -lt $expectedCols.Count; $j++) {
        if ($tolerances[$j] -eq 0.0) {
            if ($expectedCols[$j] -ne $actualCols[$j]) {
                throw "exact mismatch at data line $($i + 1), column $($j + 1): expected '$($expectedCols[$j])', actual '$($actualCols[$j])'"
            }
            continue
        }

        $expectedValue = [double]::Parse($expectedCols[$j], [System.Globalization.CultureInfo]::InvariantCulture)
        $actualValue = [double]::Parse($actualCols[$j], [System.Globalization.CultureInfo]::InvariantCulture)

        if (-not (Compare-Float -Expected $expectedValue -Actual $actualValue -Tolerance $tolerances[$j])) {
            throw "numeric mismatch at data line $($i + 1), column $($j + 1): expected $expectedValue, actual $actualValue, tolerance $($tolerances[$j])"
        }
    }
}
