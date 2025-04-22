$OutputFile = "all_sources.txt"
$IgnoredDirs = @("build", ".git", ".cache")

# Clear or create the output file
"" | Out-File -Encoding UTF8 $OutputFile

# Get all files recursively
Get-ChildItem -Recurse -File -Include *.cpp, *.h, CMakeLists.txt | Where-Object {
    $exclude = $false
    foreach ($dir in $IgnoredDirs) {
        if ($_.FullName -match [regex]::Escape("\$dir\")) {
            $exclude = $true
            break
        }
    }
    return -not $exclude
} | ForEach-Object {
    "// $($_.FullName)" | Out-File -Append -Encoding UTF8 $OutputFile
    Get-Content $_.FullName | Out-File -Append -Encoding UTF8 $OutputFile
    "" | Out-File -Append -Encoding UTF8 $OutputFile
    "// ----------------------------------------" | Out-File -Append -Encoding UTF8 $OutputFile
    "" | Out-File -Append -Encoding UTF8 $OutputFile
}

Write-Host "✅ Done! Output written to $OutputFile"
