[Setup]
AppName=MacroApp
AppVersion=1.0
DefaultDirName={autopf}\MacroApp
DefaultGroupName=MacroApp
OutputBaseFilename=setup
WizardStyle=modern

[Files]
Source: "C:\Users\santi\Documents\Source\c++\macro-app\build\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs

[Icons]
Name: "{group}\MacroApp"; Filename: "{app}\macroapp.exe"
Name: "{group}\Uninstall MacroApp"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\macroapp.exe"; Description: "Launch application"; Flags: nowait postinstall skipifsilent