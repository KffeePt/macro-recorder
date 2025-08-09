$sourceDir = ".\build"
$destinationZip = ".\MacroApp_Installer.zip"

if (Test-Path $destinationZip) {
    Remove-Item $destinationZip
}

Compress-Archive -Path "$sourceDir\*" -DestinationPath $destinationZip